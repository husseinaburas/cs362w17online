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

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)
	
testUnitTest1: unittest1.c dominion.o rngs.o
	gcc -o testUnitTest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

testUnitTest2: unittest2.c dominion.o rngs.o
	gcc -o testUnitTest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	
testUnitTest3: unittest3.c dominion.o rngs.o
	gcc -o testUnitTest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	
testUnitTest4: unittest4.c dominion.o rngs.o
	gcc -o testUnitTest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	
testCardTest1: cardtest1.c dominion.o rngs.o
	gcc -o testCardTest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	
testCardTest2: cardtest2.c dominion.o rngs.o
	gcc -o testCardTest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	
testCardTest3: cardtest3.c dominion.o rngs.o
	gcc -o testCardTest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	
testCardTest4: cardtest4.c dominion.o rngs.o
	gcc -o testCardTest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Running dominion tests:" > unittestresults.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.c rngs.c unittest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.c rngs.c unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

randomtestcard1.out: randomtestcard1.c dominion.c rngs.c
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 dominion.c rngs.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 100 >> randomtestcard1.out
	gcov -b -c dominion.c >> randomtestcard1.out
	
randomtestcard2.out: randomtestcard2.c dominion.c rngs.c
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 dominion.c rngs.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 100 >> randomtestcard2.out
	gcov -b -c dominion.c >> randomtestcard2.out
	
randomtestadventurer.out: randomtestadventurer.c dominion.c rngs.c
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer dominion.c rngs.c randomtestadventurer.c $(CFLAGS)
	randomtestadventurer 100 >> randomtestadventurer.out
	gcov -b -c dominion.c >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard badTestDrawCard testUnitTest1 testUnitTest2 testUnitTest3 testUnitTest4 testCardTest1 testCardTest2 testCardTest3 testCardTest4

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
	
cleanunittests:
	rm unittestresults.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcda *.gcno *.gcov 
