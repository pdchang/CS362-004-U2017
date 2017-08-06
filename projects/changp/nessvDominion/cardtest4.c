//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Card Test #3 - village

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"
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

int main(){
  //village card +2 actions, +1 card
  int i, j, m;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherDude = 1; //other player variable number
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy, council_room};
  int checkactions = 2;
  //intialize gameState
  initializeGame(numPlayers, k, seed, &G);
  //put village card into hand
  G.hand[thisPlayer][0] = village;
  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  memcpy(&testG, &G, sizeof(struct gameState));
  //play the card
  cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

  //test1 - check to make sure 1 card was added, so 1 card added, vilalge card discarded, so net gain 0
  printf("Test 1: Check how many cards village adds\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer], " Zero Net Gain of Cards");

  //test2 - check to see if 2 actions were added
  printf("Test 2: Check number of actions");
  printf("num actions = %d, expected num of actions %d\n", testG.numActions, checkactions);
  asserttrue(testG.numActions == checkactions, "+2 actions are added");

  //test3 - check player turn
  printf("Test 3: Check to make sure its still the player's turn\n");
  printf("expected player = %d, current player = %d\n", testG.whoseTurn, G.whoseTurn);
  asserttrue(testG.whoseTurn == G.whoseTurn, "Still the current player's turn");

  //test4 - check if card came from players own pile
  printf("Test 4: Check it came from player's Deck \n");
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1, "Player drew from own deck");

//TEST5 - make sure village is played and and used
printf("Test 5: Check to make sure smithy was discarded after being played\n");
printf("played count = %d, expected = %d\n", testG.playedCardCount, testG.playedCardCount + 1);
//-1 cause arrays start at 0
asserttrue(testG.playedCards[testG.playedCardCount - 1] == village, "village was the used card");
asserttrue(testG.playedCardCount == G.playedCardCount + 1, "Card was Played");

//final message to see if everyting passed or only some passed
if(passed_tests == 5){
  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;
}
