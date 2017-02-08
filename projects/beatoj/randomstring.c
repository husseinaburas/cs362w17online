/********************************************
 *Author:  Jeanvally G.Beato
 *Course:  CS 362 - W17
 *Professor:  Ali Aburas
 *Assignment:  Development of Random Tester
 ********************************************/

/********************************************
 
DEVELOPMENT OF RANDOM TESTER

*************
testMe():
*************
 
First I looked at the testMe() function to understand what it.  
I found the following:
 
    -testMe() gets c from the inputChar() method
    -testMe() gets s from the inputString() method
    -testMe() evaluates the values of c(char), state(int), 
     and s(string)
    -state is initialized to 0, and changes based on value of
     state & c
    -loop within testMe() continues until the value of s = "reset"
     and state = 9
    -once the previous is found, then the error message is printed and
     the program terminates with code of 200
 
 *************
 inputChar():
 *************
 
 Based on this, I implemented the inputChar() method to generate
 a random value from the ASCII table that covered the characters
 notated within testMe().  Specifically we needed the following 
 characters:  [ , ( , { , [space] , a , x , } , ) , ]
 
 The value of c needs to have any one of these characters to execute 
 the statements that change the value of state.
 
         char inputChar()
         {
         // Generates random ASCII character from range [32,126]
         char c = rand() % (127 - 32) + 32;
         return c;
         }

 *************
 inputString():
 *************
 
 Since the error message in testMe() will execute if the value of
 s = "reset ", I implemented inputString() to generate a random
 string 50% of the time, and to hard code s to equal "reset " 50% of 
 the time.  
 
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
 
 With both of these functions implemented, I was able to run the program
 and the error message eventually popped up.  Not only does s need to 
 equal "reset ", but the value of state has to also equal 9 in order
 for the program to exit with code of 200.  In order for state to 
 equal 9, the value of c has to eventually generate all of the specific
 values mentioned earlier in the inputChar() section.
