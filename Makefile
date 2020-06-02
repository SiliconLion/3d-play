out: main.c
	clang -o out main.c -std=c11 -lglfw -framework OpenGL -Wall -g
clean:
	rm out
all:
	make clean
	make
	./out