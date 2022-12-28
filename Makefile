CC = gcc
INCLUDE = -I.
CFLAGS = -g -Wall
LDFLAGS = -L. -L/usr/lib
LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

all: p2

main: p2.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run:
	./p2

clean:
	rm -f *.o
	rm -f program
