/*unittest3.c*/

//int endTurn(struct gameState *state);
/*
int endTurn(struct gameState *state) {
  int k;
  int i;
  int currentPlayer = whoseTurn(state);
  
  //Discard hand
  for (i = 0; i < state->handCount[currentPlayer]; i++){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
    state->hand[currentPlayer][i] = -1;//Set card to -1
  }
  state->handCount[currentPlayer] = 0;//Reset hand count
    
  //Code for determining the player
  if (currentPlayer < (state->numPlayers - 1)){ 
    state->whoseTurn = currentPlayer + 1;//Still safe to increment
  }
  else{
    state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
  }

  state->outpostPlayed = 0;
  state->phase = 0;
  state->numActions = 1;
  state->coins = 0;
  state->numBuys = 1;
  state->playedCardCount = 0;
  state->handCount[state->whoseTurn] = 0;

  //int k; move to top
  //Next player draws hand
  for (k = 0; k < 5; k++){
    drawCard(state->whoseTurn, state);//Draw a card
  }

  //Update money
  updateCoins(state->whoseTurn, state , 0);

  return 0;
}
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

	// ----------- TEST 1: Test that prior player discard pile increased by handCount  -----------
	// ----------- TEST 2: Test that prior player hand is all set to -1 -----------
	// ----------- TEST 3: Test that prior player handCount is 0 -----------
	// ----------- TEST 4: Test that current player is next number -----------
	// ----------- TEST 5: Test that outpostPlayed is 0 -----------
	// ----------- TEST 6: Test that phase is 0 -----------
	// ----------- TEST 7: Test that current player has 1 action -----------
	// ----------- TEST 8: Test that current player has 1 buy -----------
	// ----------- TEST 9: Test that current player has 0 played cards ----------- 
	// ----------- TEST 10: Test that current player handCount is 5 -----------
	// ----------- TEST 11: Test that current player's hand is not all -1 -----------
	// ----------- TEST 12: Test that currentPlayer has the correct number of coins -----------
	return 0;
}