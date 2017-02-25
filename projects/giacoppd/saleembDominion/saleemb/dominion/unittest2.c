//Dominic Giacoppe, SF2, unit test 2
//tests getCost
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
{
if(getCost(duchy) != 5)
	aborttest("Duchy's cost is wrong unittest2");
	
if(getCost(gold) != 6)
	aborttest("gold's cost is wrong unittest2");
	
if(getCost(gardens) != 4)
	aborttest("gardens's cost is wrong unittest2");
	
if(getCost(remodel) != 4)
	aborttest("remodel's cost is wrong unittest2");
	
if(getCost(estate) != 2)
	aborttest("estate's cost is wrong unittest2");
	
if(getCost(2133) != -1)
	aborttest("Returns a real value for a bad card, unittest2");
	
return 0;
}
