CC = gcc
INCLUDE = -I.
CFLAGS = -g -Wall
LDFLAGS = -L. -L/usr/lib
LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

all: p3

main: p3.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run:
	./p3

clean:
	rm -f *.o
	rm -f program
