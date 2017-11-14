#include <iostream>
#include <functional>
#include <memory>
#include <string>


class Socket
{
    public:
        std::string name{""};
        Socket() {}
        ~Socket() {}
        Socket(Socket& o) : name{o.name} {
            std::cout << "Socket copy constructor -> o.name " << o.name << std::endl;
            // name = o.name;
        }
        Socket(Socket&& o) noexcept : name(std::move(o.name)) {}
        void printNameAddress(std::string label) {
            std::cout << label << " ->  name data " << name.data() << std::endl;
        }
};

class Connection
{
    public:
        // Connection(Socket socket) : socket{socket} {}
        Connection(Socket socket) : socket{std::move(socket)} {
            socket.printNameAddress("Connection constructor");
            // this->socket = std::move(socket);
        }
        Socket socket;
};

class Acceptor
{
    public:
        void accept(Socket socket, const std::function <void (int)> & f) {
            std::cout << "accept -> counter " << counter << std::endl;
            f(counter--);
        }
    private:
        int counter{2};
};

class Server
{
    public:
        Server() {socket.name = "I am a socket";}
        void start() {
            do_accept();
        }
    private:
        void do_accept() {
            acceptor.accept(socket, [&](auto status) {
                std::cout << "do_accept -> status " << status << std::endl;
                if (status) {
                    socket.printNameAddress("socket pre move");
                    auto conn = std::make_shared<Connection>(std::move(socket));
                    socket.printNameAddress("socket post move");
                    conn->socket.printNameAddress("conn");
                    // std::cout << "do_accept -> socket name " << socket.name << std::endl;
                    do_accept();
                    std::cout << "do_accept -> conn address: " << &conn << std::endl;
                }
            });
        }
        Acceptor acceptor;
        Socket socket;
};

int main() {
    Server server;
    server.start();
}
