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

// Test during the game
// Test when game is expected to be over
// Test province cards are empty/not empty
// Test three supply piles empty/not empty
//
int main(){
	return 0;
}