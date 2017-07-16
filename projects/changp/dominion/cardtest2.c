//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Card Test #2 - Adventurer

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
//global variable to check if it passed, using counter
int total_tests = 6;
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
//adventurer card - reveal cards from deck until you get 2 treasure cards, and put them into hand
//then discard the rest

//variables to set up the game
  int i, j, m;
int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
int seed = 1000;
int numPlayers = 2;
int thisPlayer = 0;
struct gameState G, testG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy, council_room};

  //intialize gameState
  initializeGame(numPlayers, k, seed, &G);
  //put adventurer card into hand
  G.hand[thisPlayer][0] = adventurer;
  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

//copy game state to test case
memcpy(&testG, &G, sizeof(struct gameState));
//play the card
cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
int treasureTest = 0; //counter to find the number of treasure cards in testG
int treasureG = 0; //counter to find the number of treasure cards you start with
//test1 - find the number of cards added to hand
printf("Test 1: Check how many cards adventurer adds\n");
//adventurer gets discarded after but it adds 2 cards, so 2-1, 1 net gain
printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "+1 Net Gain of Cards");
//test2 - make sure the last 2 cards were treasure cards
printf("Test 2: Check to see if cards added are adventurer cards");
for(i = 0; i < G.handCount[thisPlayer]; i++){
  if (G.hand[thisPlayer][i] == copper || silver || gold){
    treasureG++;
  }
}
for(i = 0; i < testG.handCount[thisPlayer]; i++){
  if (testG.hand[thisPlayer][i] == copper || silver || gold){
    treasureTest++;
  }
}
asserttrue(treasureTest == treasureG + 2, "Added cards were treasure cards");
//test3 check if it came from players deck
printf("Test 3: Check it came from player's Deck \n");
printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, "Player drew from own deck");
//test4 - check to make sure its still palyers turn
printf("Test 4: Check to make sure its still the player's turn\n");
printf("expected player = %d, current player = %d\n", testG.whoseTurn, G.whoseTurn);
asserttrue(testG.whoseTurn == G.whoseTurn, "Still the current player's turn");
//Test5 - check no more actions
printf("Test 5: Check to see after playing the card there are no more actions\n");
asserttrue(testG.numActions == 0, "No actions left after playing card");
//test6 - check to make sure card was used and discarded
printf("Test 6: Check to make sure adventurer was discarded after being played\n");
printf("played count = %d, expected = %d\n", testG.playedCardCount, testG.playedCardCount + 1);
//-1 cause arrays start at 0
asserttrue(testG.playedCards[testG.playedCardCount - 1] == adventurer, "Adventurer was the used card");
asserttrue(testG.playedCardCount == G.playedCardCount + 1, "Card was Played");
//final message to see if all passed or only some passed
if(passed_tests == 6){
  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;
}
