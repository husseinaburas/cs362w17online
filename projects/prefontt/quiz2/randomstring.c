/* The following is the code I wrote for inputChar()
 * basically it just creates a random character from 32 - 126. This is because space, which is needed
 * is found at ASCII 32, and 125 is ASCII for } which is needed, and there are some characters 
 * in between that are needed to get the state to 9 */

char inputChar()
{
    char c = (rand() % (127 - 32)) + 32;
    return c;
}

/* In inputString I basically did the same thing, except I also created an array that would be returned by the function
 * 	I populated this array with characters from 101 - 118 because the characters needed fall in that scope. The instructions
 * 		never specified what kind of scope I would need for random characters so I made it as small as I could to make the test
 * 			run faster. if I had considered a - d and u - z, the test would take longer because there would be less of a chance
 * 				of getting r, e, s, and t. */

char *inputString()
{
    char* array = malloc(6);
    int i = 0;
    while(i < 5)
	{
		array[i] = (rand() % ( 118 - 101)) + 101;
		i++;
	}
    return array;
}

/*Running the test was simple, although my finished product works, not all the code i wrote worked, and had to be refactored, and 
 * the print statement in the testme function helped to see that either c wasn't being populated or maybe s wasn't being populated,
 * so my functions were wrong somehow, but eventually it worked. So basically the inputChar function returns a character and for the first state it needs to be 
 * '[', then it moves up a state, then it needs to be another radnom character and so on and so forth. That part was pretty straightforward and simple.
 * What caught me up for the first 20 minutes or so of this quiz was that inputString and inputChar are seperate from eachother. At first I thought
 * that I was going to use them in tandem so in inputString I was going to call inputChar in my while loop, which I suppose could work, but I thought
 * that the random character needed to be the same as the one populating c, so that s[0] would be the same as c, which of course is not true.
 * Once I was over that hurdle it was actually fairly simple to write inputString as I just needed it to be populated with reset randombly. Out of my 
 * many tests, one example is that it took 3,777,028 iterations to get to state == 9, and s[] == reset, and I just ran another real quick and it only took 17,099.*/
