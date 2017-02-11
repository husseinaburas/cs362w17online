#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setDeck(struct gameState * G, int * deck, int numCards, int playerNum);
void setHand(struct gameState * G, int * hand, int numCards, int playerNum);
/* compares to arrays in the order and equality of their values; returns 1 if not equal, 0 if equal */
int compare(int * one, int * two, int num);

int main(){
    
    // get user to provide a seed value for the srand function
    printf("Enter a random number to serve as a seed: ");
    int randomSeed;
    scanf("%d", &randomSeed);
    srand(randomSeed);
    
    /*********** RANDOMIZATION TEST 1 *************
     * Initialize the game with a random number of 
     * players between 2 and 4.  See if it passes
     * unit tests.
     **********************************************/
    printf("TEST ONE\n");
    
    struct gameState * G = newGame();       // will be used in random testing
    struct gameState * GCopy = newGame();   // used for comparisons and resetting struct G
    
    // generate a random number of players for the game within the range of 2-4 players
    // use formula numPlayers = rand() % (maxPlayers + 1 - minPlayers) + minPlayers
    int numPlayers = rand() % (4 + 1 - 2) + 2;
    
    int * kCards;       // holds the set of kingdom cards to be used in the game
    kCards = kingdomCards(smithy, adventurer, village, great_hall, council_room, feast,
                                       gardens, mine, remodel, outpost);
    
    initializeGame(numPlayers, kCards, randomSeed, G);
    
    // re-initialize deck so known what the expected cards to be drawn are
    // with this deck that cards that will be drawn are (in this order):
    // treasure_map, silver, sea_hag, and silver.  So two silver cards should
    // be added to the hand and treasure_map and sea_hag should be added to the
    // discard pile
    
    int deckInitializer[10] = {
        // bottom of deck
        copper,
        copper,
        copper,
        silver,
        smithy, //fifth from bottom
        village,
        silver,
        sea_hag,
        silver,
        treasure_map
        // top of deck
    };
    
    setDeck(G, deckInitializer, 10, 0);
    
    // re-initialize hand so hand is known before cards are drawn.
    // after adventurer is played, hand should be: copper, copper,
    // copper, copper, silver, and silver.
    int handInitializer[5] = {
        copper,
        copper,
        copper,
        copper,
        adventurer
    };
    
    setHand(G, handInitializer, 5, 0);
    
    // make sure player 1 goes first
    G->whoseTurn = 0;
    
    // make copy of the gameState for comparison and resetting purposes
    memcpy(GCopy, G, sizeof(struct gameState));
    
    // play adventurer card
    playCard(4, 0, 0, 0, G);
    
    // correct hand at this point should be: copper, copper, copper, copper,
    // silver, and silver.  determine if this is the case.
    int correctHand[6] = {
        copper, copper, copper, copper, silver, silver
    };
    
    if(compare(G->hand[0], correctHand, 6)){
        printf("Test Failed: Hand of player 1 not correct.\n");
    }
    
    // correct deck at this point should be: copper, copper, copper, silver,
    // smithy and village. determine if this is the deck found
    int correctDeck[6] = {
        copper, copper, copper, silver, smithy, village
    };
    
    if(compare(G->deck[0], correctDeck, 6)){
        printf("Test Failed: Deck of player 1 not correct. \n");
    }
    
    // reset game
    memcpy(G, GCopy, sizeof(struct gameState));
    
    /************* RANDOMIZATION TEST 2 ******************
     * This test will randomize which player plays the 
     * adventurer card. 
     *****************************************************/
    printf("TEST TWO\n");
    
    // randomly select whose turn it will be
    G->whoseTurn = rand() % numPlayers;
    
    // play adventurer card
    playCard(4, 0, 0, 0, G);
    
    // correct hand at this point should be: copper, copper, copper, copper,
    // silver, and silver.  determine if this is the case.
    if(compare(G->hand[G->whoseTurn], correctHand, 6)){
        printf("Test Failed: Hand of player 1 not correct.\n");
    }
    
    // correct deck at this point should be: copper, copper, copper, silver,
    // smithy and village. determine if this is the deck found
    if(compare(G->deck[G->whoseTurn], correctDeck, 6)){
        printf("Test Failed: Deck of player 1 not correct. \n");
    }
    
    
	return 0;
}


void setDeck(struct gameState * G, int * deck, int numCards, int playerNum) {
    int i;
    
    // set deck to new deck and update number of cards in deck count
    for(i = 0; i < numCards; ++i){
        G->deck[playerNum][i] = deck[i];
    }
    
    G->deckCount[playerNum] = numCards;
    
}

void setHand(struct gameState * G, int * hand, int numCards, int playerNum){
    int i;
    
    // set hand and update number of cards in hand
    for(i = 0; i < numCards; ++i){
        G->hand[playerNum][i] = hand[i];
    }
    
    G->handCount[playerNum] = numCards;
}


int compare(int * one, int * two, int num) {
    int i;
    
    for(i = 0; i < num; ++i){
        if(one[i] != two[i]){
            return 1;
        }
    }
    
    return 0;
}
