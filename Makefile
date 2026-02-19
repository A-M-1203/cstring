all: clean cstring.out

cstring.out: cstring.o
	cc $^ -o $@

cstring.o: cstring.c
	cc -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.so *.out
