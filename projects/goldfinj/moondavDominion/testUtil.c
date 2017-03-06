#include <stdio.h>
#include "testUtil.h"


int printTest(const char *desc, int expected, int actual)
{
    int result = (expected == actual);
    char *status = result ? "SUCCESS" : "FAILURE";

    printf("%s\n%s:\texpected: %d\tactual: %d\n", desc, status, expected, actual);

    return result;
}
