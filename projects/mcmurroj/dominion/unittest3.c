#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Unit test for isGameOver found in dominion.c
// Funciton call: int isGameOver(struct gameState *state) 
// Note: isGameOver function currently starts line 390 from dominion.c

void testisGameOver() {
    printf("----TEST isGameOver Function-----\n");

    int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
    int seed = 41;
   
   int i;
//---GS1 TEST----  In Game State 1 we will check to verify game is marked over with no province cards.
   struct gameState *GS1 = newGame();
    initializeGame(2,k,seed,GS1);

   GS1->supplyCount[province] = 0;  //Set province to 0
   int GS1result = isGameOver(GS1);
   int GS1expectedResult = 1;  //The function should return 1 to indicate game is over as there are no province cards lift.

  
//---GS2 TEST---- Verify that when 3 piles are empty (copper/silver/gold), game is marked as over.
   // Also verify handels cards of value -1 properly, as cards not in game session will
   // be marked as -1 as seen in dominion.c
   struct gameState *GS2 = newGame();
   initializeGame(2,k,seed,GS2);
   for(i=0;i<27;i++)
   {
    GS2->supplyCount[i] = 10;  //Set all supplies to 10
   }  
   GS2->supplyCount[copper] = 0;
   GS2->supplyCount[estate] = -1;
   GS2->supplyCount[silver] = 0;
   GS2->supplyCount[gold] = 0;
   int GS2result = isGameOver(GS2);
   int GS2expectedResult = 1;

//---GS3 TEST---- Test for situation where there are remaining province cards and 2 piles are empty.  
   // This is somewhat of an edge case to tests that if only 2 piles are empty, game is not maked over.
   struct gameState *GS3 = newGame();
    initializeGame(2,k,seed,GS3);
   for(i=0;i<27;i++)
   {
    GS3->supplyCount[i] = 10;  //Set all supplies to 10
   }  
   GS3->supplyCount[copper] = 0;
   GS3->supplyCount[gold] = 0;
   int GS3result = isGameOver(GS3);
   int GS3expectedResult = 0;

//---GS4 TEST---- This tests is where no supplies are empty.  This would simulate a new game as game was just initalized.
   // The expected return value should be 0 as this is what is set for an game that is ending.
   struct gameState *GS4 = newGame();
    initializeGame(2,k,seed,GS4);
   int GS4result = isGameOver(GS4);
   int GS4expectedResult = 0;


   if(GS1result==GS1expectedResult)
   {
    printf("PASS for ending game with no province cards remaining.  Return Value Expected:%i  Actual Return Value:%i \n",GS1expectedResult, GS1result);
   }
   else
   {
    printf("FAIL for ending game with no province cards remaining.  Return Value Expected:%i  Actual Return Value:%i \n",GS1expectedResult, GS1result);
   }

      if(GS2result==GS2expectedResult)
   {
    printf("PASS for ending game with three piles empty.  Return Value Expected:%i  Actual Return Value:%i \n",GS2expectedResult, GS2result);
   }
   else
   {
    printf("FAIL for ending game three piles empty.  Return Value Expected:%i  Actual Return Value:%i \n",GS2expectedResult, GS2result);
   }

    if(GS3result==GS3expectedResult)
   {
    printf("PASS for not ending game with two piles empty.  Return Value Expected:%i  Actual Return Value:%i \n",GS3expectedResult, GS3result);
   }
   else
   {
    printf("FAIL for not ending game two piles empty.  Return Value Expected:%i  Actual Return Value:%i \n",GS3expectedResult, GS3result);
   }
   
    if(GS4result==GS4expectedResult)
   {
    printf("PASS for not ending game with no piles empty.  Return Value Expected:%i  Actual Return Value:%i \n",GS4expectedResult, GS4result);
   }
   else
   {
    printf("FAIL for not ending game no piles empty.  Return Value Expected:%i  Actual Return Value:%i \n",GS4expectedResult, GS4result);
   }     

    return;
}




int main(int argc, char *argv[])
{
    testisGameOver();
    return 0;
}
