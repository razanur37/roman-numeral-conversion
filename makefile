all: roman.o

roman.o: roman.c
	gcc roman.c -o roman

clean:
	rm *.o
