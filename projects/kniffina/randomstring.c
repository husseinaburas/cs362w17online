/*

 1) The first thing I wanted to do was try and understand what was going on in the testMe file as a whole.
 The function calls on inputString and inputChar to get the respective string and characters. The characters must
 eventually all have been "{ [, ], (, ), {,  "}", ' ', a, x }". Once those happen it takes the string from the
 inputString function and it must read "reset" with an exit string of "\0".

 2) I started out with developing the input characters function first. Initially I started at the smallest
 value of 32 and allowed the values to be randomly chosen from 32 to 125 which. Inside of the inputString
 function I would make a call to this inputChar's function to return random character values to create the string
 to be tested. This proved to be a nearly impossible process because getting the string "reset" with an exit 
 character at the end was extremely rare. I tested it, sometimes for 10-15 minutes without success. I decided that
 I needed to simplify the process somehow to increase the possibility of the values coming up.

 3) I decided that I could just account for all of the possible characters that were needed for either of the functions
 (inputChar and inputString) inside of the inputChar function i.e. "{ [, ], (, ), {, }, ' ', a, x, r, e, s, t" . 
 By creating an array and setting it to the values of the ASCII characters that are needed to pass through the if 
 statements, it would increase the chances of them being present. Inside of the inputString malloc is called to create
 space in memory for a string of length 6. The inputChar function is called in a for-loop and given the random values
 created in inputChar.

 4) After the above implementation the runtime was cut down drastically. It was able to execute and escape the
 while loop around 20,000-40,000 iterations. This made it possible to test, and not have it crash. 


*/