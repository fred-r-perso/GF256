CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=testgf256
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

gf256.o : gf256.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)	