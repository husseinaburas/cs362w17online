/************************************************************************
 * Author: Lance Marks
 * Class: CS362
 * Description: Random Testing Quiz 2
 * ********************************************************************/

The first part of the assignment is to create the function inputChar().
My function works by randomly generating an index number that is
between 0 and the size of an array of available characters. The char
at the random index is then set to the return variable.  The selection
of characters is from the top row of the keyboard and all of the 
bracket types.  This gives an option of 17 characters for the 9 that
satisfy the requirements to increase the stage of the testme() function.

The second part of the assignment is to create the function inputString().
For this function I followed a similiar strategy of the inputChar() 
function. There is a character array with 9 characters for the 6 that need
to be generated. A for loop creates a random index to choose a random
character from the possible array for each of the 6 indices.

I have made a few changes to the array to increase the randomness.  I added
a larger array for the inputChar() function.  I also changed inputString()
from always placing a null at index 5, the null character is part of the 
posible array and must be randomly assigned to s[5].  This increases
the iterations from around 20 thousand average to around 200 thousand. An
increase by a factor of 10 in iterations.
