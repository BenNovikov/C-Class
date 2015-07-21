//
//  BNObject.c
//  Humanity
//
//  Created by BenNovikov on 27.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <stdlib.h>
#include <assert.h>

#include "BNObject.h"

#pragma mark -
#pragma mark Public Implementation

void __BNObjectDeallocate(void *object) {
    
    free(object);
}

void *__BNObjectCreate(size_t objectSize, BNObjectDeallocatorCallback deallocateCallback){
    assert (0 != objectSize);
    
    BNObject *object = calloc(1, objectSize);    
    assert (NULL != object);
    
    object->_referenceCount = 1;
    object->_deallocator = deallocateCallback;
    
    return object;
};

void *BNObjectRetain(void *object) {
    if (NULL != object){
        ((BNObject*)object)->_referenceCount++;
    }
    return object;
}

void BNObjectRelease(void *object) {
    if (NULL != object){
        uint64_t count = ((BNObject *)object)->_referenceCount;
        if (0 != count) {
            ((BNObject *)object)->_referenceCount = --count;
        }
        if (0 == count) {
            ((BNObject *)object)->_deallocator(object);
        }
    }
}

uint64_t BNObjectGetReferenceCount(void *object) {
    return (NULL != object) ? ((BNObject *)object)->_referenceCount : 0;
}
