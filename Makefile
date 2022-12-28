CC = gcc
INCLUDE = -I.
CFLAGS = -g -Wall
LDFLAGS = -L. -L/usr/lib
LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

all: p5

main: p5.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run:
	./p5

clean:
	rm -f *.o
	rm -f program

