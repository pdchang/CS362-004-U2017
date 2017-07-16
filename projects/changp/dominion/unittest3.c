//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Unit Test #3 - fulldeckCount

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>


#define TESTUNIT "updateCoins()"

//global variable to check if it passed, using counter
int total_tests = 10;
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
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
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
//starting hand is size 5
//test 1 - check to see if you have a hand of 5 copper
printf("Test 1: Check to see if it knows 5 copper is worth 5\n");
//putting 5 copper in hand
testG.handCount[thisPlayer] = 5;
testG.hand[thisPlayer][0] = copper;
testG.hand[thisPlayer][1] = copper;
testG.hand[thisPlayer][2] = copper;
testG.hand[thisPlayer][3] = copper;
testG.hand[thisPlayer][4] = copper;
//copper is worth 1 so you should get 5 back, with bonus 0
int check1 = updateCoins(thisPlayer, &testG, 0);
asserttrue(check1 == 0, "Update Coins is working");
asserttrue(testG.coins == 5, "5 Copper coins is worth 5");

//test2 - check if 5 silver are in the deck, the worth of each silver is 2, total is 10
//reseting the game state again
memcpy(&testG, &G, sizeof(struct gameState));
testG.handCount[thisPlayer] = 5;
testG.hand[thisPlayer][0] = silver;
testG.hand[thisPlayer][1] = silver;
testG.hand[thisPlayer][2] = silver;
testG.hand[thisPlayer][3] = silver;
testG.hand[thisPlayer][4] = silver;
printf("Test 2: Check to see if it knows 5 silver is worth 10\n");
int check2 = updateCoins(thisPlayer, &testG, 0);
asserttrue(check2 == 0, "Update Coins is working");
asserttrue(testG.coins == 10, "5 Silver Coins is worth 10");

//test3 - check to see if 5 gold cards is worth 15, or 3 each
memcpy(&testG, &G, sizeof(struct gameState));
testG.handCount[thisPlayer] = 5;
testG.hand[thisPlayer][0] = gold;
testG.hand[thisPlayer][1] = gold;
testG.hand[thisPlayer][2] = gold;
testG.hand[thisPlayer][3] = gold;
testG.hand[thisPlayer][4] = gold;
printf("Test 3: Check to see if it knows 5 gold is worth 15\n");
int check3 = updateCoins(thisPlayer, &testG, 0);
asserttrue(check3 == 0, "Update Coins is working");
asserttrue(testG.coins == 15, "5 Silver Coins is worth 10");

//test4 check to see if 2 copper, 2 silver, and 1 gold is equal to 9
memcpy(&testG, &G, sizeof(struct gameState));
testG.handCount[thisPlayer] = 5;
testG.hand[thisPlayer][0] = copper;
testG.hand[thisPlayer][1] = copper;
testG.hand[thisPlayer][2] = silver;
testG.hand[thisPlayer][3] = silver;
testG.hand[thisPlayer][4] = gold;
printf("Test 4: Check to see if it knows 2 copper,2 silver, 1gold is worth 9\n");
int check4 = updateCoins(thisPlayer, &testG, 0);
asserttrue(check4 == 0, "Update Coins is working");
asserttrue(testG.coins == 9, "2 Copper, 2 Silver, 1 gold is worth 9");

//test5 , check if bonus is working with 2ccopper 2 silver and 1 gold
//setting bonus to 10
memcpy(&testG, &G, sizeof(struct gameState));
testG.handCount[thisPlayer] = 5;
testG.hand[thisPlayer][0] = copper;
testG.hand[thisPlayer][1] = copper;
testG.hand[thisPlayer][2] = silver;
testG.hand[thisPlayer][3] = silver;
testG.hand[thisPlayer][4] = gold;

int bonus = 10;
printf("Test 5: Check to see if 2c, 2s, 1g, and 10 bonus is worth 19\n");
int check5 = updateCoins(thisPlayer, &testG, bonus);
asserttrue(check5 == 0, "Update Coins is working");
asserttrue(testG.coins == 19, "2 Copper, 2 Silver, 1 gold, and 10 bonus is worth 19");

if(passed_tests == 10){
  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}

  return 0;
}
