# Antonina (Toni) York
# OSU CS 362 Winter 2017
# Dominion Makefile
# Refactored to work with Avisek's (lamaa) code
# added "yorka-" to beginning of test names

CFLAGS = -Wall -fpic -coverage -lm
SEED = 1000

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
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
yorka-unittest1: yorka-unittest1.c dominion.o rngs.o
	gcc -o yorka-unittest1 -g  yorka-unittest1.c dominion.o rngs.o $(CFLAGS)
	
yorka-unittest2: yorka-unittest2.c dominion.o rngs.o
	gcc -o yorka-unittest2 -g  yorka-unittest2.c dominion.o rngs.o $(CFLAGS)
	
yorka-unittest3: yorka-unittest3.c dominion.o rngs.o
	gcc -o yorka-unittest3 -g  yorka-unittest3.c dominion.o rngs.o $(CFLAGS)
	
yorka-unittest4: yorka-unittest4.c dominion.o rngs.o
	gcc -o yorka-unittest4 -g  yorka-unittest4.c dominion.o rngs.o $(CFLAGS)	
	
yorka-cardtest1: yorka-cardtest1.c dominion.o rngs.o
	gcc -o yorka-cardtest1 -g  yorka-cardtest1.c dominion.o rngs.o $(CFLAGS)
	
yorka-cardtest2: yorka-cardtest2.c dominion.o rngs.o
	gcc -o yorka-cardtest2 -g  yorka-cardtest2.c dominion.o rngs.o $(CFLAGS)
	
yorka-cardtest3: yorka-cardtest3.c dominion.o rngs.o
	gcc -o yorka-cardtest3 -g  yorka-cardtest3.c dominion.o rngs.o $(CFLAGS)
	
yorka-cardtest4: yorka-cardtest4.c dominion.o rngs.o
	gcc -o yorka-cardtest4 -g  yorka-cardtest4.c dominion.o rngs.o $(CFLAGS)
	
yorka-randomtestadventurer: yorka-randomtestadventurer.c dominion.o rngs.o
	gcc -o yorka-randomtestadventurer -g yorka-randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
yorka-randomtestcard1: yorka-randomtestcard1.c dominion.o rngs.o
	gcc -o yorka-randomtestcard1 -g  yorka-randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	
yorka-randomtestcard2: yorka-randomtestcard2.c dominion.o rngs.o
	gcc -o yorka-randomtestcard2 -g  yorka-randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	
yorka-randomtestadventurer.out: yorka-randomtestadventurer.c dominion.o rngs.o
	echo "" > yorka-randomtestadventurer.out
	echo "Results of Random Test of Adventurer" >> yorka-randomtestadventurer.out
	echo "" >> yorka-randomtestadventurer.out
	echo "Change PRINT_TESTS to 1 to see prinouts." >> yorka-randomtestadventurer.out
	
	echo "" >> yorka-randomtestadventurer.out
	echo "=============================================" >> yorka-randomtestadventurer.out
	echo "" >> yorka-randomtestadventurer.out
	
	gcc -o yorka-randomtestadventurer yorka-randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	yorka-randomtestadventurer $(SEED) >> yorka-randomtestadventurer.out
	
	echo "" >> yorka-randomtestadventurer.out
	echo "=============================================" >> yorka-randomtestadventurer.out
	echo "" >> yorka-randomtestadventurer.out
	
	echo "gcov results:" >> yorka-randomtestadventurer.out
	gcov -b -f dominion.c >> yorka-randomtestadventurer.out
	#cat dominion.c.gcov >> yorka-randomtestadventurer.out
	
	echo "=============================================" >> yorka-randomtestadventurer.out
	echo "" >> yorka-randomtestadventurer.out
	
	echo "Done!" >> yorka-randomtestadventurer.out
	echo "" >> yorka-randomtestadventurer.out
	
yorka-randomtestcard1.out: yorka-randomtestcard1.c dominion.o rngs.o
	echo "" > yorka-randomtestcard1.out
	echo "Results of Random Test of Smithy" >> yorka-randomtestcard1.out
	echo "" >> yorka-randomtestcard1.out
	echo "Change PRINT_TESTS to 1 to see prinouts." >> yorka-randomtestcard1.out
	
	echo "" >> yorka-randomtestcard1.out
	echo "=============================================" >> yorka-randomtestcard1.out
	echo "" >> yorka-randomtestcard1.out
	
	gcc -o yorka-randomtestcard1 yorka-randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	yorka-randomtestcard1 $(SEED) >> yorka-randomtestcard1.out
	
	echo "" >> yorka-randomtestcard1.out
	echo "=============================================" >> yorka-randomtestcard1.out
	echo "" >> yorka-randomtestcard1.out
	
	echo "gcov results:" >> yorka-randomtestcard1.out
	gcov -b -f dominion.c >> yorka-randomtestcard1.out
	#cat dominion.c.gcov >> yorka-randomtestcard1.out
	
	echo "=============================================" >> yorka-randomtestcard1.out
	echo "" >> yorka-randomtestcard1.out
	
	echo "Done!" >> yorka-randomtestcard1.out
	echo "" >> yorka-randomtestcard1.out
	
