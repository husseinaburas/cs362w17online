#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"

void testNumHandCards() {
    struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &G);

    G.handCount[0] = 4;
    G.handCount[1] = 3;
    G.whoseTurn = 0;

    int i = numHandCards(&G);

    if(i==4){

        printf("Function numHandCards PASS for Player 1. Cards == 4.\n");
    }

    else{

        printf("Function numHandCards FAIL for Player 1. Cards != 4; %i \n", i);
    }

    G.whoseTurn = 1;
    i = numHandCards(&G);
    if(i==3){

        printf("Function numHandCards PASS for Player 2. Cards == 3.\n");
    }

    else{

        printf("Function numHandCards FAIL for Player 2. Cards != 3; %i \n", i);
    }

}

    

int main(int argc, char *argv[])
{
    testNumHandCards();
    return 0;
}



