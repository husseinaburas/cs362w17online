#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "newAssert.h"


void assertTrue(int left, char comparator[2],int right){
  if(comparator[0] == '='){
    if(comparator[1] == '='){
      if(left == right){
        //printf("Assertion True\n");
      }
      else{
        printf("*******Assertion False*******\n");
      }
    }
  }
  else if(comparator[0] == '>'){
    if(comparator[1] == '>'){
      if(left > right){
        printf("Assertion True\n");
      }
      else{
        printf("*******Assertion False*******\n");
      }
    }
    else if(comparator[1] == '='){
      if(left >= right){
        printf("Assertion True\n");
      }
      else{
        printf("*******Assertion False*******\n");
      }
    }
  }
  else if(comparator[0] == '<'){
    if(comparator[1] == '<'){
      if(left < right){
        printf("Assertion True\n");
      }
      else{
        printf("*******Assertion False*******\n");
      }
    }
    else if(comparator[1] == '='){
      if(left <= right){
        printf("Assertion True\n");
      }
      else{
        printf("*******Assertion False*******\n");
      }
    }
  }
  else if(comparator[0] == '!'){
    if(left != right){
      printf("Assertion True\n");
    }
    else{
      printf("*******Assertion False*******\n");
    }
  }
}
