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

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
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

runalltests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2
	#./unittest1>> unittestresults.out
	./unittest2>> alltests.out
	./unittest3>> alltests.out
	./unittest4>> alltests.out
	./cardtest1>> alltests.out
	./cardtest2>> alltests.out
	./cardtest3 >> alltests.out
	./cardtest4 >> alltests.out
	#./randomtestadventurer > randomtestadventurer.out
	./randomtestcard1 > alltests.out
	./randomtestcard2 > alltests.out
	gcov -b dominion >> alltests.out
	cat dominion.c.gcov >> alltests.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer > randomtestadventurer.out
	gcov -abcf dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	rm -f *.o *.gcov *.gcda *.gcno *.so randomtestadventurer

randomtestcard1.out: randomtestcard1
	./randomtestcard1 > randomtestcard1.out
	gcov -abcf dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	rm -f *.o *.gcov *.gcda *.gcno *.so randomtestcard1

randomtestcard2.out: randomtestcard2
	./randomtestcard2 > randomtestcard2.out
	gcov -abcf dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	rm -f *.o *.gcov *.gcda *.gcno *.so randomtestcard2

#runallrandomtests: randomtestadventurer randomtestcard1 randomtestcard2 randomtestadventurer.out randomtestcard1.out randomtestcard2.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so randomtestadventurer randomtestcard1 randomtestcard2 unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 badTestDrawCard 
