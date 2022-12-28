CC = gcc
INCLUDE = -I.
CFLAGS = -g -Wall
LDFLAGS = -L. -L/usr/lib
LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

all: program7

program7: program7.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

test: test.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run:
	./program7

clean:
	rm -f *.o
	rm -f program
