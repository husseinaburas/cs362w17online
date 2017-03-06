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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

weissmarUnittest1: weissmarUnittest1.c  dominion.o rngs.o
	gcc -o weissmarUnittest1 -g weissmarUnittest1.c dominion.o  rngs.o $(CFLAGS)

weissmarUnittest2: weissmarUnittest2.c  dominion.o rngs.o
	gcc -o weissmarUnittest2 -g weissmarUnittest2.c dominion.o  rngs.o $(CFLAGS)

weissmarUnittest3: weissmarUnittest3.c  dominion.o rngs.o
	gcc -o weissmarUnittest3 -g weissmarUnittest3.c dominion.o  rngs.o $(CFLAGS)

weissmarUnittest4: weissmarUnittest4.c  dominion.o rngs.o
	gcc -o weissmarUnittest4 -g weissmarUnittest4.c dominion.o  rngs.o $(CFLAGS)

weissmarCardtest1: weissmarCardtest1.c  dominion.o rngs.o
	gcc -o weissmarCardtest1 -g weissmarCardtest1.c dominion.o  rngs.o $(CFLAGS)

weissmarCardtest2: weissmarCardtest2.c  dominion.o rngs.o
	gcc -o weissmarCardtest2 -g weissmarCardtest2.c dominion.o  rngs.o $(CFLAGS)

weissmarCardtest3: weissmarCardtest3.c  dominion.o rngs.o
	gcc -o weissmarCardtest3 -g weissmarCardtest3.c dominion.o  rngs.o $(CFLAGS)

weissmarCardtest4: weissmarCardtest4.c  dominion.o rngs.o
	gcc -o weissmarCardtest4 -g weissmarCardtest4.c dominion.o  rngs.o $(CFLAGS)

weissmarRandomtestadventurer: weissmarRandomtestadventurer.c  dominion.o rngs.o
	gcc -o weissmarRandomtestadventurer -g weissmarRandomtestadventurer.c dominion.o  rngs.o $(CFLAGS)

weissmarRandomtestcard1: weissmarRandomtestcard1.c  dominion.o rngs.o
	gcc -o weissmarRandomtestcard1 -g weissmarRandomtestcard1.c dominion.o  rngs.o $(CFLAGS)

weissmarRandomtestcard2: weissmarRandomtestcard2.c  dominion.o rngs.o
	gcc -o weissmarRandomtestcard2 -g weissmarRandomtestcard2.c dominion.o  rngs.o $(CFLAGS)

weissmarUnittestresults.out: weissmarUnittest1 weissmarUnittest2 weissmarUnittest3 weissmarUnittest4 weissmarCardtest1 weissmarCardtest2 weissmarCardtest3 weissmarCardtest4
	@echo "weissmarUnittest1.c:" > weissmarUnittestresults.out
	./weissmarUnittest1 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "weissmarUnittest2.c:" >> weissmarUnittestresults.out
	./weissmarUnittest2 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "weissmarUnittest3.c:" >> weissmarUnittestresults.out
	./weissmarUnittest3 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "weissmarUnittest4.c:" >> weissmarUnittestresults.out
	./weissmarUnittest4 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "weissmarCardtest1.c:" >> weissmarUnittestresults.out
	./weissmarCardtest1 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "weissmarCardtest2.c:" >> weissmarUnittestresults.out
	./weissmarCardtest2 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "weissmarCardtest3.c:" >> weissmarUnittestresults.out
	./weissmarCardtest3 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "weissmarCardtest4.c:" >> weissmarUnittestresults.out
	./weissmarCardtest4 >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "gcov results for dominion.c:" >> weissmarUnittestresults.out
	gcov -b -f dominion.c  >> weissmarUnittestresults.out
	@echo "" >> weissmarUnittestresults.out
	@echo "dominion.c.gcov:" >> weissmarUnittestresults.out
	cat dominion.c.gcov >> weissmarUnittestresults.out

weissmarRandomtestadventurer.out: weissmarRandomtestadventurer
	@echo "weissmarRandomtestadventurer.c:" > weissmarRandomtestadventurer.out
	./weissmarRandomtestadventurer >> weissmarRandomtestadventurer.out
	@echo "" >> weissmarRandomtestadventurer.out
	@echo "gcov results for dominion.c:" >> weissmarRandomtestadventurer.out
	gcov -b -f dominion.c  >> weissmarRandomtestadventurer.out
	@echo "" >> weissmarRandomtestadventurer.out
	@echo "dominion.c.gcov:" >> weissmarRandomtestadventurer.out
	cat dominion.c.gcov >> weissmarRandomtestadventurer.out

weissmarRandomtestcard1.out: weissmarRandomtestcard1
	@echo "weissmarRandomtestcard1.c:" > weissmarRandomtestcard1.out
	./weissmarRandomtestcard1 >> weissmarRandomtestcard1.out
	@echo "" >> weissmarRandomtestcard1.out
	@echo "gcov results for dominion.c:" >> weissmarRandomtestcard1.out
	gcov -b -f dominion.c  >> weissmarRandomtestcard1.out
	@echo "" >> weissmarRandomtestcard1.out
	@echo "dominion.c.gcov:" >> weissmarRandomtestcard1.out
	cat dominion.c.gcov >> weissmarRandomtestcard1.out

weissmarRandomtestcard2.out: weissmarRandomtestcard2
	@echo "weissmarRandomtestcard2.c:" > weissmarRandomtestcard2.out
	./weissmarRandomtestcard2 >> weissmarRandomtestcard2.out
	@echo "" >> weissmarRandomtestcard2.out
	@echo "gcov results for dominion.c:" >> weissmarRandomtestcard2.out
	gcov -b -f dominion.c  >> weissmarRandomtestcard2.out
	@echo "" >> weissmarRandomtestcard2.out
	@echo "dominion.c.gcov:" >> weissmarRandomtestcard2.out
	cat dominion.c.gcov >> weissmarRandomtestcard2.out

allweissmarRandomTests: clean weissmarRandomtestadventurer.out weissmarRandomtestcard1.out weissmarRandomtestcard2.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so 
