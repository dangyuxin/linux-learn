CFLAGS=-pthread -g -Wall

all:mysem

mysem:main.o mysem.o
	gcc $^ -o $@ $(CFLAGS)

clean:
	rm -rf *.o
