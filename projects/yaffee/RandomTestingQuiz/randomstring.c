/*
Emma Yaffe
Random Testing Quiz

The testme function requires a specific set of actions to happen in order to produce the error.
First, it must sequentially be passed the following characters:
'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'
When it receives one of these characters in the correct order, it increments the state integer. That is, state
starts at 0. The first time it receives '[', state is incremented to 1. If it receives another '[', nothing
happens. If it then receives '(' while the state is 1, state is incremented again. This continues until the 
state is 9 -- after it receives every one of those characters in order.

Second, it must receive the string 'reset\0'. In order to produce the error, the state must be at 9 when it
receives the 'reset\0'.

With this in mind, I implemented the inputChar() and inputString() to randomly generate test inputs.

For inputChar(), I created an array that held one of each of the possible characters that would trigger a state
change. I did not include all characters due to limitations of time and of my machine, in order to make the
test complete in a resonable amount of time. I randomly chose one of the items in the array and returned value.

For inputString(), I created array that held the letters of reset: ('r', 'e', 's', 't'). I randomly chose
from those characters to generate the string. I hard-coded the last character of the string to be '\0' to avoid
errors. It needs to have the null terminating character last in order to run correctly.

To compile, type:
make

To run, type:
testme

To remove file, type:
make clean

*/
