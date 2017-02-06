/*
Name: Jon Hutter, hutterj
Date: 2017/02/05
Assignment: Quiz 2 - 
*/

/*
Explanation inputChar:

Because srand is already seeded with time(NULL) in main,
inputChar does not need to seed it again. The selected random
char is the result of rand() modded to give only printable characters.
As the printable chars go from 32 to 126, this meant modding by 95 and
then adding 32 to the pseudo-random int returned by rand(). randChar is
returned.

In order for the test to reach the error message, the random char needs 
to include chars 32 space to 125 curly end bracket in order to reach 
all 9 states.




Explanation inputString:
Again, srand is seeded in main, so not reseeded in inputString. First 
a random length between 0 and 9 is chosen via rand modded by 10. This 
serves as the length of the randString char array. The char array is
built using chars from inputChar while iterating. A null character is
added at the final index of randString.

In order for the test to reach the error message, the random string
needs to have a length including 6 (including the null character), 
as well as the alphabetic characters r,e,s,t, and those characters 
must be able to repeat in the same random string.


Potential changes:
The specification didn't mention if the inputChar and inputString should
have the same or different range of acceptable chars. For example, if 
it was necessary for the random string to have alphabetic or alphanumeric
characters only, the test would need to be redesigned to generate the 
random string without using inputChar, as inputChar needs to have a
character range of at least 32 space to 125 curly end bracket in order
to reach all 9 states.



*/
