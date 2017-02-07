#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	
	/* initialize the cost variable */
 	int cost;
 	
 	/* test name and purpose */
 	printf("-----\nStart of Unit Test 1: getCost function\n-----\n");
 	printf("\nThis test will cover the getCost function in Dominion.\n");
    printf("We will pass the different types of card numbers to the function and assert that the correct cost is returned.\n");
    printf("The cost will then be printed to the screen.\n");
    
    /* get the cost for the curse card number */
    cost = getCost(curse);
 	assert(cost == 0);
    printf("\nCurse Cost: %d coins\n", cost);
    
    /* get the cost for the estate card number */
    cost = getCost(estate);
 	assert(cost == 2);
    printf("Estate Cost: %d coins\n", cost);
    
    /* get the cost for the duchy card number */
    cost = getCost(duchy);
 	assert(cost == 5);
    printf("Duchy Cost: %d coins\n", cost);
    
    /* get the cost for the province card number */
    cost = getCost(province);
 	assert(cost == 8);
    printf("Province Cost: %d coins\n", cost);
    
    /* get the cost for the copper card number */
    cost = getCost(copper);
 	assert(cost == 0);
    printf("Copper Cost: %d coins\n", cost);
    
    /* get the cost for the silver card number */
    cost = getCost(silver);
 	assert(cost == 3);
    printf("Silver Cost: %d coins\n", cost);
    
    /* get the cost for the gold card number */
    cost = getCost(gold);
 	assert(cost == 6);
    printf("Gold Cost: %d coins\n", cost);
    
    /* get the cost for the adventurer card number */
    cost = getCost(adventurer);
 	assert(cost == 6);
    printf("Adventurer Cost: %d coins\n", cost);
    
    /* get the cost for the council_room card number */
    cost = getCost(council_room);
 	assert(cost == 5);
    printf("Council room Cost: %d coins\n", cost);
    
    /* get the cost for the feast card number */
    cost = getCost(feast);
 	assert(cost == 4);
    printf("Feast Cost: %d coins\n", cost);
    
    /* get the cost for the gardens card number */
    cost = getCost(gardens);
 	assert(cost == 4);
    printf("Gardens Cost: %d coins\n", cost);
    
    /* get the cost for the mine card number */
    cost = getCost(mine);
 	assert(cost == 5);
    printf("Mine Cost: %d coins\n", cost);
    
    /* get the cost for the remodel card number */
    cost = getCost(remodel);
 	assert(cost == 4);
    printf("Remodel Cost: %d coins\n", cost);
    
    /* get the cost for the smithy card number */
    cost = getCost(smithy);
 	assert(cost == 4);
    printf("Smithy Cost: %d coins\n", cost);
    
    /* get the cost for the village card number */
    cost = getCost(village);
 	assert(cost == 3);
    printf("Village Cost: %d coins\n", cost);
    
    /* get the cost for the baron card number */
    cost = getCost(baron);
 	assert(cost == 4);
    printf("Baron Cost: %d coins\n", cost);
    
    /* get the cost for the great_hall card number */
    cost = getCost(great_hall);
 	assert(cost == 3);
    printf("Great Hall Cost: %d coins\n", cost);
    
    /* get the cost for the minion card number */
    cost = getCost(minion);
 	assert(cost == 5);
    printf("Minion Cost: %d coins\n", cost);
    
    /* get the cost for the steward card number */
    cost = getCost(steward);
 	assert(cost == 3);
    printf("Steward Cost: %d coins\n", cost);
    
    /* get the cost for the tribute card number */
    cost = getCost(tribute);
 	assert(cost == 5);
    printf("Tribute Cost: %d coins\n", cost);
    
    /* get the cost for the ambassador card number */
    cost = getCost(ambassador);
 	assert(cost == 3);
    printf("Ambassador Cost: %d coins\n", cost);
    
    /* get the cost for the cutpurse card number */
    cost = getCost(cutpurse);
 	assert(cost == 4);
    printf("Cutpurse Cost: %d coins\n", cost);
    
    /* get the cost for the embargo card number */
    cost = getCost(embargo);
 	assert(cost == 2);
    printf("Embargo Cost: %d coins\n", cost);
    
    /* get the cost for the outpost card number */
    cost = getCost(outpost);
 	assert(cost == 5);
    printf("Outpost Cost: %d coins\n", cost);
    
    /* get the cost for the salvager card number */
    cost = getCost(salvager);
 	assert(cost == 4);
    printf("Salvager Cost: %d coins\n", cost);
    
    /* get the cost for the sea_hag card number */
    cost = getCost(sea_hag);
 	assert(cost == 4);
    printf("Sea Hag Cost: %d coins\n", cost);
    
    /* get the cost for the treasure_map card number */
    cost = getCost(treasure_map);
 	assert(cost == 4);
    printf("Treasure Map Cost: %d coins\n", cost);
    
    
    printf("\n-----\nEnd of Unit Test 1: getCost function\n-----\n");
    
    return 0;
}