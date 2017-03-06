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
int testSalvager(struct gameState g, int handPos, int choice, int cost){
    struct gameState temp;
    memcpy(&temp, &g, sizeof(struct gameState));
    int r = playSalvager(&temp,handPos,choice);
    int pass=0;
    printf("Testing return value\n");
    pass = assert(r , 0);
    printf("Testing numBuys value\n");
    pass &= assert(temp.numBuys , g.numBuys+1);
    printf("Testing coins value\n");
    pass &=assert(temp.coins , g.coins+ cost);
    printf("Testing discardCount value\n");
    pass &=assert(temp.discardCount[temp.whoseTurn] , g.discardCount[temp.whoseTurn]+1);
    printf("Testing handCount value\n");
    pass &=assert(temp.handCount[temp.whoseTurn] , g.handCount[temp.whoseTurn]-2); //trash card discard salvager
    printf("Testing deckCount value\n");
    pass &=assert(temp.deckCount[temp.whoseTurn] , g.deckCount[temp.whoseTurn]);
    if(pass)
        printf("\nTEST CASE PASSED\n");
    else
        printf("\nTEST CASE FAILED\n");

}

int main(int argc, char **argv){

    if(argc != 2){
        printf("usage: randomcard1 randomSeed\n");
        return -1;
    }
    long seed = atoi(argv[1]);
    printf("using random seed %d\n", seed);

    //set up game state
    int i,j;
    struct gameState state, tempState;
	int k[10] = {adventurer, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute,salvager , council_room};
	int players = 4;
	initializeGame(players, k, seed, &tempState);
    int costs[]={0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    int choice1;
    //test adventurer
    printf("-------------------------- Testing Salvager ------------------------\n");
    for(i=0; i<100; i++){
        printf("TEST CASE %d\n----------------------------------------\n",i+1);
        memcpy(&state, &tempState, sizeof(struct gameState));
        //generate random test case
        state.whoseTurn = floor(Random()*2);
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
        choice1 = floor(Random()*state.handCount[state.whoseTurn]);
        int handPos = floor(Random()*state.handCount[state.whoseTurn]);
        if(handPos == choice1) handPos = (handPos+1)%state.handCount[state.whoseTurn];
        state.hand[state.whoseTurn][handPos] = salvager;
        testSalvager(state,handPos,choice1,costs[state.hand[state.whoseTurn][choice1]]);
        printf("----------------------------------------\n");
    }



    return 0;
}
