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
        }

        memcpy(&Gbefore, &Gafter, sizeof(struct gameState));

        if(cardEffect(adventurer, 0, 0, 0, &Gafter, cardPos, &bonus) != 0){
			printf("TEST FAILED: player %d did not successfully play adventurer card\n", Gafter.whoseTurn);
			errorCount++;
		}
		
		if(Gafter.handCount[player] + Gafter.deckCount[player] + Gafter.discardCount[player] !=
			Gbefore.handCount[player] + Gbefore.deckCount[player] + Gbefore.discardCount[player]){
				printf("TEST FAILED: player %d's adventurer card incorrectly trashed player %d's cards\n", player, player);
				errorCount++;
            }
		
		printf("\ntesting supply and victory piles.\n");
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
		
		printf("\nTEST FAILURES: ('n/a' means should/does not exist)\n");
		printf("PLAYER #	VAVRIABLE		INTENDED VALUE	TEST VALUE\n");
        for(player = 0; player < 4; player++){
            if(player == Gafter.whoseTurn){
                if(Gafter.discard[player][Gafter.discardCount[player] - 1] != adventurer){
                    printf("player %d	discard pile	adventurer		n/a\n", player);
					errorCount++;
                }
                
                if(Gafter.handCount[player] != Gbefore.handCount[player] + 1){
                    printf("player %d	hand			%d				%d\n", player, Gbefore.handCount[player] + 1, Gafter.handCount[player]);
					errorCount++;
                }
            }
            else{ 
                if(Gafter.deckCount[player] != Gbefore.deckCount[player]){
                    printf("player %d	deck count		%d				%d\n", player, Gbefore.deckCount[player], Gafter.deckCount[player]);
					errorCount++;
                }
                for(discardPosition = 0; discardPosition < Gafter.deckCount[player]; discardPosition++){
                    if(Gafter.deck[player][discardPosition] != Gbefore.deck[player][discardPosition]){
                        printf("player %d	discard position	%d				%d\n", player, Gbefore.deck[player][discardPosition], Gafter.deck[player][discardPosition]);
						errorCount++;
                    }
                }

                if(Gafter.handCount[player] != Gbefore.handCount[player]){
                    printf("player %d	hand count		%d				%d\n", Gafter.whoseTurn, Gbefore.handCount[player], Gafter.handCount[player]);
					errorCount++;
                }
                for(discardPosition = 0; discardPosition < Gafter.handCount[player]; discardPosition++){
                    if(Gafter.hand[player][discardPosition] != Gbefore.hand[player][discardPosition]){
                        printf("player %d	hand position	%d				%d\n", player, Gbefore.hand[player][discardPosition], Gafter.hand[player][discardPosition]);
						errorCount++;
                    }
                }

                if(Gafter.discardCount[player] != Gbefore.discardCount[player]){
                    printf("player %d	discard count	%d				%d\n", player, Gbefore.discardCount[player], Gafter.discardCount[player]);
                    errorCount++;
                }
                for(discardPosition = 0; discardPosition < Gafter.discardCount[player] - 1; discardPosition++){
                    if(Gafter.discard[player][discardPosition] != Gbefore.discard[player][discardPosition]){
                        printf("player %d	discard position	%d				%d\n", player, Gbefore.discard[player][discardPosition], Gafter.discard[player][discardPosition]);
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