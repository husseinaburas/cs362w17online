#include <stdlib.h>

void assertResult(int test) {
  if (test) {
    printf("Test successful.\n");
  }
  else {
    printf("Test FAILED.\n");
  }
}
