#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//r = (rand() % (max + 1 - min)) + min ; range formula
char inputChar()
{
  //using ascii from 32 to 126
    int check = (rand() % (126 + 1 - 32) + 32);
    return check;
}

char *inputString()
{
  //mallocing char string
  char *stringy = (char*)malloc(sizeof(char) * 6);
  int i;
  //putting random chars in each part of the strong
  //only going to use lower case characters 97-122
  for (i = 0; i < 5; i++){
    char put = (rand() % (122 + 1 - 97)) + 97;
    stringy[i] = put;
  }
  //end of string has to end with null terminal
  stringy[5] = '\0';

  return stringy;

}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();

    //test to check the ascii characters that i wanted
    /*for (int i = 32; i < 127; i++){
      char c = i;
      printf("%c\n", c);
    }*/

    return 0;
}
