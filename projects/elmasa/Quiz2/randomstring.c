/*
 Andrew Elmas
 Quiz 2
 Random Testing (Fuzzer)
 
 Compile with: gcc testme.c -o testme

 In the testme() function, there is an infinite while loop that will only exit when the last conditional if statement conditions are met. There are a few if statements above which, when met, raise the state variable. These if conditionals pass to the next if statement on 2 conditions:
        1. The passed character matches and 
        2. the state variable matches.
 
    inputChar() is called by testme() and gets a char which must be random for fuzzing purposes. To accomplish fuzzing, an array of the 9 chars tested against in the first 9 condtionals in testme() is created, and a random 1 of them is returned. This will help successively pass the first 9 if condtionals. From this we see that the if conditionals are like steps leading to the final if statement.
 
 The final if conditional that finally end the infinite loop with the error message checks against a string s. This string is created by calling the inputString() function. The test only passes if the 6 character string contains in the following order the characters r e s e t \0. There are only 5 unique characters in this string. So the inputstring() function randomly selects a character from that set to fill each position in the 6 character string with a for loop. It then returns that string. Once the string randomly becomes reset\0, the final condtion is met and the execution exits with the error.

*/
