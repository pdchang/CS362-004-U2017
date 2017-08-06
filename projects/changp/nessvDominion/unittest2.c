//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Unit Test #2 - whoseTurn

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>


#define TESTUNIT "whoseTurn()"

//global variable to check if it passed, using counter
int total_tests = 3;
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
  int otherDude = 1;
struct gameState G, testG, testG1;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
int i;
//intialize gameState
initializeGame(numPlayers, k, seed, &G);

printf("----------------- Testing FUNCTION: %s ----------------\n", TESTUNIT);
//copy gameState to test case
memcpy(&testG, &G, sizeof(struct gameState));
//using endturn - looking at the code i just know it switches turns for sure
//test1 check tio make sure this player is this person's turn
printf("Test 1: Check to make sure thisPlayer or player 0 is the person's turn\n");
int check1 = whoseTurn(&testG);
asserttrue(check1 == thisPlayer, "Start of game is Player 0's turn");
//test2 check to make sure that if you end the turn it wont be player 0's turn
//ending turn first so it switches
endTurn(&testG);
printf("Test 2: If you end turn, then it should be other player's turn\n");
int check2 = whoseTurn(&testG);
asserttrue(check2 != thisPlayer, "Player has switched turns");
//test3 - check to make sure if we end turn again, the player will go back to player 0
endTurn(&testG);
printf("Test 2: End other player's turn, whose turn should be player 0\n");
int check3 = whoseTurn(&testG);
asserttrue(check3 == thisPlayer, "Turn has turned back to first player");
//message
if(passed_tests == 3){
  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}


  return 0;
}
