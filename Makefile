out: main.c
	clang -o out main.c -std=c11 -lglfw -framework OpenGL -Wall -O3
clean:
	rm out
all:
	make clean
	make
	./out