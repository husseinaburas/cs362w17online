#include "devassert.h"

int asserttrue(int expected, int actual)
{
    int match = 1;
    
    if (expected != actual)
    {
        match = 0;
    }
      
    return match;
}

int assertfalse(int expected, int actual)
{
    int match = 1;
    
    if (expected == actual)
    {
        match = 0;
    }
      
    return match;
}