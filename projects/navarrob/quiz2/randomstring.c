//
// Created by Rob Navarro on 2/2/17.
// CS362
// Random Testing Quiz 2
//

// To compile use the provided make file: make testme

// To clean up the directory use: make clean

/*
 * To develop the two functions needed for this test to pass, I began by reviewing the testme function. While reviewing
 * this function I immediately noticed that in order to print the error message certain conditions had to be met. To get
 * through the first section of the code a certain random character was required to advance to the next state. After
 * finishing the first 9 states a certain random string was required to print the error message.
 *
 * After further studying the first parts of testme, I settled on the fact that I need one of the following characters
 * "[({ax})] " at each stage. I started working on the inputChar function by first creating a string of the random
 * characters that I previously mentioned. I knew that the string length would always be 9 so I decided to randomly
 * generate a number between 0 and 8 to get an index for my random string. This allowed me to randomly chose a character
 * from my string and return it.
 *
 * I then shifted my focus to creating the random string. I noticed that for the error message to finally print the
 * random string would have to be "reset" plus a null terminating character at the end. As I started working on the
 * inputString function I decided to once again create a string with the letters that I knew I would need. I then
 * allocated space for a return string of size 6. This would ensure that the string always had the null terminating
 * character at the end. I then proceeded to create a for loop that would generate a random number from 0 to 5 for a
 * string index. With this index I would then place the place a random character from my letters string into my
 * randomString. Once the for loop finished I had a randomString with the letters required for getting to the error
 * message.
 *
 * After I finished both functions I tested them to ensure that the results were indeed random. I found that I never
 * received the same result, and that even with supplying only the needed letters, there could be several thousand
 * iterations until the error message was reached. Overall, I feel that reviewing the code before writing my two
 * functions allowed me to create a function that efficiently and randomly reached the error message.
 * */