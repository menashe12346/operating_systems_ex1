CC = gcc
#for gcov, helps identifying untested parts of the code
CFLAGS = -Wall -fprofile-arcs -ftest-coverage 

all: dijkstra

dijkstra: dijkstra.c
	$(CC) $(CFLAGS) -o dijkstra dijkstra.c

clean:
	rm -f dijkstra *.gcno *.gcda *.gcov

coverage: dijkstra # ensures that dijkstra is built before running the coverage analysis
# simulate the program's execution with a specific set of inputs
	./dijkstra < input.txt 
#generate a report
	gcov dijkstra.c