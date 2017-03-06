CFLAGS= -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.c rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.c rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.c rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest4: cardtest4.c dominion.c rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	
unittests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresult.out
	./unittest2 &>> unittestresult.out
	./unittest3 &>> unittestresult.out
	./unittest4 &>> unittestresult.out
	./cardtest1 &>> unittestresult.out
	./cardtest2 &>> unittestresult.out
	./cardtest3 &>> unittestresult.out
	./cardtest4 &>> unittestresult.out
	gcov -b -f dominion.c >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
randGameState.o: randGameState.h randGameState.c 
	gcc -c randGameState.c $(CFLAGS)

randomtestcard1: randomtestcard1.c randGameState.o dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c randGameState.o dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c randGameState.o dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c randGameState.o dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: randomtestadventurer.c randGameState.o dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c randGameState.o dominion.o rngs.o $(CFLAGS)
	
randomtests: randGameState.o randomtestcard1 randomtestcard2 randomtestadventurer
	./randomtestcard1 5 &> randomtestcard1.out
	./randomtestcard2 5 &> randomtestcard2.out
	./randomtestadventurer 5 &> randomtestadventurer.out
	gcov -b -f dominion.c > coverage.out
	gcov dominion.c >> coverage.out
	cat dominion.c.gcov >> coverage.out

all_tests: randGameState.o randomtestcard1 randomtestcard2 randomtestadventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresult.out
	./unittest2 &>> unittestresult.out
	./unittest3 &>> unittestresult.out
	./unittest4 &>> unittestresult.out
	./cardtest1 &>> unittestresult.out
	./cardtest2 &>> unittestresult.out
	./cardtest3 &>> unittestresult.out
	./cardtest4 &>> unittestresult.out
	gcov -b -f dominion.c >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./randomtestcard1 5 &> randomtestcard1.out
	./randomtestcard2 5 &> randomtestcard2.out
	./randomtestadventurer 5 &> randomtestadventurer.out
	gcov -b -f dominion.c > coverage.out
	gcov dominion.c >> coverage.out
	cat dominion.c.gcov >> coverage.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so
