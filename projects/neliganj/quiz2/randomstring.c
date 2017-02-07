/* 
CS 362
Quiz 2
Boone Neligan

Function inputChar() produces a character with an ASCII value between 32 and 125. This range includes all upper and lowercase letters, digits 0-9, and the commonly used special characters. 

Function inputString() produces a 5 character length string of lower case letters.

Initially the randomly generated string could be from 1 - 10 characters, and consist of lower and upper case letters, as well as special characters. This test set proved too vast to trigger the error in a feasibile number of tests, so the test set was restricted to 5 characters randomly selected from the set of lower case letters.  With this smaller set, the error was triggered on average after about 1.5 million iterations through the loop.

*/