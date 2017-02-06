/*unittest2.c*/

/* int buyCard(int supplyPos, struct gameState *state) {
  int who;
  if (DEBUG){
    printf("Entering buyCard...\n");
  }
  who = state->whoseTurn;

  if (state->numBuys < 1){
    if (DEBUG)
      printf("You do not have any buys left\n");
    return -1;
  } else if (supplyCount(supplyPos, state) <1){
    if (DEBUG)
      printf("There are not any of that type of card left\n");
    return -1;
  } else if (state->coins < getCost(supplyPos)){
    if (DEBUG) 
      printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
    return -1;
  } else {
    state->phase=1;
    //state->supplyCount[supplyPos]--;
    gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
  
    state->coins = (state->coins) - (getCost(supplyPos));
    state->numBuys--;
    if (DEBUG)
      printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
  }

  //state->discard[who][state->discardCount[who]] = supplyPos;
  //state->discardCount[who]++;
    
  return 0;
*/

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


// NOTE CHECK RETURN VALUE BEFORE DOING CALCULATIONS

	// ----------- TEST 1: Test for number of buys for players turn decreases by 1  -----------

	// ----------- TEST 2: Test that the number of buys does not go negative -----------

	// ----------- TEST 3: Test that the number of coins for current player decreased appropriately -----------

	// ----------- TEST 4: Test that the current players amount of coins did not go below 0 -----------

	// ----------- TEST 5: Test that the total number of cards the player has increases by 1 (sum of all decks) -----------

	// ----------- TEST 6: Test that the other player does not gain a card -----------

	// ----------- TEST 7: Test that the other player does not lose a card -----------

	// ----------- TEST 8: Test that the supply count for bought card decreased by 1 -----------

	// ----------- TEST 9: Test that the supply count for bought card did not go below 0 -----------

	// ----------- TEST 10: Test that cannot buy a card if number of buys is 0 -----------

	// ----------- TEST 11: Test that cannot buy a card if no cards of that type available -----------

	// ----------- TEST 12: Test that cannot buy a card if player does not have enough money -----------




	return 0;
}
