//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Card Test #3 - council_room

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"
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
//council room cards +4 cards , +1 buy, other player draws one
int i, j, m;
int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
int seed = 1000;
int numPlayers = 2;
int thisPlayer = 0;
int otherDude = 1; //other player variable number
struct gameState G, testG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
sea_hag, tribute, smithy, council_room};

//intialize gameState
initializeGame(numPlayers, k, seed, &G);
//put council_room card into hand
G.hand[thisPlayer][0] = council_room;
printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
memcpy(&testG, &G, sizeof(struct gameState));
//play the card
cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
//test1 - check 4 cards are added, -1 for the council_room card being discarded, net gain 3
printf("Test 1: Check how many cards council_room adds\n");
printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 3, "+3 Net Gain of Cards");
//test2 - check to make sure other play gained a card
printf("Test2: Check if other player gained cards\n");
printf("other hand count = %d, expected = %d \n", testG.handCount[otherDude], G.handCount[otherDude] +1);
asserttrue(testG.handCount[otherDude] == G.handCount[otherDude] + 1, "Other Player gained a card too");
//test3 - check if there are no more actions
printf("Test 3: Check to see after playing the card there are no more actions\n");
asserttrue(testG.numActions == 0, "No actions left after playing card");
//test4 - check players turn is right
printf("Test 4: Check to make sure its still the player's turn\n");
printf("expected player = %d, current player = %d\n", testG.whoseTurn, G.whoseTurn);
asserttrue(testG.whoseTurn == G.whoseTurn, "Still the current player's turn");
//test5 - check to make sure there is another buy
printf("Test 5: Check to make sure council_room added a buy\n");
printf("num buys = %d, expected num buys = %d\n", testG.numBuys, G.numBuys + 1);
asserttrue(testG.numBuys == G.numBuys + 1, "check the num buys");
//test6 - check to make sure card was used and discarded
printf("Test 6: Check to make sure adventurer was discarded after being played\n");
printf("played count = %d, expected = %d\n", testG.playedCardCount, testG.playedCardCount + 1);
//-1 cause arrays start at 0
asserttrue(testG.playedCards[testG.playedCardCount - 1] == council_room, "council_room was the used card");
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
