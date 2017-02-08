int checkAssertion(int value1, int value2, int *numFailingTests, int *numPassedTests) {
    printf("\n     Expected: %d     Actual: %d ", value1, value2);
    if (value1 == value2) {
        printf(" -- TEST PASSED\n");
        (*numPassedTests)++;
    } else {
        printf(" -- TEST FAILED\n");
        (*numFailingTests)++;
    }
    printf("\n");
    return 0;
}