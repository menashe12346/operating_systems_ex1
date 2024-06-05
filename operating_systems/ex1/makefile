all: stack_overflow_no_debug stack_overflow_with_debug divide_by_zero_no_debug divide_by_zero_with_debug invalid_memory_no_debug invalid_memory_with_debug

stack_overflow_no_debug: stack_overflow.c
	gcc -o stack_overflow_no_debug stack_overflow.c

divide_by_zero_no_debug: divide_by_zero.c
	gcc -o divide_by_zero_no_debug divide_by_zero.c

invalid_memory_no_debug: invalid_memory.c
	gcc -o invalid_memory_no_debug invalid_memory.c

stack_overflow_with_debug: stack_overflow.c
	gcc -g -o stack_overflow_with_debug stack_overflow.c

divide_by_zero_with_debug: divide_by_zero.c
	gcc -g -o divide_by_zero_with_debug divide_by_zero.c

invalid_memory_with_debug: invalid_memory.c
	gcc -g -o invalid_memory_with_debug invalid_memory.c

clean: 
	rm -f stack_overflow_no_debug divide_by_zero_no_debug invalid_memory_no_debug stack_overflow_with_debug divide_by_zero_with_debug invalid_memory_with_debug core