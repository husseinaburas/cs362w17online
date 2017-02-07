/*James Le
Quiz 2 - Random Testing
1/31/2017

The goal of this quiz is having the function testme() print out the "error" message
after going through a series of steps.

The first step is the main() function calling on testme() to look for certain chars
and strings in order to display the "error" message. It will have to look for specific
chars "([{ , a, x}])" and increases the state by 1, until it reaches 9 from 0.

This is done by calling the inputChar() function through the variable c to find random characters 
using the ASCII number chart, and translating decimal values into their corresponding letters. 
I chose the min decimal value as 32, which is the (space), and the max as 126, which is the tilda(~),
to cover all the characters needed to increase the state to 9.

The inputChar() function will then return a random character from the range of 32 to 126 and increment state to 9.
Once the state reaches 9, it will look for a series of char in order to form the string
"reset" with a terminating null at the end. 

This is done by calling on the inputString() function through the variable s. This function loops 6 times 
and to get a random character from the list that contains the character "r-e-s-t" and a terminating null, 
creating a string of 6 random letters with a terminating null at the end. This will keep going indefinitely 
until the string "reset" is formed.

At first, I had inputString() generate the ASCII decimal numbers randomly from 32 which is a (space),
to 126, which is a tilda(~). This works fine during the step of increasing the state from 0 - 9 for the 
inputChar() function, however, using that to form the string "reset" would take forever 
as there are so many different combinations. My program will not stop running after 20 mins, so I had
to force it to stop.

I also tried to make inputString() perform severeal do while loops using chars generated from inputChar()
to create the string "reset", like do{ string[0] = inputChar(); }while (string[0] != r), etc. But that 
would finish the string right away, which I don't know if it's also one of the correct way to do this quiz
as the test coverage is really small.

Therefore, I had to cut it down to just using the char "r-e-s-t" along with the terminating null. This makes 
reduces a lot of time to create the string "reset", but it also offers a good range of iterations. 
If I cut down to randomly generate the string "reset" from the char"r-e-s-t" without the terminating null included,
this would also end the test extremely quick. So, I think looping 6 times with the terminating null is the 
best method to cover the test.
*/