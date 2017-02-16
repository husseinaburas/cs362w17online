#!/bin/bash
./unittest1 >> rununittest.out
./unittest2 >> rununittest.out
./unittest3 >> rununittest.out
./unittest4 >> rununittest.out
gcov -b dominion.c >> unittestCov1.out
cat dominion.c.gcov >> unittestCov1.out