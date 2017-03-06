#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Random testing for smithyAction function from dominion.c
// Funciton call: int smithyAction(int currentPlayer,int handPos,struct gameState *state)
// Note: smithyAction function currently starts line 1311 from dominion.c

void testRandSmithyAction() {
  
  //--Change Number of Cycles
  int numberOfCycles = 100000;

  //Static Game Variables
  int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
  //int temphand[MAX_HAND];
  struct gameState *randGameState = newGame();
  
  //Tally of Tests Passed/Failed
  int testsRun = 0;
  int test1Passed =0;
  int test1Failed =0;
  int test2Passed =0;
  int test2Failed =0;
  int test3Passed =0;
  int test3Failed =0;
  int test4Passed =0;
  int test4Failed =0;
  
  int currentRandomSeed;
  int randPlayer,numPlayers;
  int preDeckSize, preHandSize, preDiscardSize;
  int tempCard, randSmithyHandLocation;
  int postDeckSize, postHandSize, postDiscardSize;
  int i, j;
  int smithyInHandPre, smithyInDeckPre, smithyInDiscardPre;
  int smithyInHandPost, smithyInDeckPost, smithyInDiscardPost;
  int getSmithyDifference;
  for(i=0; i < numberOfCycles; i++)
  {
    //Setup Initial Conditions.
    // Random Variables: numPlayers, randPlayer, currentRandomSeed, deckSize, handSize
    //                   discardSize, deck[MAXDECK]

    //----Reset Variables----
    memset(randGameState,0, sizeof(struct gameState));  //Clear bits in randGameState
    //memset(temphand,0, MAX_HAND);
    postDeckSize= 0; postHandSize=0; postDiscardSize=0;
    smithyInHandPre=0; smithyInDeckPre=0; smithyInDiscardPre=0;
    smithyInHandPost=0; smithyInDeckPost=0; smithyInDiscardPost=0; 

    //----Assign to Random Variables----
    numPlayers = (rand() % MAX_PLAYERS) +1;
    currentRandomSeed = rand();
    randPlayer = rand() % numPlayers;
    
    //----Initialize and Assign Cards----
    initializeGame(numPlayers, k, currentRandomSeed, randGameState);
    preDeckSize = ((rand() % (MAX_DECK-9))+10);  //Deck size set 10-MAX_HAND
    preHandSize = ((rand() % (MAX_HAND))+1);  //Hand size set 1-MAX_HAND
    preDiscardSize = (rand() % 10);  //Discard size 0-9
    randGameState->whoseTurn = randPlayer;
    randGameState->deckCount[randPlayer] = preDeckSize;
    randGameState->handCount[randPlayer] = preHandSize;
    randGameState->discardCount[randPlayer] = preDiscardSize;

    //----Assign Hand Location to Manually Add Smithy Card----
    randSmithyHandLocation = (rand() % preHandSize);  // Use for if statement when assigning in deck

    //----Randomly Assign Deck----
    for(j=0; j < preDeckSize; j++)
    {
      tempCard = rand() % 27;  //Rand card index 0-26
      randGameState->deck[randPlayer][j] = tempCard;
      if(tempCard==smithy)
        {
          smithyInDeckPre++;
        } 
    }
    //----Randomly Assign Discard----
    for(j=0; j < preDiscardSize; j++)
    {
      tempCard = rand() % 27;  //Rand card index 0-26
      randGameState->discard[randPlayer][j] = tempCard;
      if(tempCard==smithy)
        {
          smithyInDiscardPre++;
        } 
    }
    //----Randomly Assign Hand----
    for(j=0; j < preHandSize; j++)
    {
      //----Manually assign one card in Hand to Smithy Card----
      if(j==randSmithyHandLocation)
      {
        randGameState->hand[randPlayer][j] = smithy;
        smithyInHandPre++;
      }

      else{
        tempCard = rand() % 27;  //Rand card index 0-26
        randGameState->hand[randPlayer][j] = tempCard;
        if(tempCard==smithy)
        {
          smithyInHandPre++;
        } 
      }
    }

   
    //----Call Tested Function----
    smithyAction(randPlayer, randSmithyHandLocation, randGameState);

    //----Gather Post Execution Data----
    postDeckSize= randGameState->deckCount[randPlayer];
    postHandSize= randGameState->handCount[randPlayer];
    postDiscardSize= randGameState->discardCount[randPlayer];
    

        //----Check Smithy's In Deck----
    for(j=0; j < postDeckSize; j++)
    {
      tempCard = randGameState->deck[randPlayer][j];
       if(tempCard==smithy)
        {
          smithyInDeckPost++;
        } 
    }
        //----Check Smithy's In Discard----
    for(j=0; j < postDiscardSize; j++)
    {
      tempCard = randGameState->discard[randPlayer][j];
       if(tempCard==smithy)
        {
          smithyInDiscardPost++;
        } 
    }
        //----Check Smithy's In Hand----
    for(j=0; j < postHandSize; j++)
    {
      tempCard = randGameState->hand[randPlayer][j];
       if(tempCard==smithy)
        {
          smithyInHandPost++;
        } 
    }

    getSmithyDifference = (smithyInDeckPre+smithyInDiscardPre) - (smithyInDeckPost+smithyInDiscardPost);

  //-----RUN TESTS------

  //----TEST1---- Verify Correct Number Of Cards In Hand (We Gain 3 Cards, discard one)
  if(postHandSize == preHandSize + 2)
    {
        test1Passed++;
        testsRun++;
    }
    else
    {
        test1Failed++;
        testsRun++;
    }

  //----TEST2---- Verify Correct Number in Deck and Discard (pre-2 (Draw 3 discard 1))
  if((preDeckSize+preDiscardSize) == (postDiscardSize+postDeckSize-3))
    {
        test2Passed++;
        testsRun++;
    }
    else
    {
        test2Failed++;
        testsRun++;
    }

    //----TEST3---- Verify No Missing Smithy Cards (Differnece in Hand Reflects Difference in Deck/Discard)
  if((smithyInHandPost - smithyInHandPre) == getSmithyDifference)
    {
        test3Passed++;
        testsRun++;
    }
    else
    {
        test3Failed++;
        testsRun++;
    }

  //----TEST4---- Verify Correct Number of Smithy Cards In Discard/Deck
  if( (smithyInDiscardPre+smithyInDeckPre) == (smithyInDiscardPost+smithyInDeckPost-1))
    {
        test4Passed++;
        testsRun++;
    }
    else
    {
        test4Failed++;
        testsRun++;
    }




  }

  printf("Number of Tests Run: %i \n", testsRun);
  printf("Number of Tests Passed: %i \n",test1Passed+test2Passed+test3Passed+test4Passed);
  printf("Number of Tests Failed: %i \n",test1Failed+test2Failed+test3Failed+test4Failed);
  printf("Test 1- Verify # of Cards in Hand Passed:%i -- Failed:%i \n",test1Passed,test1Failed);
  printf("Test 2- Verify # of Cards in Discard+Deck Passed:%i -- Failed:%i \n",test2Passed,test2Failed);
  printf("Test 3- Verify No Smithy Cards Missing From Hand/Deck/Discard Combined Passed:%i -- Failed:%i \n",test3Passed,test3Failed);
  printf("Test 4- Verify # of Smithy Cards in Discard+Deck Passed:%i -- Failed:%i \n",test4Passed,test4Failed);



    return;
}



int main(int argc, char *argv[])
{
    printf("----Random Test smithyAction Function-----\n");

    int randSeed;
    if(argc == 2)  //Will either assign rng seed from command line (if given), or produce random seed locally
    {
      randSeed = atoi(argv[1]);
      printf("Random Seed From Command Line: %i \n", randSeed);
    }
    else{
      srand(time(NULL));
      randSeed = rand();
      printf("Random Seed From Program: %i\t(--see command line options for Makefile)\n", randSeed);
    }

    //SET RANDOM SEED!!!
    srand(randSeed);
    testRandSmithyAction();
    return 0;
}







//Notes:  For these tests, I assumed that the Smithy Card was in the hand and the input to the function was called appropriatly.
// Could test with smity cards being drawn (potentially) in rand test vr. Unit test hardcoded deck/discard
