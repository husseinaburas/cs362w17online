//
//  main.c
//  cs362
//
//  Created by josephLong on 2/2/17.
//  Copyright © 2017 josephLong. All rights reserved.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    
    
    // Generates a random number between 0 and 9.
    int r = (rand() % 9) ;
    
    //array that holds elements for character in testMe()
    char store[] = { '[' , '(' , '{' , ' ' , 'a' , 'x' , '}' , ')' , ']' };

    //Return the randomly generated character from the store[] array
    return store[r];
}

char *inputString()
{
    //Constant for Word Size
    int MAX = 6;
    
    //index variable for for
    int i = 0;
    
    //word array
    char word[MAX];
    
    //array that holds alphabet
    char alpha[26] = {'a','b','c','d','e',
                        'f','g','h','i','j',
                        'k','l','m','n','o',
                        'p','q','r','s','t',
                        'u','v','w','x','y','z'};

    //build the string to pass to be tested
    for (i = 0 ; i < MAX ; i++)
    {
        
        //Append the word with the termination character if at last index.
        if ( i == 5)
        {
            word[MAX-1] = '\0';
        }
        else
        {
            //generate a random number between 0 - 25 to capture letter
            int r = rand() % 25;
            word[i] = alpha[r];
        }
    }
    
   
    return word;
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
        //s = "reset";
        //state = 9;
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
        
        if (c == '[' && state == 0)
            state = 1;
        if (c == '(' && state == 1)
            state = 2;
        if (c == '{' && state == 2)
            state = 3;
        if (c == ' '&& state == 3)
            state = 4;
        if (c == 'a' && state == 4)
            state = 5;
        if (c == 'x' && state == 5)
            state = 6;
        if (c == '}' && state == 6)
            state = 7;
        if (c == ')' && state == 7)
            state = 8;
        if (c == ']' && state == 8)
            state = 9;
        if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e'
            && s[4] == 't' && s[5] == '\0' && state == 9)
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
