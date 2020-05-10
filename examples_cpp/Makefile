CC             = g++
CFLAGS         = -Wall -g -O2 -std=c++14

all: simple

simple: ../ringbuffer.cpp simple.cpp
	$(CC) $(CFLAGS) -o simple simple.cpp ../ringbuffer.cpp

clean:
	rm -f simple
