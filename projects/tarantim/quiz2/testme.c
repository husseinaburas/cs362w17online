#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //will return ascii num from 32 through 125
    //which goes from space through close curly brace
    int c = rand() % 94 + 32;
    return c;
}

char *inputString()
{
    char *str = (char*)malloc(6 * sizeof(char));
    int i, x;
    memset(str, 0, sizeof(str));
    char ch;

    for(i=0; i<5; i++){
      //if even index
      if(i % 2 == 0){
        //randomly select lower case letter
        
        str[i] = rand() % 26 + 97;

      //if odd index select a vowel
      }else{
          x = rand() % 5 + 1;
          if(x == 1)//a
            ch = 97;
          else if(x == 2)//e
            ch = 101;
          else if(x == 3)//i
            ch = 105;
          else if(x == 4)//o
            ch = 111;
          else if(x == 5)//u
            ch = 117;
          else 
            ch = inputChar();
          str[i] = ch;
      }
    }
    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  int x = 1;
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
    x++;
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}