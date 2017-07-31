//Philip Chang changp@oregonstate.edu
//CS 362 - Assignment 4
//Random Test Adventurer

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"


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
  G.deckCount[thisPlayer] = rand() % MAX_DECK;
  G.discardCount[thisPlayer] = rand() % MAX_DECK;
  G.handCount[thisPlayer] = rand() % MAX_HAND;
  handpos = rand() % G.handCount[thisPlayer]; // 0 to handcount - 1
  G.hand[thisPlayer][handpos] = adventurer;
  smithyCard(handpos, &testG);
  printf("+3 Cards and discard smithy\n");
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
  asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "+2 Net Gain of Cards");
  //TEST2 - make sure they got it from the write deck
  printf("Check it came from player's Deck \n");
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
  asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3, "Player drew from own deck");
  //TEST3 - make sure smithy is played and and used
  printf("Check to make sure smithy was discarded after being played\n");
  printf("played count = %d, expected = %d\n", testG.playedCardCount, testG.playedCardCount + 1);
  //-1 cause arrays start at 0
  asserttrue(testG.playedCards[testG.playedCardCount - 1] == smithy, "Smithy was the used card");
  asserttrue(testG.playedCardCount == G.playedCardCount + 1, "Card was Played");
  //TEST4 - make sure its still the current Players turn
  printf("Check to make sure its still the player's turn\n");
  printf("expected player = %d, current player = %d\n", testG.whoseTurn, G.whoseTurn);
  asserttrue(testG.whoseTurn == G.whoseTurn, "Still the current player's turn");
  //Test5 - Make sure there there are no more actions after playing the card
  printf("Check to see after playing the card there are no more actions\n");
  asserttrue(testG.numActions == 0, "No actions left after playing card");
  test_count++;
}while(test_count != 2); // keep doing tests until you hit 500
if(passed_tests == total_tests){
  printf("\n >>>>> Random Testing complete %s <<<<<\n\n", TESTCARD);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;

}
