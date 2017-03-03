CFLAGS = -Wall -fpic -coverage -lm

Lee=../leeeltDominion
Hat=../hatchimgDominion

all: playdom player testDrawCard testBuyCard badTestDrawCard

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

unittest1: dominion.o rngs.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o rngs.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o rngs.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o rngs.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: dominion.o rngs.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o rngs.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o rngs.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o rngs.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o rngs.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o rngs.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: dominion.o rngs.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

main_test=unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

unittestresults.out: ${main_test} 	
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo >> unittestresults.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> unittestresults.out
	grep "function getCost" dominion.c.gcov >> unittestresults.out
	grep "function drawCar" dominion.c.gcov >> unittestresults.out
	grep "function updateC" dominion.c.gcov >> unittestresults.out
	grep "function isGameO" dominion.c.gcov >> unittestresults.out
	grep "function playAdv" dominion.c.gcov >> unittestresults.out
	grep "function playSmi" dominion.c.gcov >> unittestresults.out
	grep "function playVil" dominion.c.gcov >> unittestresults.out
	sed -n 1133,1144p dominion.c.gcov >> unittestresults.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> unittestresults.out
	echo >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c
	cat dominion.c.gcov >> unittestresults.out

randomtestcard1.out: randomtestcard1
	./randomtestcard1 5 >> randomtestcard1.out
	echo >> randomtestcard1.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestcard1.out
	grep "function playVil" dominion.c.gcov >> randomtestcard1.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestcard1.out
	echo >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	echo >> randomtestcard1.out
	gcov dominion.c
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	./randomtestcard2 5 >> randomtestcard2.out
	echo >> randomtestcard2.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestcard2.out
	sed -n 1133,1144p dominion.c.gcov >> randomtestcard2.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestcard2.out
	echo >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	echo >> randomtestcard2.out
	gcov dominion.c
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer 5  >> randomtestadventurer.out
	echo >> randomtestadventurer.out
	gcov -b dominion.c 
	printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestadventurer.out
	grep "function playAdv" dominion.c.gcov >> randomtestadventurer.out
	printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestadventurer.out
	echo >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	echo >> randomtestadventurer.out
	gcov dominion.c
	cat dominion.c.gcov >> randomtestadventurer.out

random_tests: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

rngsLee.o: $(Lee)/rngs.h $(Lee)/rngs.c
	gcc -I$(Lee) -c $(Lee)/rngs.c -o $@ $(CFLAGS)

dominionLee.o: $(Lee)/dominion.h $(Lee)/dominion.c rngs.o
	gcc -I$(Lee) -c $(Lee)/dominion.c -o $@ $(CFLAGS)


unittest1Lee: dominionLee.o rngsLee.o unittest1.c
	gcc -o $@ unittest1.c dominionLee.o rngsLee.o $(CFLAGS)

unittest2Lee: dominionLee.o rngsLee.o unittest2.c
	gcc -o $@ unittest2.c dominionLee.o rngsLee.o $(CFLAGS)

unittest3Lee: dominionLee.o rngsLee.o unittest3.c
	gcc -o $@ unittest3.c dominionLee.o rngsLee.o $(CFLAGS)

unittest4Lee: dominionLee.o rngsLee.o unittest4.c
	gcc -o $@ unittest4.c dominionLee.o rngsLee.o $(CFLAGS)

cardtest1Lee: dominionLee.o rngsLee.o cardtest1.c
	gcc -o $@ cardtest1.c dominionLee.o rngsLee.o $(CFLAGS)

cardtest2Lee: dominionLee.o rngsLee.o cardtest2.c
	gcc -o $@ cardtest2.c dominionLee.o rngsLee.o $(CFLAGS)

cardtest3Lee: dominionLee.o rngsLee.o cardtest3.c
	gcc -o $@ cardtest3.c dominionLee.o rngsLee.o $(CFLAGS)

cardtest4Lee: dominionLee.o rngsLee.o cardtest4.c
	gcc -o $@ cardtest4.c dominionLee.o rngsLee.o $(CFLAGS)

randomtestcard1Lee: dominionLee.o rngsLee.o randomtestcard1.c
	gcc -o $@ randomtestcard1.c dominionLee.o rngsLee.o $(CFLAGS)

randomtestcard2Lee: dominionLee.o rngsLee.o randomtestcard2.c
	gcc -o $@ randomtestcard2.c dominionLee.o rngsLee.o $(CFLAGS)

randomtestadventurerLee: dominionLee.o rngsLee.o randomtestadventurer.c
	gcc -o $@ randomtestadventurer.c dominionLee.o rngsLee.o $(CFLAGS)

lee_test=unittest1Lee unittest2Lee unittest3Lee unittest4Lee cardtest1Lee cardtest2Lee cardtest3Lee cardtest4Lee
lee_results=unittestresults.Lee randomtestcard1.Lee randomtestcard2.Lee randomtestadventurer.Lee

