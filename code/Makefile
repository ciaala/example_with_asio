CXXFLAGS=-std=c++1z -DASIO_STANDALONE
COMPILE=g++ $(CXXFLAGS)

all: hello echo

hello: hello.cpp
	$(COMPILE) -o $@ $^

echo: echo.cpp
	$(COMPILE) -pthread -o $@ $^
