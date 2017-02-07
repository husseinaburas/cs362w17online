/*
 Long, Joseph C.
 CS 362, Winter 2017
 randomstring.c
 
 
 Overview:
 
 Testme.c core function, testme(), has a series of if statements that flows down like a waterfall to 
 get to the final, ninth statement, which is the reset code. The program requires the value passed to 
 the if statement to be a specific character:
 { '[' , '(' , '{' , ' ' , 'a' , 'x' , '}' , ')' , ']' }
 
 It then walks down the if statements each time one of those characters is handed to the appropriate if 
 statement ( by the function inputChar) and changes the state by one, getting itself closer to the final 
 if statement, which then randomly generates characters until five characters in the array spell out the 
 word “reset”.
 
 The time that it takes to generate the characters in inputChar() is much less as the state goes to 9 very 
 fast and there is only the need to get one character.
 
 Once you are in state 9, you have to randomly generate a character for five spaces on an array from the alphabet.  
 This requires all randomly generated letters to spell out “reset”.
 
 inputString():  I designed this function to generate a letter from an array containing each letter of the alphabet.  
 When the function is called, it uses rand to get a random number between 0 and 25 and selects the letter with that 
 index from the character array.   It then does this 4 more times and appends the string with the termination
 character. Finally it passes the string back to testme to see if it says “reset”.
 
 inputChar():  This function is does less work than inputString().  I created an array to store the characters 
 which testme is looking for (nine characters ).  It then will pass one of the randomly generated characters to testme. 
 Since It only has nine characters to choose from and since the only check in the initial states of test me is for the 
 character to be one of those nine passed, it moves down the algorithm in testme fairly fast and its job is over.
 

*/
