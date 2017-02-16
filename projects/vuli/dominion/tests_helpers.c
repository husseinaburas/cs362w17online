#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "tests_helpers.h"



/*********************************************************************
* asserttrue()
* Params:
*     condition: statement to check validity; true if > 0
*     r_main: increments if pass condition
* Returns: None.
*********************************************************************/
void asserttrue(int condition, int* r_main) {
  if (condition > 0) {
    printf("TEST PASSED!\n");
    (*r_main)++;
  } else {
    printf("TEST FAILED -- BUG ALERT!!!\n");
  }
}


/*********************************************************************
* getCardName()
* Returns: String of card name.
*********************************************************************/
char* getCardName(int card) {
  /* Array of card names, same order as enum CARD */
  char* cardNames[] = 
    {"curse",
     "estate",
     "duchy",
     "province",

     "copper",
     "silver",
     "gold",

     "adventurer",
     "council_room",
     "feast",
     "gardens",
     "mine",
     "remodel",
     "smithy",
     "village",

     "baron",
     "great_hall",
     "minion",
     "steward",
     "tribute",

     "ambassador",
     "cutpurse",
     "embargo",
     "outpost",
     "salvager",
     "sea_hag",
     "treasure_map"
    };

    return cardNames[card];
}


/********************************************************************
* printCurrentPlayer()
* Returns: Print current player's deck, hand, discard pile
********************************************************************/
void printCurrentPlayer(int currentPlayer, struct gameState* state) {
  int i;
  printf("---Player %d's Hand count=%d\n", currentPlayer, state->handCount[currentPlayer]);
  for (i=0; i<state->handCount[currentPlayer]; i++)
    printf("%s\t", getCardName(state->hand[currentPlayer][i]));
  printf("\n");
  printf("---Player %d's Deck count=%d\n", currentPlayer, state->deckCount[currentPlayer]);
  for (i=0; i<state->deckCount[currentPlayer]; i++)
    printf("%s\t", getCardName(state->deck[currentPlayer][i]));
  printf("\n");
  printf("---Player %d's Discard count=%d\n", currentPlayer, state->discardCount[currentPlayer]);
  for (i=0; i<state->discardCount[currentPlayer]; i++)
    printf("%s\t", getCardName(state->discard[currentPlayer][i]));
  printf("\n");
}


/*********************************************************************
* getNumCardsHand()
* Returns: Return number of specific card in player's Hand
*********************************************************************/
int getNumCardsHand(int player, int card, struct gameState* state) {
    int count=0, i;
    for (i=0; i<state->handCount[player]; i++) {
        if (state->hand[player][i] == card) count++;
    }
    return count;
}


/*********************************************************************
* getNumCardsDeck()
* Returns: Return number of specific card in player's Deck
*********************************************************************/
int getNumCardsDeck(int player, int card, struct gameState* state) {
    int count=0, i;
    for (i=0; i<state->deckCount[player]; i++) {
        if (state->deck[player][i] == card) count++;
    }
    return count;
}


/*********************************************************************
* getNumCardsDiscard()
* Returns: Return number of specific card in player's Discard
*********************************************************************/
int getNumCardsDiscard(int player, int card, struct gameState* state) {
    int count=0, i;
    for (i=0; i<state->discardCount[player]; i++) {
        if (state->discard[player][i] == card) count++;
    }
    return count;
}



/*********************************************************************
* randomInRange()
* Returns random integer in range [0, max]
*********************************************************************/
int randomInRange(int max) {
  int out;
  do {
    out = floor(Random() * (max+1));
  } while (out > max);
  return out;
}


