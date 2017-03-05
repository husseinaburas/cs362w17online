/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing function: getCost
 *
 * makefile:
 *  unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 *
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include "rngs.h"

 // set PRINT_TEST to 0 to remove print statements from output
 #define PRINT_TEST 0

 //function to check assertion
 int assertTrue(int compare, char* test) {
   if (compare == 1) {
     #if (PRINT_TEST == 1)
       printf("\tTest for %s passed\n", test);
     #endif
     return 0;
   } else {
     #if (PRINT_TEST == 1)
      printf("\tTest for %s failed\n", test);
     #endif
     return 1;
   }
 }

 //function to test individual card cost
 int testCardCost(int card, char* cname, int expectedCost) {
   #if (PRINT_TEST == 1)
      printf("\tTest getCost %s for expected cost %d\n", cname, expectedCost);
   #endif
   int cost = getCost(card);
   int checkResult = assertTrue((cost == expectedCost), cname);
   return checkResult;
 }

 int main() {
   printf("\nTESTING FUNCTION: getCost()\n");

   int allPassed = 0; //initialized to true
   //test curse cost
   if(testCardCost(curse, "curse", 0) == 1){
     allPassed = 1;
   }
   //test estate cost
   if(testCardCost(estate, "estate", 2) == 1){
     allPassed = 1;
   }
   //test duchy cost
   if(testCardCost(duchy, "duchy", 5) == 1){
     allPassed = 1;
   }
   //test province cost
   if(testCardCost(province, "province", 8) == 1){
     allPassed = 1;
   }
   //test copper cost
   if(testCardCost(copper, "copper", 0) == 1){
     allPassed = 1;
   }
   //test silver cost
   if(testCardCost(silver, "silver", 3) == 1){
     allPassed = 1;
   }
   //test gold cost
   if(testCardCost(gold, "gold", 6) == 1){
     allPassed = 1;
   }
   //test adventurer cost
   if(testCardCost(adventurer, "adventurer", 6) == 1){
     allPassed = 1;
   }
   //test council_room
   if(testCardCost(council_room, "council_room", 5) == 1){
     allPassed = 1;
   }
   //test feast
   if(testCardCost(feast, "feast", 4) == 1){
     allPassed = 1;
   }
   //test gardens
   if(testCardCost(gardens, "gardens", 4) == 1){
     allPassed = 1;
   }
   //test mine
   if(testCardCost(mine, "mine", 5) == 1){
     allPassed = 1;
   }
   //test remodel
   if(testCardCost(remodel, "remodel", 4) == 1){
     allPassed = 1;
   }
   //test smithy
   if(testCardCost(smithy, "smithy", 4) == 1){
     allPassed = 1;
   }
   //test village
   if(testCardCost(village, "village", 3) == 1){
     allPassed = 1;
   }
   //test baron
   if(testCardCost(baron, "baron", 4) == 1){
     allPassed = 1;
   }
   //test great_hall
   if(testCardCost(great_hall, "great_hall", 3) == 1){
     allPassed = 1;
   }
   //test minion
   if(testCardCost(minion, "minion", 5) == 1){
     allPassed = 1;
   }
   //test steward
   if(testCardCost(steward, "steward", 3) == 1){
     allPassed = 1;
   }
   //test tribute
   if(testCardCost(tribute, "tribute", 5) == 1){
     allPassed = 1;
   }
   //test ambassador
   if(testCardCost(ambassador, "ambassador", 3) == 1){
     allPassed = 1;
   }
   //test cutpurse
   if(testCardCost(cutpurse, "cutpurse", 4) == 1){
     allPassed = 1;
   }
   //test embargo
   if(testCardCost(embargo, "embargo", 2) == 1){
     allPassed = 1;
   }
   //test outpost
   if(testCardCost(outpost, "outpost", 5) == 1){
     allPassed = 1;
   }
   //test salvager
   if(testCardCost(salvager, "salvager", 4) == 1){
     allPassed = 1;
   }
   //test sea_hag
   if(testCardCost(sea_hag, "sea_hag", 4) == 1){
     allPassed = 1;
   }
   //test treasure_map
   if(testCardCost(treasure_map, "treasure_map", 4) == 1){
     allPassed = 1;
   }
   //test invalid value
   int invalid = -1;
   if(testCardCost(invalid, "invalid", -1) == 1){
     allPassed = 1;
   }

   //if all passed is still true, all passed!
   if (allPassed == 0) {
     printf("\tFINAL: ALL TESTS PASSED\n");
   } else {
     printf("\tFINAL: TESTS DID NOT ALL PASS\n");
   }
   return 0;
 }
