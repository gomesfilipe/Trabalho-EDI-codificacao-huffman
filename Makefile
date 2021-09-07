comp:
	gcc src/*.c client/main.c -o tp2

run:
	valgrind ./tp2
	