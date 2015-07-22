//
//  BNAutoreleaseStackTest.c
//  Human
//
//  Created by BenNovikov on 05.07.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BNAutoreleaseStackTest.h"
#include "BNAutoreleaseStack.h"
#include "BNObject.h"
#include "BNString.h"

#pragma mark -
#pragma mark Private Declaraion
void BNAutoreleaseStackTestExecute(void);


#pragma mark -
#pragma mark Public Implementaion
void BNAutoreleaseStackTestRun(void) {
    BNAutoreleaseStackTestExecute();
}

#pragma mark -
#pragma mark Private Implementaion
void BNAutoreleaseStackTestExecute(void) {
    // After AutoreleaseStack and a few objects were created
    uint32_t const objectsNumber = 200000;
    BNString *object[objectsNumber];
    char text[7 + snprintf(0,0,"%+d", objectsNumber)];
    
    uint64_t capacity = objectsNumber;
    BNAutoreleaseStack *stack = BNAutoreleaseStackCreateWithCapacity(capacity);

    for (uint64_t index = 0; index < objectsNumber; index++) {
        sprintf(text, "object#%llu", index);
        object[index] = BNStringCreateWithData(text);
    }
    
    //  stack has to be empty
    assert(true == BNAutoreleaseStackIsEmpty(stack));
    
    //  push objects to the stack
    for (uint64_t index = 0; index < objectsNumber; index++) {
//        if (true == BNAutoreleaseStackIsFull(stack)) {
//            printf(" \nStack is Full! ");
//        } else {
//            printf("push %s; ", BNStringGetData(object[index]));
//        }
        BNAutoreleaseStackPush(stack, object[index]);
    }
    printf("\n");
    
    //  pop one, it has to be poppedObject
    BNAutoreleaseStackPopType poppedResult = BNAutoreleaseStackPop(stack);
    assert(BNAutoreleaseStackPoppedObject == poppedResult);
    
    //  pop until empty
    poppedResult = BNAutoreleaseStackPopUntilEmpty(stack);
    
    //  it has to be poppedNULL
    assert(BNAutoreleaseStackPoppedNULL == poppedResult);

    BNObjectRelease(stack);
}
