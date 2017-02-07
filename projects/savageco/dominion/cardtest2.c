/*
  cardtest2.c
  Corey Savage
  Assignment 3
  
  Description: Testing for Smithy Card
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void assert_true(int);

int main() {



}

// Used to print success or failure messages for test. Comparisons will be made within the 
// function parameters to test results. 
void assert_true(int bool) {
  
  if (bool != 0) {
    printf("      -Test Passed");
  }
  else {
    printf("      -Test Failed");
  }

}
