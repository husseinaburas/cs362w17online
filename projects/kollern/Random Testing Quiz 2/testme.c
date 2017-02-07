#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <sys/stat.h>

char inputChar()
{
	// First, pick a number between 0 and 
	// 25.
	int randNum = 94 * (rand() / (RAND_MAX + 1.0));
	// The ASCII code for ‘a’ is 97, so
	// add 97 to the random number to get
	// a lower case letter.
	randNum = randNum + 32;
	// Type cast to character to convert Ascii
	// it to a char type.
	char randChar = (char)randNum;
    return randChar;
}
// This version uses calls from the previous function
//char *inputString(int Size)
//{
//    // TODO: rewrite this function
//		
//	// argument error checking before the assignment
//	char *result = malloc((Size + 2)*sizeof(char)); // using 2 spaces for a new line and a null terminator
//	int i;
//	for (i = 0; i < Size; i++) {
//		result[i] = inputChar();
//	}
//	result[Size + 1] = '\0';
//    return result;
//}
char *inputString()
{
	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
	int Size = 5;
	char *result = malloc((Size + 1)*sizeof(char)); // using 2 spaces for a new line and a null terminator
	int i, j;
	for (i = 0; i < Size; i++) {
		j = rand() % 27; // to produce numbers within the range of 0-26; place 26 is the empty character
		result[i] = alphabet[j];
	}
	result[Size] = '\0';
	return result;
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
	free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
	int test = (rand()+1) % 100;
	/*char *result = malloc((test + 2)*sizeof(char));
	while (1) {
		result = inputString(test);
		printf("%s",result);
	}*/
	testme();
    return 0;
}
