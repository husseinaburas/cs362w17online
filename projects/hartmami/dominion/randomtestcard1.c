/***********************************************************************************************
**
**  Author:       Michael Hartman
**
**  Date:           2017-02-17
**
**  Filename:       randomtestcard1.c
**
**  Description:    randomtester for the card smithy in dominion tests:
**
**  verify preconditions
**  verify smithy is at the top of curPlayer's discard pile
**  verify curPlayer's playedCardCount has been incremented to 1
**  verify curPlayer has 7 cards in their hand
**  error verify curPlayer has 6 cards in their hand due to (assignment2 bug)
**  verify curPlayer has 4 cards in their deck
**  error curPlayer has 5 cards in their deck due to bug
**  verify the fifth card in curPlayer's hand is correct
**  verify the sixth card in curPlayer's hand is a correct
**  verify the seventh card in curPlayer's hand is a correct
**  previous tests verify cards came from curPlayer's deck into their hand
**  verify all players are as expected
**  verify treasure_map is 26
**  run 1000 iterations
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
#define TESTCARD "smithy"

int main()
{
	srand(time(NULL));
	int seed = (rand() % 999) + 1;
	int bonus = 0;
	int bug = 0;  // if initialized to 0 then test will run additional known bug tests
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int curPlayer = 0;
	int i = 0;
	int j = 0;
	int handCard1, handCard2, handCard3, handCard4 = 0;
	int deckCard1, deckCard2, deckCard3, deckCard4, deckCard5, deckCard6, deckCard7 = 0;
	int failcount = 0;
	int temp = 0;

	for(j=0; j < 1000; j++)
	{
	int players = (rand() % 3) + 2;
	initializeGame(players, k, seed, &G);  // initialize game state for 2 players

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
	    G.hand[curPlayer][0] = smithy;
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

			G.deckCount[curPlayer] = 7;  // curPlayer has 7 cards in their deck
	    G.deck[curPlayer][0] = deck[curPlayer][0] = deckCard1;
	    G.deck[curPlayer][1] = deck[curPlayer][2] = deckCard2;
	    G.deck[curPlayer][2] = deck[curPlayer][2] = deckCard3;
	    G.deck[curPlayer][3] = deck[curPlayer][3] = deckCard4;
	    G.deck[curPlayer][4] = deck[curPlayer][4] = deckCard5;
			G.deck[curPlayer][5] = deck[curPlayer][5] = deckCard6;
	    G.deck[curPlayer][6] = deck[curPlayer][6] = deckCard7;

			char * card1 = {"error"};
			char * card2 = {"error"};
			char * card3 = {"error"};

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

			card1 = getCard(deckCard7);
			if( j == 0 )
			{
				printf("The card at top of the deck is a %s:  ", card1);
				testAssert(G.deck[curPlayer][6] == deckCard7);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][6] == deckCard7);
				if(temp == 1)
					failcount++;
			}


			card2 = getCard(deckCard6);
			if( j == 0 )
			{
				printf("The card 2nd from the top of the deck is a %s:  ", card2);
				testAssert(G.deck[curPlayer][5] == deckCard6);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][5] == deckCard6);
				if(temp == 1)
					failcount++;
			}


			card3 = getCard(deckCard5);
			if( j == 0 )
			{
				printf("The card 3nd from the top of the deck is a %s:  ", card3);
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
				printf("Player %d has 7 cards in their deck:  ", curPlayer);
				testAssert(G.deckCount[curPlayer] == 7);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deckCount[curPlayer] == 7);
				if(temp == 1)
					failcount++;
			}

			curPlayer++;
		}

		curPlayer = 0;

		printf("	Playing %s\n", TESTCARD);


		char * card11 = {"error"};
		char * card22 = {"error"};
		char * card33 = {"error"};

		// gameState, currentPlayer, handPos
		// card, choice1, choice2, choice3, gameState, handPos, bonus
		cardEffect(smithy, 0, 0, 0, &G, 0, &bonus);

		if( j == 0 )
		{
			printf("Verify %s is at the top of Player %d discard pile:  ", TESTCARD, curPlayer);
			testAssert(G.playedCards[curPlayer] == smithy);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.playedCards[curPlayer] == smithy);
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
			printf("Verify Player %d has 7 cards in their hand:  ", curPlayer);
			testAssert(G.handCount[curPlayer] == 7);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.handCount[curPlayer] == 7);
			if(temp == 1)
				failcount++;
		}

		if( bug == 0 )
		{
			if( j == 0 )
			{
				printf("	Verify Player %d has 6 cards in their hand due to bug:  ", curPlayer);
				testAssert(G.handCount[curPlayer] == 6);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.handCount[curPlayer] == 6);
				if(temp == 1)
					failcount++;
			}
		}

		if( j == 0 )
		{
			printf("Verify Player %d has 4 cards in their deck:  ", curPlayer);
			testAssert(G.deckCount[curPlayer] == 4);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.deckCount[curPlayer] == 4);
			if(temp == 1)
				failcount++;
		}

		if( bug == 0 )
		{
			if( j == 0 )
			{
				printf("	Player %d has 5 cards in their deck due to bug:  ", curPlayer);
				testAssert(G.deckCount[curPlayer] == 5);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deckCount[curPlayer] == 5);
				if(temp == 1)
					failcount++;
			}
		}

		if( j == 0 )
		{
			printf("Verify Player %d has 4 cards in their deck:  ", curPlayer);
			testAssert(G.deckCount[curPlayer] == 4);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.deckCount[curPlayer] == 4);
			if(temp == 1)
				failcount++;
		}

		card11 = getCard(deck[curPlayer][6]);
		if( j == 0 )
		{
			printf("Verify the fifth card in Player %d's hand is a %s:  ", curPlayer, card11);
			testAssert(G.hand[curPlayer][5] == deck[curPlayer][6]);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.hand[curPlayer][5] == deck[curPlayer][6]);
			if(temp == 1)
				failcount++;
		}

		card22 = getCard(deck[curPlayer][5]);
		if( j == 0 )
		{
			printf("Verify the sixth card in Player %d's hand is a %s:  ", curPlayer, card22);
			testAssert(G.hand[curPlayer][6] == deck[curPlayer][5]);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.hand[curPlayer][6] == deck[curPlayer][5]);
			if(temp == 1)
				failcount++;
		}

		card33 = getCard(deck[curPlayer][4]);
		if( j == 0 )
		{
			printf("Verify the seventh card in Player %d's hand is a %s:  ", curPlayer, card33);
			testAssert(G.hand[curPlayer][7] == deck[curPlayer][4]);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(G.hand[curPlayer][7] == deck[curPlayer][4]);
			if(temp == 1)
				failcount++;
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

			card111 = getCard(deck[curPlayer][6]);
			if( j == 0 )
			{
				printf("Player %d's top of the deck is a %s:  ", curPlayer, card111);
				testAssert(G.deck[curPlayer][6] == deck[curPlayer][6]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][6] == deck[curPlayer][6]);
				if(temp == 1)
					failcount++;
			}

			card222 = getCard(deck[curPlayer][5]);
			if( j == 0 )
			{
				printf("Player %d's 2nd card from the top of the deck is a %s:  ", curPlayer, card222);
				testAssert(G.deck[curPlayer][5] == deck[curPlayer][5]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][5] == deck[curPlayer][5]);
				if(temp == 1)
					failcount++;
			}

			card333 = getCard(deck[curPlayer][4]);
			if( j == 0 )
			{
				printf("Player %ds 3nd card from the top of the deck is a %s:  ", curPlayer, card333);
				testAssert(G.deck[curPlayer][4] == deck[curPlayer][4]);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deck[curPlayer][4] == deck[curPlayer][4]);
				if(temp == 1)
					failcount++;
			}

			if( j == 0 )
			{
				printf("Player %d has 7 cards in their deck:  ", curPlayer);
				testAssert(G.deckCount[curPlayer] == 7);
				printf("\n");
			}
			if( j > 0 )
			{
				temp = testAssert(G.deckCount[curPlayer] == 7);
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

		if( j == 0 )
		{
			printf("Verify treasure_map is 26:  ");
			testAssert(treasure_map == 26);
			printf("\n");
		}
		if( j > 0 )
		{
			temp = testAssert(treasure_map == 26);
			if(temp == 1)
				failcount++;
		}
	}

	printf("\n");
	printf("total failed tests: %d\n", failcount);
	printf("\n");

	return 0;
}
