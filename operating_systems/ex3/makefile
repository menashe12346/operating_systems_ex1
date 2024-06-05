cc = gcc
FLAG = -Wall -g

all:libclasspoisson.so main

poisson.o: poisson.c poisson.h
	$(cc) $(FLAG) -fPIC -c $< -lm

libclasspoisson.so: poisson.o poisson.o
	$(cc) -shared -o $@ $^ -lm

# MAIN
main.o: main.c poisson.h

main: main.o libclasspoisson.so
	$(cc) $(FLAG) -o $@ $< ./libclasspoisson.so -lm

clean:
	rm -f *.so *.o *.a main