#ifndef _TESTS_HELPERS
#define _TESTS_HELPERS

#define NOISY_TEST 1
#define NUM_RANDOM_TESTS 80

void asserttrue(int condition, int* r_main);
char* getCardName(int card);
void printCurrentPlayer(int player, struct gameState* state);
int getNumCardsHand(int player, int card, struct gameState* state);
int getNumCardsDeck(int player, int card, struct gameState* state);
int getNumCardsDiscard(int player, int card, struct gameState* state);
int randomInRange(int max);
void testCardGeneralRequirements(int* caseCount, char* casename, int* testCount, int* r_main,
    int card, int choice1, int choice2, int choice3, int handPos, int* bonus,
    struct gameState* G, struct gameState* preG);
struct gameState randomGameState();

#endif