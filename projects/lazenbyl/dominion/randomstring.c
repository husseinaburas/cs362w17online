Laura Lazenby 
CS 362
Quiz 2 

  	In order to complete this assignment, I first looked at the pre conditions and post conditions of the testme function. After 
analyzing the function, the inputChar function was the one that needed to change throughout the while loop, so that was the function
in which I implemented randomization. 

	To develop the input string function, I looked at where it was being used and I noticed it was always checking for the same string, so 
making it random would be unnecessary.

	To develop the input char function, I looked at the different characters it was expecting and made a random number generator, generated 
a random number between 0 and 8 and generated one the characters for which the program was looking. The program relies on the previous 
iteration, so it takes a few iterations to get the right combination in order to fail. During local development, I noticed it varied 
in the number of iterations it took before it failed. For example, the first time I ran it, it only took 58 times to fail and the last
time I ran it, it took 133 times before it failed. 