#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "council room"

int main(){
	int i, j, r;
	int currentAddedCard = 4, otherAddedCard = 1, discardedCard = 1;
	int addedBuy = 1;
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
	g.hand[player1][handPos] = council_room;
	memcpy(&test_g, &g, sizeof(struct gameState));
	
	/* Must update function call due to different implementation
	r = playCouncil_Room(&test_g, handPos); */
	
	// Updated call based on original Dominion code:
	// Used 0 for choices and bonus because variables not used for this card.
	r = cardEffect(council_room, 0, 0, 0, &test_g, handPos, 0);
	
	// Did the function work (should return 0)?
	asserttrue("returned 0 as expected", r, 0);
	
	// Did current player receive the correct effects from the card?
	// Did current player receive 4 additional cards and discard the played card?
	asserttrue("current player hand count", test_g.handCount[player1], g.handCount[player1] + currentAddedCard - discardedCard);
	// Did other players receive 1 additional card?
	asserttrue("other player hand count", test_g.handCount[player2], g.handCount[player2] + otherAddedCard);
	// Did the 1 additional card come from the other player's deck?
	asserttrue("other player deck count", test_g.deckCount[player2], g.deckCount[player2] - otherAddedCard);
	// Was one buy correctly added to total buys?
	asserttrue("total buy count", test_g.numBuys, g.numBuys + addedBuy);
	// Did current player discard council room card to the played pile?
	asserttrue("played card count", test_g.playedCardCount, g.playedCardCount + discardedCard);
	// Is the last played card a council room card?
	if(test_g.playedCardCount > 0)
		asserttrue("last played card", test_g.playedCards[test_g.playedCardCount-1], council_room);
	else
		asserttrue("last played card", -1, council_room);

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