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

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	
randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer.out: randomtestadventurer 
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c -o randomtestadventurer -lm -g
	./randomtestadventurer &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	gcov -b randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
	
randomtestcard1.out: randomtestcard1 
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard1.c rngs.c -o randomtestcard1 -lm -g
	./randomtestcard1 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	gcov -b randomtestcard1.c >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out
	
randomtestcard2.out: randomtestcard2 
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard2.c rngs.c -o randomtestcard2 -lm -g
	./randomtestcard2 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	gcov -b randomtestcard2.c >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out
	
unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c -o unittest2 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c -o cardtest2 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c -o cardtest3 -lm -g
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c -o cardtest4 -lm -g
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomcardtest1 randomcardtest2

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe cardtest1 cardtest1.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe unittestresults.out randomtestadventurer randomtestadventurer.exe randomtestadventurer.out randomcardtest1 randomcardtest1.exe randomcardtest1.out randomcardtest2 randomcardtest2.exe randomcardtest2.out *.gcov *.gcda *.gcno *.so

cleanadventurer:
	rm -f *.o randomtestadventurer randomtestadventurer.exe randomtestadventurer.out randomDom.out*.gcov *.gcda *.gcno *.so
	
cleancard1:
	rm -f *.o randomtestcard1 randomtestcard1.exe randomtestcard1.out randomDom.out*.gcov *.gcda *.gcno *.so
	
cleancard2:
	rm -f *.o randomtestcard2 randomtestcard2.exe randomtestcard2.out randomDom.out*.gcov *.gcda *.gcno *.so
