#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"

void testSupplyCount(){


  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &G);

  G.supplyCount[adventurer] = 5;
  G.supplyCount[embargo] = 3;
  G.supplyCount[minion] = 2;
  G.supplyCount[tribute] = 1;
  G.supplyCount[village] = 4;



    /*******Test 1********/
  int adventurerSupplyCount = supplyCount(adventurer,&G);


    if(adventurerSupplyCount==5){

        printf("Function supplyCount PASS for adventurerSupplyCount.\n");
    }

    else{

        printf("Function supplyCount FAIL for adventurerSupplyCount. %i \n", adventurerSupplyCount);
    }

  int embargoSupplyCount = supplyCount(embargo,&G);


    if(embargoSupplyCount==3){

        printf("Function supplyCount PASS for embargoSupplyCount.\n");
    }

    else{

        printf("Function supplyCount FAIL for embargoSupplyCount. %i \n", embargoSupplyCount);
    }

   int minionSupplyCount = supplyCount(minion,&G);


    if(minionSupplyCount==2){

        printf("Function supplyCount PASS for minionSupplyCount.\n");
    }

    else{

        printf("Function supplyCount FAIL for minionSupplyCount. %i \n", minionSupplyCount);
    } 

    int tributeSupplyCount = supplyCount(tribute,&G);


    if(tributeSupplyCount==1){

        printf("Function supplyCount PASS for tributeSupplyCount.\n");
    }

    else{

        printf("Function supplyCount FAIL for tributeSupplyCount. %i \n", tributeSupplyCount);
    }

    int villageSupplyCount = supplyCount(village,&G);


    if(villageSupplyCount==4){

        printf("Function supplyCount PASS for villageSupplyCount.\n");
    }

    else{

        printf("Function supplyCount FAIL for villageSupplyCount. %i \n", villageSupplyCount);
    }

    /*******Test 2********/
    //ensure function didn't modify supply count 
    if(G.supplyCount[village]==4){

      printf("Function supplyCount PASS. Did not modify supply count.\n");
    }
    else{

      printf("Function supplyCount FAIL. Modified supply count.\n");

    }
}



    

int main(int argc, char *argv[])
{
    testSupplyCount();
    return 0;
}


