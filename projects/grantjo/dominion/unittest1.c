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
  // Testing getCost Function
  // Test Suite contains tests of all valid inputs along with
  // a very large out of range input and a negative out of range input

  int error_count = 0,
      error_total = 0;
 printf("------------------------ Testing getCost Function ----------------------\n");

 printf("Testing Valid Inputs to getCost\n");
 // Test values taken from wiki.dominionstrategy.com

  error_count += asserttrue(getCost(curse) == 0, "Curse Cost Incorrect");

  error_count += asserttrue(getCost(estate) == 2, "Estate Cost Incorrect");
  
  error_count += asserttrue(getCost(duchy) == 5, "Duchy Cost Incorrect");
  
  error_count += asserttrue(getCost(province) == 8, "Province Cost Incorrect");
  
  error_count += asserttrue(getCost(copper) == 0, "Copper Cost Incorrect");
  
  error_count += asserttrue(getCost(silver) == 3, "Silver Cost Incorrect");
  
  error_count += asserttrue(getCost(gold) == 6, "Gold Cost Incorrect");
  
  error_count += asserttrue(getCost(adventurer) == 6, "Adventurer Cost Incorrect");
  
  error_count += asserttrue(getCost(council_room) == 5, "Council Room Cost Incorrect");
  
  error_count += asserttrue(getCost(feast) == 4, "Feast Cost Incorrect");
  
  error_count += asserttrue(getCost(gardens) == 4, "Gardens Cost Incorrect");
  
  error_count += asserttrue(getCost(mine) == 5, "Mine Cost Incorrect");
  
  error_count += asserttrue(getCost(remodel) == 4, "Remodel Cost Incorrect");
  
  error_count += asserttrue(getCost(smithy) == 4, "Smithy Cost Incorrect");

  error_count += asserttrue(getCost(village) == 3, "Village Cost Incorrect");
  
  error_count += asserttrue(getCost(baron) == 4, "Baron Cost Incorrect");
  
  error_count += asserttrue(getCost(great_hall) == 3, "Great Hall Cost Incorrect");
  
  error_count += asserttrue(getCost(minion) == 5, "Minion Cost Incorrect");
  
  error_count += asserttrue(getCost(steward) == 3, "Steward Cost Incorrect");
  
  error_count += asserttrue(getCost(tribute) == 5, "Tribute Cost Incorrect");
  
  error_count += asserttrue(getCost(ambassador) == 3, "Ambassador Cost Incorrect");
  
  error_count += asserttrue(getCost(cutpurse) == 4, "Cutpurse Cost Incorrect");
  
  error_count += asserttrue(getCost(embargo) == 2, "Embargo Cost Incorrect");
  
  error_count += asserttrue(getCost(outpost) == 5, "Outpost Cost Incorrect");
  
  error_count += asserttrue(getCost(salvager) == 4, "Salvager Cost Incorrect");
  
  error_count += asserttrue(getCost(sea_hag) == 4, "Sea Hag Cost Incorrect");
  
  error_count += asserttrue(getCost(treasure_map) == 4, "Treasure Map Cost Incorrect");

  // Print all tests successfull if no errors, else report num errors
  if (error_count == 0)
    printf("\n\tAll Tests Successful: getCost (valid inputs)\n\n");
  else
    printf("\n\t%d Tests Failed: getCost (valid inputs)\n\n", error_count);
  
  error_total = error_count;
  error_count = 0;

  // Test a large number and a negative number
  printf("Testing Invalid Input to getCost\n");

  error_count += asserttrue(getCost(1000) == -1, "Expected -1 on Invalid Large Input");
 
  error_count += asserttrue(getCost(-10) == -1, "Expected -1 on Invalid Negative Input");

  // Check if all tests passed or only a subset
  if (error_count == 0)
    printf("\tAll Tests Successful: getCost (invalid inputs)\n\n");
  else
    printf("\t%d Tests Failed: getCost (invalid inputs)\n\n", error_count);
 
  error_total += error_count;

  // Check if all tests for entire unittest were successful, if not print out
  // total errors
  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL getCost\n");
  else
    printf("\t%d TESTS FAILED getCost\n", error_total);

 printf("------------------------ Finish Testing getCost  ----------------------\n");

  return 0; 
}


