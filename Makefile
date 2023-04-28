CC = gcc
FLAGS = -Wall -g
TARGETS = cmp copy libcodecA.so libcodecB.so encode decode stshell

.PHONY: all clean

all: $(TARGETS)

stshell: stshell.c stshell.h 
	$(CC) $(FLAGS) -c $^
	$(CC) $(FLAGS) -o $@ $@.o

cmp: cmp.c
	$(CC) $(FLAGS) -o $@ $^

copy: copy.c
	$(CC) $(FLAGS) -o $@ $^

encode: encode.c
	$(CC) $(FLAGS) -o $@ $^

decode: decode.c
	$(CC) $(FLAGS) -o $@ $^

libcodecA.so: codecA.c
	$(CC) $(FLAGS) -fPIC -c $^
	gcc -shared -o $@ codecA.o

libcodecB.so: codecB.c
	$(CC) $(FLAGS) -fPIC -c $^
	gcc -shared -o $@ codecB.o

clean:
	rm -f *.o *.h.gch $(TARGETS) 
