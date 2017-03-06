/*
Random Testing Quiz 2
Rachel Weissman-Hohler
2/5/17

I started by reading through the code and noting what kinds of input might make the error message print. 
For the message to print, the input string needs to be "reset" and the state needs to equal 9. For the 
state to get to 9, the char must be (on successive loops) '[', '(', '{', ' ', 'a', 'x', '}', ')', and ']'. 

To start with, I made inputChar() return a random char from the string "()[]{} abcdefghijklmnopqrstuvwxyz".
Then, inputString() used inputChar() to build a random string of length 5 (plus one for the null character),
since this is the length of the string required to trigger the message. 

While this approach worked, it sometimes took minutes to trigger the error, and I realised that I could
reach the message more quickly if the set of possible chars was limited to only those checked for in testme().
Accordingly, I changed the string of candidate chars to "()[]{} aerstx". This results in the message being
triggered in a handful of seconds.
*/