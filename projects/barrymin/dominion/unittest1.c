#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
int main(){
  int i;
  //  - hard code each card's true cost
  int costs[]={0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
  int pass = 1;
	printf("------------------------ Testing getCost() -------------------------\n");

  for(i=0; i<=treasure_map;i++){
    printf("\nTEST %i:\n Card %d cost = %d, expected = %d\n",i+1,i, getCost(i), costs[i]);
    if(getCost(i) == costs[i]){
      printf(" test SUCCESSFUL\n");
    }else{
      printf(" test FAILED\n");
      pass = 0;
    }
  }
  if(pass)
    printf("--------------------------------------------------------------------\ngetCost() test SUCCESSFUL\n");
  else
    printf("--------------------------------------------------------------------\ngetCost() test FAILED\n");
  printf("-------------------------- Testing complete --------------------------\n");
 return 0;
}
