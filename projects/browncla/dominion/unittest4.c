/*unittest4.c*/
//int isGameOver(struct gameState *state)
/*
int isGameOver(struct gameState *state) {
  int i;
  int j;
  
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
  {
    j++;
  }
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}
*/



// DURING THE GAME
// ----------- TEST 1: Test supplyCount[province] doesn't change -----------
// ----------- TEST 2: Test supplyCount[province] is not equal to 0 -----------
// ----------- TEST 3: Test supplyCounts do not change -----------
// ----------- TEST 4: Test no three supply counts are 0 -----------

// NO PROVINCE CARDS
// ----------- TEST 5: Test supplyCount doesn't change for any cards -----------
// ----------- TEST 6: Test supplyCount[province] = 0 -----------

// 3 SUPPLY PILES AT 0
// ----------- TEST 7: Test supplyCount doesn't change for any cards -----------
// ----------- TEST 8: Test 3 piles have a count of 0 -----------

int main(){

	int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	return 0;
}