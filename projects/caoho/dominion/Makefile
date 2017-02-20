CFLAGS = -fprofile-arcs -ftest-coverage -Wall -lm

all: playdom player testDrawCard testBuyCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f *.o test.exe test testInit testInit.exe  *.gcov *.gcda *.gcno *.so
  
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

unittest1: dominion.c unittest1.c rngs.c
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(CFLAGS)
	
unittest2: dominion.c unittest2.c rngs.c
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)

unittest3: dominion.c unittest3.c rngs.c
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)

unittest4: dominion.c unittest4.c rngs.c
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)

cardtest1: dominion.c cardtest1.c rngs.c
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)

cardtest2: dominion.c cardtest2.c rngs.c
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c $(CFLAGS)

cardtest3: dominion.c cardtest3.c rngs.c
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c $(CFLAGS)

cardtest4: cardtest4.c dominion.c rngs.c
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c $(CFLAGS)
						
rununittest: unittest1 unittest2 unittest3 unittest4
	echo "Results saved to rununittest.out" &> rununittest.out
	./unittest1 >> rununittest.out
	./unittest2 >> rununittest.out
	./unittest3 >> rununittest.out
	./unittest4 >> rununittest.out
	gcov -b dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1>> unittestresults.out
	./unittest2>> unittestresults.out
	./unittest3>> unittestresults.out
	./unittest4>> unittestresults.out
	./cardtest1>> unittestresults.out
	./cardtest2>> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b dominion >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 badTestDrawCard 
