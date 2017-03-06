CFLAGS = -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

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

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3
	./cardtest1 > unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -abcf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

runalltests:
	make randomtestadventurer
	./randomtestadventurer > randomtestadventurer.out
	gcov -abcf dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	rm -f *.o *.gcov *.gcda *.gcno *.so randomtestadventurer
	make randomtestcard1
	./randomtestcard1 > randomtestcard1.out
	gcov -abcf dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	rm -f *.o *.gcov *.gcda *.gcno *.so randomtestcard1
	make randomtestcard2
	./randomtestcard2 > randomtestcard2.out
	gcov -abcf dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	rm -f *.o *.gcov *.gcda *.gcno *.so randomtestcard2
	make unittestresults.out
	make clean

clean:
	rm -f *.o randomtestcard1 randomtestcard2 randomtestadventurer cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 *.gcov *.gcda *.gcno *.so

