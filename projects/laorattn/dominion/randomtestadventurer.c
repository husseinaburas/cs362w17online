// random test for dominion adventurer card
// cs362 Namtalay laorattanavech
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 10000

int main(int argc, char *argv[]) {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int i, j, r, players, current_player, seed;
	int errors = 0;
	int error1 = 0;
	int error2 = 0;
	int error3 = 0;
	int error4 = 0;
	int error5 = 0;
	int error6 = 0;
	struct gameState state;
	struct gameState temp;
	if (argv[1]==NULL){
		seed = time(NULL);
		printf("using seed by time: %d\n",seed);
	}
	else{
		seed = atoi(argv[1]);
		printf("using seed from agrument: %d\n",seed);
	}
	
	srand(seed);// get from argv
	
	printf("#######Start random test for adventurer card...#######\n");
	for (i = 0; i < MAX_TESTS; i++) {
		// random from 2-4 players
		players = (rand() % 3) + 2;

		//seed = rand();		
		initializeGame(players, k, seed, &state);	//initialize Gamestate

		current_player = (rand() % players)/*+1*/; 

		//Initiate states stuff
		state.whoseTurn = current_player;
		state.deckCount[current_player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
		state.discardCount[current_player] = rand() % MAX_DECK;
		state.handCount[current_player] = rand() % MAX_HAND;
		state.hand[current_player][0] = adventurer;
		state.numActions = rand() % 10; 
		
		int deckCount = state.deckCount[current_player];
		state.deck[current_player][deckCount-1] = smithy; //set first card picked up to be non-treasure to make sure that one card should be discarded
		memcpy(&temp, &state, sizeof(struct gameState)); //copy pre test to temp
		
		//use adventurer card
		r = cardEffect(adventurer, 0, 0, 0, &state, 0, 0);		
		assert (r == 0);
		
		//CHECK1: two first cards on hand are treasure cards
		int count = state.handCount[current_player];
		for (j=1; j<=2; j++){
			if (state.hand[current_player][count-j] != copper && state.hand[current_player][count-j] != silver && state.hand[current_player][count-j] != gold ){
				errors++; 
				error1++;
			}
		}
		//CHECK2: action stay the same
		if (state.numActions != (temp.numActions)) { 
			errors++; 
			error2++;
		}
		//CHECK3: hand count +2: 
		if( state.handCount[current_player] != temp.handCount[current_player]+2){
			errors++;
			error3++;
		}
		//CHECK other players
		for(j=1; j<players; j++){
			if(j!=current_player){
				//CHECK4: other players hand stay the same
				if(state.handCount[j] != temp.handCount[j]){
					errors++;
					error4++;
				}
				//CHECK5: other player deck stay the same
				if(state.deckCount[j] != temp.deckCount[j]){
					errors++;
					error5++;
				}
				//CHECK6: other player discard pile stay the same
				if(state.discardCount[j] != temp.discardCount[j]){
					errors++;
					error6++;
				}
			}
		}
		

	}	
	printf("Errors: %d\n", errors);
	printf("Error1: %d\n", error1);
	printf("Error2: %d\n", error2);
	printf("Error3: %d\n", error3);
	printf("Error4: %d\n", error4);
	printf("Error5: %d\n", error5);
	printf("Error6: %d\n", error6);
	printf("#######Finished random test for adventurer card.#######\n");
	return 0;
}