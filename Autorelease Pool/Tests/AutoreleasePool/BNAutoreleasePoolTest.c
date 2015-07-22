//
//  BNAutoreleasePoolTest.c
//  Human
//
//  Created by BenNovikov on 06.07.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "BNMacros.h"
#include "BNLinkedList.h"
#include "BNHumanBeing.h"
#include "BNAutoreleaseStack.h"
#include "BNAutoreleasePool.h"
#include "BNAutoreleasePoolTest.h"
#include "BNAutoreleasePoolPrivate.h"

#pragma mark -
#pragma mark Private Declaraion
static
void BNAutoreleasePoolTestExecute(void);

static
void BNAutoreleasePoolMultipleTestExecute(void);

static
void BNAutoreleasePoolStringTestExecute(void);

#pragma mark -
#pragma mark Public Implementaion
void BNAutoreleasePoolTestRun(void) {
    BNObjectLaunchTest(BNAutoreleasePoolTestExecute());
    BNObjectLaunchTest(BNAutoreleasePoolMultipleTestExecute());
    BNObjectLaunchTest(BNAutoreleasePoolStringTestExecute());
}

#pragma mark -
#pragma mark Private Implementaion
void BNAutoreleasePoolTestExecute() {
    uint64_t objectsNumber = UINT32_MAX >> 12; //UINT32_MAX >> 6;
    printf("Current Test     :%lld \n2*(UINT32_MAX>>6):%u\n", objectsNumber * 2, 2*(UINT32_MAX >> 6));

    
    BNAutoreleasePool *pool = BNAutoreleasePoolCreate(NULL);
    
    for (uint64_t index = 0; index < objectsNumber; index++) {
        BNAutoreleasePoolAddObject(pool, BNObjectCreateOfType(BNObject));
    }
    
    BNAutoreleasePoolDrain(pool);
    
    pool = BNAutoreleasePoolCreate(NULL);
    
    for (uint64_t index = 0; index < objectsNumber; index++) {
        BNAutoreleasePoolAddObject(pool, BNObjectCreateOfType(BNObject));
    }
    
    BNAutoreleasePoolDrain(pool);
}

void BNAutoreleasePoolMultipleTestExecute(){
    uint64_t objectsNumber = UINT32_MAX >> 10; //UINT32_MAX >> 6;
    uint32_t nestedPools = 4;
    printf("Current Test     :%lld \n2*(UINT32_MAX>>6):%u\n", objectsNumber, 2*(UINT32_MAX >> 6));
    
    BNAutoreleasePool *pool = BNAutoreleasePoolCreate(NULL);
    for (uint64_t index = 0; index < objectsNumber / nestedPools; index++) {
        BNAutoreleasePoolAddObject(pool, BNObjectCreateOfType(BNObject));
    }
    
    BNAutoreleasePool *pool2 = BNAutoreleasePoolCreate(pool);
    for (uint64_t index = 0; index < objectsNumber / nestedPools; index++) {
        BNAutoreleasePoolAddObject(pool2, BNObjectCreateOfType(BNObject));
    }
    
    BNAutoreleasePool *pool3 = BNAutoreleasePoolCreate(pool2);
    for (uint64_t index = 0; index < objectsNumber / nestedPools; index++) {
        BNAutoreleasePoolAddObject(pool3, BNObjectCreateOfType(BNObject));
    }
    
    BNAutoreleasePool *pool4 = BNAutoreleasePoolCreate(pool3);
    for (uint64_t index = 0; index < objectsNumber / nestedPools; index++) {
        BNAutoreleasePoolAddObject(pool4, BNObjectCreateOfType(BNObject));
    }
    
    BNAutoreleasePoolDrain(pool4);
    BNAutoreleasePoolDrain(pool3);
    BNAutoreleasePoolDrain(pool2);
    BNAutoreleasePoolDrain(pool);
}

void BNAutoreleasePoolStringTestExecute() {
    
    //    add some Objects to the pool
    uint64_t const objectsNumber = UINT32_MAX >> 13; //UINT32_MAX >> 6;
    BNString *object[objectsNumber];
    char text[1 + snprintf(0,0,"%+lld", objectsNumber)];
    printf("%lld\n", objectsNumber);
    
    //    After AutoreleasePool has been created
    BNAutoreleasePool *pool = BNAutoreleasePoolCreate(NULL);
    
    for (uint64_t index = 0; index < objectsNumber; index++) {
        sprintf(text, "#%llu", index);
        object[index] = BNStringCreateWithData(text);
        BNAutoreleasePoolAddObject(pool, object[index]);
    }
    
    //    After newPool1 was created and filled with objects
    BNAutoreleasePool *newPool1 = BNAutoreleasePoolCreate(pool);
    for (uint64_t index = 0; index < objectsNumber; index++) {
        sprintf(text, "#%llu", index);
        object[index] = BNStringCreateWithData(text);
        BNAutoreleasePoolAddObject(newPool1, object[index]);
    }
    
    //    drain pool
    BNAutoreleasePoolDrain(newPool1);
    
    //    After newPool2 was created and filled with objects
    BNAutoreleasePool *newPool2 = BNAutoreleasePoolCreate(pool);
    for (uint64_t index = 0; index < objectsNumber; index++) {
        sprintf(text, "#%llu", index);
        object[index] = BNStringCreateWithData(text);
        BNAutoreleasePoolAddObject(newPool2, object[index]);
    }
    
    //    After newPool3 was created and filled with objects
    BNAutoreleasePool *newPool3 = BNAutoreleasePoolCreate(newPool2);
    for (uint64_t index = 0; index < objectsNumber; index++) {
        sprintf(text, "#%llu", index);
        object[index] = BNStringCreateWithData(text);
        BNAutoreleasePoolAddObject(newPool3, object[index]);
    }
    
    //    drain pools
    BNAutoreleasePoolDrain(newPool3);
    BNAutoreleasePoolDrain(newPool2);    
    BNAutoreleasePoolDrain(pool);
}
