CXXFLAGS=-std=c++1z -DASIO_STANDALONE
COMPILE=g++ $(CXXFLAGS) -I ../asio-1.10.6/include

all: hello echo

hello: hello.cpp
	$(COMPILE) -o $@ $^

echo: echo.cpp
	$(COMPILE) -pthread -o $@ $^
