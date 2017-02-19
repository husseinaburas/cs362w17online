CFLAGS = -Wall -fpic -coverage -lm

all: playdom player testDrawCard testBuyCard badTestDrawCard

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

unittest1: dominion.o rngs.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o rngs.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o rngs.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o rngs.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: dominion.o rngs.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o rngs.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o rngs.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o rngs.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o rngs.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o rngs.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestcardadventurer: dominion.o rngs.o randomtestcardadventurer.c
	gcc -o randomtestcardadventurer randomtestcardadventurer.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo >> unittestresults.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> unittestresults.out
	grep "function getCost" dominion.c.gcov >> unittestresults.out
	grep "function drawCar" dominion.c.gcov >> unittestresults.out
	grep "function updateC" dominion.c.gcov >> unittestresults.out
	grep "function isGameO" dominion.c.gcov >> unittestresults.out
	grep "function playAdv" dominion.c.gcov >> unittestresults.out
	grep "function playSmi" dominion.c.gcov >> unittestresults.out
	grep "function playVil" dominion.c.gcov >> unittestresults.out
	sed -n 1133,1144p dominion.c.gcov >> unittestresults.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> unittestresults.out
	echo >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c
	cat dominion.c.gcov >> unittestresults.out

randomtestcard1.out: randomtestcard1
	./randomtestcard1 >> randomtestcard1.out
	echo >> randomtestcard1.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomcardtest1.out
	grep "function playVil" dominion.c.gcov >> randomtestcard1.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomcardtest1.out
	echo >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	echo >> randomtestcard1.out
	gcov dominion.c
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	./randomtestcard2 >> randomtestcard2.out
	echo >> randomtestcard2.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomcardtest1.out
	grep "function playVil" dominion.c.gcov >> randomtestcard2.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomcardtest1.out
	echo >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	echo >> randomtestcard2.out
	gcov dominion.c
	cat dominion.c.gcov >> randomtestcard2.out

randomtestcardadventurer.out: randomtestcardadventurer
	./randomtestcardadventurer >> randomtestcardadventurer.out
	echo >> randomtestcardadventurer.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomcardtest1.out
	grep "function playVil" dominion.c.gcov >> randomtestcardadventurer.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomcardtest1.out
	echo >> randomtestcardadventurer.out
	cat dominion.c.gcov >> randomtestcardadventurer.out
	echo >> randomtestcardadventurer.out
	gcov dominion.c
	cat dominion.c.gcov >> randomtestcardadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

clean:
	rm -f *.o playdom test testDrawCard badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player testInit *.exe *.gcov *.gcda *.gcno *.so *.out randomtestcard1 randomtestcard2 randomtestcardadventurer
