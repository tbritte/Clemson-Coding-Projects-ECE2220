CC = gcc
INCLUDE = -I.
CFLAGS = -g -Wall
LDFLAGS = -L. -L/usr/lib
LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

all: p4

main: p4.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run:
	./p4

clean:
	rm -f *.o
	rm -f program
