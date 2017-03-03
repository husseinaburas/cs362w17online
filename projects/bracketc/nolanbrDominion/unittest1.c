#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

//UNIT TEST 1 - getCost() function

int main(){
    int actualCost[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4, -1}; //actual cost of each card
    
    int i;
    int failed = 0;
    for (i = curse; i <= treasure_map+1; i++) //loop through cards, checking returned cost against actual cost (also checks for a value of -1 if invalid card passed to getCost)
    {
        int cost = getCost(i);
        if (actualCost[i] != cost)
        {
            printf("getCost TEST FAILED: Card %d\n", i);
            failed = 1;
        }
    }
    if (failed == 0)
    {
        printf("getCost TEST PASSED\n");
    }
    
    return 0;
}
