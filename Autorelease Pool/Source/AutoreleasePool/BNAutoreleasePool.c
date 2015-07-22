//
//  BNAutoreleasePool.c
//  Human
//
//  Created by BenNovikov on 06.07.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "BNObject.h"
#include "BNMacros.h"
#include "BNLinkedList.h"
#include "BNAutoreleasePool.h"
#include "BNAutoreleaseStack.h"
#include "BNAutoreleasePoolPrivate.h"

struct BNAutoreleasePool {
    BNObject            _super;
    
    BNLinkedList        *_list;
    BNAutoreleaseStack  *_stack;
    BNAutoreleasePool   *_parentPool;
};

const uint64_t kBNStackCapacity = 1024;

#pragma mark -
#pragma mark Private Declaration

//Declared by BNAutoreleasePoolPrivate.h
//static
//BNLinkedList *BNAutoreleasePoolGetList(BNAutoreleasePool *pool);

static
void BNAutoreleasePoolInit(BNAutoreleasePool *pool);

static
void BNAutoreleasePoolSetList(BNAutoreleasePool *pool, BNLinkedList *list);

static
BNAutoreleaseStack *BNAutoreleasePoolGetStack(BNAutoreleasePool *pool);

static
void BNAutoreleasePoolSetStack(BNAutoreleasePool *pool, BNAutoreleaseStack *stack);

static
BNAutoreleasePool *BNAutoreleasePoolGetParentPool(BNAutoreleasePool *pool);

static
void BNAutoreleasePoolSetParentPool(BNAutoreleasePool *pool, BNAutoreleasePool *parentPool);

static
BNAutoreleaseStack *BNAutoreleasePoolGetNextStack(BNAutoreleasePool *pool);

static
BNAutoreleaseStack *BNAutoreleasePoolSetNewStack(BNAutoreleasePool *pool);

#pragma mark -
#pragma mark Public Implementation

BNAutoreleasePool *BNAutoreleasePoolCreate(BNAutoreleasePool *parentPool) {
    BNAutoreleasePool *pool = BNObjectCreateOfType(BNAutoreleasePool);
    BNAutoreleasePoolInit(pool);
   
    return pool;
}

void __BNAutoreleasePoolDeallocate(void *pool) {
    
    __BNObjectDeallocate(pool);
}

void BNAutoreleasePoolAddObject(BNAutoreleasePool *pool, void *object) {
    if (NULL != pool && NULL != object) {
        
        BNAutoreleaseStackPush(BNAutoreleasePoolGetNextStack(pool), object);
    }
}

void BNAutoreleasePoolDrain(BNAutoreleasePool *pool) {
    if (NULL != pool) {
        BNAutoreleaseStack *stack = BNAutoreleasePoolGetStack(pool);
        BNLinkedList *list = BNAutoreleasePoolGetList(pool);
        BNAutoreleaseStackPopType popped;
        do {
            popped = BNAutoreleaseStackPop(stack);

            if (true == BNAutoreleaseStackIsEmpty(stack)) {
                BNObjectRelease(stack);
                BNLinkedListRemoveFirstObject(list);
                stack = (BNAutoreleaseStack *)BNLinkedListGetFirstObject(list);
                BNAutoreleasePoolSetStack(pool, stack);
            }
        } while (BNAutoreleaseStackPoppedObject == popped);

            if (NULL == BNAutoreleasePoolGetParentPool(pool)) {
                BNObjectRelease(stack);
                BNAutoreleasePoolSetList(pool, NULL);                
            } else {
//                BNObjectRelease(stack);
                BNAutoreleasePoolSetStack(pool, NULL);
                BNAutoreleasePoolSetParentPool(pool, NULL);
        }
        BNObjectRelease(pool);
    }
}

#pragma mark -
#pragma mark Private Implementation

void BNAutoreleasePoolInit(BNAutoreleasePool *pool) {
    if (NULL != pool) {
        BNAutoreleasePool *parentPool = BNAutoreleasePoolGetParentPool(pool);
        BNLinkedList *list = NULL;
        BNAutoreleaseStack *stack = NULL;
        if (NULL == parentPool) {
            list = BNLinkedListCreate();
            stack = BNAutoreleaseStackCreateWithCapacity(kBNStackCapacity);
            BNLinkedListAddObject(list, stack);
        } else {
            list = BNAutoreleasePoolGetList(parentPool);
            stack = BNAutoreleasePoolGetStack(parentPool);
            BNAutoreleasePoolSetParentPool(pool, parentPool);
        }
        assert(NULL != list && NULL != stack);
        BNAutoreleasePoolSetList(pool, list);
        BNAutoreleasePoolSetStack(pool, stack);
        BNAutoreleaseStackPush(BNAutoreleasePoolGetNextStack(pool), NULL);
    }
    
}

BNLinkedList *BNAutoreleasePoolGetList(BNAutoreleasePool *pool) {
    BNLinkedList *list = BNGetObjectVar(pool, _list);
    assert(NULL != list);
    
    return list;
}

void BNAutoreleasePoolSetList(BNAutoreleasePool *pool, BNLinkedList *list) {
    BNSetObjectVar(pool, _list, list);
}

BNAutoreleaseStack *BNAutoreleasePoolGetStack(BNAutoreleasePool *pool) {
    BNAutoreleaseStack *stack = BNGetObjectVar(pool, _stack);
    assert(NULL != stack);
    
    return stack;
}

void BNAutoreleasePoolSetStack(BNAutoreleasePool *pool, BNAutoreleaseStack *stack) {
    BNSetObjectVar(pool, _stack, stack);
}

BNAutoreleasePool *BNAutoreleasePoolGetParentPool(BNAutoreleasePool *pool) {
    return BNGetObjectVar(pool, _parentPool);
}

void BNAutoreleasePoolSetParentPool(BNAutoreleasePool *pool, BNAutoreleasePool *parentPool) {
    BNRetainSetter(pool, _parentPool, parentPool);
}

BNAutoreleaseStack *BNAutoreleasePoolGetNextStack(BNAutoreleasePool *pool) {
    BNAutoreleaseStack *stack = NULL;
    if (NULL != pool) {
        stack = BNAutoreleasePoolGetStack(pool);
        BNAutoreleaseStack *nextStack;
        if (NULL == stack || true == BNAutoreleaseStackIsFull(stack)) {
            nextStack = ((BNAutoreleaseStack *)BNLinkedListGetObjectBeforeObject(BNAutoreleasePoolGetList(pool), stack));
            if (NULL != nextStack && stack != nextStack) {
                stack = nextStack;
            } else {
                stack = BNAutoreleasePoolSetNewStack(pool);
            }
        }
        BNAutoreleasePoolSetStack(pool, stack);
    }
    
    return stack;
}

BNAutoreleaseStack *BNAutoreleasePoolSetNewStack(BNAutoreleasePool *pool) {
    BNAutoreleaseStack *stack = NULL;
    if (NULL != pool) {
        stack = BNAutoreleaseStackCreateWithCapacity(kBNStackCapacity);
        BNLinkedListAddObject(BNAutoreleasePoolGetList(pool), stack);
        BNAutoreleasePoolSetStack(pool, stack);
    }
    
    return stack;
}
