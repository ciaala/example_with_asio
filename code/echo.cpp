#include "connection.h"
#include <asio.hpp>
#include <iostream>
#include <future>
#include <signal.h>
#include <thread>
#include <vector>
#include <string>

struct server {
    // Constructor
    server(asio::io_service &service)
            : m_acceptor{service,
                         asio::ip::tcp::endpoint{
                                 asio::ip::tcp::v4(),
                                 4321}}, server_socket{service} {
    }

    void start() {
        do_accept();
    }

private:
    void do_accept() {
        m_acceptor.async_accept(server_socket, [&](auto error) {
            if (!error) {
                auto conn = std::make_shared<connection>(std::move(server_socket), connections);
                std::cout << "New connection accepted." << std::endl;
                connections.push_back(conn);

                conn->start();

                do_accept();
            }
        });
    }

    std::vector<std::shared_ptr<connection>> connections;
    asio::ip::tcp::acceptor m_acceptor;
    asio::ip::tcp::socket server_socket;
};

void test_message() {
    std::string str = "test";
    std::vector<std::string> vectors;
    vectors.push_back(std::move(str));

    std::cout << "No nullptr '" << str << "'" << std::endl;

}

int main(int argc, char **argv) {

    // test_message();

    auto &&service = asio::io_service{};
    auto &&server = ::server{service};

    server.start();

    auto &&signals = asio::signal_set(service, SIGINT);
    signals.add(SIGINT);
    signals.async_wait([&](auto error, auto signal) {
        if (!error && !service.stopped()) {
            std::cout << "Received SIGINT. Terminating. " << '\n';
            service.stop();
        }
    });

    auto const cpus = std::thread::hardware_concurrency();
    auto pool = std::vector<std::future<void>>{cpus};

    for (auto &future : pool) {
        future = std::async(std::launch::async, [&] {
            service.run();
        });
    }
}
