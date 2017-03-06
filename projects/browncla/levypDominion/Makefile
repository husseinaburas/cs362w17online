<<<<<<< HEAD
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

browncla_unittest1: browncla_unittest1.c dominion.o rngs.o
	gcc -o browncla_unittest1 -g  browncla_unittest1.c dominion.o rngs.o $(CFLAGS)

browncla_unittest2: browncla_unittest2.c dominion.o rngs.o
	gcc -o browncla_unittest2 -g  browncla_unittest2.c dominion.o rngs.o $(CFLAGS)

browncla_unittest3: browncla_unittest3.c dominion.o rngs.o
	gcc -o browncla_unittest3 -g  browncla_unittest3.c dominion.o rngs.o $(CFLAGS)

browncla_unittest4: browncla_unittest4.c dominion.o rngs.o
	gcc -o browncla_unittest4 -g  browncla_unittest4.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest1: browncla_cardtest1.c dominion.o rngs.o
	gcc -o browncla_cardtest1 -g  browncla_cardtest1.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest2: browncla_cardtest2.c dominion.o rngs.o
	gcc -o browncla_cardtest2 -g  browncla_cardtest2.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest3: browncla_cardtest3.c dominion.o rngs.o
	gcc -o browncla_cardtest3 -g  browncla_cardtest3.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest4: browncla_cardtest4.c dominion.o rngs.o
	gcc -o browncla_cardtest4 -g  browncla_cardtest4.c dominion.o rngs.o $(CFLAGS)

browncla_randomtestcard1: browncla_randomtestcard1.c dominion.o rngs.o
	gcc -o browncla_randomtestcard1 -g  browncla_randomtestcard1.c dominion.o rngs.o $(CFLAGS)

browncla_randomtestcard2: browncla_randomtestcard2.c dominion.o rngs.o
	gcc -o browncla_randomtestcard2 -g  browncla_randomtestcard2.c dominion.o rngs.o $(CFLAGS)

browncla_randomtestadventurer: browncla_randomtestadventurer.c dominion.o rngs.o
	gcc -o browncla_randomtestadventurer -g  browncla_randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

unittestresults.out: browncla_unittest1 browncla_unittest2 browncla_unittest3 browncla_unittest4 browncla_cardtest1 browncla_cardtest2 browncla_cardtest3 browncla_cardtest4
	./browncla_unittest1 &> unittestresults.out
	./browncla_unittest2 >> unittestresults.out
	./browncla_unittest3 >> unittestresults.out
	./browncla_unittest4 >> unittestresults.out
	./browncla_cardtest1 >> unittestresults.out
	./browncla_cardtest2 >> unittestresults.out
	./browncla_cardtest3 >> unittestresults.out
	./browncla_cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestcard1.out: browncla_randomtestcard1
	./browncla_randomtestcard1 30 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: browncla_randomtestcard2
	./browncla_randomtestcard2 30 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: browncla_randomtestadventurer
	./browncla_randomtestadventurer 30 &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestresults.out: browncla_randomtestcard1 browncla_randomtestcard2 browncla_randomtestadventurer
	./browncla_randomtestcard1 30 &> randomtestresults.out
	./browncla_randomtestcard2 30 >> randomtestresults.out
	./browncla_randomtestadventurer 30 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

allTestResults.out: browncla_unittest1 browncla_unittest2 browncla_unittest3 browncla_unittest4 browncla_cardtest1 browncla_cardtest2 browncla_cardtest3 browncla_cardtest4 browncla_randomtestcard1 browncla_randomtestcard2 browncla_randomtestadventurer
	./browncla_unittest1 &> allTestResults.out
	./browncla_unittest2 >> allTestResults.out
	./browncla_unittest3 >> allTestResults.out
	./browncla_unittest4 >> allTestResults.out
	./browncla_cardtest1 >> allTestResults.out
	./browncla_cardtest2 >> allTestResults.out
	./browncla_cardtest3 >> allTestResults.out
	./browncla_cardtest4 >> allTestResults.out
	./browncla_randomtestcard1 30 >> allTestResults.out
	./browncla_randomtestcard2 30 >> allTestResults.out
	./browncla_randomtestadventurer 30 >> allTestResults.out
	gcov -b dominion.c >> allTestResults.out
	cat dominion.c.gcov >> allTestResults.out


clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so 
=======
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

