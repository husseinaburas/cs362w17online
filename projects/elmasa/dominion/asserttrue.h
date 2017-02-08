/*
 The replacement assert method so testing can continue if failure occurs
 */

#include <string.h>
#include <stdio.h>

void asserttrue(int theEqualityBool, int *testFailed) {
    
    if (theEqualityBool) {
        printf("l The Test Passed\n");
    }
    else {
        printf("X The Test did NOT Pass\n");
        *testFailed = 1;
    }
    return;
}
