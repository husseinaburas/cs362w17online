Thomas Adamcewicz
CS 362
2/5/17
Quiz 2


Development of random tester in testme.c 

In order to write the bodies of inputChar() and inputString(), I first evaluated the testme() function. 
In the testme() function there's a certain order of values that must be generated from inputChar and
inputString in order for testme() to reach its final stage and return the error message. In order to get 
to the next level in the testme() evaluation, a certain state must be reached. In order to get from state 0
to state 9, inputChar() must generate the chars: '[', '(', '{', ' ', 'a', 'x', '}', ')', and ']'. In order to
radnomly generate this range of characters in the inputChar() function, I set its return to rand() % 94 + 32.
This will generate random chars from ASCII value 32 (' ') to ASCII value 125 ('}') which is a sufficient range
to quickly and randomly generate all the needed chars to reach state 9. The final if statement requires state 9
but also for inputString() to generate the string 'reset'. In order to randomly generate this string in the inputString()
function, I set it to generate each char of the string as stringOut[i] = rand() % 16 + 101. This will generate random chars
from ASCII value 101 ('e') to ASCII value 116 ('t') which is a sufficient range to quickly and randomly generate 
the string 'reset'. I originally set stringOut[i] equal to a random char from 'a' to 'z', but found that reducing
the range of available characters significantly increased the speed of finding the error message.
Once this string is generated the testme() function will print 'error' and exit with a status of 200.