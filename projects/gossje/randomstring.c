Jeff Goss - CS362 randomstring.c

My implementation of inputChar returns a random ASCII character. 
Despite the large variance in possible characters that can be returned by the function, state 9 is often quickly reached. 
This is because the state does not reset back to 0 on each iteration of the while loop. 

Initially I had the same random generation rules for inputString. However, this large variance made printing the error message occur too rarely.
This is because an exact combination of lower-case characters is needed in order to print the error message and end the while loop.
Realizing that I needed to reduce the variance, I instead opted to have the inputString function generate only lower-case characters. 
An alternative solution would be to limit the potential characters specially to 'r', 'e', 's', and 't'. However that approach felt not random enough. 

Using only lower-case character generation in my inputString function still required a large number of iterations in order to produce the error message.

Run 1: Iteration 882903: c = , s = reset, state = 9
Run 2: Iteration 55638: c = >, s = reset, state = 9
Run 3: Iteration 22913706: c = ?, s = reset, state = 9

