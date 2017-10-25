#ifndef CONNECTION_H
#define CONNECTION_H

#include <asio.hpp>
#include <array>
#include <memory>
#include <utility>
#include <queue>
#include <string>
#include <iostream>

struct connection
  : std::enable_shared_from_this<connection> {
  connection(asio::ip::tcp::socket sock)
    : m_sock{std::move(sock)}
    , m_strand{m_sock.get_io_service()} {

  }

  void start() {
    do_read();
  }

  private:
    void write(std::string data) {
      m_out.push_back(data);

      if(m_out.size() < 2) {
        do_write();
      }
    }

    void do_read() {
      m_sock.async_read_some(asio::buffer(m_buff),
        [&, self = shared_from_this()](auto error, auto read) {
        if(!error) {
          auto begin = m_buff.data();
          auto end = begin + read;
          m_strand.post([&, data=std::string{begin, end}]{
            write(data);
          });
        do_read();
        }
      });
    }

    void do_write() {
      asio::async_write(m_sock, asio::buffer(m_out.front()),
        m_strand.wrap([&, self = shared_from_this()](auto error, auto written) {
        m_out.pop_front();

        if(!error) {
          if(!m_out.empty()) {
            do_write();
          }
        }
      }));
    }

    asio::ip::tcp::socket m_sock;
    asio::strand m_strand;
    std::array<char, 1024> m_buff{};
    std::deque<std::string> m_out{};
  };

#endif
