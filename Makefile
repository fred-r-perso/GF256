CC=gcc
AR=ar
CFLAGS=-Wall
LDFLAGS=
EXEC=testgf256
LIB=libgf256.a
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
TESTSUITE_SOURCE := test.c
LIB_SRC=$(filter-out $(TESTSUITE_SOURCE),$(wildcard *.c))
LIB_OBJ=$(LIB_SRC:.c=.o)

all : $(EXEC) $(LIB)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIB): $(LIB_OBJ)
	$(AR) rcs $(LIB) $(LIB_OBJ)

gf256.o : gf256.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
	rm -rf ${LIB}	