/*********************************************************************
* testCardGeneralRequirements()
* Test general requirements that apply to most cards and Deck+Hand+Discard 
* scenarios:
* -- Decreases Hand+Deck+Discard count by 1
* -- Increases playedCardCount by 1
* -- Adds card previously at handPos to playedCards
* -- Removes card previously at handPos from hand
* -- Does not change game state except for current player
* Params:
*   G: original game state (will be changed after function executes)
*   preG: where copy of original game state will be stored
*********************************************************************/
void testCardGeneralRequirements(int* caseCount, char* casename, int* testCount, int* r_main,
    int card, int choice1, int choice2, int choice3, int handPos, int* bonus,
    struct gameState* G, struct gameState* preG) 
{
    int count1, count2, r, i, j;
    struct gameState preG_mod;
    int player = G->whoseTurn;
    int G_HandDeckDiscard[2*MAX_DECK + MAX_HAND], preG_HandDeckDiscard[2*MAX_DECK + MAX_HAND];
    int G_HandDeckDiscardCount, preG_HandDeckDiscardCount;

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Successful execution\n", *caseCount, casename, ++(*testCount));
    memcpy(preG, G, sizeof(struct gameState)); 
    r = cardEffect(card, choice1, choice2, choice3, G, handPos, bonus);
    asserttrue(r==0, r_main); 
    if (NOISY_TEST) {
        printf("Before execution:\n");
        printCurrentPlayer(player, preG);
        printf("After execution:\n");
        printCurrentPlayer(player, G);
    }   

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand+Deck+Discard count decreased by 1\n", *caseCount, casename, ++(*testCount));
    count1 = preG->handCount[player] + preG->discardCount[player] + preG->deckCount[player];
    count2 = G->handCount[player] + G->discardCount[player] + G->deckCount[player];
    asserttrue(count1==count2+1, r_main);
    if (NOISY_TEST) printf("Count before: %d\nCount after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Played card count increased by 1\n", *caseCount, casename, ++(*testCount));
    count1 = preG->playedCardCount;
    count2 = G->playedCardCount;
    asserttrue(count2==count1+1, r_main);
    if (NOISY_TEST) printf("Played count before: %d\nPlayed count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Card at handPos added to playedCards\n", *caseCount, casename, ++(*testCount));
    asserttrue(G->playedCards[G->playedCardCount-1] == preG->hand[player][handPos], r_main);

