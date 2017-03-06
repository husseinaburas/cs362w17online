CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4
	./cardtest1 &> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer 3 &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	echo -e "\n\n" >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1
	./randomtestcard1 3 &> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	echo -e "\n\n" >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	./randomtestcard2 3 &> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	echo -e "\n\n" >> randomtestcard2.out

randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2
	./randomtestadventurer 3 &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	echo -e "\n\n" >> randomtestadventurer.out
	./randomtestcard1 3 &> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	echo -e "\n\n" >> randomtestcard1.out
	./randomtestcard2 3 &> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	echo -e "\n\n" >> randomtestcard2.out

all: randomtestresults

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
