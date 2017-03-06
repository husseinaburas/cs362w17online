CFLAGS = -Wall -fpic -coverage -lm -ftest-coverage

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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: unittest1.c dominion.o custom_assert.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o custom_assert.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o custom_assert.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o custom_assert.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o custom_assert.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o custom_assert.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o custom_assert.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o custom_assert.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

unittestresults.out: cardtest4 cardtest3 cardtest2 cardtest1 unittest1 unittest2 unittest3 unittest4 dominion.o
	echo -e "unittest1\n" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda
	
	echo -e "\nunittest2\n" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda
	
	echo -e "\nunittest3\n" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda

	echo -e "\nunittest4\n" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda

	echo -e "\ncardtest1\n" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda

	echo -e "\ncardtest2\n" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda

	echo -e "\ncardtest3\n" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda

	echo -e "\ncardtest4\n" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	rm *.gcda


all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
