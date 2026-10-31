
# Find all C source files
src := $(wildcard *.c)

# Convert .c files into .o files
obj := $(patsubst %.c,%.o,$(src))

# Default target
a.out: $(obj)
	gcc -o $@ $^

# Compile each C file into an object file
%.o: %.c
	gcc -c $< -o $@

# Remove object files and executable
clean:
	rm -f $(obj) a.out

.PHONY: clean



# do all file compilation


# Variable	   Meaning	                 Example
# $@	         Target filename	           main.o
# $<	         First prerequisite          main.c
# $^	         All prerequisites	         main.c header.h
# $*	         Stem matched by %           main