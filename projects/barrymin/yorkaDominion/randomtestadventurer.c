#include <stdio.h>
#include "dominion.h"
#include "rngs.h"


int assert(int a, int b){
    //printf("value: %d   Expected: %d  ",a,b);
    if(a==b){
        printf("PASS\n");
        return 1;
    }
    else {
        printf("FAIL\n");
        return 0;
    }
}

int testAdventurer(struct gameState g, int player,int handPos,int * locations){

    struct gameState temp;
    int i;
    memcpy(&temp, &g, sizeof(struct gameState));
    //play card
    int r= playAdventurer(&temp);
    //discard adventurer
    g.hand[player][handPos] = g.hand[player][g.handCount[player]-1];
    g.handCount[player]--;
    int t=0;
    for(i=g.deckCount[player]; i>=0;i--){
        if(t>=2) break;
        if(g.deck[player][i]>= copper && g.deck[player][i] <= gold){
            t++;
            g.handCount[player]++;
            g.hand[player][g.handCount[player]]= g.deck[player][i];
            g.deckCount[player]--;
        }else{
            g.discardCount[player]++;
            g.discard[player][g.discardCount[player]]= g.deck[player][i];
        }
    }
    if(t<2){
        for(i=0; i<g.discardCount[player];i++){
            if(t>=2) break;
            if(g.discard[player][i]>= copper && g.discard[player][i] <= gold){
            t++;
            g.handCount[player]++;
            g.hand[player][g.handCount[player]]= g.discard[player][i];

        }
        g.deckCount[player]=g.discardCount[player];
        g.discardCount[player]=0;
        memcpy(g.deck[player], temp.deck[player], sizeof(int) * g.discardCount[player]);
        memcpy(g.discard[player], temp.discard[player], sizeof(int)*g.discardCount[player]);
        }
    }
     //assert(r , 0);
     assert(memcmp(&g, &temp, sizeof(struct gameState)) ,0);
           // printf("TEST FAILED");

}

int main(int argc, char **argv){

    if(argc != 2){
        printf("usage: randomadventurer randomSeed\n");
        return -1;
    }
    long seed = atoi(argv[1]);
    printf("using random seed %d\n", seed);

    //set up game state
    int i,j,handPos;
    struct gameState state, tempState;
	int k[10] = {adventurer, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute,salvager , council_room};
	int players = floor(Random()*4);
	initializeGame(players, k, seed, &tempState);

    //test adventurer
    printf("-------------------------- Testing Adventurer ------------------------\n");

    //generate random test case
for(i=0; i<100;i++){
    memcmp(state, tempState, sizeof(struct gameState));
    state.whoseTurn = floor(Random()*players);
    //randomize player's cards
    int treasureLoc ={-1,-1,-1,-1};
    state.handCount[state.whoseTurn] = floor(Random()*MAX_HAND);
    for(j=0; j < state.handCount[state.whoseTurn]; j++){
        state.hand[state.whoseTurn][j] = floor(Random() * treasure_map);
    }
    handPos = floor(Random()*state.handCount[state.whoseTurn]);
    state.hand[state.whoseTurn][handPos] = adventurer;

    state.deckCount[state.whoseTurn] = floor(Random()*MAX_DECK);
    for(j=0; j < state.deckCount[state.whoseTurn]; j++){
            state.deck[state.whoseTurn][j] = floor(Random() * treasure_map);
    }

    state.discardCount[state.whoseTurn] = floor(Random()*MAX_DECK);
    for(j=0; j < state.discardCount[state.whoseTurn]; j++){
            state.discard[state.whoseTurn][j] = floor(Random() * treasure_map);
    }

    testAdventurer(state,state.whoseTurn,handPos,treasureLoc);
    //assert handcount +2
    //if loc[1]!= -1 assert deckcount = deckcount - loc[1]+1
}
    return 0;
}
