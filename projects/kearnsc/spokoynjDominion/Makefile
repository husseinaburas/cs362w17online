#----------------------------------------------------------------------------------
# CS362-400-W17	Assignment 5 makefile		05 Mar 2017 
# Chris Kearns		kearnsc@oregonstate.edu
# "make unittestresults.out" will compile and run all tests indicated and write
#	detailed gcov coverage data to a file named "unittestresults.out".
# "make randomtestresults.out" will compile and run all tests indicated and write
#	detailed gcov coverage data to 3 seperate files named "randomtest??????.out".
# "make all" will compile as indicated without gcov or executing any programs.
# "make clean" will delete EVERYTHING but the source code files.
#---------------------------------------------------------------------------------

CFLAGS = -Wall -fpic -coverage -lm
CFLAGS2 = -Wall -lm

# Original makefile commands...
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testBuyCard.c dominion.o rngs.o
	gcc -o testBuyCard -g testBuyCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

# ...End orginal makefile.

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

randomtestresults.out: dominion_helpers.h dominion.h dominion.c rngs.h rngs.c \
				 player.c interface.h interface.c playdom.c randomtestadventurer.c \
				 randomtestcard1.c randomtestcard2.c
	gcc -c dominion.c -g $(CFLAGS)
	gcc -c rngs.c -g $(CFLAGS)
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o rta -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	gcc -o rtc1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o rtc2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	gcc -c interface.c -g  $(CFLAGS)
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	./rta -1 &> randomtestadventurer.out
	gcov -b -c dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	./rtc1 -1 &> randomtestcard1.out
	gcov -b -c dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	./rtc2 -1 &> randomtestcard2.out
	gcov -b -c dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

all: dominion_helpers.h dominion.h dominion.c rngs.h rngs.c \
	player.c interface.h interface.c playdom.c unittest1.c \
	unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c \
	cardtest3.c cardtest4.c randomtestadventurer.c randomtestcard1.c \
	randomtestcard2.c
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
	gcc -o rta -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS2)
	gcc -o rtc1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS2)
	gcc -o rtc2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS2)
	gcc -c interface.c -g  $(CFLAGS2)
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS2)

clean:
	rm -f  playdom player ut1 ut2 ut3 ut4 ct1 ct2 ct3 ct4 rta rtc1 rtc2 *.o *.gcov *.gcda *.gch *.gcno *.so *.out
