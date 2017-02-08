  
CFLAGS = -Wall -fpic -coverage -lm

all: playdom player testDrawCard testBuyCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f *.o test.exe test testInit testInit.exe  *.gcov *.gcda *.gcno *.so
	$(info ******** testing all *******)
  
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)
  $(info ******** compiling rngs.o *******)
  
dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	$(info ******** compiling dominion.o *******)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling playdom *******)
  
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling testDrawCard *******)
  
badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling badTestDrawCard *******)
  
testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling testBuyCard *******)
  
testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)
	$(info ******** compiling testAll *******)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)
	$(info ******** compiling interface.o *******)
  
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	$(info ******** compiling runtests *******)

unittest1: dominion.c unittest1.c rngs.c
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling unittest1 *******)
	
unittest2: dominion.c unittest2.c rngs.c
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling unittest2 *******)

unittest3: dominion.c unittest3.c rngs.c
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling unittest3 *******)

unittest4: dominion.c unittest4.c rngs.c
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling unittest4 *******)

cardtest1: dominion.c cardtest1.c rngs.c
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling cardtest1 *******)

cardtest2: dominion.c cardtest2.c rngs.c
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling cardtest2 *******)

cardtest3: dominion.c cardtest3.c rngs.c
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling cardtest3 *******)

cardtest4: cardtest4.c dominion.c rngs.c
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c $(CFLAGS)
	$(info ******** compiling cardtest4 *******)
						
rununittest: unittest1 unittest2 unittest3 unittest4
	echo "Results saved to rununittest.out" &> rununittest.out
	./unittest1 >> rununittest.out
	./unittest2 >> rununittest.out
	./unittest3 >> rununittest.out
	./unittest4 >> rununittest.out
	gcov -b dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "*****************************************" &> unittestresults.out	
	echo "Exececuting UNITTEST1" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./unittest1>> unittestresults.out
	echo " " >> unittestresults.out	
	echo "*****************************************" >> unittestresults.out	
	echo "Exececuting UNITTEST2" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./unittest2>> unittestresults.out
	echo " " >> unittestresults.out	
	echo "*****************************************" >> unittestresults.out	
	echo "Exececuting UNITEST3" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./unittest3>> unittestresults.out
	echo " " >> unittestresults.out	
	echo "*****************************************" >> unittestresults.out	
	echo "Exececuting UNITEST4" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./unittest4>> unittestresults.out
	echo " " >> unittestresults.out	
	echo "*****************************************" >> unittestresults.out	
	echo "Exececuting CARDTEST1" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./cardtest1>> unittestresults.out
	echo " " >> unittestresults.out	
	echo "*****************************************" >> unittestresults.out	
	echo "Exececuting CARDTEST2" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./cardtest2>> unittestresults.out
	echo " " >> unittestresults.out	
	echo "*****************************************" >> unittestresults.out	
	echo "Exececuting CARDTEST3" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./cardtest3 >> unittestresults.out
	echo " " >> unittestresults.out	
	echo "*****************************************" >> unittestresults.out	
	echo "Exececuting CARDTEST4" >> unittestresults.out
	echo "*****************************************" >> unittestresults.out	
	./cardtest4 >> unittestresults.out
	echo " " >> unittestresults.out		
	echo "************************************************************" >> unittestresults.out	
	echo "Exececuting combined unit test coverage stats for dominion.c" >> unittestresults.out	
	echo "************************************************************" >> unittestresults.out	
	gcov -b dominion >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	$(info ******** compiling player *******)

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
	$(info ******** clean2 is on *******)
