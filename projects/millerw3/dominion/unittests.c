//
//  main.c
//  assignment_3_testing
//
//  Created by William Miller on 1/31/17.
//  Copyright © 2017 William Miller. All rights reserved.
//

#include <stdio.h>
#include "cardtest1.h"
#include "cardtest2.h"
#include "cardtest3.h"
#include "cardtest4.h"
#include "unittest1.h"
#include "unittest2.h"
#include "unittest3.h"
#include "unittest4.h"
#include "testFunctions.h"
#include <errno.h>

#define MAX_PLAYERS 4


int main() {
    int numPlayers;
    
    // peforms all card and function unit tests on games of size 2 to MAX_PLAYERS
    
    for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {
        testAllPlayers(adventurer, numPlayers);
        testAllPlayers(village, numPlayers);
        testAllPlayers(smithy, numPlayers);
        testAllPlayers(great_hall, numPlayers);
        testUpdateCoins(numPlayers);
        testDicardCard(numPlayers);
        testWhoseTurn(numPlayers);
        testGainCard(numPlayers);
    }
    
    
    return 0;
}