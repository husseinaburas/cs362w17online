#include "assert_custom.h"

void assert_custom(int result, char *str)
{
   if(result)
   {
      printf("ASSERT PASS: %s\n", str);
   } else {
      printf("ASSERT FAIL: %s\n", str);
   }
}
