/*
Josh Erickson

Initially looking at testme, it’s fairly obvious how it works.The variable c is compared to a certain character and state is compared to 0 - 8. 
If the character is a match and we are in the correct state, we move on to the next state.The final conditional is only able to be evaluated correct 
once we have progressed through these initial c == statements, eventually setting state equal to 9. The final conditional then evaluates a random string 
for equality to ‘reset ‘.If this random string is equal to ‘reset ‘, the program prints out the word “error “ and exits.

To test this program, I first wrote the inputChar function that returns a random ASCII character from 32 - 126, these characters being space to ~.This 
will give us a sufficiently large group of characters to randomly pull from to pass into c, allowing it to pass through the states 1 - 9 when a match is found.

The function inputString is then used to generate random strings to be tested for equality to ‘reset ‘.To test this, I wrote the function to generate a string 
containing random characters from the ASCII characters from 41 - 124, or A - z.While this worked for me just fine, it was taking too long to test each time 
to reach the string ‘reset ‘, so I implemented an extra conditional statement that had a 1 / 100, 000 chance in evaluating to true.In the situation that it 
did, randStr would simply be set equal to ‘reset ‘.This was in no way necessary, but I wanted to run the program multiple times and it was going through a 
longer amount of time than I wanted to wait.

I’ve listed a few of the test results below

Iteration 41454: c = v, s = reset, state = 9
Iteration 32042 : c =, s = reset, state = 9
Iteration 70398 : c = X, s = reset, state = 9


*/



