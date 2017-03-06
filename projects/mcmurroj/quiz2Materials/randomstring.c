/*
randomstring.c is a text file that outlines how the inputChar() and inputString()
functions work.

--------------
1) Implementation for char inputChar() justification
--------------
First, I looked at the ASCII table to see what corresponding decimal values the trigger
characters.  All the characters included fell into the range 32-125, so I decided to trigger
all characters within that range, and also test boundaries by adding/subtracting 1 from the range
(new range 31-126).  There is no need to change the odds of occurances here, because as found during testing,
the state increments at a quick enough rate on its own.

--------------
2) Implementation for char inputString() justification
--------------
In this implementation had to play with the odds of generating a completly random
lower case number every time.  I have a variable called 'changeOdds' that can be set
to change the likleyhood of generating a r,e,s,t, or any lowercase (including r,e,s,t).
The closer the changeOdds variable is to 0, the more likley the random char will be an r/e/s/t.
For the sake of this quiz submission, I have choosen to set this variable to 10, as this often generates
over 1,000,000 iterations of tests before it errors out.  


*/
