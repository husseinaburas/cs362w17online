OBJDIR=obj
MKDIR_P = mkdir -p

.PHONY: directories

all: directories random_testing

random_testing: testme.o randomstring.o
	cc -o random_testing obj/testme.o obj/randomstring.o

testme.o: src/testme.c
	cc -c src/testme.c -o obj/testme.o

randomstring.o: src/randomstring.c
	cc -c src/randomstring.c -o obj/randomstring.o

directories: ${OBJDIR}

${OBJDIR}:
	${MKDIR_P} ${OBJDIR}

clean:
	rm obj/*.o
	rm -r obj/
	rm random_testing

$
