#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Unit test for smithyAction found in dominion.c
// Funciton call: int smithyAction(int currentPlayer,int handPos,struct gameState *state)
// Note: smithyAction function currently starts line 1311 from dominion.c

void testsmithyAction() {
  printf("----TEST smithyAction Function-----\n");

  int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
  int seed = 44;
  int playerZero = 0;

//---GS1 TEST---- Test that we Gain 3 cards from draw, and discard 1, so hand will have 7 cards.

  struct gameState *GS1 = newGame();
  initializeGame(2,k,seed,GS1);
  GS1->handCount[playerZero] = 5;
  GS1->hand[playerZero][0] = feast;  
  GS1->hand[playerZero][1] = adventurer;  
  GS1->hand[playerZero][2] = smithy;  
  GS1->hand[playerZero][3] = tribute;  
  GS1->hand[playerZero][4] = gardens; 
  GS1->deckCount[playerZero] = 5;
  GS1->deck[playerZero][0] = estate;  
  GS1->deck[playerZero][1] = silver;  
  GS1->deck[playerZero][2] = great_hall;  
  GS1->deck[playerZero][3] = copper;  
  GS1->deck[playerZero][4] = duchy;  
  GS1->discardCount[playerZero] = 1;
  GS1->discard[playerZero][0] = feast;


//---GS2 TEST---- Test that we Gain 3 cards even with 5 cards in discard
  struct gameState *GS2 = newGame();
  initializeGame(2,k,seed,GS2);
  GS2->handCount[playerZero] = 5;
  GS2->hand[playerZero][0] = feast;  
  GS2->hand[playerZero][1] = adventurer;  
  GS2->hand[playerZero][2] = smithy;  
  GS2->hand[playerZero][3] = tribute;  
  GS2->hand[playerZero][4] = gardens; 
  GS2->deckCount[playerZero] = 0;
  GS2->discardCount[playerZero] = 5;
  GS2->discard[playerZero][0] = estate;  
  GS2->discard[playerZero][1] = silver;  
  GS2->discard[playerZero][2] = great_hall;  
  GS2->discard[playerZero][3] = copper;  
  GS2->discard[playerZero][4] = duchy;  

//---GS3 TEST---- Verify a Smithy card is in the discard pile
  struct gameState *GS3 = newGame();
  initializeGame(2,k,seed,GS3);
  GS3->handCount[playerZero] = 5;
  GS3->hand[playerZero][0] = feast;  
  GS3->hand[playerZero][1] = adventurer;  
  GS3->hand[playerZero][2] = smithy;  
  GS3->hand[playerZero][3] = tribute;  
  GS3->hand[playerZero][4] = gardens; 
  GS3->deckCount[playerZero] = 0;
  GS3->discardCount[playerZero] = 5;
  GS3->discard[playerZero][0] = estate;  
  GS3->discard[playerZero][1] = silver;  
  GS3->discard[playerZero][2] = great_hall;  
  GS3->discard[playerZero][3] = copper;  
  GS3->discard[playerZero][4] = duchy;  

//---GS4 TEST---- Verify a Smithy card is not in hand.
  struct gameState *GS4 = newGame();
  initializeGame(2,k,seed,GS4);
  GS4->handCount[playerZero] = 5;
  GS4->hand[playerZero][0] = feast;  
  GS4->hand[playerZero][1] = adventurer;  
  GS4->hand[playerZero][2] = smithy;  
  GS4->hand[playerZero][3] = tribute;  
  GS4->hand[playerZero][4] = gardens; 
  GS4->deckCount[playerZero] = 0;
  GS4->discardCount[playerZero] = 5;
  GS4->discard[playerZero][0] = estate;  
  GS4->discard[playerZero][1] = silver;  
  GS4->discard[playerZero][2] = great_hall;  
  GS4->discard[playerZero][3] = copper;  
  GS4->discard[playerZero][4] = duchy;  

//---GS5 TEST---- Verify playCards increments by one (trash flag not set)
  struct gameState *GS5 = newGame();
  initializeGame(2,k,seed,GS5);
  GS5->handCount[playerZero] = 5;
  GS5->playedCardCount = 0;   //Number of played card count set to 0
  GS5->hand[playerZero][0] = feast;  
  GS5->hand[playerZero][1] = adventurer;  
  GS5->hand[playerZero][2] = smithy;  
  GS5->hand[playerZero][3] = tribute;  
  GS5->hand[playerZero][4] = gardens; 
  GS5->deckCount[playerZero] = 0;
  GS5->discardCount[playerZero] = 5;
  GS5->discard[playerZero][0] = estate;  
  GS5->discard[playerZero][1] = silver;  
  GS5->discard[playerZero][2] = great_hall;  
  GS5->discard[playerZero][3] = copper;  
  GS5->discard[playerZero][4] = duchy;  
  

  int j;

  smithyAction(playerZero,2,GS1);
  int expectedCardsInHandGS1 = 7;  //Gain 3 and discard 1 (5+3-1=7)
  if(expectedCardsInHandGS1 == GS1->handCount[playerZero]){
        printf("PASS for success on drawing 3 cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS1, GS1->handCount[playerZero]);
    }
    else
    {
        printf("FAIL for success on drawing 3 cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS1, GS1->handCount[playerZero]);
    }


  smithyAction(playerZero,2,GS2);
  int expectedCardsInHandGS2 = 7;  //Gain 3 and discard 1 (5+3-1=7)
  if(expectedCardsInHandGS2 == GS2->handCount[playerZero]){
        printf("PASS for success on drawing 3 cards from discard.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS2, GS2->handCount[playerZero]);
    }
    else
    {
        printf("FAIL for success on drawing 3 cards from discard.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS2, GS2->handCount[playerZero]);
    }

  smithyAction(playerZero,2,GS3);  //Check to see if any discard card is a smithy
  int isSmithyInDiscard = 0;
  for(j=0; j < GS3->discardCount[playerZero]; j++)
  {
    if(GS3->discard[playerZero][j] == smithy)
    {
      isSmithyInDiscard =1;
    }
  }

  if(isSmithyInDiscard == 1){
        printf("PASS for success on discarding Smithy Card.  Success Flag:%i  isSmithyInDiscard:%i \n", 1, isSmithyInDiscard);
    }
    else
    {
        printf("FAIL for success on discarding Smithy Card.  Success Flag:%i  isSmithyInDiscard:%i \n", 1, isSmithyInDiscard);
    }

  smithyAction(playerZero,2,GS4); 
  int isSmithyInHand = 1;
  for(j=0; j < GS4->handCount[playerZero]; j++)
  {
    if(GS4->hand[playerZero][j] == smithy)
    {
      isSmithyInHand =0;
    }
  }

  if(isSmithyInHand == 1){
        printf("PASS for success on removing Smithy from Hand.  Success Flag:%i  isSmithyInHand:%i \n", 1, isSmithyInHand);
    }
    else
    {
        printf("FAIL for success on removing Smithy from Hand.  Success Flag:%i  isSmithyInHand:%i \n", 1, isSmithyInHand);
    }

  smithyAction(playerZero,2,GS5);  //Check to see if any discard card is a smithy
  int expectedPlayedCardCountGS5 = 1;  //Gain 1 and discard 1 (5+1-1=1)
  if(expectedPlayedCardCountGS5 == GS5->playedCardCount){
        printf("PASS for incrementing played cards (trash flag not set).  PlayedCards Expected:%i  PlayedCards Returned:%i \n", expectedPlayedCardCountGS5, GS5->playedCardCount);
    }
  else
    {
        printf("FAIL for incrementing played cards (trash flag not set).  PlayedCards Expected:%i  PlayedCards Returned:%i \n", expectedPlayedCardCountGS5, GS5->playedCardCount);
    }


    return;
}



int main(int argc, char *argv[])
{
    testsmithyAction();
    return 0;
}
