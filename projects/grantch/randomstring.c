/*
Christopher Grant
Random Testing Quiz 2 writeup

To do this I looked at the cases in which testme() had to go through
to get to the "error" statement.

For this to run in a decent amount of time I decided to restrict the domain 
of my imputChar() function to only be chars from the test cases in testme(). 
That domain set is " []{}()aerstx". 

inputChar() function uses rand() to pull from char *charList = " []{}()aerstx"; 
and returns the selection. 

In inputString() I use malloc to create a pointer to space for 6 chars.
I picked 6 chars because the fail case is the string "reset".
5 chars and a null term.
To do this I called the inputChar() in a for loop to build random strings.
After which it places a '\0' at postion [5];
Than it returns the pointer to the function. 

Here is the results of a test run (SLOWER VER):
Domain of inputChar() = " []{}()aerstx"
Domain of inputString() = " []{}()aerstx"

TEST RUN1:
Iteration 383113: c = x, s = [[{st, state = 9
Iteration 383114: c = a, s =  sa{}, state = 9
Iteration 383115: c = ], s = a[a [, state = 9
Iteration 383116: c = {, s = reset, state = 9

TEST RUN2:
Iteration 587495: c = [, s = }a(}}, state = 9
Iteration 587496: c = }, s = [}(sr, state = 9
Iteration 587497: c = (, s = x tet, state = 9
Iteration 587498: c =  , s = reset, state = 9

TEST RUN3:
Iteration 85118: c = s, s =  [a]}, state = 9
Iteration 85119: c = t, s = a]xx), state = 9
Iteration 85120: c = }, s = (tt}r, state = 9
Iteration 85121: c =  , s = reset, state = 9


This can be made to run faster by further restricting each functions domain.
inputChar() domain be " []{}()ax" and the domain for inputString() be
"erst". After doing this it was much faster. 

Here is the results of a test run (FAST VER):
Domain of inputChar() = " []{}()ax"
Domain of inputString() = "erst"

TEST RUN1:
Iteration 360: c = ), s = trttr, state = 9
Iteration 361: c = ], s = tesse, state = 9
Iteration 362: c = [, s = retrr, state = 9
Iteration 363: c = (, s = reset, state = 9

TEST RUN2:
Iteration 438: c = (, s = ttrre, state = 9
Iteration 439: c = ), s = rrsss, state = 9
Iteration 440: c = ], s = eseee, state = 9
Iteration 441: c = x, s = reset, state = 9

TEST RUN3:
Iteration 1974: c = }, s = sertt, state = 9
Iteration 1975: c = x, s = sssrt, state = 9
Iteration 1976: c =  , s = tsrsr, state = 9
Iteration 1977: c = (, s = reset, state = 9

This was much faster to error out. 




error chris@SPARROWTWO:/mnt/c/cs362/quiz2$

*/