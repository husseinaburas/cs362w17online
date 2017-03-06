#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "adventurer"

int main(){
	int i, j, r;
	int newTreasure = 2, discardedCard = 1;
	int handPos = 0;
	int seed = 1000;
	int numPlayers = 2;
	int player1 = 0, player2 = 1;
	int testTreasureCount, expTreasureCount;
	int drawnTreasure = 0;
	int tempHand[MAX_HAND];
	int cardDrawn = -1;
	int z = 0;
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
	g.hand[player1][handPos] = adventurer;
	memcpy(&test_g, &g, sizeof(struct gameState));
	
	/* Must update function call due to different implementation
	r = playAdventurer(&test_g); */
	
	// Updated call based on group member's code:
	r = adventurerCard(&test_g, drawnTreasure, player1, tempHand, cardDrawn, z);
	
	// Did the function work (should return 0)?
	asserttrue("returned 0 as expected", r, 0);
	
	// Did current player receive 2 new cards and discard the played adventurer card?
	asserttrue("current player's hand", test_g.handCount[player1], g.handCount[player1] + newTreasure - discardedCard);
	// Did current player receive 2 treasure cards?
	testTreasureCount = treasure_in_hand(&test_g, player1);
	expTreasureCount = treasure_in_hand(&g, player1);
	asserttrue("current player treasure cards", testTreasureCount, expTreasureCount + newTreasure);
	// Did current player discard adventurer card to the played pile?
	asserttrue("played card count", test_g.playedCardCount, g.playedCardCount + discardedCard);
	// Is the last played card a adventurer card?
	if(test_g.playedCardCount > 0)
		asserttrue("last played card", test_g.playedCards[test_g.playedCardCount-1], adventurer);
	else
		asserttrue("last played card", -1, adventurer);
	
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
