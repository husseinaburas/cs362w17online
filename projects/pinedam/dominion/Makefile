CFLAGS = -Wall -fpic -coverage -lm

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

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o 
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

rununittest1:  unittest1
	-./unittest1 &> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

unittest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

rununittest2:  unittest2
	-./unittest2 >> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

unittest3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

rununittest3:  unittest3
	-./unittest3 >> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

unittest4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

rununittest4:  unittest4
	-./unittest4 >> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

cardtest1: dominion.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

runcardtest1:  cardtest1
	-./cardtest1 >> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

cardtest2: dominion.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

runcardtest2:  cardtest2
	-./cardtest2 >> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

cardtest3: dominion.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

runcardtest3:  cardtest3
	-./cardtest3 >> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

cardtest4: dominion.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

runcardtest4:  cardtest4
	-./cardtest4 >> unittestresults.out
	-gcov -b dominion.c >> unittestresults.out
	-cat dominion.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

alltest: rununittest1 rununittest2 rununittest3 rununittest4 runcardtest1 runcardtest2 runcardtest3 runcardtest4

clean:
	rm -f *.o playdom.exe playdom unittest1 test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
