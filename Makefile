NAME = myserver

CFLAGS = -Wall -Wextra -g

SRCS = $(wildcard *.c)

all:	$(NAME)

$(NAME):	$(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "myserver is ready to go online"

clean:
	rm -f $(NAME) $(NAME).dSYM
	@echo "myserver is cleansed"

t: all
	./$(NAME)

re: clean all

.PHONY: all clean re


