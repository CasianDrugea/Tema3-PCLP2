.PHONY: all clean run build

all: checker

build: checker

run: checker
	./checker

%.o: %.asm
	nasm -f elf $< -o $@

%.o: %.c
	gcc -c -g -m32 $< -o $@

%.o: utils/%.c
	gcc -c -g -m32 $< -o $@

checker: composite_palindrome.o checker_composite_palindrome.o utils.o
	gcc -no-pie -m32 -g $^ -o $@

clean:
	rm -f checker *.o out/*.out 

