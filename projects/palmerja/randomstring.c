 /* 
First, one has to look at the code to understand a basic concept on what is going on.
From a basic standpoint, it looks that the code is just a loop that cycles through your random functions.
First the code needs to get to a state of 9 and each of the random symbols that are in the code. 
I created a random character generator that concsistantly hit state 9. 
The next step was to create a random string generator. Firsts I attempted by just adding letters such as 
a and b the the array that I would run into the error of over 130,000 iteration range  until an error message appeared.
So, I set up a loop to run 6 times while each time with settling on two letters of 'e' and 't'. 
I would like to state that this methon is very inefficient (random testing) because it is very difficult to control 
the variables as well as pinpointing what variables will be in use. It was difficult to control the variables without 
affecting the effectiveness of the random generator.


*/