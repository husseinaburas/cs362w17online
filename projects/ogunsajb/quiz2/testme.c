#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//char stringBuffer[MAXLEN];
//compile: gcc -o unittest testme.c
char inputChar()
{
	char min = 32; // ' '
	char max = 126;//
	char c;
    
	//ref: http://c-faq.com/lib/randrange.html
	
     return (char)(min + rand() / (RAND_MAX / (max - min + 1) + 1));
	 
}

char *inputString()
{
#define MAXLEN 15
    // TODO: rewrite this function
    //return "";
	//ref: http://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
    //static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
	static char trigger[] = "reset";
    int length, n;
	char *randomString = NULL;

	//memset(stringBuffer, 0, sizeof(stringBuffer));
	
	length = rand() % MAXLEN; //printf("length = %d\n",length);
	
    if (length) {
        randomString = malloc(sizeof(char) * (length +1));
		//randomString = stringBuffer;
		
        if (randomString) {  
           if(length == 5){//return 'reset' every once in a while
				 for (n = 0;n < length;n++)             
					randomString[n] = trigger[n];			   
		   }
		   else{	   
				 for (n = 0;n < length;n++) 
					randomString[n] = inputChar(); 
		   }

            randomString[length] = '\0';
        }
    }
	else
		randomString = "NULL"; //avoid segementation faults
	
    return randomString;	
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
