int checkAssertion(int value1, int value2, int *numFailingTests, int *numPassedTests) {
    if (value1 == value2) {
        printf(" -- TEST PASSED\n");
        (*numPassedTests)++;
    } else {
        printf(" -- TEST FAILED\n");
        (*numFailingTests)++;
    }
    return 0;
}