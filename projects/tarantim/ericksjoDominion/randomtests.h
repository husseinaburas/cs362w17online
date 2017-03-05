#ifndef RANDOMTESTADVENTURER_H
#define RANDOMTESTADVENTURER_H

#include "dominion.h"

struct testResults{

	int whoseTurnCnt[MAX_PLAYERS];
	int	targetcardCnt[2];
	int returnVal[2];
	int playedcardcntTest[2];
	int playedcardpileTest[2];
	int outpostTest[2];
	int phaseTest[2];	
	int numactionTest[2];
	int numbuysTest[2];
	int otherhandsTest[2];	
	int otherdecksTest[2];
	int treasureTest[2];

	//added for smithy
	int handcountTest[2];
	int deckcountTest[2];


};

#endif