//Automated Random Test for the Adventure card
// Compile --  gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c -o randomtestadventurer -lm -g
// find . -name "*.gcda" -print0 | xargs -0 rm
// ./randomtestadventurer
// gcov randomtestadventurer
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

///////// Global Variable /////////
int test_passed = 0;
////////////////////////////////


void check_results(int a)
{
  if(a == 0)
  {
    test_passed++;
  }

}


int main(int argc, char *argv[])
{
  int a, b, playersn, randomSeed, userRandomSeed, value, countDeck, countHand;
  int currentplayer = 1;
  struct gameState game;

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  userRandomSeed = 0;
  userRandomSeed = atoi(argv[1]);

  printf("User Inputed: %d \n", userRandomSeed);


  printf("\nAutomated Random Test -- ADVENTURER\n-----------\nThere are 10 rounds of testing...\nEach round has 100 random tests...\n");


  for(int z = 0; z < 10 ; z++)
  {
    printf("Testing Round %d\n", (z+1));
    for(int i = 0; i < 100; i ++)
    {
      playersn = rand() % 4; // Randon Number of players

      if (userRandomSeed == 0) // RandomSeed
      {
          randomSeed = rand() % 100000; // Random Seed
      }
      else
      {
        randomSeed = rand() % userRandomSeed;
      }
      a = initializeGame(playersn,cards, randomSeed, &game); // Initiliaze the game


      value = rand() % 6; // set a value random

      if(value == 1) // if the value is 1 set the deckCount to 0
      {
        game.deckCount[currentplayer] = 0;
        countDeck = 0 ;
      }
      else // otherwise pick a random value
      {
        countDeck = rand() % MAX_DECK;
        game.deckCount[currentplayer] = countDeck;
      }

      countHand = rand() % MAX_HAND;
      game.handCount[currentplayer] = countHand;


      game.discardCount[currentplayer] = rand() % MAX_DECK;

      b = cardEffect(adventurer, 1, 1, 1, &game);

      check_results(b);

    }

  }
  printf("\nResults\n----------\n");
  printf("Test's Passed: %d\n",test_passed );
  printf("Test's Failed: %d\n",(1000 - test_passed) );
  printf("Total Number of Test's: %d\n",1000 );


}
