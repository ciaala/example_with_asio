#include "connection.h"
#include <asio.hpp>
#include <iostream>
#include <future>
#include <signal.h>
#include <thread>
#include <vector>

struct server
  {
  server(asio::io_service & service)
    : m_acceptor{service,
                 asio::ip::tcp::endpoint{
                   asio::ip::tcp::v4(),
                   4321}}
    , m_sock{service} {
    }

    void start() {
      do_accept();
    }

  private:
    void do_accept() {
      m_acceptor.async_accept(m_sock, [&](auto error){
        if(!error) {
          auto conn = std::make_shared<connection>(std::move(m_sock));
          conn->start();

          do_accept();
        }
      });
    }

    asio::ip::tcp::acceptor m_acceptor;
    asio::ip::tcp::socket m_sock;
  };

int main() {
  auto && service = asio::io_service{};
  auto && server = ::server{service};

  server.start();

  auto && signals = asio::signal_set(service, SIGINT);
  signals.add(SIGINT);
  signals.async_wait([&](auto error, auto signal){
    if(!error && !service.stopped()) {
      std::cout << "Received SIGINT. Terminating. " << '\n';
      service.stop();
    }
  });

  auto const cpus = std::thread::hardware_concurrency();
  auto pool = std::vector<std::future<void>>{cpus};

  for(auto & future : pool)
    {
    future = std::async(std::launch::async, [&]{
      service.run();
    });
    }
  }
