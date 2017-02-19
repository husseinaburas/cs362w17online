/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-17
**
**  Filename:       randomtestadventurer.c
**
**  Description:    randomtester for the card adventurer in dominion tests:
**
**  tester generates Pseudo random kingdom, hand, and deck cards for 2 to 4 players then
**  	conducts all tests with full output uses getCard() helper function to
**  	properly display all hand and deck card names
**  verify preconditions
**  verify adventurer is at the top of curPlayer's discard pile
**  verify curPlayer's playedCardCount has been incremented to 1
**  verify curPlayer has expected number of cards in their hand
**  verify curPlayer has expected number of cards in their deck
**  verify the fifth card in curPlayer's hand
**  verify the sixth card in curPlayer's hand
**  verify all players are as expected
**
**  run 999 more iterations of the tests with limited output that can be
**  	checked agianst the first full run to determine the specific test
**  	which failed
**
**  seed, and number of players is logged for each iteration
**
**  finally a total count of all failed tests is output to randomtestadventurer.out
**
***********************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>
#define TESTCARD "adventurer"

int main()
{
	srand(time(NULL));
	int seed = (rand() % 999) + 2;
	int bonus = 0;
	struct gameState G;
	int curPlayer = 0;
	int i = 0;
	int j = 0;
	int handCard1, handCard2, handCard3, handCard4 = 0;
	int deckCard1, deckCard2, deckCard3, deckCard4, deckCard5, deckCard6, deckCard7, deckCard8 = 0;
	int failcount = 0;
	int temp = 0;
	int kingdom1, kingdom2, kingdom3, kingdom4, kingdom5, kingdom6, kingdom7, kingdom8, kingdom9, kingdom10 = 0;

	for(j=0; j < 1000; j++)
	{
	int players = (rand() % 3) + 2;

	kingdom1 = adventurer;
	kingdom2 = (rand() % 19) + 7;
	kingdom3 = (rand() % 19) + 7;
	kingdom4 = (rand() % 19) + 7;
	kingdom5 = (rand() % 19) + 7;
	kingdom6 = (rand() % 19) + 7;
	kingdom7 = (rand() % 19) + 7;
	kingdom8 = (rand() % 19) + 7;
	kingdom9 = (rand() % 19) + 7;
	kingdom10 = (rand() % 19) + 7;
	int k[10] = {kingdom1, kingdom2, kingdom3, kingdom4, kingdom5, kingdom6, kingdom7, kingdom8, kingdom9, kingdom10};

	initializeGame(players, k, seed, &G);  // initialize game state

	printf("\n	Pseudo Random Seed is: %d \n", seed);
	printf("	Number of Players is: %d \n", players);
	printf("	Testing Card: %s \n\n", TESTCARD);

		G.playedCardCount = 0;  // curPlayer has not played any cards
		int hand[5][9];
		int deck[5][9];

		for(i=0; i < players; i++)
		{
	    handCard1 = rand() % 26;
	    handCard2 = rand() % 26;
	    handCard3 = rand() % 26;
	    handCard4 = rand() % 26;

			G.handCount[curPlayer] = 5; // curPlayer has 5 cards in their hand
	    G.hand[curPlayer][0] = adventurer;
	    G.hand[curPlayer][1] = hand[curPlayer][1] = handCard1;
	    G.hand[curPlayer][2] = hand[curPlayer][2] = handCard2;
	    G.hand[curPlayer][3] = hand[curPlayer][3] = handCard3;
	    G.hand[curPlayer][4] = hand[curPlayer][4] = handCard4;

			deckCard1 = rand() % 26;
			deckCard2 = rand() % 26;
			deckCard3 = rand() % 26;
			deckCard4 = rand() % 26;
			deckCard5 = rand() % 26;
			deckCard6 = rand() % 26;
			deckCard7 = rand() % 26;
			deckCard8 = rand() % 26;

			G.deckCount[curPlayer] = 8;  // curPlayer has 8 cards in their deck
	    G.deck[curPlayer][0] = deck[curPlayer][0] = deckCard1;
	    G.deck[curPlayer][1] = deck[curPlayer][2] = deckCard2;
	    G.deck[curPlayer][2] = deck[curPlayer][2] = deckCard3;
	    G.deck[curPlayer][3] = deck[curPlayer][3] = deckCard4;
	    G.deck[curPlayer][4] = deck[curPlayer][4] = deckCard5;
			G.deck[curPlayer][5] = deck[curPlayer][5] = deckCard6;
	    G.deck[curPlayer][6] = deck[curPlayer][6] = deckCard7;
	    G.deck[curPlayer][7] = deck[curPlayer][7] = deckCard8;

			char * card1 = {"error"};
			char * card2 = {"error"};
			char * card3 = {"error"};
			char * card4 = {"error"};

			if( j == 0 )
			{
				printf("Player %d has 5 cards in their hand:  ", curPlayer);
				testAssert(G.handCount[curPlayer] == 5);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.handCount[curPlayer] == 5);
				if(temp == 1)
					failcount++;
			}

			card1 = getCard(deckCard8);
			if( j == 0 )
			{
				printf("The card at top of the deck is a %s:  ", card1);
				testAssert(G.deck[curPlayer][7] == deckCard8);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][7] == deckCard8);
				if(temp == 1)
					failcount++;
			}

			card2 = getCard(deckCard7);
			if( j == 0 )
			{
				printf("The card 2nd from the top of the deck is a %s:  ", card2);
				testAssert(G.deck[curPlayer][6] == deckCard7);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][6] == deckCard7);
				if(temp == 1)
					failcount++;
			}

			card3 = getCard(deckCard6);
			if( j == 0 )
			{
				printf("The card 3nd from the top of the deck is a %s:  ", card3);
				testAssert(G.deck[curPlayer][5] == deckCard6);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][5] == deckCard6);
				if(temp == 1)
					failcount++;
			}

			card4 = getCard(deckCard5);
			if( j == 0 )
			{
				printf("The card 4th from the top of the deck is a %s:  ", card4);
				testAssert(G.deck[curPlayer][4] == deckCard5);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][4] == deckCard5);
				if(temp == 1)
					failcount++;
			}

			if( j == 0 )
			{
				printf("Player %d has 8 cards in their deck:  ", curPlayer);
				testAssert(G.deckCount[curPlayer] == 8);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deckCount[curPlayer] == 8);
				if(temp == 1)
					failcount++;
			}

			curPlayer++;
		}

		curPlayer = 0;

		printf("	Playing %s\n", TESTCARD);

		char * card22 = {"error"};
		char * card33 = {"error"};

		// drawntreasure, gameState, cardDrawn, z, currentPlayer, temphand[]
		// card, choice1, choice2, choice3, gameState, handPos, bonus
		cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);

		if( j == 0 )
		{
			printf("\nVerify %s is at the top of Player %d discard pile:  ", TESTCARD, curPlayer);
			testAssert(G.playedCards[curPlayer] == adventurer);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.playedCards[curPlayer] == adventurer);
			if(temp == 1)
				failcount++;
		}

		if( j == 0 )
		{
			printf("Verify Player %d's playedCardCount has been incremented to 1:  ", curPlayer);
			testAssert(G.playedCardCount == 1);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.playedCardCount == 1);
			if(temp == 1)
				failcount++;
		}

		if( j == 0 )
		{
			printf("Player %d has %d cards in their hand  \n", curPlayer, G.handCount[curPlayer]);
			printf("\n");
		}

		if( j == 0 )
		{
			printf("Player %d has %d cards in their deck  \n", curPlayer, G.deckCount[curPlayer]);
			printf("\n");
		}

		card22 = getCard(G.hand[curPlayer][5]);
		if( j == 0 )
		{
			printf("The fifth card in Player %d's hand is a %s  \n", curPlayer, card22);
			printf("\n");
		}

		card33 = getCard(G.hand[curPlayer][6]);
		if( j == 0 )
		{
			printf("The sixth card in Player %d's hand is a %s  \n", curPlayer, card33);
			printf("\n");
		}

		while(curPlayer < (players - 1))
		{
			curPlayer++;

			char * card111 = {"error"};
			char * card222 = {"error"};
			char * card333 = {"error"};
			char * card444 = {"error"};
			char * card555 = {"error"};

			if( j == 0 )
			{
				printf("Player %d has 5 cards in their hand:  ", curPlayer);
				testAssert(G.handCount[curPlayer] == 5);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.handCount[curPlayer] == 5);
				if(temp == 1)
					failcount++;
			}

			card111 = getCard(deck[curPlayer][7]);
			if( j == 0 )
			{
				printf("Player %d's top of the deck is a %s:  ", curPlayer, card111);
				testAssert(G.deck[curPlayer][7] == deck[curPlayer][7]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][7] == deck[curPlayer][7]);
				if(temp == 1)
					failcount++;
			}

			card222 = getCard(deck[curPlayer][6]);
			if( j == 0 )
			{
				printf("Player %d's 2nd card from the top of the deck is a %s:  ", curPlayer, card222);
				testAssert(G.deck[curPlayer][6] == deck[curPlayer][6]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][6] == deck[curPlayer][6]);
				if(temp == 1)
					failcount++;
			}

			card333 = getCard(deck[curPlayer][5]);
			if( j == 0 )
			{
				printf("Player %ds 3nd card from the top of the deck is a %s:  ", curPlayer, card333);
				testAssert(G.deck[curPlayer][5] == deck[curPlayer][5]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][5] == deck[curPlayer][5]);
				if(temp == 1)
					failcount++;
			}

			if( j == 0 )
			{
				printf("Player %d has 8 cards in their deck:  ", curPlayer);
				testAssert(G.deckCount[curPlayer] == 8);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deckCount[curPlayer] == 8);
				if(temp == 1)
					failcount++;
			}

			card444 = getCard(hand[curPlayer][4]);
			if( j == 0 )
			{
				printf("Verify the fifth card in Player %d's hand is a %s:  ", curPlayer, card444);
				testAssert(G.hand[curPlayer][4] == hand[curPlayer][4]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.hand[curPlayer][4] == hand[curPlayer][4]);
				if(temp == 1)
					failcount++;
			}

			card555 = getCard(hand[curPlayer][3]);
			if( j == 0 )
			{
				printf("Verify the fourth card in Player %d's hand is a %s:  ", curPlayer, card555);
				testAssert(G.hand[curPlayer][3] == hand[curPlayer][3]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.hand[curPlayer][3] == hand[curPlayer][3]);
				if(temp == 1)
					failcount++;
			}
		}
	}

	printf("\n");
	printf("total failed tests: %d\n", failcount);
	printf("\n");

	return 0;
}
