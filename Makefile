out: main.c
	clang -o out main.c -std=c11 -lglfw -framework OpenGL -Wall -g -O3
clean:
	rm out
all:
	make clean
	make
	./out