/**********************************
 *Author:  Jeanvally G.Beato
 *Course:  CS 362 - W17
 *Professor:  Ali Aburas
 *Assignment:  Random Testing Quiz 2
 **********************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Generates random ASCII character from range [32,126]
    char c = rand() % (127 - 32) + 32;
    return c;
}

char *inputString()
{
    // Creates a random string and returns it
    char reset[6] = "reset ";
    static char stringArray[6];
    
    // Randomy toggles between generating random string and hard coded string with 50/50 chance
    if((rand()%2) == 0)
    {
        for(int i=0; i < 5; i++)
        {
            stringArray[i] = ((rand() % (127 - 32)) + 32);
        }
    }
    // Uses hard coded string
    else
    {
        for(int j=0; j < 5; j++)
        {
            stringArray[j] = reset[j];
        }
    }
    
    return stringArray;
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
