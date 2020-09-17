matcap: programs/matcap.c
	clang -o executeable/matcap programs/matcap.c -std=c11 -Ilib -Iexternlibs -lglfw -framework OpenGL -Wall -O3
waves: programs/waves.c
	clang -o executeable/waves programs/waves.c -std=c11 -Ilib -Iexternlibs -lglfw -framework OpenGL -Wall -O3
tests: testing/tests.c
	clang -o testing/tests testing/tests.c -std=c11 -Ilib -Iexternlibs -Itesting -Wall -O3

runmatcap:
	executeable/matcap
runwaves:
	executeable/waves
runtests:
	testing/tests