###########################################################
##### Added to CFLAGS to enable gcov coverage testing #####
###########################################################

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








#####################################################################################
####### Compile Each unit test and include the asserttrue assertion helper file	#####
##### 		The -fprofile-arcs -ftest-coverage flags tell the compiler to 	#####
#####		generate the additional files needed by gcov 			#####
#####################################################################################

	### Compile Unit Tests for Non Card Methods and create necessary gcov files ###
unittest1: dominion.o rngs.o unittest1.c
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)
unittest2: dominion.o rngs.o unittest2.c
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)
unittest3: dominion.o rngs.o unittest3.c
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)
unittest4: dominion.o rngs.o unittest4.c
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)
	
	### Compile Unit Tests for Card Methods and create necessary gcov files ###
cardtest1: dominion.o rngs.o cardtest1.c
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)
cardtest2: dominion.o rngs.o cardtest2.c
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)
cardtest3: dominion.o rngs.o cardtest3.c
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)
cardtest4: dominion.o rngs.o cardtest4.c
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o -fprofile-arcs -ftest-coverage $(CFLAGS)

#######################################################################################
###### Call ‘make unittestresults.out’ to run all of the following indented code ######
#######################################################################################
unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	
	###### Run the Executables created above to both output results to unittestresults.out file 
	#	AND ALSO to have gcov output coverage results to a .gcda file (will be created if 
	#	doesn’t exist or add it’s results to previous runs in a pre-existing .gcda file)

	rm -f dominion.c.gcov dominion.gcda

	./unittest1 > unittestresults.out	# Output unittest1 print statements to a new unittestresults.out file
	gcov --branch-probabilities --function-summaries unittest1.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  
	rm -f dominion.c.gcov dominion.gcda
	echo \n\n******** END OF CODE COVERAGE FOR UNIT TEST Method 1 ********\n\n >> unittestresults.out


	./unittest2 >> unittestresults.out	# Append unittest2 print statements to an existing unittestresults.out file
	gcov --branch-probabilities --function-summaries unittest2.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  
	rm -f dominion.c.gcov dominion.gcda	
	echo \n\n******** END OF CODE COVERAGE FOR UNIT TEST Method 2 ********\n\n >> unittestresults.out


	./unittest3 >> unittestresults.out	# Append unittest3 print statements to an existing unittestresults.out file
	gcov --branch-probabilities --function-summaries unittest3.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  
	rm -f dominion.c.gcov dominion.gcda
	echo --\n\n******** END OF CODE COVERAGE FOR UNIT TEST Method 3 ********\n\n >> unittestresults.out

	./unittest4 >> unittestresults.out	# Append unittest4 print statements to an existing unittestresults.out file	
	gcov --branch-probabilities --function-summaries unittest4.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  	
	rm -f dominion.c.gcov dominion.gcda
	echo --\n\n******** END OF CODE COVERAGE FOR UNIT TEST Method 4 ********\n\n >> unittestresults.out

	./cardtest1 >> unittestresults.out	# Append cardtest1 print statements to an existing unittestresults.out file	
	gcov --branch-probabilities --function-summaries cardtest1.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  
	rm -f dominion.c.gcov dominion.gcda
	echo --\n\n******** END OF CODE COVERAGE FOR UNIT TEST CARD 1 ********\n\n >> unittestresults.out

	./cardtest2 >> unittestresults.out	# Append cardtest2 print statements to an existing unittestresults.out file
	gcov --branch-probabilities --function-summaries cardtest2.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  
	rm -f dominion.c.gcov dominion.gcda
	echo --\n\n******** END OF CODE COVERAGE FOR UNIT TEST CARD 2 ********\n\n >> unittestresults.out

	./cardtest3 >> unittestresults.out	# Append cardtest3 print statements to an existing unittestresults.out file
	gcov --branch-probabilities --function-summaries cardtest3.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  
	rm -f dominion.c.gcov dominion.gcda	
	echo --\n\n******** END OF CODE COVERAGE FOR UNIT TEST CARD 3 ********\n\n >> unittestresults.out


	./cardtest4 >> unittestresults.out	# Append cardtest4 print statements to an existing unittestresults.out file
	gcov --branch-probabilities --function-summaries cardtest4.c >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out		# Outputs the Summary of the gcov
	cat dominion.c.gcov >> unittestresults.out  

	echo \n\n******** END OF CODE COVERAGE FOR UNIT TEST CARD 4 ********\n\n >> unittestresults.out



	###### Run gcov and output results to the existing unittestresults.out file  
	#	AND ALSO include branch frequencies to the output file as well as branch summary info using the --branch-probabilities flag
	#	AND ALSO include output summaries for each function (in addition to the file level summary) using the --function-summaries flag














all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out 