browncla_unittest1: browncla_unittest1.c dominion.o rngs.o
	gcc -o browncla_unittest1 -g  browncla_unittest1.c dominion.o rngs.o $(CFLAGS)

browncla_unittest2: browncla_unittest2.c dominion.o rngs.o
	gcc -o browncla_unittest2 -g  browncla_unittest2.c dominion.o rngs.o $(CFLAGS)

browncla_unittest3: browncla_unittest3.c dominion.o rngs.o
	gcc -o browncla_unittest3 -g  browncla_unittest3.c dominion.o rngs.o $(CFLAGS)

browncla_unittest4: browncla_unittest4.c dominion.o rngs.o
	gcc -o browncla_unittest4 -g  browncla_unittest4.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest1: browncla_cardtest1.c dominion.o rngs.o
	gcc -o browncla_cardtest1 -g  browncla_cardtest1.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest2: browncla_cardtest2.c dominion.o rngs.o
	gcc -o browncla_cardtest2 -g  browncla_cardtest2.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest3: browncla_cardtest3.c dominion.o rngs.o
	gcc -o browncla_cardtest3 -g  browncla_cardtest3.c dominion.o rngs.o $(CFLAGS)

browncla_cardtest4: browncla_cardtest4.c dominion.o rngs.o
	gcc -o browncla_cardtest4 -g  browncla_cardtest4.c dominion.o rngs.o $(CFLAGS)

browncla_randomtestcard1: browncla_randomtestcard1.c dominion.o rngs.o
	gcc -o browncla_randomtestcard1 -g  browncla_randomtestcard1.c dominion.o rngs.o $(CFLAGS)

browncla_randomtestcard2: browncla_randomtestcard2.c dominion.o rngs.o
	gcc -o browncla_randomtestcard2 -g  browncla_randomtestcard2.c dominion.o rngs.o $(CFLAGS)

browncla_randomtestadventurer: browncla_randomtestadventurer.c dominion.o rngs.o
	gcc -o browncla_randomtestadventurer -g  browncla_randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

unittestresults.out: browncla_unittest1 browncla_unittest2 browncla_unittest3 browncla_unittest4 browncla_cardtest1 browncla_cardtest2 browncla_cardtest3 browncla_cardtest4
	./browncla_unittest1 &> unittestresults.out
	./browncla_unittest2 >> unittestresults.out
	./browncla_unittest3 >> unittestresults.out
	./browncla_unittest4 >> unittestresults.out
	./browncla_cardtest1 >> unittestresults.out
	./browncla_cardtest2 >> unittestresults.out
	./browncla_cardtest3 >> unittestresults.out
	./browncla_cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestcard1.out: browncla_randomtestcard1
	./browncla_randomtestcard1 30 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: browncla_randomtestcard2
	./browncla_randomtestcard2 30 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: browncla_randomtestadventurer
	./browncla_randomtestadventurer 30 &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestresults.out: browncla_randomtestcard1 browncla_randomtestcard2 browncla_randomtestadventurer
	./browncla_randomtestcard1 30 &> randomtestresults.out
	./browncla_randomtestcard2 30 >> randomtestresults.out
	./browncla_randomtestadventurer 30 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	#cat dominion.c.gcov >> randomtestresults.out

allTestResults.out: browncla_unittest1 browncla_unittest2 browncla_unittest3 browncla_unittest4 browncla_cardtest1 browncla_cardtest2 browncla_cardtest3 browncla_cardtest4 browncla_randomtestcard1 browncla_randomtestcard2 browncla_randomtestadventurer
	./browncla_unittest1 &> allTestResults.out
	./browncla_unittest2 >> allTestResults.out
	./browncla_unittest3 >> allTestResults.out
	./browncla_unittest4 >> allTestResults.out
	./browncla_cardtest1 >> allTestResults.out
	./browncla_cardtest2 >> allTestResults.out
	./browncla_cardtest3 >> allTestResults.out
	./browncla_cardtest4 >> allTestResults.out
	./browncla_randomtestcard1 30 >> allTestResults.out
	./browncla_randomtestcard2 30 >> allTestResults.out
	./browncla_randomtestadventurer 30 >> allTestResults.out
	gcov -b dominion.c >> allTestResults.out
	#cat dominion.c.gcov >> allTestResults.out


clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so 
>>>>>>> 3dd9421e657b84505b473479ce99be6eb676e2a5
