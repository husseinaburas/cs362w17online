/* Ryan Vandewynkel
 * CS362
 *
 *
 * For the inputChar() function, I made a char array that holds all possible chars that will
 * be checked for to change the state variable.  I leveraged srand from the main function and
 * obtained a value in the range 0-8.  After using the rand() function, I used a variable to store
 * the character located within the array, where the randomly generated value was.  This process
 * eventually returned the appropriate char that would increment the state variable.
 *
 * For the inputString() function, I created another array of only characters that were needed.
 * I created an empty char array to store the randomly generated string.  There needed to be 6
 * characters in the string, so I looped over the charList 6 times, with each passing generating
 * a random integer in the range 0-4 to select a character.  The randomString variable was updated
 * and then returned at the end.
 *
 * The state variable increases with each matching char that is returned.  After the state has reached
 * the value of 9, the random string is now matters because even if the string matches if the state is
 * not equal to 9 the error message will not be reached.  Once string is matched and state is equal to 9
 * the exit message occurs.
 */

