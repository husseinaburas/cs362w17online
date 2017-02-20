#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "assert_custom.h"
#include "string.h"

#define TEST_RUNS 10

int testCardVillage(struct gameState *G, struct gameState *copyG, int player, int handPos) {
   
   // test player hand card count does not increase
   int hCntDiff = G->handCount[player] - copyG->handCount[player];
   assert_custom(hCntDiff == 0, "test handCount does not increase");

   // test deckCount decrease
    int deckCntDiff = G->deckCount[player] - copyG->deckCount[player];
   assert_custom(deckCntDiff < 0, "test deckCount decreased");
   assert_custom(deckCntDiff == -1, "test deckCount decrease by 1 card");

   // test numActions increase by 2
   int numActDiff = G->numActions - copyG->numActions;
   assert_custom(numActDiff > 0, "test numActions increases");
   assert_custom(numActDiff == 2, "test numActions increases by 2");

   // test discardCount increase
   int disCntDiff = G->discardCount[player] - copyG->discardCount[player];
   assert_custom(disCntDiff > 0, "test discardCount increase");
   assert_custom(disCntDiff == 1, "test discardCount increase by 1 card");

   // test playedCardCount increase
   int playedCardDiff = G->playedCardCount - copyG->playedCardCount;
   assert_custom(playedCardDiff > 0, "test playedCardCount increase");
   assert_custom(playedCardDiff == 1, "test playedCardCount increase by 1 card");

   // test village removed from hand
   assert_custom(G->hand[player][handPos] != village, "test village is removed from hand");

  return 0;
}

int main (int argc, char *argv[]) {
    
    int seed = 738;
    
    if (argv[1] == NULL)
    {
        seed = 738;
        printf("No argument passed, seed set to: %i\n", seed);
    } else {
        seed = atoi(argv[1]);
        printf("Seed set to: %i\n", seed);
    }
    
    // seed random number generator
    srand(seed);
    
    struct gameState G, copyG;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    int p = 0, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    int i = 0;
    for(i = 0; i < TEST_RUNS; i++)
    {
        printf("---------------- Village Card Test Run# %i ----------------\n", i);
        
        // Generate randomly between 2 and 4 players
        p = (rand() % 3) + 2;
        initializeGame(p, k, seed, &G);
        printf("number of players: %i\n", p);
        
        // Randomly choose a player to play card
        int player = rand() % p;
        G.whoseTurn = player;
        printf("whoseTurn: %i\n", G.whoseTurn);
        printf("player: %i\n", player);
        
        // Radomly choose hand position of card
        int handCt = G.handCount[player];
        if( handCt < 1 )
        {
            handPos = 0;
        } else {
            handPos = rand() % handCt;
        }
        printf("handPos: %i\n", handPos);
        
        // place card in player hand
        G.hand[player][handPos] = village;
        
        // confirm village card is in hand
        assert_custom(G.hand[player][handPos] == village, "test village card is in hand");
        
        // randomly generate the number of cards deck available to player
        G.deckCount[player] = rand() % (MAX_DECK + 1);
        printf("deckCount: %i\n", G.deckCount[player]);
        
        // save initial state
        memcpy(&copyG, &G, sizeof(struct gameState));
        
        cardEffect(village, choice1, choice2, choice3, &G, handPos, &bonus);
        
        // run testCard function comparing initial game state to game state after playing card
        testCardVillage(&G, &copyG, player, handPos);
        
        printf("---------------- End of Village Card Test Run# %i ----------------\n", i);
    }

    return 0;
}
