CC = gcc
CFLAGS = -Wall

build: p.c bmp_header.h
	$(CC) $(CFLAGS) p.c -o p

p: p.c bmp_header.h
	$(CC) $(CFLAGS) p.c -o p

run: p
	./p

.PHONY: clean
clean:
	rm -rf *.o p
