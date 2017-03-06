int checkAssertion(int value1, int value2, int *numFailingTests, int *numPassedTests) {
    printf("\n     Expected: %d     Actual: %d ", value1, value2);
    int retVal = 0;
    if (value1 == value2) {
        printf(" -- TEST PASSED\n");
        (*numPassedTests)++;
        retVal = 1;
    } else {
        printf(" -- TEST FAILED\n");
        (*numFailingTests)++;
        retVal = 0;
    }
    printf("\n");
    return retVal;
}