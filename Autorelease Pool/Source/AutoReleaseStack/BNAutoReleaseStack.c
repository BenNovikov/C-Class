//
//  AutoreleaseStack.c
//  Human
//
//  Created by BenNovikov on 03.07.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "BNAutoreleaseStack.h"
#include "BNObject.h"
#include "BNMacros.h"

struct BNAutoreleaseStack {
    BNObject _super;
    
    void **_data;
    uint64_t _capacity;
    uint64_t _count;
};

#pragma mark -
#pragma mark Private Declaration

static
void **BNAutoreleaseStackGetData(BNAutoreleaseStack *stack);

static
void BNAutoreleaseStackSetDataAtIndex(BNAutoreleaseStack *stack, void *object, uint64_t index);

static
uint64_t BNAutoreleaseStackGetCapacity(BNAutoreleaseStack *stack);

static
void BNAutoreleaseStackSetCapacity(BNAutoreleaseStack *stack, uint64_t capacity);

static
uint64_t BNAutoreleaseStackGetCountField(BNAutoreleaseStack *stack);

static
void BNAutoreleaseStackSetCount(BNAutoreleaseStack *stack, uint64_t count);

#pragma mark -
#pragma mark Public Implementation

BNAutoreleaseStack *BNAutoreleaseStackCreateWithCapacity(uint64_t capacity) {
    BNAutoreleaseStack *stack = BNObjectCreateOfType(BNAutoreleaseStack);
    BNAutoreleaseStackSetCapacity(stack, capacity);
    BNAutoreleaseStackSetCount(stack, 0);
    
    return stack;
}

void __BNAutoreleaseStackDeallocate(void *stack) {
    
    __BNObjectDeallocate(stack);
}

uint64_t BNAutoreleaseStackGetCount(BNAutoreleaseStack *stack) {
    return BNAutoreleaseStackGetCountField(stack);
}

void BNAutoreleaseStackPush(void *stack, void *object) {
    if (NULL != stack) {
        assert(false == BNAutoreleaseStackIsFull(stack));
        uint64_t count = BNAutoreleaseStackGetCount(stack);
        BNAutoreleaseStackSetCount(stack, count + 1);
        BNAutoreleaseStackSetDataAtIndex(stack, object, count);
    }
}

BNAutoreleaseStackPopType BNAutoreleaseStackPop(void *stack){
    if (NULL != stack && false == BNAutoreleaseStackIsEmpty(stack)) {
        uint64_t count = BNAutoreleaseStackGetCount(stack) - 1;
        void **data = BNAutoreleaseStackGetData(stack)[count];
        BNAutoreleaseStackSetCount(stack, count);
        
        if (NULL != data) {
            BNObjectRelease(data);
            
            return BNAutoreleaseStackPoppedObject;
        }
    }
    
    return BNAutoreleaseStackPoppedNULL;
}

BNAutoreleaseStackPopType BNAutoreleaseStackPopUntilEmpty(void *stack) {
    BNAutoreleaseStackPopType result;
    assert(NULL != stack);
    do {
        result = BNAutoreleaseStackPop(stack);
    } while (BNAutoreleaseStackPoppedNULL != result);

    return result;
}

bool BNAutoreleaseStackIsFull(void *stack) {
    return (NULL != stack) && (BNAutoreleaseStackGetCount(stack) == BNAutoreleaseStackGetCapacity(stack));
}

bool BNAutoreleaseStackIsEmpty(void *stack) {
    return (NULL != stack) && (0 == BNAutoreleaseStackGetCount(stack));
}

#pragma mark -
#pragma mark Private Implementation

void **BNAutoreleaseStackGetData(BNAutoreleaseStack *stack) {
    return BNGetObjectVar(stack, _data);
}

void BNAutoreleaseStackSetDataAtIndex(BNAutoreleaseStack *stack, void *object, uint64_t index) {
    if (NULL != stack && (index < BNAutoreleaseStackGetCount(stack) || 0 == index)) {

        void **data = BNAutoreleaseStackGetData(stack)[index];
        if (data != object) {
            
//            if (NULL != data) {
//                BNObjectRelease(data);
//            }
            BNAutoreleaseStackGetData(stack)[index] = object;
            
        }
    }
}

uint64_t BNAutoreleaseStackGetCapacity(BNAutoreleaseStack *stack) {
    return BNGetPrimitiveVar(stack, _capacity);
}

void BNAutoreleaseStackSetCapacity(BNAutoreleaseStack *stack, uint64_t capacity) {
    BNSetObjectVar(stack, _capacity, capacity);
}

uint64_t BNAutoreleaseStackGetCountField(BNAutoreleaseStack *stack) {
    return BNGetPrimitiveVar(stack, _count);
}

void BNAutoreleaseStackSetCount(BNAutoreleaseStack *stack, uint64_t count) {
    if (NULL != stack) {
        uint64_t capacity = BNGetPrimitiveVar(stack, _capacity);
        if (0 == count) {
            if (NULL != stack->_data) {
                free(stack->_data);
                stack->_data = NULL;
            } else {
//                stack->_data = calloc(1, capacity * sizeof(*stack->_data));
                stack->_data = malloc(capacity * sizeof(*stack->_data));
                assert(NULL != stack->_data);
            }
        }
        if (count <= capacity) {
            BNSetObjectVar(stack, _count, count);
        }        
    }
}
