//Philip Chang changp@oregonstate.edu
//CS362 - Assignment 3
//Unit Test #4 - buycard

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> use own assert
#include "rngs.h"
#include <stdlib.h>


#define TESTUNIT "buyCard()"

//global variable to check if it passed, using counter
int total_tests = 7;
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

//test1 to see if you have no buys
printf("Test 1: Check if you have no buys are you still able to buy a card\n");
//setting numBuys to 0
testG.numBuys = 0;
int check1 = buyCard(province, &testG);
asserttrue(check1 == -1, "If no buys, then you can't buy");

//test2 - check if we set province pile to 0, then you can't buy the card
//putting numBuys back to 1, the default
testG.numBuys = 1;
//set the state coins to be able to buy province
testG.coins = 8;// 8 coins to buy a province so we can buy it

//set number of province cards
testG.supplyCount[province] = 0;
printf("Test 2: If we have no supply of province, we can't buy it\n");
//buying the card
int check2 = buyCard(province, &testG);
asserttrue(check2 == -1, "If no supply of province, can't buy province");

//test3 - check to see if we dont have enough coins, we can't buy card
//putting variables back
testG.numBuys = 1;
testG.supplyCount[province] = 8;
//setting coins to 0, so we can't buy
testG.coins = 0;

int check3 = buyCard(province, &testG);
printf("Test 3: Not enough money to buy\n");
asserttrue(check3 == -1, "if you dont have money, you can't buy");

//test4 = check to see if you actually can buy the card, the card is in your hand
testG.numBuys = 1;
testG.coins = 10;
testG.supplyCount[province] = 8;

int check4 = buyCard(province, &testG);
int find = 0; //flag used to find card
//bought cards are gone to the deck, so we find it

for (i = 0; i < testG.deckCount[thisPlayer]; i++){
  if (testG.deck[thisPlayer][i] == province){
    find = 1;
    break;
  }
}
printf("Test 4: Check if you buy the card with right parameters, it goes to deck\n");
asserttrue(find == 1, "Bought  Card is in deck");

//test5 now that we bought teh card, in same state, we have to test if numBuys went down, it should be 0

printf("Test 5: See if numBuys went down to 0\n");
asserttrue(testG.numBuys == 0, "numBuys is zero");

//test6 cehck supply count of province, it shoudl be 7 instead of 8

printf("Test 6: check to see if we have less province cards, by 1\n");
asserttrue(supplyCount(province, &testG) == 7, "there are now one less province cards");

//test 7 check to see if coins went down

printf("Test 7: check to see num coins reduced from 10 to 2\n");
asserttrue(testG.coins == 2, "num coins has been reduced by 8, the cost of province");
//finall message

if(passed_tests == 7){
  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);
}
else{
  printf("\n >>>>> Only %d / %d tests have passed\n\n", passed_tests, total_tests);
}


  return 0;
}