unittestresults.Lee: ${lee_test}	
	./unittest1Lee >> unittestresults.Lee
	./unittest2Lee >> unittestresults.Lee
	./unittest3Lee >> unittestresults.Lee
	./unittest4Lee >> unittestresults.Lee
	./cardtest1Lee >> unittestresults.Lee
	./cardtest2Lee >> unittestresults.Lee
	./cardtest3Lee >> unittestresults.Lee
	./cardtest4Lee >> unittestresults.Lee
	-echo >> unittestresults.Lee
	-gcov -b dominionLee.o 
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> unittestresults.Lee
	-grep "function getCost" dominion.c.gcov >> unittestresults.Lee
	-grep "function drawCar" dominion.c.gcov >> unittestresults.Lee
	-grep "function updateC" dominion.c.gcov >> unittestresults.Lee
	-grep "function isGameO" dominion.c.gcov >> unittestresults.Lee
	-grep "function playAdv" dominion.c.gcov >> unittestresults.Lee
	-grep "function playSmi" dominion.c.gcov >> unittestresults.Lee
	-grep "function playVil" dominion.c.gcov >> unittestresults.Lee
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> unittestresults.Lee
	-echo >> unittestresults.Lee
	-cat dominion.c.gcov >> unittestresults.Lee
	-echo >> unittestresults.Lee
	-gcov dominionLee.o
	-cat dominion.c.gcov >> unittestresults.Lee

randomtestcard1.Lee: randomtestcard1Lee
	./randomtestcard1Lee 5 >> randomtestcard1.Lee
	-echo >> randomtestcard1.Lee
	-gcov -b dominionLee.o
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestcard1.Lee
	-grep "function playVil" dominion.c.gcov >> randomtestcard1.Lee
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestcard1.Lee
	-echo >> randomtestcard1.Lee
	-cat dominion.c.gcov >> randomtestcard1.Lee
	-echo >> randomtestcard1.Lee
	-gcov dominionLee.o
	-cat dominion.c.gcov >> randomtestcard1.Lee

randomtestcard2.Lee: randomtestcard2Lee
	./randomtestcard2Lee 5 >> randomtestcard2.Lee
	-echo >> randomtestcard2.Lee
	-gcov -b dominionLee.o
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestcard2.Lee
	-sed -n 1133,1144p dominion.c.gcov >> randomtestcard2.Lee
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestcard2.Lee
	-echo >> randomtestcard2.Lee
	-cat dominion.c.gcov >> randomtestcard2.Lee
	-echo >> randomtestcard2.Lee
	-gcov dominionLee.o
	-cat dominion.c.gcov >> randomtestcard2.Lee

randomtestadventurer.Lee: randomtestadventurerLee
	./randomtestadventurerLee 5  >> randomtestadventurer.Lee
	-echo >> randomtestadventurer.Lee
	-gcov -b dominionLee.o
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestadventurer.Lee
	-grep "function playAdv" dominion.c.gcov >> randomtestadventurer.Lee
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestadventurer.Lee
	-echo >> randomtestadventurer.Lee
	-cat dominion.c.gcov >> randomtestadventurer.Lee
	-echo >> randomtestadventurer.Lee
	-gcov dominionLee.o
	-cat dominion.c.gcov >> randomtestadventurer.Lee

random_tests_lee: randomtestcard1.Lee randomtestcard2.Lee randomtestadventurer.Lee

rngsHat.o: $(Hat)/rngs.h $(Hat)/rngs.c
	gcc -I$(Hat) -c $(Hat)/rngs.c -o $@ $(CFLAGS)

dominionHat.o: $(Hat)/dominion.h $(Hat)/dominion.c rngs.o
	gcc -I$(Hat) -c $(Hat)/dominion.c -o $@ $(CFLAGS)


unittest1Hat: dominionHat.o rngsHat.o unittest1.c
	gcc -o $@ unittest1.c dominionHat.o rngsHat.o $(CFLAGS)

unittest2Hat: dominionHat.o rngsHat.o unittest2.c
	gcc -o $@ unittest2.c dominionHat.o rngsHat.o $(CFLAGS)

unittest3Hat: dominionHat.o rngsHat.o unittest3.c
	gcc -o $@ unittest3.c dominionHat.o rngsHat.o $(CFLAGS)

unittest4Hat: dominionHat.o rngsHat.o unittest4.c
	gcc -o $@ unittest4.c dominionHat.o rngsHat.o $(CFLAGS)

cardtest1Hat: dominionHat.o rngsHat.o cardtest1.c
	gcc -o $@ cardtest1.c dominionHat.o rngsHat.o $(CFLAGS)

cardtest2Hat: dominionHat.o rngsHat.o cardtest2.c
	gcc -o $@ cardtest2.c dominionHat.o rngsHat.o $(CFLAGS)

cardtest3Hat: dominionHat.o rngsHat.o cardtest3.c
	gcc -o $@ cardtest3.c dominionHat.o rngsHat.o $(CFLAGS)

