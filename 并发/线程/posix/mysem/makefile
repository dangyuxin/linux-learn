CFLAGS=-pthread -g -Wall

mysem:main.o mysem.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o
