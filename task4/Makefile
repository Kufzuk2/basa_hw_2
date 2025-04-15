all: 
	g++ -c std_sort.cpp -o std_sort.o
	gcc -c radix_sort.c -o radix_sort.o
	gcc -c main.c -o main.o
	g++ radix_sort.o std_sort.o main.o -o radix
	./radix