    // /*********/
    // /* This test produces incorrect result if player draws exactly the same card as the card previously at handPos -- removed for now */
    // printf("---------CASE %d: %s -- TEST %d: Card at handPos removed from current player's hand\n", *caseCount, casename, ++(*testCount));
    // count1 = getNumCardsHand(player, card, preG);
    // count2 = getNumCardsHand(player, card, G);
    // asserttrue(count2==count1-1, r_main);
    // if (NOISY_TEST) printf("Card at handPos: %s\nCard count before: %d\nCard count after: %d\n", 
    //     getCardName(preG->hand[player][handPos]), count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged except for played card and current player\n", *caseCount, casename, ++(*testCount));
    memcpy(&preG_mod, G, sizeof(struct gameState));
    preG_mod.handCount[player] = G->handCount[player];  // make current player's hand, deck, discard before execution equal after execution
    preG_mod.deckCount[player] = G->deckCount[player];
    preG_mod.discardCount[player] = G->discardCount[player];
    preG_mod.playedCardCount = G->playedCardCount;
    memcpy(preG_mod.hand[player], G->hand[player], sizeof(int)*MAX_HAND);
    memcpy(preG_mod.deck[player], G->deck[player], sizeof(int)*MAX_DECK);
    memcpy(preG_mod.discard[player], G->discard[player], sizeof(int)*MAX_DECK);
    memcpy(preG_mod.playedCards, G->playedCards, sizeof(int)*MAX_DECK);
    asserttrue(memcmp(G, &preG_mod, sizeof(struct gameState))==0, r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards in Hand+Deck+Discard unchanged except removing played card\n", *caseCount, casename, ++(*testCount));
    // Copy Hand+Deck+Discard before execution to preG_HandDeckDiscard
    preG_HandDeckDiscardCount = 0;
    for (i=0; i<preG->handCount[player]; i++) {
        preG_HandDeckDiscard[preG_HandDeckDiscardCount] = preG->hand[player][i];
        preG_HandDeckDiscardCount++;
    }
    for (i=0; i<preG->deckCount[player]; i++) {
        preG_HandDeckDiscard[preG_HandDeckDiscardCount] = preG->deck[player][i];
        preG_HandDeckDiscardCount++;
    }
    for (i=0; i<preG->discardCount[player]; i++) {
        preG_HandDeckDiscard[preG_HandDeckDiscardCount] = preG->discard[player][i];
        preG_HandDeckDiscardCount++;
    }
    // Copy Hand+Deck+Discard after execution to G_HandDeckDiscard
    G_HandDeckDiscardCount = 0;
    for (i=0; i<G->handCount[player]; i++) {
        G_HandDeckDiscard[G_HandDeckDiscardCount] = G->hand[player][i];
        G_HandDeckDiscardCount++;
    }
    for (i=0; i<G->deckCount[player]; i++) {
        G_HandDeckDiscard[G_HandDeckDiscardCount] = G->deck[player][i];
        G_HandDeckDiscardCount++;
    }
    for (i=0; i<G->discardCount[player]; i++) {
        G_HandDeckDiscard[G_HandDeckDiscardCount] = G->discard[player][i];
        G_HandDeckDiscardCount++;
    }
    // Make -1 all cards in preG_HandDeckDiscard that appear in G_HandDeckDiscard, and vice versa
    for (i=0; i<preG_HandDeckDiscardCount; i++) {
        for (j=0; j<G_HandDeckDiscardCount; j++) {
            if (preG_HandDeckDiscard[i] == G_HandDeckDiscard[j] && preG_HandDeckDiscard[i] != -1) {
                preG_HandDeckDiscard[i] = -1;
                G_HandDeckDiscard[j] = -1;
                break;
            }
        }
    }
    for (i=0; i<G_HandDeckDiscardCount; i++) {
        for (j=0; j<preG_HandDeckDiscardCount; j++) {
            if (G_HandDeckDiscard[i] == preG_HandDeckDiscard[j] && G_HandDeckDiscard[i] != -1) {
                G_HandDeckDiscard[i] = -1;
                preG_HandDeckDiscard[j] = -1;
                break;
            }
        }
    }
    // There should be no -1 cards in preG_HandDeckDiscard and G_HandDeckDiscard now (except played card)
    count1 = 0;
    for (i=0; i<preG_HandDeckDiscardCount; i++) {
        if (preG_HandDeckDiscard[i] > -1 && preG_HandDeckDiscard[i] != card) {
            count1++;
            if (NOISY_TEST) printf("Card in Hand+Deck+Discard before but not after #%d: %s\n", count1, getCardName(preG_HandDeckDiscard[i]));
        }
    }
    count2 = 0;
    for (i=0; i<G_HandDeckDiscardCount; i++) {
        if (G_HandDeckDiscard[i] > -1) {
            count2++;
            if (NOISY_TEST) printf("Card in Hand+Deck+Discard after but not before #%d: %s\n", count2, getCardName(G_HandDeckDiscard[i]));
        }
    }
    asserttrue(count1==0 && count2==0, r_main);
}


/*********************************************************************
* randomGameState()
* Returns random game state that satisfies the following requirements:
* -- Player in range 0..MAX_PLAYERS-1
* -- Deck, Discard, and Played count in range 0..MAX_DECK-1
* -- Hand count of Player in range 0..MAX_HAND-1
* -- All cards in Player's Deck, Discard, Hand, Played in range curse..treasure_map
*********************************************************************/
struct gameState randomGameState() {
    struct gameState G;
    int player, i;

    /* Fill game state with random bytes */
    for (i=0; i < sizeof(struct gameState); i++) {
        ((char*)&G)[i] = floor(Random() * 256);
    }
    
    /* Construct player in range 0..MAX_PLAYERS-1; Deck, Discard, Played count in range 0..MAX_DECK-1;
    Hand count in range 0..MAX_HAND-1 */
    G.whoseTurn = randomInRange(MAX_PLAYERS-1);
    player = G.whoseTurn;
    G.deckCount[player] = randomInRange(MAX_DECK-1);
    G.discardCount[player] = randomInRange(MAX_DECK-1);
    G.handCount[player] = randomInRange(MAX_HAND-1);
    G.playedCardCount = randomInRange(MAX_DECK-1);
    // G.deckCount[player] = 40;
    // G.discardCount[player] = 15;
    // G.handCount[player] = 9;
    // G.playedCardCount = 12;

    /* Construct Deck, Discard, Hand, Played with cards in range curse..treasure_map */
    for (i=0; i<G.deckCount[player]; i++) {
        G.deck[player][i] = randomInRange(treasure_map);
    }
    for (i=0; i<G.discardCount[player]; i++) {
        G.discard[player][i] = randomInRange(treasure_map);
    }
    for (i=0; i<G.handCount[player]; i++) {
        G.hand[player][i] = randomInRange(treasure_map);
    }
    for (i=0; i<G.playedCardCount; i++) {
        G.playedCards[i] = randomInRange(treasure_map);
    }

    return G;
}

