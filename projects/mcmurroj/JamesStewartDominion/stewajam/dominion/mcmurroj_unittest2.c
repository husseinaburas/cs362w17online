#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"


//Unit test for getCost found in dominion.c
// Funciton call: int getCost(int cardNumber)
//Note: testgetCost function currently starts line 5893 from dominion.c

void testgetCost() {
	printf("----TEST getCost Function-----\n");
	
    int costArray[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};  // Costs referenced from http://dominion.diehrstraits.com/?set=All&f=list
    char*NameArray[27] = {"curse","estate","duchy","province","copper",
    "silver","gold","adventurer","council_room","feast","gardens","mine",
    "remodel","smithy","village","baron","great_hall","minion","steward",
    "tribute","ambassador","cutpurse","embargo","outpost","salvager","sea_hag","treasure_map"};
    char *(*pointerToNameArray)[27] = &NameArray;

   for(int i=0; i <27; i++)
   {
   		int tempCost = getCost(i);

   		if(tempCost == costArray[i])
   		{
   		printf("PASS for parameters %s.  Cost Expected:%i  Cost Returned:%i \n",(*pointerToNameArray)[i], costArray[i], tempCost);
   		}

    	else
    	{
    	printf("FAIL for parameters %s.  Cost Expected:%i  Cost Returned:%i \n",(*pointerToNameArray)[i], costArray[i], tempCost);
    	}
   }
   
   int outsideOfCardNumBounds = 30;
   int expectedReturnOfOutsideBounds = -1;
   int costOutsideBounds = getCost(outsideOfCardNumBounds); 

   if(costOutsideBounds == expectedReturnOfOutsideBounds)
   	{
   	printf("PASS for invalid vard.  Return Value Expected:%i   Return Value:%i \n",expectedReturnOfOutsideBounds, costOutsideBounds);
   	}

    else
    {
    printf("FAIL for invalid vard.  Return Value Expected:%i   Return Value:%i \n",expectedReturnOfOutsideBounds, costOutsideBounds);
    }

    return;
}







int main(int argc, char *argv[])
{
    testgetCost();
    return 0;
}
