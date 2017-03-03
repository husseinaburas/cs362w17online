/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define ASSERT_M(exp, MSG) if(!exp) {printf("%s: FAILED!\n", MSG); error = 1;}
#define ASSERT(exp) if(!exp) {printf("Test FAILED!\n"); error = 1;}
int error=0;

int checkAdventurer(struct gameState *post, int currentPlayer, int drawntreasure) {

int temphand[MAX_HAND];
int z = 0;// this is the counter for the temp hand	
int cardDrawn, saved_dt;   
struct gameState pre;

		 
    memcpy (&pre, post, sizeof(struct gameState));
	saved_dt = drawntreasure;
	
#if 1
	while(drawntreasure<2){
		if (pre.deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, &pre);
		  }
 	  
		drawCard(currentPlayer, &pre);
		cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer] - 1];//?? //top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else{
			temphand[z]=cardDrawn;
			pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		 }
     }
	 
       
	while(z-1>=0){
		pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
      }	

#endif

    playAdventurer(currentPlayer, post, saved_dt);

#if  1
    //ASSERT_M(( memcmp(&pre, post, sizeof(struct gameState)) == 0), "adventurer error!"  );
	//check certain aspects of the game state....
	for(z=0; z < MAX_HAND; z++){
		
		ASSERT_M( (pre.hand[currentPlayer][z] == post->hand[currentPlayer][z]), "adventurer hand error!");
		if(error) printf("pre: %d; post: %d\n",pre.hand[currentPlayer][z], post->hand[currentPlayer][z]);
		error=0;
	}
	
	ASSERT_M( (pre.handCount[currentPlayer] == post->handCount[currentPlayer]), "adventurer hand count error!");
	if(error) printf("pre handCount: %d; post handCount: %d\n",pre.handCount[currentPlayer], post->handCount[currentPlayer]);
	error=0;
	
	for(z=0; z < MAX_DECK; z++){
		ASSERT_M( (pre.discard[currentPlayer][z] == post->discard[currentPlayer][z]), "adventurer discard error!");
		if(error) printf("pre discard: %d; post discard: %d\n",pre.discard[currentPlayer][z], post->discard[currentPlayer][z]);
		error=0;
		
		ASSERT_M( (pre.deck[currentPlayer][z] == post->deck[currentPlayer][z]), "adventurer deck error!");
		if(error) printf("pre deck: %d; post deck: %d\n",pre.deck[currentPlayer][z], post->deck[currentPlayer][z]);
		error=0;
	}
	
	ASSERT_M( (pre.deckCount[currentPlayer] == post->deckCount[currentPlayer]), "adventurer deck count error!");	
	if(error) printf("pre deckCount: %d; post deckCount: %d\n",pre.deckCount[currentPlayer], post->deckCount[currentPlayer]);
	error=0;
	
	ASSERT_M( (pre.discardCount[currentPlayer] == post->discardCount[currentPlayer]), "adventurer discardCount count error!");	
	if(error) printf("pre discardCount: %d; post discardCount: %d\n",pre.discardCount[currentPlayer], post->discardCount[currentPlayer]);	
#endif	
}

