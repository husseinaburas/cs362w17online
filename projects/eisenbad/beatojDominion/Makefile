CFLAGS = -Wall -fprofile-arcs -ftest-coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

betterTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o betterTestDrawCard -g  betterTestDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)
	
eisenbad_randomtestadventurer.out: eisenbad_randomtestadventurer.c eisenbad_randtestfuncs.c dominion.o rngs.o
	gcc -o eisenbad_randomtestadventurer -g eisenbad_randomtestadventurer.c eisenbad_randtestfuncs.c dominion.o rngs.o $(CFLAGS)

eisenbad_randomtestcard1.out: eisenbad_randomtestcard1.c eisenbad_randtestfuncs.c dominion.o rngs.o
	gcc -o eisenbad_randomtestcard1 -g eisenbad_randomtestcard1.c eisenbad_randtestfuncs.c dominion.o rngs.o $(CFLAGS)

eisenbad_randomtestcard2.out: eisenbad_randomtestcard2.c eisenbad_randtestfuncs.c dominion.o rngs.o
	gcc -o eisenbad_randomtestcard2 -g eisenbad_randomtestcard2.c eisenbad_randtestfuncs.c dominion.o rngs.o $(CFLAGS)
	
eisenbad_randomtestresults.out: eisenbad_randomtestadventurer.c eisenbad_randomtestcard1.c eisenbad_randomtestcard2.c eisenbad_randtestfuncs.c dominion.o rngs.o
	gcc -o eisenbad_randomtestadventurer -g eisenbad_randomtestadventurer.c eisenbad_randtestfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_randomtestcard1 -g eisenbad_randomtestcard1.c eisenbad_randtestfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_randomtestcard2 -g eisenbad_randomtestcard2.c eisenbad_randtestfuncs.c dominion.o rngs.o $(CFLAGS)
	
	./eisenbad_randomtestadventurer 192 > eisenbad_randomtestresults.out
	./eisenbad_randomtestcard1 132 >> eisenbad_randomtestresults.out
	./eisenbad_randomtestcard2 30 >> eisenbad_randomtestresults.out
	echo --------------------- eisenbad_randomtestadventurer.c gcov results ------------------ >> eisenbad_randomtestresults.out
	gcov -b -f eisenbad_randomtestadventurer.c >> eisenbad_randomtestresults.out
	echo --------------------- eisenbad_randomtestcard1.c gcov results ------------------ >> eisenbad_randomtestresults.out
	gcov -b -f eisenbad_randomtestcard1.c >> eisenbad_randomtestresults.out
	echo --------------------- eisenbad_randomtestcard2.c gcov results ------------------ >> eisenbad_randomtestresults.out
	gcov -b -f eisenbad_randomtestcard2.c >> eisenbad_randomtestresults.out
	echo ------------------- dominion.c gcov results ------------------ >> eisenbad_randomtestresults.out
	gcov -b -f dominion.c >> eisenbad_randomtestresults.out
	echo ------------------- dominion.c.gcov ------------------ >> eisenbad_randomtestresults.out
	cat dominion.c.gcov >> eisenbad_randomtestresults.out  

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

unittests: eisenbad_unittest1.c eisenbad_unittest2.c eisenbad_unittest3.c eisenbad_unittest4.c eisenbad_testfuncs.c dominion.o rngs.o
	gcc -o eisenbad_unittest1 -g eisenbad_unittest1.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_unittest2 -g eisenbad_unittest2.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_unittest3 -g eisenbad_unittest3.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_unittest4 -g eisenbad_unittest4.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)

cardtests: eisenbad_cardtest1.c eisenbad_cardtest2.c eisenbad_cardtest3.c eisenbad_cardtest4.c eisenbad_testfuncs.c dominion.o rngs.o
	gcc -o eisenbad_cardtest1 -g eisenbad_cardtest1.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_cardtest2 -g eisenbad_cardtest2.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_cardtest3 -g eisenbad_cardtest3.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)
	gcc -o eisenbad_cardtest4 -g eisenbad_cardtest4.c eisenbad_testfuncs.c dominion.o rngs.o $(CFLAGS)

eisenbad_unittestresults.out: unittests cardtests dominion.o
	./eisenbad_cardtest1 > eisenbad_unittestresults.out
	./eisenbad_cardtest2 >> eisenbad_unittestresults.out
	./eisenbad_cardtest3 >> eisenbad_unittestresults.out
	./eisenbad_cardtest4 >> eisenbad_unittestresults.out
	./eisenbad_unittest1 >> eisenbad_unittestresults.out
	./eisenbad_unittest2 >> eisenbad_unittestresults.out
	./eisenbad_unittest3 >> eisenbad_unittestresults.out
	./eisenbad_unittest4 >> eisenbad_unittestresults.out
	echo --------------------- eisenbad_cardtest1.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_cardtest1.c >> eisenbad_unittestresults.out
	echo ------------------- eisenbad_cardtest2.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_cardtest2.c >> eisenbad_unittestresults.out
	echo ------------------- eisenbad_cardtest3.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_cardtest3.c >> eisenbad_unittestresults.out
	echo ------------------- eisenbad_cardtest4.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_cardtest4.c >> eisenbad_unittestresults.out
	echo ------------------- eisenbad_unittest1.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_unittest1.c >> eisenbad_unittestresults.out
	echo ------------------- eisenbad_unittest2.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_unittest2.c >> eisenbad_unittestresults.out
	echo ------------------- eisenbad_unittest3.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_unittest3.c >> eisenbad_unittestresults.out
	echo ------------------- eisenbad_unittest4.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f eisenbad_unittest4.c >> eisenbad_unittestresults.out
	echo ------------------- dominion.c gcov results ------------------ >> eisenbad_unittestresults.out
	gcov -b -f dominion.c >> eisenbad_unittestresults.out
	echo ------------------- dominion.c.gcov ------------------ >> eisenbad_unittestresults.out
	cat dominion.c.gcov >> eisenbad_unittestresults.out  

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out

clean:
	rm -f *.o *.c~ *~ eisenbad_unittest1 eisenbad_unittest2 eisenbad_unittest3 eisenbad_unittest4 eisenbad_cardtest1 eisenbad_cardtest2 eisenbad_cardtest3 eisenbad_cardtest4 
	rm -f badTestDrawCard betterTestDrawCard testDrawCard playdom.exe playdom test.exe test player player.exe
	rm -f testInit testInit.exe *.gcov *.gcda *.gcno *.so
	rm -f eisenbad_randomtestadventurer eisenbad_randomtestcard1 eisenbad_randomtestcard2
