CFLAGS = -g -Wall -Wno-unused-variable
OBJECTS = permissionbits.o

CC = gcc

all:clean sfind

sfind: sfind.o sfindFunction.h
	$(CC) $(CFLAGS) sfindFunction.c $@.o -o $@

# generic
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f mynewls
	rm -f myls
	rm -f core *.o a.out
	rm -f DIRECTORY.html
	rm -rf *.dSYM
	rm -f sfind
webclean:
	rm -f DIRECTORY.html
