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

	echo -e "\nunittest2\n" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo -e "\nunittest3\n" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo -e "\nunittest4\n" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo -e "\ncardtest1\n" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo -e "\ncardtest2\n" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo -e "\ncardtest3\n" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo -e "\ncardtest4\n" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestcard1: randomtestcard1.c dominion.o random_test_runner.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1.out: randomtestcard1
	echo -e "Random Testing for Council Room\n" > randomtestcard1.out
	./randomtestcard1 1 >> randomtestcard1.out
	gcov dominion.c -b -f >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o random_test_runner.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2.out: randomtestcard2
	echo -e "Random Testing for Smithy\n" > randomtestcard2.out
	./randomtestcard2 1 >> randomtestcard2.out
	gcov dominion.c -b -f >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer: randomtestadventurer.c dominion.o random_test_runner.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	echo -e "Random Testing for Adventurer\n" > randomtestadventurer.out
	./randomtestadventurer 1 >> randomtestadventurer.out
	gcov dominion.c -b -f >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

hartmami_randomtestcard1: hartmami_randomtestcard1.c dominion.o rngs.o
	gcc -o hartmami_randomtestcard1 -g  hartmami_randomtestcard1.c dominion.o rngs.o $(CFLAGS)

hartmami_randomtestcard2: hartmami_randomtestcard2.c dominion.o rngs.o
	gcc -o hartmami_randomtestcard2 -g  hartmami_randomtestcard2.c dominion.o rngs.o $(CFLAGS)

hartmami_randomtestadventurer: hartmami_randomtestadventurer.c dominion.o rngs.o
	gcc -o hartmami_randomtestadventurer -g  hartmami_randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

hartmami_randomtestcard1.out: hartmami_randomtestcard1
	echo "Results saved to randomtestcard1.out" &> randomtestcard1.out
	./hartmami_randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

hartmami_randomtestcard2.out: hartmami_randomtestcard2
	echo "Results saved to randomtestcard2.out" &> randomtestcard2.out
	./hartmami_randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

hartmami_randomtestadventurer.out: hartmami_randomtestadventurer
	echo "Results saved to randomtestadventurer.out" &> randomtestadventurer.out
	./hartmami_randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

hartmami_unittest1: hartmami_unittest1.c dominion.o rngs.o
	gcc -o hartmami_unittest1 -g  hartmami_unittest1.c dominion.o rngs.o $(CFLAGS)

hartmami_unittest2: hartmami_unittest2.c dominion.o rngs.o
	gcc -o hartmami_unittest2 -g  hartmami_unittest2.c dominion.o rngs.o $(CFLAGS)

hartmami_unittest3: hartmami_unittest3.c dominion.o rngs.o
	gcc -o hartmami_unittest3 -g  hartmami_unittest3.c dominion.o rngs.o $(CFLAGS)

hartmami_unittest4: hartmami_unittest4.c dominion.o rngs.o
	gcc -o hartmami_unittest4 -g  hartmami_unittest4.c dominion.o rngs.o $(CFLAGS)

hartmami_cardtest1: hartmami_cardtest1.c dominion.o rngs.o
	gcc -o hartmami_cardtest1 -g  hartmami_cardtest1.c dominion.o rngs.o $(CFLAGS)

hartmami_cardtest2: hartmami_cardtest2.c dominion.o rngs.o
	gcc -o hartmami_cardtest2 -g  hartmami_cardtest2.c dominion.o rngs.o $(CFLAGS)

hartmami_cardtest3: hartmami_cardtest3.c dominion.o rngs.o
	gcc -o hartmami_cardtest3 -g  hartmami_cardtest3.c dominion.o rngs.o $(CFLAGS)

hartmami_cardtest4: hartmami_cardtest4.c dominion.o rngs.o
	gcc -o hartmami_cardtest4 -g  hartmami_cardtest4.c dominion.o rngs.o $(CFLAGS)

hartmami_unittestresults.out: hartmami_unittest1 hartmami_unittest2 hartmami_unittest3 hartmami_unittest4 hartmami_cardtest1 hartmami_cardtest2 hartmami_cardtest3 hartmami_cardtest4
	echo "Results saved to unittestresults.out" &> unittestresults.out
	./hartmami_unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	./hartmami_unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	./hartmami_unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	./hartmami_unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	./hartmami_cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	./hartmami_cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	./hartmami_cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	./hartmami_cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


all: hartmami_unittestresults.out hartmami_randomtestcard1.out hartmami_randomtestcard2.out hartmami_randomtestadventurer.out

allen_all: unittestresults.out randomtestcard1.out randomtestcard2.out randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard1 randomtestcard2 randomtestadventurer
