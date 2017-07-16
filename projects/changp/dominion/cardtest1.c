//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Card Test #1 - smithy

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
//global variable to check if it passed, using counter
int total_tests = 5;
int passed_tests = 0; //counter


//own asserttrue function
void asserttrue(int tf, char *test){
  if (tf){
    printf("TEST: %s SUCCESSFULLY Completed\n", test);
    passed_tests++;
  }
  else{
    printf("TEST: %s Failed\n", test);
  }
}

//main
int main(){
  //variables to set up the game
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
struct gameState G, testG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

//intialize gameState
initializeGame(numPlayers, k, seed, &G);
//put smithy card into hand
G.hand[thisPlayer][0] = smithy;
printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
//TEST1 - check that 3 cards are drawn
//3 cards are drawn, and smithy is discarded, so actually gain 2 cards
printf("Test 1: +3 Cards and discard smithy\n");
//copy game state to test case
memcpy(&testG, &G, sizeof(struct gameState));
//play the card
cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
//test 1 assert to see if those total of 2 cards are gained
printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "+2 Net Gain of Cards");
//TEST2 - make sure they got it from the write deck
printf("Test 2: Check it came from player's Deck \n");
printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3, "Player drew from own deck");
//TEST3 - make sure smithy is played and and used
printf("Test 3: Check to make sure smithy was discarded after being played\n");
printf("played count = %d, expected = %d\n", testG.playedCardCount, testG.playedCardCount + 1);
//-1 cause arrays start at 0
asserttrue(testG.playedCards[testG.playedCardCount - 1] == smithy, "Smithy was the used card");
asserttrue(testG.playedCardCount == G.playedCardCount + 1, "Card was Played");
//TEST4 - make sure its still the current Players turn
printf("Test 4: Check to make sure its still the player's turn\n");
printf("expected player = %d, current player = %d\n", testG.whoseTurn, G.whoseTurn);
asserttrue(testG.whoseTurn == G.whoseTurn, "Still the current player's turn");
//Test5 - Make sure there there are no more actions after playing the card
printf("Test 5: Check to see after playing the card there are no more actions\n");
asserttrue(testG.numActions == 0, "No actions left after playing card");
//final message to see if all passed or only some passed
if(passed_tests == 5){
  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;
}
