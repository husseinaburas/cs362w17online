#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Unit test for scoreFor found in dominion.c
// Funciton call: int scoreFor (int player, struct gameState *state)
// Note: scoreFor function starts line 417 from dominion.c

void testscoreFor() {
  printf("----TEST scoreFor Function-----\n");

    int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
    int seed = 42;
    int playerZero = 0;

//---GS1 TEST---- In Game State 1 we will check to verify correct point allowance with estate/curse/duchy/province/great_hall
    // in the current hand.  Deck and discard empty.
   struct gameState *GS1 = newGame();
   initializeGame(2,k,seed,GS1);

   //Player current hand
   GS1->handCount[playerZero] = 5;
   GS1->hand[playerZero][0] = curse;  //Victory Value: -1
   GS1->hand[playerZero][1] = province;  //Victory Value: 6
   GS1->hand[playerZero][2] = great_hall;  //Victory Value: 1
   GS1->hand[playerZero][3] = estate;  //Victory Value: 1
   GS1->hand[playerZero][4] = duchy;  //Victory Value: 3
   GS1->discardCount[playerZero] = 0;
   GS1->deckCount[playerZero] = 0;
   int expectedScoreGS1= 10;         //DeckTotal: 10

//---GS2 TEST----  Test for estate/curses/duchy/province/great_hall cards in the discard pile
   struct gameState *GS2 = newGame();
   initializeGame(2,k,seed,GS2);
   //Player current hand
   GS2->handCount[playerZero] = 0;
   GS2->discardCount[playerZero] = 5;
   GS2->discard[playerZero][0] = curse;  //Victory Value: -1
   GS2->discard[playerZero][1] = province;  //Victory Value: 6
   GS2->discard[playerZero][2] = great_hall;  //Victory Value: 1
   GS2->discard[playerZero][3] = estate;  //Victory Value: 1
   GS2->discard[playerZero][4] = duchy;  //Victory Value: 3
   GS2->deckCount[playerZero] = 0;
   int expectedScoreGS2= 10;         //DeckTotal: 10

//---GS3 TEST---- Test for estate/curses/duchy/province/great_hall cards in the draw pile
   struct gameState *GS3 = newGame();
   initializeGame(2,k,seed,GS3);
   //Player current hand
   GS3->handCount[playerZero] = 0;
   GS3->discardCount[playerZero] = 0;
   GS3->deckCount[playerZero] = 5;
   GS3->deck[playerZero][0] = curse;  //Victory Value: -1
   GS3->deck[playerZero][1] = province;  //Victory Value: 6
   GS3->deck[playerZero][2] = great_hall;  //Victory Value: 1
   GS3->deck[playerZero][3] = estate;  //Victory Value: 1
   GS3->deck[playerZero][4] = duchy;  //Victory Value: 3
   int expectedScoreGS3= 10;         //DeckTotal: 10

//---GS4 TEST----  Test the garden card when in the hand.
   struct gameState *GS4 = newGame();
   initializeGame(2,k,seed,GS4);
   //Player current hand
   GS4->handCount[playerZero] = 10;
   GS4->hand[playerZero][0] = copper;  
   GS4->hand[playerZero][1] = silver;  
   GS4->hand[playerZero][2] = gold;  
   GS4->hand[playerZero][3] = tribute;  
   GS4->hand[playerZero][4] = smithy;  
   GS4->hand[playerZero][5] = adventurer;  
   GS4->hand[playerZero][6] = feast;  
   GS4->hand[playerZero][7] = copper;  
   GS4->hand[playerZero][8] = silver;  
   GS4->hand[playerZero][9] = gardens;  
   GS4->discardCount[playerZero] = 0;
   GS4->deckCount[playerZero] = 0;
   int expectedScoreGS4= 1;         //Garden= 10/10
   
  int scoreOutcomeGS1 = scoreFor(playerZero, GS1); 
    if(expectedScoreGS1 == scoreOutcomeGS1){
        printf("PASS for parameters estate/duchy/curse/great_hall/province in hand.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS1, scoreOutcomeGS1);
    }
    else
    {
        printf("FAIL for parameters estate/duchy/curse/great_hall/province in hand.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS1, scoreOutcomeGS1);
    }

    int scoreOutcomeGS2 = scoreFor(playerZero, GS2); 
    if(expectedScoreGS2 == scoreOutcomeGS2){
        printf("PASS for parameters estate/duchy/curse/great_hall/province in discard.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS2, scoreOutcomeGS2);
    }
    else
    {
        printf("FAIL for parameters estate/duchy/curse/great_hall/province in discard.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS2, scoreOutcomeGS2);
    }

    int scoreOutcomeGS3 = scoreFor(playerZero, GS3); 
    if(expectedScoreGS3 == scoreOutcomeGS3){
        printf("PASS for parameters estate/duchy/curse/great_hall/province in deck.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS3, scoreOutcomeGS3);
    }
    else
    {
        printf("FAIL for parameters estate/duchy/curse/great_hall/province in deck.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS3, scoreOutcomeGS3);
    }

    int scoreOutcomeGS4 = scoreFor(playerZero, GS4); 
    if(expectedScoreGS4 == scoreOutcomeGS4){
        printf("PASS for parameters garden in deck of size 10.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS4, scoreOutcomeGS4);
    }
    else
    {
        printf("FAIL for parameters garden in deck of size 10.  Score Expected:%i  Score Returned:%i \n", expectedScoreGS4, scoreOutcomeGS4);
    }

    return;
}



int main(int argc, char *argv[])
{
    testscoreFor();
    return 0;
}
