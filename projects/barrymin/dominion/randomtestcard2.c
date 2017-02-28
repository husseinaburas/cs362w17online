
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"

int assert(int a, int b){
    printf("value: %d   Expected: %d  ",a,b);
    if(a==b){
        printf("PASS\n");
        return 1;
    }
    else {
        printf("FAIL\n");
        return 0;
    }
}
int testSmithy(struct gameState g, int handPos){
    struct gameState temp;
    memcpy(&temp, &g, sizeof(struct gameState));
    int r = playSmithy(&temp);
    int pass = 0;
    printf("Testing return value\n");
    pass = assert(r , 0);
    printf("Testing discardCount value\n");
    pass &=assert(temp.discardCount[temp.whoseTurn] , g.discardCount[temp.whoseTurn]+1);
    printf("Testing handCount value\n");
    pass &=assert(temp.handCount[temp.whoseTurn] , g.handCount[temp.whoseTurn]+2); //discard smithy, +3 cards
    printf("Testing deckCount value\n");
    pass &=assert(temp.deckCount[temp.whoseTurn] , g.deckCount[temp.whoseTurn]-3);
    if(pass)
        printf("\nTEST CASE PASSED\n");
    else
        printf("\nTEST CASE FAILED\n");

}

int main(int argc, char **argv){

    if(argc != 2){
        printf("usage: randomcard2 randomSeed\n");
        return -1;
    }
    long seed = atoi(argv[1]);
    printf("using random seed %d\n", seed);

    //set up game state
    int i,j;
    struct gameState state, tempState;
	int k[10] = {adventurer, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute,salvager , council_room};
	int players = floor(Random()*4);
	initializeGame(players, k, seed, &tempState);
    //test adventurer
    printf("-------------------------- Testing Smithy ------------------------\n");
    for(i=0; i<10; i++){
        printf("TEST CASE %d\n----------------------------------------\n",i+1);
        memcpy(&state, &tempState, sizeof(struct gameState));
        //generate random test case
        state.whoseTurn = floor(Random()*players);
        //randomize player's cards
        state.handCount[state.whoseTurn] = floor(Random()*MAX_HAND);
        for(j=0; j < state.handCount[state.whoseTurn]; j++){
            state.hand[state.whoseTurn][j] = floor(Random() * treasure_map);
        }
        state.deckCount[state.whoseTurn] = floor(Random()*MAX_DECK);
        for(j=0; j < state.deckCount[state.whoseTurn]; j++){
                state.deck[state.whoseTurn][j] = floor(Random() * treasure_map);
        }
        state.discardCount[state.whoseTurn] = floor(Random()*MAX_DECK);
        for(j=0; j < state.discardCount[state.whoseTurn]; j++){
                state.discard[state.whoseTurn][j] = floor(Random() * treasure_map);
        }
        int handPos = floor(Random()*state.handCount[state.whoseTurn]);
        state.hand[state.whoseTurn][handPos] = smithy;
        testSmithy(state,handPos);
        printf("----------------------------------------\n");
    }



    return 0;
}
