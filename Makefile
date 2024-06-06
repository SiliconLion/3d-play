CFLAGS := -g -std=c11 -O3
WARNINGS := -Wall -Winline -Wno-deprecated
INCLUDE := -Ilib -Iexternlibs
LIBRARIES := -lm -lglfw -framework OpenGL

all: matcap randomwalker waves transform tests

matcap: programs/matcap.c
	clang -o executeable/matcap programs/matcap.c \
	$(INCLUDE) $(LIBRARIES) $(WARNINGS) $(CFLAGS)
randomwalker: programs/random-walker.c
	clang -o executeable/randomwalker programs/random-walker.c \
	$(INCLUDE) $(LIBRARIES) $(WARNINGS) $(CFLAGS)
waves: programs/waves.c
	clang -o executeable/waves programs/waves.c \
	$(INCLUDE) $(LIBRARIES) $(WARNINGS) $(CFLAGS)
transform: programs/transform.c
	clang -o executeable/transform programs/transform.c \
	$(INCLUDE) $(LIBRARIES) $(WARNINGS) $(CFLAGS)
tests: testing/tests.c
	clang -o testing/tests testing/tests.c \
	$(INCLUDE) $(LIBRARIES) $(WARNINGS) $(CFLAGS)

clean:
	rm -rf executeable/*
	echo clean done

runmatcap:
	executeable/matcap
runwaves:
	executeable/waves
runtransform:
	executeable/transform
runrandomwalker:
	executable/randomwalker

runtests:
	testing/tests
