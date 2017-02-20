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

clean:
	rm -f *.o randomtestcard1 randomtestcard2 randomtestadventurer *.gcov *.gcda *.gcno *.so

