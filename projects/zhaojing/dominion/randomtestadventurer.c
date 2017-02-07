#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include <math.h>
#include <time.h>
#include "asserttrue.h"

int main(){
	printf("******begin random testing on adventurer card******\n");

	//initialize game
	struct gameState Gbefore, Gafter;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int i, j, player, results, discardPosition, errorCount;
    int bonus = 0;
    int cardPos = 0;
    int num = 0;
    int pos = 0;
	int seed = rand();
	srand(time(NULL));
	
	printf("testing whether game successfully initiated: ");
    results = initializeGame(4, k, seed, &Gafter); 
    asserttrue(results == 0);
	
	//begin testing
    for(i = 0, errorCount = 0; i < 1000; i++){		
        printf("\nrandom testing round #%d:\n", i+1);
		
		printf("testing original state before any player uses adventurer card.\n");
        Gafter.whoseTurn = rand() % 4;
        for(player = 0; player < 4; player++){
            Gafter.handCount[player] = rand() % (500 - 1) + 1;
            for(j = 0; j < Gafter.handCount[player]; j++){
                Gafter.hand[player][j] = rand() % (treasure_map + 1);
                if(Gafter.hand[player][j] == copper || Gafter.hand[player][j] == silver
                   || Gafter.hand[player][j] == gold || Gafter.hand[player][j] == adventurer){
                    j--;
                }
            }
            num = rand() % (Gafter.handCount[player] % 10 + 1);
            for(j = 0; j <= num; j++){
                pos = rand() % Gafter.handCount[player];
                Gafter.hand[player][pos] = adventurer;
            }
            if(player == Gafter.whoseTurn) cardPos = pos;
            printf("testing whether player%d's card position matches: ", player);
			asserttrue(cardPos >= 0);

            if(500 - Gafter.handCount[player] > 0){
                Gafter.deckCount[player] = rand() % (500 - Gafter.handCount[player]) + 1;
                for(j = 0; j < Gafter.deckCount[player]; j++){
                    Gafter.hand[player][j] = rand() % (treasure_map + 1);
                    if(Gafter.hand[player][j] == copper || Gafter.hand[player][j] == silver
                       || Gafter.hand[player][j] == gold || Gafter.hand[player][j] == adventurer){
                        j--;
                    }
                }
                num = rand() % (Gafter.deckCount[player] % 10 + 1);
                for(j = 0; j < num; j++){
                    pos = rand() % Gafter.deckCount[player];
                    Gafter.deck[player][pos] = rand() % 3 + copper;
                }
            }
            else Gafter.deckCount[player] = 0;

            if(500 - Gafter.handCount[player] - Gafter.deckCount[player] > 0){
                Gafter.discardCount[player] = rand() % (500 - Gafter.handCount[player] - Gafter.deckCount[player]) + 1;
                for(j = 0; j < Gafter.discardCount[player]; j++){
                    Gafter.hand[player][j] = rand() % (treasure_map + 1);
                    if(Gafter.hand[player][j] == copper || Gafter.hand[player][j] == silver
                       || Gafter.hand[player][j] == gold || Gafter.hand[player][j] == adventurer){
                        j--;
                    }
                }
                num = rand() % (Gafter.discardCount[player] % 10 + 1);
                for(j = 0; j < num; j++){
                    pos = rand() % Gafter.discardCount[player];
                    Gafter.discard[player][pos] = rand() % 3 + copper;
                }
            }
            else Gafter.discardCount[player] = 0; 

            printf("Player %d has %d cards in hand\n", player, Gafter.handCount[player]);
			printf("Player %d has %d cards in deck\n", player, Gafter.deckCount[player]);
			printf("Player %d discarded %d cards\n", player, Gafter.discardCount[player]);
        }

        memcpy(&Gbefore, &Gafter, sizeof(struct gameState));

		printf("testing resulting state when player %d uses adventurer card.\n", Gafter.whoseTurn);
		printf("testing whether player %d successfully played adventurer card: ", Gafter.whoseTurn);
        results = cardEffect(adventurer, 0, 0, 0, &Gafter, cardPos, &bonus);
        asserttrue(results == 0);
		
		printf("testing supply and victory piles.\n");
		printf("testing supply count on curse cards: ");
		if(Gafter.supplyCount[curse] == Gbefore.supplyCount[curse]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of curse cards\n", player);
			errorCount++;
		}
		printf("testing supply count on estate cards: ");
		if(Gafter.supplyCount[estate] == Gbefore.supplyCount[estate]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of estate cards\n", player);
			errorCount++;
		}
		printf("testing supply count on duchy cards: ");
		if(Gafter.supplyCount[duchy] == Gbefore.supplyCount[duchy]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of duchy cards\n", player);
			errorCount++;
		}
		printf("testing supply count on province cards: ");
		if(Gafter.supplyCount[province] == Gbefore.supplyCount[province]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of province cards\n", player);
			errorCount++;
		}
		
        for(player = 0; player < 4; player++){
            printf("Player %d has %d cards in \n", player, Gafter.handCount[player]);
			printf("Player %d has %d cards in deck\n", player, Gafter.deckCount[player]);
			printf("Player %d discarded %d cards\n", player, Gafter.discardCount[player]);
			
            if(player == Gafter.whoseTurn){
                if(Gafter.discard[player][Gafter.discardCount[player] - 1] != adventurer){
                    printf("TEST FAILED: player %d's adventurer card did not add adventurer card to player %'d discard pile\n", player, player);
					errorCount++;
                }
                
                if(Gafter.handCount[player] != Gbefore.handCount[player] + 1){
                    printf("TEST FAILED: player %d's adventurer card did not add 2 cards to player %d's hand\n", player, player);
					errorCount++;
                }
				
                if(Gafter.handCount[player] + Gafter.deckCount[player] + Gafter.discardCount[player] !=
					Gbefore.handCount[player] + Gbefore.deckCount[player] + Gbefore.discardCount[player]){
						printf("TEST FAILED: player %d's adventurer card incorrectly trashed player %d's cards\n", player, player);
						errorCount++;
                }
            }
            else{ 
                if(Gafter.deckCount[player] != Gbefore.deckCount[player]){
                    printf("TEST FAILED: player %d's adventurer card incorrectly changed player %d's deck count\n", Gafter.whoseTurn, player);
					errorCount++;
                }
                for(discardPosition = 0; discardPosition < Gafter.deckCount[player]; discardPosition++){
                    if(Gafter.deck[player][discardPosition] != Gbefore.deck[player][discardPosition]){
                        printf("TEST FAILED: player %d's adventurer card incorrectly changed player %d's deck position\n", Gafter.whoseTurn, player);
						errorCount++;
                    }
                }

                if(Gafter.handCount[player] != Gbefore.handCount[player]){
                    printf("TEST FAILED: player %d's adventurer card incorrectly changed player %d's hand count\n", Gafter.whoseTurn, player);
					errorCount++;
                }
                for(discardPosition = 0; discardPosition < Gafter.handCount[player]; discardPosition++){
                    if(Gafter.hand[player][discardPosition] != Gbefore.hand[player][discardPosition]){
                        printf("TEST FAILED: player %d's adventurer card incorrectly changed player %d's hand position\n", Gafter.whoseTurn, player);
						errorCount++;
                    }
                }

                if(Gafter.discardCount[player] != Gbefore.discardCount[player]){
                    printf("TEST FAILED: player %d's adventurer card incorrectly changed player %d's discard count\n", Gafter.whoseTurn, player);
                    errorCount++;
                }
                for(discardPosition = 0; discardPosition < Gafter.discardCount[player] - 1; discardPosition++){
                    if(Gafter.discard[player][discardPosition] != Gbefore.discard[player][discardPosition]){
                        printf("TEST FAILED: player %d's adventurer card incorrectly changed player %d's discard position\n", Gafter.whoseTurn, player);
						errorCount++;
                    }
                }
            }
        }
    }

    printf("\nOut of 1000 rounds of random testing, adventurer card produced %d errors.\n", errorCount);
	printf("Note that number of errors are not limited to 1 per round.\n");
	
    printf("******end random testing on adventurer card******\n");
	return 0;
}