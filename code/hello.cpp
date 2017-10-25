#include <asio.hpp>
#include <chrono>
#include <iostream>

int main() {
  auto && service = asio::io_service{};
  auto && timer = asio::steady_timer{service};

  timer.expires_from_now(std::chrono::seconds{1});
  timer.async_wait([](auto error){
    std::cout << "timer fired!\n";
  });

  service.run();
}
