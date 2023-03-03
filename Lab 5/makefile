CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = driver.c functions.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: LAB5

LAB5: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c functions.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) LAB5