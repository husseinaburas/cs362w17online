#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define ASCII_CHAR_MIN 0
#define ASCII_CHAR_MAX 127

/***********************************************************************
Description: Returns a pseudo-random ascii char between [0,127] on the 
    ascii table.  
Pre-conditions: seed is set with srand()
Post-conditions: Returns an ascii char in the range [0,127] on the ascii
    table.  
***********************************************************************/
char inputChar()
{
    int ascii_index = rand() % ASCII_CHAR_MAX;
    char rand_char = ascii_index;

    return rand_char;
}

/***********************************************************************
Description: Returns a string made up of pseudo-randomly selected chars
    from the available_chars array. The desired string is
    'reset'. Different permutations of length 5 of the available chars
    will be generated until 'reset' is randomly chosen as the string.
Pre-conditions: seed is set with srand()
Post-conditions: Returns a pointer to a char array of length 6, populated
    by pseudo-randomly generated permutations of the available chars.
***********************************************************************/
char *inputString()
{
    // ascii values for possible chars 'r', 'e', 's', and 't' are 
    // 114, 101, 115, 116
    char available_chars[4] = {101, 114, 115, 116};

    int string_index = 0;
    int string_length = 5;
    char output_string[string_length];
    char rand_char = 0;
    char *output_string_ptr;

    for(string_index = 0; string_index < string_length; string_index++){
        rand_char = available_chars[rand() % 4];
        output_string[string_index] = rand_char;
    } 

    output_string_ptr = output_string;
    return output_string_ptr;
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
    return 0;
}