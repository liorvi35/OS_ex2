CC = gcc
FLAGS = -Wall -g
SHARED = --shared -fPIC
LIBS = libcodecA.so libcodecB.so
TARGETS = cmp copy # $(LIBS) encode decode

.PHONY: all clean

all: $(TARGETS)

cmp: cmp.c
	$(CC) $(FLAGS) -o $@ $^

copy: copy.c
	$(CC) $(FLAGS) -o $@ $^

# encode: encode.c $(LIBS)
# 	$(CC) $(FLAGS) -o $@ $^

# decode: decode.c $(LIBS)
# 	$(CC) $(FLAGS) -o $@ $^

# libcodecA.so: codecA.c
# 	$(CC) $(FLAGS) $(SHARED) -c $@ $^ 

# libcodecB.so: codecB.c
# 	$(CC) $(FLAGS) $(SHARED) -c $@ $^

clean:
	rm -f $(TARGETS) *.o