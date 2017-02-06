#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int asserttrue(int condition, char* message)
{
  if (!condition) {
    printf("\tError: %s\n", message);
    return 1;
  }

  return 0;
}


int main(int argc, char** argv) 
{
  struct gameState G;
  int i = 0,
      success = 1, 
      error_count = 0,
      error_total = 0, 
      seed = 0,
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  seed = 1 + rand() % 10;
  // Make sure initialize game returns success, if not exit
  success = initializeGame(2, k, seed, &G);
  asserttrue(success == 0, "Failed to Initialize Game");
  if ( success == -1 ) return 1; 

  printf("----------------------- Begin Test isGameOver  ---------------------\n");
  printf("Testing isGameOver after game initialized (ie just begun)\n");
  // call isGameOver on game state
  success = isGameOver(&G);

  // assert that return value is 0 for game still in progress
  error_count += asserttrue(success == 0, "Game Shouldn't be Over at Beginning");
 
  if (error_count == 0)
    printf("\tAll Tests Successful isGameOver after game initialized\n\n");
  else
    printf("\t%d Tests Failed isGameOver after game initialized\n\n)", error_count);

  error_total += error_count;
  error_count = 0;

  printf("Testing isGameOver provence supply 0\n");
  
  // Set province supply to 0
  G.supplyCount[province] = 0;
  // Call is game over
  success = isGameOver(&G);

  // assert return value is 1 for game over
  error_count += asserttrue(success == 1, "Game should be over when province supply is 0");

  if (error_count == 0)
    printf("\tAll Tests Successful isGameOver province supply 0\n\n");
  else
    printf("\t%d Tests Failed isGameOver province supply 0\n\n", error_count);

  error_total += error_count;
  error_count = 0;


  printf("Testing isGameOver with 3 supply empty ( estate, duchy, village )\n");
  
  // Set province back to normal and estate/duchy/village supply to 0
  G.supplyCount[province] = 8;
  G.supplyCount[duchy] = 0;
  G.supplyCount[estate] = 0;
  G.supplyCount[village] = 0;

  // Call isGameOver
  success = isGameOver(&G);

  // assert that return value is 1 for game over
  error_count += asserttrue(success == 1, "Game should be over when 3 supplies are 0");

  if (error_count == 0)
    printf("\tAll Tests Successful, estate, duchy, village supply 0\n\n");
  else
    printf("\t%d Tests Failed, estate, duchy, village supply 0\n\n", error_count);


  error_total += error_count;
  error_count = 0;


  printf("Testing isGameOver with 2 supply empty ( estate, duchy )\n");
  
  // Set village back to normal
  G.supplyCount[village] = 8;

  // Call isGameOver
  success = isGameOver(&G);

  // assert that return value is 0 for game over
  error_count += asserttrue(success == 0, "Game should not be over with only 2 empty supplies");

  if (error_count == 0)
    printf("\tAll Tests Successful, estate, duchy supply 0\n\n");
  else
    printf("\t%d Tests Failed, estate, duchy supply 0\n\n", error_count);


  error_total += error_count;
  error_count = 0;


  printf("Testing isGameOver with 1 supply empty ( estate )\n");

  
  // Set duchy back to normal
  G.supplyCount[duchy] = 8;

  // Call isGameOver
  success = isGameOver(&G);

  // assert that return value is 0 for game over
  error_count += asserttrue(success == 0, "Game should not be over with only 1 empty supply");

  if (error_count == 0)
    printf("\tAll Tests Successful, estate supply 0\n\n");
  else
    printf("\t%d Tests Failed, estate supply 0\n\n", error_count);


  error_total += error_count;
  error_count = 0;

  printf("Testing isGameOver, every cards supply 0 except province\n");
  
  // set all card supply, except province, to 0
  for (i = curse; i < treasure_map; i++) {
    if (i != province)
      G.supplyCount[i] = 0;
  }

  // call isGameOver
  success = isGameOver(&G);
  // assert that value is 1 for game over
  error_count += asserttrue(success == 1, "Game should be over if at least 3 supplies 0");
 
  if (error_count == 0)
    printf("\tAll Tests Successful, every cards supply 0 except province\n\n");
  else
    printf("\t%d Tests Failed, every cards supply 0 except province\n\n", error_count);

  error_total += error_count;
  error_count = 0;

  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL isGameOver\n");
  else
    printf("%d TESTS FAILED isGameOver\n", error_total);
  
  
  printf("----------------------- END Test isGameOver ---------------------\n");
  

  return 0; 
}


