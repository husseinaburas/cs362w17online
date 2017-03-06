/*
inputChar() -- generate a random character that falls within the range of ASCII chars. 
Min value is 26 ('SPACE') and MAX value is 126 ('~'). Return this value to the caller.
With values in the ASCII range above, the state machine in testme.c would advance whenever
a character of interest is produced.

inputString() -- genreate a random string. Random length? Random characters? Not sure of the 
exact qualification, so I have incorporated random string length, with a max length of 15, and 
random characters in the ASCII range defined in inputChar(). With this vast randomness, it would
take a very long test time to hit the error in testme(). 

Since we know the conditions in string that could possibly produce an error, we can reduce the test
time by randomly throwing in the combination of characters that can possible cause an error, "reset".
In inputString(), I generate a random string length. I chose the case when the random string length is
5 as a trigger point to return the "reset" combination of characters. The test time is reduced by a 
significant amount of time, and even though s = "reset" often the test still runs hundreds to thousands
of iterations before hitting the error.

*/