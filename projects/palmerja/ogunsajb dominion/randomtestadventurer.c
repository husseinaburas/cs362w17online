#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {
    struct gameState G;
    int seed = 1000;
    int numPlayers = 2;
    int curPlayer = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};  
    int deckSize;
    int handSize;
    int i;
    int j;
    int q;
    int randomCard;
    int randK;
    int m;
    int coinCount;
    int x;
    int discardCopper;
    int discardSilver;
    int discardGold;
    int coinCountBefore;
    int testPassed = 0;
    int drawTestFailed = 0;
    int discardTestFailed = 0;
	int handBefore;
	int handAfter;
	int handFailure = 0;
	int discardBefore;
	int discardAfter;
	int discardFailure = 0;
	int deckBefore;
	int deckAfter;
    
    srand(time(NULL));
   //randomize hand size
    for(i = 0; i < 1000000; i++){
        initializeGame(numPlayers, k, seed, &G);
        coinCountBefore = 0;
        deckSize = rand() % (MAX_DECK + 1);
   //set handsize
        handSize = rand() % (deckSize + 1);
      
        
        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
        
       
        
        for (j = 0; j < numPlayers; j++){
            for(q = 0;q < G.deckCount[j]; q++){
                randomCard = rand() % (50 + 1);
                randK = rand() % (10);
                if(randomCard == 1){
                    G.deck[j][q] = copper;
                } else if(randomCard == 2){
                    G.deck[j][q] = silver;
                }else if(randomCard == 3){
                    G.deck[j][q] = gold;
                }else {
                    G.deck[j][q] = k[randK];
                }
            }
        } 
        
        for(m = 0; m < G.handCount[curPlayer]; m++){
            if(G.hand[curPlayer][m] == copper || G.hand[curPlayer][m] == silver || G.hand[curPlayer][m] == gold){
                coinCountBefore++;
            }
        }
        //printf("Coin Count before: %d\n", coinCount);
        //printf("discard count before: %d\n", G.discardCount[curPlayer]);
        //printf("deckSize: %d, deck: %d, and hand: %d\n", deckSize, G.deckCount[0], G.handCount[0]); 
        adventurerEffect(curPlayer, &G);  

		deckBefore = G.deckCount[0];
		//printf("deck before %d\n", deckBefore);
		handBefore = G.handCount[0];
		//printf("Hand before %d\n",handBefore);
		discardBefore = G.playedCardCount;
		//printf("Discard before %d\n", discardBefore);

		deckAfter = G.deckCount[0];
		//printf("deck after %d\n", deckAfter);
		handAfter = G.handCount[0];
		//printf("hand After %d\n", handAfter);
		discardAfter = G.playedCardCount;
		//printf("Discard After %d\n\n", discardAfter);


        
        coinCount = 0;
        
        for(m = 0; m < G.handCount[curPlayer]; m++){
            if(G.hand[curPlayer][m] == copper || G.hand[curPlayer][m] == silver || G.hand[curPlayer][m] == gold){
                coinCount++;
            }
        }
        //printf("Coin Count after: %d\n", coinCount);
        //printf("discard count after: %d\n", G.discardCount[curPlayer]);
        discardCopper = 0;
        discardSilver = 0;
        discardGold = 0;
        for(x = 0; x < G.discardCount[curPlayer]; x++){
            if(G.discard[curPlayer][x] == copper) {
                discardCopper++;
            } else if(G.discard[curPlayer][x] == silver) {
                discardSilver++;
            } else if(G.discard[curPlayer][x] == gold) {
                discardGold++;
            }
        }
        int passed = 1;
        if(coinCount > (coinCountBefore + 2)){
            printf("Too many cards drawn: Test Failed\n\n");
            drawTestFailed++;
            passed = 0;
        }
        
        if( coinCount < coinCountBefore){
            printf("Fewer cards exist in hand than were first present: Test Failed\n\n");
            drawTestFailed++;
            passed = 0;
        }
        if(discardCopper != 0){
            printf("Copper was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

        if(discardSilver != 0){
            printf("Silver was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

        if(discardGold != 0){
            printf("Gold was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

        if(passed == 1){
            printf("All Tests: Passed\n\n");
            testPassed++;
        }

		if (handAfter != (handBefore + 2)) {
			printf("Incorrect amount of cards drawn: Test Failed\n\n");
			handFailure++;
			passed = 0;
		}
		if (discardAfter != (discardBefore + 1)) {
			printf("Smithy Not Discarded after use: Test Failed\n\n");
			discardFailure++;
			passed = 0;
		}
   }
   
   printf("\n\n");
   printf("# of Tests Passed: %d\n", testPassed);
   printf("# of Cards Drawn To Hand Failed: %d\n", handFailure);
   printf("# of Smithy Discarded Fails: %d\n\n", discardFailure);
   
   return 0;
}