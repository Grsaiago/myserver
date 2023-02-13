SERVER_NAME = server 
CLIENT_NAME = client

CFLAGS = -Wall -Wextra -g

SERVER_SRCS = $(wildcard server_*.c)
CLIENT_SRCS = $(wildcard client_*.c)

all:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME):	$(SERVER_SRCS)
	@$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER_NAME)
	@echo "Server ready to go online"

$(CLIENT_NAME): $(CLIENT_SRCS)
	@$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT_NAME)
	@echo "Client ready to go online"

clean:
	@rm -rf $(SERVER_NAME) $(SERVER_NAME).dSYM $(CLIENT_NAME) $(CLIENT_NAME).dSYM
	@echo "Myserver no longer available"

t: all
	./$(SERVER_NAME)

re: clean all

.PHONY: all clean re


