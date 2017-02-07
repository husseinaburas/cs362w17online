-inputChar()

For this function I determined the aschii values of all the characters that testme() was expecting. I wasn't sure just putting those values into an array and picking randomly from it was acceptable so I found the range within which the values fell (32-175). I generated a random number within that range to generate random characters.


-inputString()


For this function I also generated random ascii values. I limited the range of values to all lower case letters (97-122). I generated random values for all 5 characters of the string and then appended a terminating 0 on the end. Although this isn't totally random in the broadest sense of the word, I thought it was reasonable to limit the values to lower case letters since it already took 23,874,039 iterations of the loop for the random values to combine into "reset."