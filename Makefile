CFLAGS := -g -O3 -std=c11
WARNINGS := -Wall -Winline -Wno-deprecated
INCLUDE := -Ilib -Iexternlibs
LIBRARIES := -lm -lglfw -framework OpenGL

all: matcap spirograph waves transform tests

matcap: programs/matcap.c
	clang -o executeable/matcap programs/matcap.c \
	$(INCLUDE) $(LIBRARIES) $(WARNINGS) $(CFLAGS)
spirograph: programs/spirograph.c
	clang -o executeable/spirograph programs/spirograph.c \
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
runspirograph:
	executable/spirograph

runtests:
	testing/tests
