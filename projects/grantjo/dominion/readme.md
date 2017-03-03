## CS362 dominion folder
#### Student: grantjo
---

### makefile rules 

make:
  makes all original dominion binaries
  1. player
  2. playdom
  3. testDrawCard
  4. testBuyCard
  5. badTestBuyCard

make unittestresults.out
  - generates all unittests and cardtests
  - creates unittestresults.out file with results of all tests and gcov data

  Sub make rules:
  make unittest1
  make unittest2
  make unittest3
  make unittest4
  make cardtest1
  make cardtest2
  make cardtest3
  make cardtest4

make randomtestcard1.out
  - generates randomtestcard1 (Village Card random test)
  - creates randomtestcard1.out file with results of random test and gcov data

  Sub make rule: 
  make randomtestcard1

make randomtestcard2.out
  - generates randomtestcard2 (Great Hall Card random test)
  - creates randomtestcard1.out file with results of random test and gcov data
  
  Sub make rule: 
  make randomtestcard2 

make randomtestadventurer.out
  - generates randomtestadventurer (Adventurer Card random test)
  - creates randomtestadventurer.out file with results of random test and gcov data

  Sub make rule: 
  make randomtestadventurer

make random_tests
  - makes randomtestcard1.out randomtestcard2.out and randomtestadventurer.out

make unittestresults.Hat
  - generates all unittests and cardtests with dominion code from
    the hatchimgDominion folder
  - creates unittestresults.Hat file with results of all tests and gcov data

  Sub make rules:
  make unittest1Hat
  make unittest2Hat
  make unittest3Hat
  make unittest4Hat
  make cardtest1Hat
  make cardtest2Hat
  make cardtest3Hat
  make cardtest4Hat

make randomtestcard1.Hat
  - generates randomtestcard1Hat (Village Card random test with dominion code
    from hatchimgDominion)
  - creates randomtestcard1.Hat file with results of random test and gcov data
  
  Sub make rule:
  make randomtestcard2Hat

make randomtestcard2.Hat
  - generates randomtestcard2Hat (Great Hall Card random test with dominion
    code from hatchimgDominion)
  - creates randomtestcard1.Hat file with results of random test and gcov data
  
  Sub make rule:
  make randomtestcard2Hat

make randomtestadventurer.Hat
  - generates randomtestadventurerHat (Adventurer Card random test with
    dominion code from hatchimgDominion)
  - creates randomtestadventurer.Hat file with results of random test and gcov data
  
  Sub make rule:
  make randomtestadventurerHat
make random_tests_hat
  - makes randomtestcard1.Hat randomtestcard2.Hat and randomtestadventurer.Hat

make unittestresults.Lee
  - generates all unittests and cardtests with dominion code from
    the leeeltDominion folder
  - creates unittestresults.Lee file with results of all tests and gcov data

  Sub make rules:
  make unittest1Lee
  make unittest2Lee
  make unittest3Lee
  make unittest4Lee
  make cardtest1Lee
  make cardtest2Lee
  make cardtest3Lee
  make cardtest4Lee

make randomtestcard1.Lee
  - generates randomtestcard1Lee (Village Card random test with dominion code
    from leeeltDominion)
  - creates randomtestcard1.Lee file with results of random test and gcov data
  
  Sub make rule:
  make randomtestcard2Lee

make randomtestcard2.Lee
  - generates randomtestcard2Lee (Great Hall Card random test with dominion
    code from leeeltDominion)
  - creates randomtestcard1.Lee file with results of random test and gcov data
  
  Sub make rule:
  make randomtestcard2Lee

make randomtestadventurer.Lee
  - generates randomtestadventurerLee (Adventurer Card random test with
    dominion code from leeeltDominion)
  - creates randomtestadventurer.Lee file with results of random test and gcov data
  
  Sub make rule:
  make randomtestadventurerLee
make random_tests_hat
  - makes randomtestcard1.Lee randomtestcard2.Lee and randomtestadventurer.Lee