yorka-randomtestcard2.out: yorka-randomtestcard2.c dominion.o rngs.o
	echo "" > yorka-randomtestcard2.out
	echo "Results of Random Test of Village" >> yorka-randomtestcard2.out
	echo "" >> yorka-randomtestcard2.out
	echo "Change PRINT_TESTS to 1 to see prinouts." >> yorka-randomtestcard2.out
	
	echo "" >> yorka-randomtestcard2.out
	echo "=============================================" >> yorka-randomtestcard2.out
	echo "" >> yorka-randomtestcard2.out
	
	gcc -o yorka-randomtestcard2 yorka-randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	yorka-randomtestcard2 $(SEED) >> yorka-randomtestcard2.out
	
	echo "" >> yorka-randomtestcard2.out
	echo "=============================================" >> yorka-randomtestcard2.out
	echo "" >> yorka-randomtestcard2.out
	
	echo "gcov results:" >> yorka-randomtestcard2.out
	gcov -b -f dominion.c >> yorka-randomtestcard2.out
	#cat dominion.c.gcov >> yorka-randomtestcard2.out
	
	echo "=============================================" >> yorka-randomtestcard2.out
	echo "" >> yorka-randomtestcard2.out
	
	echo "Done!" >> yorka-randomtestcard2.out
	echo "" >> yorka-randomtestcard2.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
yorka-unittestresults.out: yorka-unittest1.c yorka-unittest2.c yorka-unittest3.c yorka-unittest4.c yorka-cardtest1.c yorka-cardtest2.c yorka-cardtest3.c yorka-cardtest4.c dominion.o rngs.o
	echo "" > yorka-unittestresults.out
	echo "Results of Dominion Unit Tests" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	echo "Change PRINT_TESTS to 1 in individual test files to see prinouts." >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-unittest1.c:" >> yorka-unittestresults.out
	gcc -o yorka-unittest1 yorka-unittest1.c -g dominion.o rngs.o $(CFLAGS)
	yorka-unittest1 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-unittest2.c:" >> yorka-unittestresults.out
	gcc -o yorka-unittest2 yorka-unittest2.c -g dominion.o rngs.o $(CFLAGS)
	yorka-unittest2 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-unittest3.c:" >> yorka-unittestresults.out
	gcc -o yorka-unittest3 yorka-unittest3.c -g dominion.o rngs.o $(CFLAGS)
	yorka-unittest3 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-unittest4.c:" >> yorka-unittestresults.out
	gcc -o yorka-unittest4 yorka-unittest4.c -g dominion.o rngs.o $(CFLAGS)
	yorka-unittest4 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-cardtest1.c:" >> yorka-unittestresults.out
	gcc -o yorka-cardtest1 yorka-cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	yorka-cardtest1 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-cardtest2.c:" >> yorka-unittestresults.out
	gcc -o yorka-cardtest2 yorka-cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	yorka-cardtest2 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-cardtest3.c:" >> yorka-unittestresults.out
	gcc -o yorka-cardtest3 yorka-cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	yorka-cardtest3 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "yorka-cardtest4.c:" >> yorka-unittestresults.out
	gcc -o yorka-cardtest4 yorka-cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	yorka-cardtest4 >> yorka-unittestresults.out
	
	echo "" >> yorka-unittestresults.out
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "gcov results:" >> yorka-unittestresults.out
	gcov -b -f dominion.c >> yorka-unittestresults.out
	#cat dominion.c.gcov >> yorka-unittestresults.out
	
	echo "=============================================" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out
	
	echo "Dominion unit tests complete!" >> yorka-unittestresults.out
	echo "" >> yorka-unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o *.out yorka-randomtestadventurer yorka-randomtestcard1 yorka-randomtestcard2 testDrawCard badTestDrawCard yorka-unittest1 yorka-unittest2 yorka-unittest3 yorka-unittest4 yorka-cardtest1 yorka-cardtest2 yorka-cardtest3 yorka-cardtest4 *.gcda *.gcno *.gcov playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so