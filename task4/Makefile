all:
	gcc gen_arr.c -o build/gen_arr
	./build/gen_arr
	gcc rad_sort.c -o build/rad_sort
	./build/rad_sort
	g++ -std=c++11 -O3 std_sort.cpp -o build/std_sort
	./build/std_sort
	python3 text_data/draw_graphs.py
