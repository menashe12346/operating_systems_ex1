all: max_sub_array

# -pg for gprof
max_sub_array: max_sub_array.c
	gcc -o max_sub_array max_sub_array.c -pg

clean:
	rm -f max_sub_array gmon.out
