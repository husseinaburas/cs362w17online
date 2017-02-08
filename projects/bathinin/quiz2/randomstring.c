/* Name:Nipun Bathini
   Assignment: Quiz 2
   
   
   
   --------inputChar()---------
   The goal to fix this function, was to print return an ASCII value (ignoring the first 32).  
   All I had to do was return rand to get the ascii values but added 32 to skip the first 32. 
   
   
   -----inputString()------
   I know that the above function inputChar() is going to return ascii values. My goal was trying to get my code to hit the error message.
   I created a string a allocated it to hold the 5 ascii characters I need it to. 
   I then randomized an int, which would then be run through an if statement and if it is equal to 1, reset is printed.  
   If it did not, I created a for loop that would fill the strings with 5 random characters that are returned from the above function inputChar(). 
   I would finally return the string s. The if statemnt above becomes useful, because most of the time it will print out the random 5 characters from the for loop explained. 
   This makes it so the program doesn't run for a really long time, before hitting the error message.
   
   How to run:
   1. gcc -o testme testme.c
   2. testme
   
   /*