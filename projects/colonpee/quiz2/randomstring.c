/*
Emiliano Colon
colonpee
OSU CS 362

By first looking at testme.c, you can note that the only way the program is going to 
output the error is by first passing the nine conditionals so that the state gets set to 9. 
These conditionals use the function inputChar that will return a random character from 
space (' ') to }. Once the state is set to 9, s needs to be set to "reset", this is 
done by having a function called inputString that returns a random string of size 5 and 
the NULL character at the end. I implemented this function to return a string with random 
characters from a-z, since only lowercase characters are needed. This assignment really ramped up 
my CPU fans as the 4th and 5th iteration took a very long time to get the result. It is amazing how 
fast computers can do work these days. I imagine how trivial this would be if it was implemented
on a multi-core thread.

Here are some examples of the runs:
1st: Iteration 6345518: c = 5, s = reset, state = 9
2nd: Iteration 3326054: c = W, s = reset, state = 9
3rd: Iteration 3127424: c = ], s = reset, state = 9
4th: Iteration 19885648: c = 2, s = reset, state = 9
5th: Iteration 15465199: c = A, s = reset, state = 9

/*