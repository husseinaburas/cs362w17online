//Dominic Giacoppe, SF2, unit test 3
//tests kingdomCards
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"

void aborttest(char * msg)
{
printf("%s\n", msg);
exit(1);
//this func just prints things for me
}

int main()
{ //tries to create a random set of cards.
int cardset[10] = {sea_hag, duchy, mine, feast, gardens, steward, village, cutpurse, salvager, smithy}; 
int * returnedset = kingdomCards(sea_hag, duchy, mine, feast, gardens, steward, village, cutpurse, salvager, smithy);
if(returnedset == NULL)
	aborttest("Pointer is null, unittest3");
int x = 0;
for(; x < 10; x++)
{
	if(cardset[x] != returnedset[x])
	{
		printf("%d\n", x);
		aborttest("kingdomCards failed to produce the proper card for the above tick unittest 3");
	}
}
return 0;
}
