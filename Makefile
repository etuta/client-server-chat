CFLAGS=-g -Wall -o -pedantic

.PHONY: all
all: chat-server chat-client

chat-server: chat-server.c
	gcc -pthread $(CFLAGS) -o $@ $^

chat-client: chat-client.c
	gcc -pthread $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f chat-server chat-client
