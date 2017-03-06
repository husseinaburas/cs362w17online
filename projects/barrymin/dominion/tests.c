/*
- Requirements
  -How to test
    - test case
    - test case
*/

//getCost()
/*
- returns cost of passed card or -1 if card invalid
  - hard code each card's true cost
  - compare returned value with hard codded values
    - do all cards
    - do invalid cards
*/
//isGameOver()
/*
- returns 1 if:
- The Province Supply pile is empty
  - create state with empty province supply:
    - state->supplyCount[Province] = 0
    - assert isGameOver == 1
    - assert state didn't change
  - create state with non empty province supply
    - init game
    - assert isGameOver !=1 ?or? assert isGameOver == 0
    - assert state didn't change

- 3 supply piles are empty
  - create state with non empty supply piles
      - init game
      - assert isGameover != 1
      - assert state didn't change
  - create state with empty 3 supplies
      - state->supplyCount[Estate] = 0
      - state->supplyCount[Duchy] = 0
      - state->supplyCount[Curse] = 0
      - assert isGameOver = 1
      - assert state didn't change
*/
//scoreFor()
/*
- returns score of passed player
  - Manually set player score
  *** note the gardens score
    - use hand only with all score cards
    - use deck only with all score cards
    - use discard only with all score cards
    - use hand deck and discard each with one estate
    - use hand deck and discard each with one curse
    - use hand deck and discard each with one duchy
    - use hand deck and discard each with one great hall
    - use hand deck and discard each with one province
    - use one garden with some amount > 10 of cards in hand discard and deck
    - combine the three with some score cards
    - no score cards
      - assert returned score == score manually set
      - assert state didnt change
*/
//fullDeckCount()
/*
- returns total amount of passed card in deck + hand + discard
  -manually set player cards
    for 0 to 10 as card
    - zero cards
      - assert return == 0
    - one in deck, one in discard and one in hand
      - assert return == 3
      - assert state didnt change

    - some amount of cards
*/

//playSmithy
/* ** note test discard smithy
- Draw 2 cards
  - create state with cards in player hand and 3 cards in deck
    - assert new handCount of whosTurn == prev HandCount + 3
    - assert new deck == prev deck -3
    - assert state didnt change except for hand and discard of whosplayer
  - create state with no cards in deck
    - assert new handCount of whosTurn == prev HandCount + 3
    - assert new deck == prev discard - 3
  - create state with 1 or 2 cards in deck
    - assert new handCount of whosTurn == prev HandCount + 3
    - assert new deck == prev deck + discard - 3

*/
//playAdventurer
/* ** note test discard adventurer
** note if player doesnt have treasure cards infnt loop
- draws cards until it gets 2 treasure cards
  - player deck has two treasures one in middle and one last and discard has none hand doesnt matter?
    - assert deck == 0
    - assert player has the two treasure cards
    - assert discard == deck
  - player deck has 2 at front
    - assert deck == prev deck -2
    - assert player has the two treasure cards
    - assert discard == prev discard
  - player deck has 2 at second and fourth positions
    - assert deck == prev deck -4
    - assert player has the two treasure cards
    - assert discard == prev discard + 2
*/
//playSalvager
/*
- + 1 buy
  - set numbBuys = 0,5
  - assert new state->numBuys == state->numBuys++
- trash a card (choice1 which is hand[player][choice1])
  - set hand with choice1 as first, last and middle with different card types
  - choice1 card not in hand
  - choice1 not in discard
  - choice1 not in deck
    - also test hand with no cards
- gain cost of trashed card
  - set state->coins = 0, state->coins = 1
  - state->coins == state->coins+ choice1 cost (hard codded)
*/
//playGreat_hall
/*
- +1 card (draws card from deck)
  - assert deck - 1
  - assert hand count+1
- +1 action
  - assert state->actions + 1
*/
