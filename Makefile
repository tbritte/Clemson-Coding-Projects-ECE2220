CC = gcc
INCLUDE = -I.
CFLAGS = -g -Wall
LDFLAGS = -L. -L/usr/lib
LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

all: p1

main: p1.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run:
	./p1

clean:
	rm -f *.o
	rm -f program
