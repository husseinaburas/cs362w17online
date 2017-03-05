#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int p = 0;
    int set_smithy = 0;
	int seed = 3000;
	int numPlayer = 2;
	int maxTreasureCount = 5;
    int maxDeckCount = 20;
    int startDeckCount = 5;
	int i, r, j, deckCount, range, expected_treasure;
	int treasureCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine
			, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 5;
	int testPassed = 1;
    int treasureSlots[MAX_DECK];

	int adventurers[MAX_HAND];
	for (i = 0; i < MAX_HAND; i++)
	{
		adventurers[i] = adventurer;
	}

	printf ("\nTESTING playAdventurer():\n");

    for (deckCount = startDeckCount; deckCount <= maxDeckCount; deckCount++)
    {
        for (treasureCount = 0; treasureCount <= deckCount; treasureCount++)
        {
            #if (NOISY_TEST == 1)
                printf("Test player %d with %d cards in deck and %d treasure card(s) in deck.\n", p, deckCount, treasureCount);
            #endif

            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
            G.deckCount[p] = deckCount;                 // set the number of cards in deck
            
            memcpy(G.hand[p], adventurers, sizeof(int) * 1); // set adventurer card as first card in hand

            // assign treasure cards at random points in the deck
            for (i = 0; i < treasureCount; i++)
            {
                treasureSlots[i] = rand() % deckCount;
            }

            for (i = 0; i < deckCount; i++)
            {
                set_smithy = 1;
                for (j = 0; j <= treasureCount; j++)
                {
                    if (treasureSlots[j] == i && treasureCount > 0)
                    {
                        G.deck[p][i] = silver; // set treasure card
                        set_smithy = 0;
                        break;
                    }
                }
                if (set_smithy == 1)
                {
                    G.deck[p][i] = smithy; // set abritrary non-treasure card
                }
            }

            playAdventurer(&G, 0);

            int adventurers_in_hand = 0;
            int treasures_in_deck = 0;
            for (i = 0; i <= G.deckCount[p]; i++)
            {   
                if (G.deck[p][i] == silver)
                {
                    treasures_in_deck++;
                }
                else if (G.hand[p][i] == adventurer)
                {
                    adventurers_in_hand++;
                }
            }

            if (treasureCount < 2)
            {
                expected_treasure = 0;
            }
            else
            {
                expected_treasure = treasureCount - 2;
            }

            #if (NOISY_TEST == 1)
                printf("Treasure cards in deck after playAdventurer() = %d, expected = %d\n", treasures_in_deck, expected_treasure);
            #endif

            #if (NOISY_TEST == 1)
                printf("Adventurers in hand = %d, expected = %d\n", adventurers_in_hand, 0);
            #endif

            if (treasures_in_deck == expected_treasure && adventurers_in_hand == 0)
            {
                // pass
            }
            else
            {
                // fail
                testPassed = 0;	
            }
        }
    }

	if (testPassed == 1)
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}

	return 0;
}
