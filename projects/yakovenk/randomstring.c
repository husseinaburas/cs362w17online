To print the error I traced the code and found out that we need to input characters "[({ ax})]" in that order and then have the inputString be equal to "reset". First, I validated that idea by passing in exactly those values and got the error. Since this is about random testing and we are supposed to be using random values I started writing first the inputCharacter() function, which returns a random character out of the range of printable characters. In real situaltion I'd probably like to try all possible characters and random garbage values, but here, for the sake of speed, I did just printable characters. Then I tested this and made sure that we get to state=9 to make sure that random characters are getting generated and we are going down our necessary path.
Then I started on the random string. To get to the error, we need the string to equal to "reset" so I wrote a function that randomly generates characters in a string. At first I was using the inputString() as my generator, but that took too long. Also, for the sake of time, I limited the length of the string to be exactly 5 characters. Ideally we would test different lengths, but because of time and problem definition, I limited it in this way.
Even with these limitations it took a while to run. While typing this up I ran the test a total of 4 times and the results varied pretty wildly. Some took only numdreds of thousands of tries, some tens of millions. 


Iteration 10678257: c = _, s = reset, state = 9
Iteration 8960304: c = }, s = reset, state = 9
Iteration 883527: c = 2, s = reset, state = 9
Iteration 24442416: c = +, s = reset, state = 9
