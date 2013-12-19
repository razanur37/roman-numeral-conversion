all: int_to_roman.o roman_to_int.o roman.o

int_to_roman.o: int_to_roman.c
	gcc int_to_roman.c -o int_to_roman.o

roman_to_int.o: roman_to_int.c
	gcc roman_to_int.c -o roman_to_int.o

roman.o: roman.c
	gcc roman.c -o roman.o

clean:
	rm *.o