//John Teuber
//quiz 2
//Random Testing 
//
//
//
//inputChar():
//	Implemented by finding the remainder of a rand() output and dividing 
//	by the range of ASCII characters plus 1 to include the highest value.
//	The lowest value of an ASCII number
//	was taken to be 32 (Space) and the highest was taken to be 126 (tilde).
//	This means there is a range of 94 which requires the rand() to be 
//	divided by 95.
//
//	This remainder was added to 32 and typecast to a character to return
//	an ASCII character.
//
//inputString():
//      Implemented by finding the remainder of a rand() output and dividing
//      by the ranger of lowercase letters in the alphabet. Since the testme
//      function is looking for a string of 5 letters followed by a null
//      terminator, inputString produces a random letter for each index
//      using a for loop and then places a null terminator in the last index.
//
//Finding the error message: 
//	Random characters are produced until the state reaches 9; 
//	To generate the error message it is required for the string to spell
//	out 'reset\0'. Because I am producing random characters in lower case
//	for each index it is expected that eventually the random tester 
//	will spell out the required combination of characters
//
//	I have tested my random tester with positive results and have seen the 
//	occurrence of each character produced in the correct index of the 
//	string.    	  	     
//
