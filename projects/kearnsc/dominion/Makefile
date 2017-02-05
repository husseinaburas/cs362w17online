#----------------------------------------------------------------------------------
# CS362-400-W17	Project 3 makefile		5 Feb 2017
# Chris Kearns		kearnsc@oregonstate.edu
# "make unittestresults.out" will compile and run all tests indicated and write
#	detailed gcov coverage data to a file named "unittestresults.out".
# "make all" will compile as indicated without gcov or executing any programs.
# "make clean" will delete EVERYTHING but the source code files.
#---------------------------------------------------------------------------------

CFLAGS = -Wall -fpic -coverage -lm
CFLAGS2 = -Wall -lm

unittestresults.out: dominion_helpers.h dominion.h dominion.c rngs.h rngs.c \
				 player.c interface.h interface.c playdom.c unittest1.c \
				 unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c \
				 cardtest3.c cardtest4.c
	gcc -c dominion.c -g $(CFLAGS)
	gcc -c rngs.c -g $(CFLAGS)
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o ut1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o ut2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o ut3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o ut4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o ct1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o ct2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o ct3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o ct4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	gcc -c interface.c -g  $(CFLAGS)
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	./ut1 &> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./ut2 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./ut3 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./ut4 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./ct1 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./ct2 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./ct3 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./ct4 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: dominion_helpers.h dominion.h dominion.c rngs.h rngs.c \
	player.c interface.h interface.c playdom.c unittest1.c \
	unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c \
	cardtest3.c cardtest4.c
	gcc -c dominion.c -g $(CFLAGS2)
	gcc -c rngs.c -g $(CFLAGS2)
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS2)
	gcc -o ut1 -g unittest1.c dominion.o rngs.o $(CFLAGS2)
	gcc -o ut2 -g unittest2.c dominion.o rngs.o $(CFLAGS2)
	gcc -o ut3 -g unittest3.c dominion.o rngs.o $(CFLAGS2)
	gcc -o ut4 -g unittest4.c dominion.o rngs.o $(CFLAGS2)
	gcc -o ct1 -g cardtest1.c dominion.o rngs.o $(CFLAGS2)
	gcc -o ct2 -g cardtest2.c dominion.o rngs.o $(CFLAGS2)
	gcc -o ct3 -g cardtest3.c dominion.o rngs.o $(CFLAGS2)
	gcc -o ct4 -g cardtest4.c dominion.o rngs.o $(CFLAGS2)
	gcc -c interface.c -g  $(CFLAGS2)
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS2)

clean:
	rm -f  playdom player ut1 ut2 ut3 ut4 ct1 ct2 ct3 ct4 *.o *.gcov *.gcda *.gch *.gcno *.so *.out
