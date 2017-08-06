//Philip Chang changp@oregonstate.edu
//CS 362 - Assignment 4
//Random Test village

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"


int total_tests = 6 * 500; //6 assert trues, 500 differnt random combos
int passed_tests = 0;
//own assert function
void asserttrue(int tf, char *test){
  if (tf){
    //printf("TEST: %s SUCCESSFULLY Completed\n", test);
    //only print out failed tests since lots of tests
    //since so many tests, we'll only print if it fails
    passed_tests++;
  }
  else{
    printf("TEST: %s Failed\n", test);
  }
}
//void adventurerCard(int handpos, struct gameState *state)


int main(){
  //seed Random
  srand(time(NULL));

  //variables for the game
int handpos; //randomize this
int seed;//randomize this
int numPlayers; //randomize this between 2 and 4
int thisPlayer;
int test_count = 0;
int checkactions = 2;
struct gameState G, testG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy, council_room};
printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
printf ("RANDOM TESTS.\n");
do{
  printf("TEST # %d: \n", test_count);
  numPlayers = rand() % 4 + 2; //generates 2-4 players
  thisPlayer = rand() % numPlayers;//between 0 and numPlayers - 1
  seed = rand();//random seed
  initializeGame(numPlayers, k, seed, &G); //initialize gameState
  memcpy(&testG, &G, sizeof(struct gameState)); //copy game state
  //randomize the counts for the player
  G.deckCount[thisPlayer] = rand() % MAX_DECK + 1; //always at least 1 card
  G.discardCount[thisPlayer] = rand() % MAX_DECK + 1; //always at least 1 card
  G.handCount[thisPlayer] = rand() % MAX_HAND + 1; //always at least 1 card
  handpos = rand() % G.handCount[thisPlayer]; // 0 to handcount - 1
  G.hand[thisPlayer][handpos] = adventurer;
  //villageCard(handpos, &testG);
  //using victors refractored code
  call_village(&testG, handpos);
  printf("Check how many cards village adds\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer], " Zero Net Gain of Cards");

  //test2 - check to see if 2 actions were added
  printf("Check number of actions");
  printf("num actions = %d, expected num of actions %d\n", testG.numActions, checkactions);
  asserttrue(testG.numActions == checkactions, "+2 actions are added");

  //test3 - check player turn
  printf("Check to make sure its still the player's turn\n");
  printf("expected player = %d, current player = %d\n", testG.whoseTurn, G.whoseTurn);
  asserttrue(testG.whoseTurn == G.whoseTurn, "Still the current player's turn");

  //test4 - check if card came from players own pile
  printf("Check it came from player's Deck \n");
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1, "Player drew from own deck");

//TEST5 - make sure village is played and and used
printf("Check to make sure village was discarded after being played\n");
printf("played count = %d, expected = %d\n", testG.playedCardCount, testG.playedCardCount + 1);
//-1 cause arrays start at 0
asserttrue(testG.playedCards[testG.playedCardCount - 1] == village, "village was the used card");
asserttrue(testG.playedCardCount == G.playedCardCount + 1, "Card was Played");
  test_count++;
}while(test_count != 1); // keep doing tests until you hit 500
if(passed_tests == total_tests){
  printf("\n >>>>> Random Testing complete %s <<<<<\n\n", TESTCARD);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;

}
