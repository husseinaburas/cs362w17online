Stephanie Creamer - CS 362
Winter 2017 - Quiz 2

My design was to create an array of the required characters to make the string to trigger the error text.  I use this kind of approach 
for randomization in other coursework, so it was kind of a natural solution for me to come to implement for this assignment (or really 
any that have to do with randomization).

Using this array, I generated random numbers for the index in inputChar() and returned them to the inputString() function.  inputString() 
  generated a six character string from the array provided in inputChar().  Providing the array consisting only of results decreased the 
  processing time required before the exit string was finally generated (ex. Iteration 2180897: c = }, s = reset, state = 9).

I suppose I technically "cheated" by having two 'e' characters in the alpha array, but it was also the only duplicate character needed 
for the exit string to be generated, so I'm going to call it good.
