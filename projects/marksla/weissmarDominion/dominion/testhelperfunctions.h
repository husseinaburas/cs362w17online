#ifndef TESTHELPERFUNCTIONS_H
#define TESTHELPERFUNCTIONS_H

int fillPlayerHandDeckDiscardRandom(int player, struct gameState *state);

int fillPlayerHand(int player, int card, int count, struct gameState *state);

int placePlayerHand(int player, int card, int position, struct gameState *state);

int fillPlayerDeck(int player, int card, int count, struct gameState *state);

int placePlayerDeck(int player, int card, int position, struct gameState *state);

int fillPlayerDiscard(int player, int card, int count, struct gameState *state);

int placePlayerDiscard(int player, int card, int position, struct gameState *state);

int assertTest(int result, int expected, int testNumber);

int controlPlayAdventurer(struct gameState *state, int handPos);

int controlPlaySmithy(struct gameState *state, int handPos);

#endif
