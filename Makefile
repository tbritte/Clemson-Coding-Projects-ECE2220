CC = gcc
INCLUDE = -I.
CFLAGS = -g -Wall
LDFLAGS = -L. -L/usr/lib
LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

all: prog6

program6: prog6.o bmp.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run:
	./prog6

clean:
	rm -f *.o
	rm -f program