int main(int argc, char *argv[]) {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int drawntreasure = 2;
	struct gameState G, pre;
	//int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	//		sea_hag, tribute, smithy, council_room};

    int tcc_hand, tcc_deck, tcc_discard, tcc_total;	//tcc = treasure card count	
	int NUMCARDS = 27;
	int NUMCARDS_IN_PLAY = 17;
	int TOT_KCARDS = 20;
	int KCARD_FIRSTINDEX = adventurer;
	int MAX_KCARDS = 10;
	int MIN_STARTING_CARDS = 2;
	int MAX_STARTING_CARDS = 15;
	int k[MAX_KCARDS];					// array storing 10 cards to use in a single game
	int NUMTREASURECARDS = 3;
	int TREASURE_FIRSTINDEX = copper;
	
	// declare random test variables
	int rand_kcard[MAX_KCARDS];			// adventurer and 9 other randomly selected kingdom cards
	int rand_numhandcards;				// starting number of cards in hand from 2 to 10
	int rand_numdeckcards;				// starting number of cards in deck from 2 to 10
	int rand_numdiscards;				// starting number of cards in discard from 2 to 10
	int rand_thiscard;					// 1 of 17 cardtypes in play (1 curse, 3 victory 3 treasure, 10 kingdom)
	int rand_isTreasure;				// boolean determining whether a card is a Treasure card

	int cardtype[NUMCARDS];				// counts of each card type in deck and discard (potential discards)			
			
			

	SelectStream(2);
	if (argc < 2){
		printf("use case: randomtestcard1 <seed> \n");
		exit(1);
	}
	
	PutSeed(atoi(argv[1]));
    
    printf("-----------------Random Testing Card: %s ----------------\n", TESTCARD);	
	for (m =0; m<2000; m++){
//		for(i =0; i < sizeof(struct gameState); i++){
//			((char*) &G)[i] = floor(Random() * 256);
//		}

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
//borrowed from professor's assignment 4 solution in git -- begin

		//		establish number of cards in hand from 2 to 10
		rand_numhandcards = (rand() % (MAX_STARTING_CARDS - MIN_STARTING_CARDS + 1)) + MIN_STARTING_CARDS;
		//printf("\tstarting cards in hand: %d\n", rand_numhandcards);
		G.handCount[thisPlayer] = rand_numhandcards;
		G.hand[thisPlayer][0] = adventurer;

		//		establish number of cards in deck from 2 to 10
		rand_numdeckcards = (rand() % (MAX_STARTING_CARDS - MIN_STARTING_CARDS + 1)) + MIN_STARTING_CARDS;
		//printf("\tstarting cards in deck: %d\n", rand_numdeckcards);
		G.deckCount[thisPlayer] = rand_numdeckcards;

		//		establish number of cards in discard from 2 to 10
		rand_numdiscards = (rand() % (MAX_STARTING_CARDS - MIN_STARTING_CARDS + 1)) + MIN_STARTING_CARDS;
		//printf("\tstarting cards in discard: %d\n", rand_numdiscards);
		G.discardCount[thisPlayer] = rand_numdiscards;

		//		establish each card
		//			cards in hand
		G.hand[thisPlayer][0] = adventurer;
		for (i=1; i<rand_numhandcards; i++) {
			rand_isTreasure = rand() % 2;
			if (rand_isTreasure) {
				G.hand[thisPlayer][i] = (rand() % NUMTREASURECARDS) + TREASURE_FIRSTINDEX;
				tcc_hand++;
			}
			else {
				rand_thiscard = rand() % (NUMCARDS_IN_PLAY - NUMTREASURECARDS);
				if (rand_thiscard < TREASURE_FIRSTINDEX)
					G.hand[thisPlayer][i] = rand_thiscard;
				else {
					G.hand[thisPlayer][i] = k[rand_thiscard - TREASURE_FIRSTINDEX];
				}
			}
		}

		//			cards in deck
		for (i=0; i<rand_numdeckcards; i++) {
			rand_isTreasure = rand() % 2;
			if (rand_isTreasure) {
				G.deck[thisPlayer][i] = (rand() % NUMTREASURECARDS) + TREASURE_FIRSTINDEX;
				tcc_deck++;
			}
			else {
				rand_thiscard = rand() % (NUMCARDS_IN_PLAY - NUMTREASURECARDS);
				if (rand_thiscard < TREASURE_FIRSTINDEX)
					G.deck[thisPlayer][i] = rand_thiscard;
				else
					G.deck[thisPlayer][i] = k[rand_thiscard - TREASURE_FIRSTINDEX];
			}
		}
		for (i=0; i<rand_numdeckcards; i++) cardtype[G.deck[thisPlayer][i]]++;
		//for (i=0; i<rand_numdeckcards; i++) printf("\t\tdeckcard[%d] = %s\n", i, card[G.deck[thisPlayer][i]]);

		//			cards in discard
		for (i=0; i<rand_numdiscards; i++) {
			rand_isTreasure = rand() % 2;
			if (rand_isTreasure) {
				G.discard[thisPlayer][i] = (rand() % NUMTREASURECARDS) + TREASURE_FIRSTINDEX;
				tcc_discard++;
			}
			else {
				rand_thiscard = rand() % (NUMCARDS_IN_PLAY - NUMTREASURECARDS);
				if (rand_thiscard < TREASURE_FIRSTINDEX)
					G.discard[thisPlayer][i] = rand_thiscard;
				else
					G.discard[thisPlayer][i] = k[rand_thiscard - TREASURE_FIRSTINDEX];
			}
		}
		for (i=0; i<rand_numdiscards; i++) cardtype[G.discard[thisPlayer][i]]++;
//borrowed from professor's assignment 4 solution in git -- end		
		
//		thisPlayer = floor(Random() * (MAX_PLAYERS-1));
//		G.deckCount[thisPlayer] = floor(Random() * (MAX_DECK-1));
//		G.discardCount[thisPlayer] = floor(Random() * (MAX_DECK-1));
//		G.handCount[thisPlayer] = floor(Random() * (MAX_HAND-1));
//		G.playedCardCount = floor(Random() * (MAX_DECK-1));
//			
//		for(j=0; j< MAX_HAND; j++)
//			G.hand[thisPlayer][j] = 4 + floor(Random() * 2);


	printf("Random TEST case [%d]\n", m);
	
	// case of drawntreasure ==2
	drawntreasure = 0 + floor(Random() * 2);
	checkAdventurer(&G, thisPlayer, drawntreasure);
	}

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


