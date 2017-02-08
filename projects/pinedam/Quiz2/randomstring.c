Random testing Quiz 2 
Monica Pineda
Description: Implement a random tester for the function testme() in testme.c that is capable of printing the error message.
You should implement inputChar() and inputString() to produce random values. Write up the development of your random tester 
and how it finds the error message as randomstring.c. Submit testme.c and randomstring.c under your onid directory in class github. 
(under your onid directory and not under dominion directory). The randomstring.c is a text file that outlines how you developed your solution and how it works!

I began by reviewing the code in order to figure out the specifications of the testme () function. 

 * It consistts of a loop that performs checks on 3 variables
 * It gets the c varibale from inputChar
 * It gets the s variable from inputString
 * The state is incremented when c holds a certain character 
 * The loop prints the contents of all three variables for each iteration and continually exicutes unitl s="reset"
	and state=9 which it then prints out "error" and exits with code 200

I then moved to the implementations using only the specific characters that would progress the loop. I created two const char name testChar and testString, 
which hold these characters. I then sized the char array "s" to a size of 6 to incorporate 5 random characters form testChar and a termninating character, 
since that is what testme looks for. Once I got that running I widened the base of characters that inputChar could randomly choose from and tested it, 
but the runtimes were too long for practical testing. So in order to test this I shortened testChar to the base characters again that testme is looking for. 

			Results:
------------------------------------------
test 							iteration
Run 1:							16892407
Run 2:							20017459
Run 3:							3458364
Run 4:							2692818
Run 5:							27583779
Run 6:							23847640
Run 7:							7620518
Run 8:							21688258
Run 9:							35929514
Run 10:							16299543
-----------------------------------------
AVG: 							17603030