cardtest4Hat: dominionHat.o rngsHat.o cardtest4.c
	gcc -o $@ cardtest4.c dominionHat.o rngsHat.o $(CFLAGS)

randomtestcard1Hat: dominionHat.o rngsHat.o randomtestcard1.c
	gcc -o $@ randomtestcard1.c dominionHat.o rngsHat.o $(CFLAGS)

randomtestcard2Hat: dominionHat.o rngsHat.o randomtestcard2.c
	gcc -o $@ randomtestcard2.c dominionHat.o rngsHat.o $(CFLAGS)

randomtestadventurerHat: dominionHat.o rngsHat.o randomtestadventurer.c
	gcc -o $@ randomtestadventurer.c dominionHat.o rngsHat.o $(CFLAGS)

hat_test=unittest1Hat unittest2Hat unittest3Hat unittest4Hat cardtest1Hat cardtest2Hat cardtest3Hat cardtest4Hat
hat_results=unittestresults.Hat randomtestcard1.Hat randomtestcard2.Hat randomtestadventurer.Hat

unittestresults.Hat: ${hat_test}	
	./unittest1Hat >> unittestresults.Hat
	./unittest2Hat >> unittestresults.Hat
	./unittest3Hat >> unittestresults.Hat
	./unittest4Hat >> unittestresults.Hat
	./cardtest1Hat >> unittestresults.Hat
	./cardtest2Hat >> unittestresults.Hat
	./cardtest3Hat >> unittestresults.Hat
	./cardtest4Hat >> unittestresults.Hat
	-echo >> unittestresults.Hat
	-gcov -b dominionHat.o 
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> unittestresults.Hat
	-grep "function getCost" dominion.c.gcov >> unittestresults.Hat
	-grep "function drawCar" dominion.c.gcov >> unittestresults.Hat
	-grep "function updateC" dominion.c.gcov >> unittestresults.Hat
	-grep "function isGameO" dominion.c.gcov >> unittestresults.Hat
	-grep "function play_adv" dominion.c.gcov >> unittestresults.Hat
	-grep "function play_smi" dominion.c.gcov >> unittestresults.Hat
	-grep "function play_vil" dominion.c.gcov >> unittestresults.Hat
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> unittestresults.Hat
	-echo >> unittestresults.Hat
	-cat dominion.c.gcov >> unittestresults.Hat
	-echo >> unittestresults.Hat
	-gcov dominionHat.o
	-cat dominion.c.gcov >> unittestresults.Hat

randomtestcard1.Hat: randomtestcard1Hat
	./randomtestcard1Hat 5 >> randomtestcard1.Hat
	-echo >> randomtestcard1.Hat
	-gcov -b dominionHat.o
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestcard1.Hat
	-grep "function play_vil" dominion.c.gcov >> randomtestcard1.Hat
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestcard1.Hat
	-echo >> randomtestcard1.Hat
	-cat dominion.c.gcov >> randomtestcard1.Hat
	-echo >> randomtestcard1.Hat
	-gcov dominionHat.o
	-cat dominion.c.gcov >> randomtestcard1.Hat

randomtestcard2.Hat: randomtestcard2Hat
	./randomtestcard2Hat 5 >> randomtestcard2.Hat
	-echo >> randomtestcard2.Hat
	-gcov -b dominionHat.o
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestcard2.Hat
	-sed -n 1133,1144p dominion.c.gcov >> randomtestcard2.Hat
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestcard2.Hat
	-echo >> randomtestcard2.Hat
	-cat dominion.c.gcov >> randomtestcard2.Hat
	-echo >> randomtestcard2.Hat
	-gcov dominionHat.o
	-cat dominion.c.gcov >> randomtestcard2.Hat

randomtestadventurer.Hat: randomtestadventurerHat
	./randomtestadventurerHat 5  >> randomtestadventurer.Hat
	-echo >> randomtestadventurer.Hat
	-gcov -b dominionHat.o
	-printf "\n********************* COVERAGE SUMMARY ***********************\n" \
	  >> randomtestadventurer.Hat
	-grep "function play_adv" dominion.c.gcov >> randomtestadventurer.Hat
	-printf "********************* END SUMMARY ****************************\n\n" \
	  >> randomtestadventurer.Hat
	-echo >> randomtestadventurer.Hat
	-cat dominion.c.gcov >> randomtestadventurer.Hat
	-echo >> randomtestadventurer.Hat
	-gcov dominionHat.o
	-cat dominion.c.gcov >> randomtestadventurer.Hat

random_tests_hat: randomtestcard1.Hat randomtestcard2.Hat randomtestadventurer.Hat



player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

clean:
	rm -f *.o playdom test testDrawCard badTestDrawCard ${main_test} ${lee_test} ${lee_results} ${hat_test} ${hat_results} player testInit *.exe *.gcov *.gcda *.gcno *.so *.out randomtestcard1 randomtestcard2 randomtestadventurer
