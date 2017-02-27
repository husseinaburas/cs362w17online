/* Author: Bilal Saleem
 * Date: 1/31/17
 * Quiz 2 Write-up
 *
 * The inputChar() function selects, using the rand() function, a position within a string
 * of 67 characters.  The character found at that position is then placed in a character variable
 * that is returned.  
 *
 * The inputString() function uses the rand() function to select between five options.  The five
 * options are:
 * 	1) r		3) s		5) inputChar()
 *	2) e		4) t
 * If options 1-4 are selected, then the given character is inserted into a string in locations
 * randomString[0..4] (between 0 position and 4 position).  The same is with option 5, however, a 
 * random character from a set of 67 characters is selected. 
 * 
 * With this set up, there is at least a 20% chance that the character selected is either r, e, s or t.
 * and about a 20% chance some other character is selected.  On average, it takes less than 10,000 
 * iterations for the stop error state to be encountered.  
 */
