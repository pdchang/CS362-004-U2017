//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Unit Test #1 - isGameOver

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>


#define TESTUNIT "isGameOver()"

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

//main
int main(){
  //variables to set up the game
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
struct gameState G, testG, testG1;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
int i;
//intialize gameState
initializeGame(numPlayers, k, seed, &G);

printf("----------------- Testing FUNCTION: %s ----------------\n", TESTUNIT);
//copy gameState to test case
memcpy(&testG, &G, sizeof(struct gameState));
//copying over the state again to refresh it for another test
memcpy(&testG1, &G, sizeof(struct gameState));
//test1 - check to see if province cards is empty, the game ends
printf("Test 1: Check to see if province is empty, then game will end\n");
//set state to have no province cards
testG.supplyCount[province] = 0;
//setting variable to return value of the function - return value of 1 means game over
int check1 = isGameOver(&testG);
asserttrue(check1 == 1, "Game is Over with empty province supply");

//test2 - check to see if there is 1 2 or 3 provivince cards left, then the game is not over
printf("Test 2: Check to see if province is not empty, game will continue\n");
for (i = 1; i <= 3; i++){
  testG.supplyCount[province] = i;
  int check2 = isGameOver(&testG);
  asserttrue(check2 == 0, "Game is not over with province cards left");
}
//test3 - check to see if 3 supply counts are empty , then the game is over

//making 3 supply piles empty
testG1.supplyCount[0] = 0;
testG1.supplyCount[1] = 0;
testG1.supplyCount[2] = 0;
int check3 = isGameOver(&testG1);
printf("Test 3: Check to see if there are 3 supply counts that are empty than game ends\n");
asserttrue(check3 == 1, "3 Empty Supply Count means game ends");

//test4 = check to make sure if there are no empty supply piles then game doesn't ends
printf("Test 4: If no supply piles are empty, then game should continue \n");
for(i = 0; i < 25; i++){
  testG1.supplyCount[i] = 1; //just setting each supply pile to 1 so there are no empty piles
}
int check4 = isGameOver(&testG1);
asserttrue(check4 == 0, "All supply piles not empty, so game continues");


//message to end test with
if(passed_tests == 6){
  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;
}
