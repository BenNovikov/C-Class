//
//  BNStringTest.c
//  Human
//
//  Created by BenNovikov on 6/10/15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <assert.h>
#include <stdio.h>

#include "BNString.h"
#include "BNStringTest.h"
#include "BNMacros.h"

#pragma mark -
#pragma mark Private Declarations
static
void BNStringTestExecute(void);

#pragma mark -
#pragma mark Public Implementations
void BNStringTestRun(void){
    BNStringTestExecute();
}

#pragma mark -
#pragma mark Private Implementations
void BNStringTestExecute(void){
    //after a string was created
    BNString *myString = BNStringCreateWithData("This is sample text about Lorem Ipsum");
    assert(NULL != myString);
    
    //after a string was created
    BNString *anotherString = BNStringCreateWithData(NULL);
    assert(NULL != anotherString);
    
    //  print data out
    printf("String returned: %s\n", BNStringGetData(myString));
    printf("NULL returned: %s\n", BNStringGetData(anotherString));
    
    //  set nothing to _data field of string
    BNStringSetData(myString, NULL);
    
    //  print data out
    printf("NULL returned: %s\n", BNStringGetData(myString));
    
    //  set something else to _data field of string
    BNStringSetData(myString, "This is sample text about Lorem Ipsum");
    
    //  print data out
    printf("String returned: %s\n", BNStringGetData(myString));
    
    BNObjectRelease(anotherString);
    BNObjectRelease(myString);
}
