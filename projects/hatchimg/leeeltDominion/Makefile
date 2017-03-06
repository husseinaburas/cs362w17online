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

myunit1: myunittest1.c dominion.o rngs.o
	gcc -o myunit1 -g myunittest1.c dominion.o rngs.o $(CFLAGS)

myunit2: myunittest2.c dominion.o rngs.o
	gcc -o myunit2 -g myunittest2.c dominion.o rngs.o $(CFLAGS)

myunit3: myunittest3.c dominion.o rngs.o
	gcc -o myunit3 -g myunittest3.c dominion.o rngs.o $(CFLAGS)

myunit4: myunittest4.c dominion.o rngs.o
	gcc -o myunit4 -g myunittest4.c dominion.o rngs.o $(CFLAGS)

mycard1: mycardtest1.c dominion.o rngs.o
	gcc -o mycard1 -g mycardtest1.c dominion.o rngs.o $(CFLAGS)

mycard2: mycardtest2.c dominion.o rngs.o
	gcc -o mycard2 -g mycardtest2.c dominion.o rngs.o $(CFLAGS)

mycard3: mycardtest3.c dominion.o rngs.o
	gcc -o mycard3 -g mycardtest3.c dominion.o rngs.o $(CFLAGS)

mycard4: mycardtest4.c dominion.o rngs.o
	gcc -o mycard4 -g mycardtest4.c dominion.o rngs.o $(CFLAGS)

myrandomtestadventurer: myrandomtestadventurer.c dominion.o rngs.o
	gcc -o myrandomtestadventurer -g myrandomtestadventurer.c dominion.o rngs.o $(CFLAGS)

myrandomtestcard1: myrandomtestcard1.c dominion.o rngs.o
	gcc -o myrandomtestcard1 -g myrandomtestcard1.c dominion.o rngs.o $(CFLAGS)

myrandomtestcard2: myrandomtestcard2.c dominion.o rngs.o
	gcc -o myrandomtestcard2 -g myrandomtestcard2.c dominion.o rngs.o $(CFLAGS)

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

all: playdom player testDrawCard testBuyCard badTestDrawCard myunit1 myunit2 myunit3 myunit4 mycard1 mycard2 mycard3 mycard4 myrandomtestadventurer myrandomtestcard1 myrandomtestcard2

unittestresults.out: playdom player testDrawCard testBuyCard badTestDrawCard unit1 unit2 unit3 unit4 card1 card2 card3 card4
	rm -rf dominion.gcda
	./unit1 > unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out
	rm -rf dominion.gcda
	./unit2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out
	rm -rf dominion.gcda
	./unit3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./unit4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

randomtestadventurer.out: playdom player testDrawCard testBuyCard badTestDrawCard randomtestadventurer
	rm -rf dominion.gcda
	./randomtestadventurer -1 > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	
randomtestcard1.out: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard1
	rm -rf dominion.gcda
	./randomtestcard1 -1 > randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	
randomtestcard2.out: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard2
	rm -rf dominion.gcda
	./randomtestcard2 -1 > randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	
clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
