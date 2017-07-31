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

#define TESTCARD "adventurer"


int total_tests = 7 * 500; //7 assert trues, 500 differnt random combos
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
int i, j, m;
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
  int treasureTest = 0; //counter to find the number of treasure cards in testG
  int treasureG = 0; //counter to find the number of treasure cards you start with
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
  adventurerCard(handpos, &testG);
  printf("Check how many cards adventurer adds\n");
  //adventurer gets discarded after but it adds 2 cards, so 2-1, 1 net gain
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
  asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2, "+1 Net Gain of Cards");
  //test2 - make sure the last 2 cards were treasure cards
  printf("Check to see if cards added are adventurer cards\n");
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
  printf("Check it came from player's Deck \n");
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
  asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2, "Player drew from own deck");
  //test4 - check to make sure its still palyers turn
  printf("Check to make sure its still the player's turn\n");
  printf("expected player = %d, current player = %d\n", testG.whoseTurn, G.whoseTurn);
  asserttrue(testG.whoseTurn == G.whoseTurn, "Still the current player's turn");
  //Test5 - check no more actions
  printf("Check to see after playing the card there are no more actions\n");
  asserttrue(testG.numActions == 0, "No actions left after playing card");
  //test6 - check to make sure card was used and discarded
  printf("Check to make sure adventurer was discarded after being played\n");
  printf("played count = %d, expected = %d\n", testG.playedCardCount, testG.playedCardCount + 1);
  //-1 cause arrays start at 0
  asserttrue(testG.playedCards[testG.playedCardCount - 1] == adventurer, "Adventurer was the used card");
  asserttrue(testG.playedCardCount == G.playedCardCount + 1, "Card was Played");

  test_count++;
}while(test_count != 501); // keep doing tests until you hit 500
if(passed_tests == total_tests){
  printf("\n >>>>> Random Testing complete %s <<<<<\n\n", TESTCARD);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;

}
