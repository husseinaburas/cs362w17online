#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "village"

int main(){
	int i, j, r;
	int addedCard = 1, discardedCard = 1;
	int addedActions = 2;
	int handPos = 0;
	int seed = 1000;
	int numPlayers = 2;
	int player1 = 0, player2 = 1;
	struct gameState g, test_g;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			smithy, village, baron, great_hall};
	char* victory[3] = {"estate", "duchy", "province"};
	char* kingdom[20] = {"adventurer", "council_room", "feast", "gardens", "mine", 
			"remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", 
			"tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", 
			"sea_hag", "treasure_map"};
	
	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);
	// Initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &g);
	// Give current player a village card to play
	g.hand[player1][handPos] = village;
	memcpy(&test_g, &g, sizeof(struct gameState));
	r = playVillage(&test_g, handPos);
	
	// Did the function work (should return 0)?
	asserttrue("returned 0 as expected", r, 0);
	
	// Did current player receive the correct effects from the card?
	// Did current player receive 1 new card and discard the played card?
	asserttrue("current player hand count", test_g.handCount[player1], g.handCount[player1] + addedCard - discardedCard);
	// Did current player receive 2 additional actions?
	asserttrue("actions count", test_g.numActions, g.numActions + addedActions);
	// Did current player discard card to the played pile?
	asserttrue("played card count", test_g.playedCardCount, g.playedCardCount + discardedCard);
	// Is top card in played pile a village?
	if(test_g.playedCardCount > 0)
		asserttrue("last played card", test_g.playedCards[test_g.playedCardCount-1], village);
	else
		asserttrue("last played card", -1, village);
	
	// Did any other players experience a state change?
	asserttrue("non-current player hand count", test_g.handCount[player2], g.handCount[player2]);
	asserttrue("non-current player deck count", test_g.deckCount[player2], g.deckCount[player2]);
	asserttrue("non-current player discard count", test_g.discardCount[player2], g.discardCount[player2]);
	
	// Did victory card piles experience a state change?
	j = 0;
	for(i = estate; i <= province; i++){
		asserttrue(victory[j], test_g.supplyCount[i], g.supplyCount[i]);
		j++;
	}
	
	// Did kingdom card piles experience a state change?
	j = 0;
	for(i = adventurer; i <= treasure_map; i++){
		asserttrue(kingdom[j], test_g.supplyCount[i], g.supplyCount[i]);
		j++;
	}
	
	printf("--------------- Completed Card: %s ---------------\n", TESTCARD);
	return 0;
}