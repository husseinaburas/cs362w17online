Kim, William
Kimw
Quiz 2
CS362
2/4/17

Development:

For quiz two we needed to create a function inputChar that would return a 
character and a function inputString that would return a string that would 
cause test me to print the error message.

Reading the testme code, inputChar needs to randomly generate a characters 
in the range of 32-126 on the ASCII chart. I originally reused the inputChar 
method to randomly generate the 5 chars in the my new string but that ended 
up taking too many interations. I refactored my code to only used a random 
generate range of 97-122 which is lowercase a-z. That dropped the iteration 
down significantly.

Tests:

First run: Iteration 21927767: c = *, s = reset, state = 9
Second run: Iteration 3145003: c = 3, s = reset, state = 9
Third run: Iteration 18235167: c = *, s = reset, state = 9

How it finds the error:
Looking at the code, c first needs to generate [ which will increment the 
state to 1. Then c needs to generate a ( which will increment the state 
to 2. Then c needs to generate a { which will increment the state to 3. 
Then c needs to generate a ' ' which will increment the state to 4. Then 
c needs to generate a a which will increment the state to 5. Then c needs 
to generate a x which will increment the state to 6. Then c needs to generate 
a } which will increment the state to 7. Then c needs to generate a ) which will 
increment the state to 8. Then c needs to generate a ] which will increment 
the state to 9. This is why inputChar generates 32-126 to cover all characters 
required to hit the error code. Once we get to state 9, we now need to randomly 
generate a char array of 6 which spells reset with a '\0' at the end in order to 
hit the error message. My input string method generates random lower case letters 
for index 0 - 4 and inserts a '\0' and the end to signify the end of the string.