/* Author: Bilal Saleem
 * Date: 1/31/17
 * Function to test: int* kingdomCards(int, int, int, int, int, int, int, int, int, int)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0


void assert(bool j, char * msg){
	if(j == false) {
		printf("Test Failed -- %s \n", msg);
	}
}

int main() {
	int i, k; // iterator
	int numAdv, numFeast, numGarden, numMine, numVillage;  // used in TEST THREE for determining how many decks were created for									       // adventurer, feast, gardens, mine, and village
	int * kCards = 0;

	printf("unittest2.c\n");
	/************** TEST ONE *****************
 	* Should not return a null value
 	* ****************************************/

	kCards = kingdomCards(adventurer, council_room, feast, gardens,
				mine, remodel, smithy, village, baron, great_hall);

	assert(kCards != 0, "Memory not allocated");

	free(kCards);

	/************* TEST TWO ***********************
 	* Should not be able to assign non-kingdom cards
 	* *********************************************/
	
	kCards = kingdomCards(curse, estate, duchy, province, copper, silver, gold,
				adventurer, council_room, feast);

	for(i = 0; i < 10; ++i){
		assert(kCards[i] > gold, "Non-kingdom card assigned");	// all enumerated CARD types are kingdom cards after gold CARD	

	}
	
	free(kCards);

	/*************** TEST THREE ************************
 	* Should not be able to assign the same card multiple
 	* times
 	* *************************************************/
	
	numAdv = numFeast = numGarden = numMine = numVillage = 0;
	
	kCards = kingdomCards(adventurer, adventurer, feast, feast, gardens, mine,
				gardens, mine, village, adventurer);

	// check and see how many of each deck has been "created"
	for(i = 0; i < 10; ++i){
		if(kCards[i] == adventurer)
			numAdv++;
		else if(kCards[i] == feast)
			numFeast++;
		else if(kCards[i] == gardens)
			numGarden++;
		else if(kCards[i] == mine)
			numMine++;
		else if(kCards[i] == village)
			numVillage++;
	}
	
	assert(numAdv <= 1, "Multiple adventurer decks created");
	assert(numFeast <= 1, "Multiple feast decks created");
	assert(numGarden <= 1, "Multiple garden decks created");
	assert(numMine <= 1, "Multiple mine decks created");
	assert(numVillage <= 1, "Multiple village decks created");
	
	free(kCards);

	/************* TEST FOUR ******************
 	* Should not accept negative values
 	* ****************************************/

	kCards = kingdomCards(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10);

	for(i = 0; i < 10; ++i){
		assert(kCards[i] > 0, "Negative values assigned to deck array");		

	}
	
	free(kCards);

	/************* TEST FIVE ****************
 	* Should not accept card value greater than
 	* treasure_map (last enumerated CARD type)
 	* ***************************************/

	kCards = kingdomCards(treasure_map+1, treasure_map+2, treasure_map+3, treasure_map+4,
			treasure_map+5, treasure_map+6, treasure_map+7, treasure_map+8,
			treasure_map+9, treasure_map+10);

	for(i = 0; i < 10; ++i){
		assert(kCards[i] <= treasure_map, "Value greater than last enumerated CARD type assigned");
	}
	return 0;
}
