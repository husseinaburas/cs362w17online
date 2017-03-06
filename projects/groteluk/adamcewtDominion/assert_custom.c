#include "assert_custom.h"

int assert_custom(int result, char *str)
{
   int failFlag = 0;

   if(result)
   {
      printf("ASSERT PASS: %s\n", str);
   } else {
      printf("ASSERT FAIL: %s\n", str);
      failFlag = 1;
   }
return failFlag;
}
