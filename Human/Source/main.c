//
//  main.c
//  Human
//
//  Created by BenNovikov on 30.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <stdio.h>

#include "BNMacros.h"
#include "BNObjectTest.h"
#include "BNArrayTest.h"
#include "BNStringTest.h"
#include "BNHumanBeingTest.h"
#include "BNLinkedListTest.h"
#include "BNAutoreleasePoolTest.h"
#include "BNAutoreleaseStackTest.h"


int main(int argc, const char * argv[])
{
    BNObjectLaunchTest(BNObjectTestRun());
    BNObjectLaunchTest(BNArrayTestRun());
    BNObjectLaunchTest(BNStringTestRun());
    BNObjectLaunchTest(BNHumanBeingTestRun());
    BNObjectLaunchTest(BNLinkedListTestRun());    
    BNObjectLaunchTest(BNAutoreleaseStackTestRun());
    BNObjectLaunchTest(BNAutoreleasePoolTestRun());
    
    return 0;
}
