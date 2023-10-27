#Niculici Mihai-Daniel 315 CA
# compiler setup
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# define targets
TARGETS = simple_queries

build: $(TARGETS)

simple_queries: simple_queries.c
	$(CC) $(CFLAGS) simple_queries.c -o simple_queries

pack:
	zip -FSr 315CA_NiculiciMihai-Daniel_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean