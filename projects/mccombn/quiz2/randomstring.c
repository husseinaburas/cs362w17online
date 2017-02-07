/*

Nick McComb | www.nickmccomb.net
Written for CS362 Quiz 2 in Winter 2017

I really like writing tests like this that just throw random tests at the code to check for all posiblilities and just throws processor cycles at the problem. During my testing, I found the 'reset' phrase (definitely the hardest part of the randomness) at 12 million and then iteration 41327494.

This approach also allows a large amount of modularity for testing and can allow the code to be transported between testing cases more easily (which can save developer time when testing different code later).

My inputChar function works by generating a random number, and modulating it by 34 (because there are 34 different characters I want to test). Then it adds 97 so that the number is a valid ASCII character (starting at lower case a and then ending with '}'). A reference is available here: http://www.asciitable.com/. I then special case out the '(', ')', '[', ']', and the ' ' by just adding on extra values and using if statements. It's definitely not the most efficient, but it tests all of the lowercase letters.

My inputString function mallocs memory for the string (which is freed later in testme()), loops through adding random characters from the inputChar() method, and then finally adds a null terminator, and returns the reference to the string.

Then the rest of testme() is the same, besides some commented out testing code and free(s).

In all, the code takes a while to run, but its a type of "grab a coffee and come back" situation in my mind, and could potentially, in some situations, catch some extra bugs.

*/