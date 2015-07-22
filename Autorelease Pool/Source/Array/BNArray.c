//
//  BNHumanArray.c
//  Human
//
//  Created by BenNovikov on 31.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "BNArray.h"
#include "BNMacros.h"
#include "BNArrayPrivate.h"

// memory allocation buffer, capacity in elements
const uint64_t kBNExpand = 10;

// kBNMaxCount - maximum number of elements in array
const uint64_t kBNMaxCount = UINT64_MAX - kBNExpand - 1;

struct BNArray {
    BNObject _super;
    
    void **_data;
    uint64_t _count;
};

#pragma mark -
#pragma mark Private Declarations

static
void BNArraySetCount(BNArray *array, uint64_t count);

static
void **BNArrayGetDataField(BNArray *array);

static
uint64_t BNArrayGetCountField(BNArray *array);

static
uint64_t BNArrayGetCapacity(BNArray *array, uint64_t count);

#pragma mark -
#pragma mark Public Implementations

void __BNArrayDeallocate(void *array) {
    BNArrayRemoveAllObjects(array);
        
    __BNObjectDeallocate(array);
}

void *BNArrayInit() {
    BNArray *array = BNObjectCreateOfType(BNArray);
    BNArraySetCount(array, 0);

    return array;
}

uint64_t BNArrayGetCount(void *array) {
    
    return BNArrayGetCountField(array);
}

uint64_t BNArrayGetIndexOfObject(void *array, void *object) {
    uint64_t result = 0;
    if (NULL != object) {
        for (uint64_t index = 0; index < BNArrayGetCount(array); index++) {
            if (BNArrayGetObjectAtIndex(array, index) == object) {
                result = index;
                break;
            }
        }
    }
    
    return result;
}

bool BNArrayContainsObject(void *array, void *object) {
    if (NULL != array && NULL != object) {
        
        return (object == BNArrayGetObjectAtIndex(array,BNArrayGetIndexOfObject(array, object)));
    }
    
    return false;
}

void BNArrayAddObject(void *array, void *object) {
    if (NULL != array && NULL != object) {
        uint64_t index = BNArrayGetCount(array);
        
        BNArraySetCount(array, index + 1);
        BNArraySetObjectAtIndex(array, object, index);

    }
}

void *BNArrayGetObjectAtIndex(void *array, uint64_t index) {
    if (NULL != array && NULL != BNArrayGetDataField(array)) {
        assert(index <= BNArrayGetCount(array));

        return BNArrayGetDataField(array)[index];
    }
    
    return NULL;
}

void BNArraySetObjectAtIndex(void *array, void *object, uint64_t index) {
    if (NULL != array) {
        assert (index < BNArrayGetCount(array));
        void **data = BNArrayGetDataField(array);
        if (data != object) {
            BNObjectRetain(object);
            if (NULL != data && NULL != data[index]) {
                BNObjectRelease(data[index]);
            }
            data[index] = object;
        }
    }
}

void BNArrayRemoveObjectAtIndex(void *array, uint64_t index) {
    uint64_t count = BNArrayGetCount(array);

    if (NULL != array && index < count) {
        BNArraySetObjectAtIndex(array, NULL, index);
        
        void **data = BNArrayGetDataField(array);
        memmove(&data[index], &data[index + 1], (count - 1 - index) * sizeof(*data));
        
        BNArraySetCount(array, count - 1);
    }
}

void BNArrayRemoveAllObjects(void *array) {
    if (NULL != array && 0 != BNArrayGetCount(array)) {
        for (uint64_t index = 0; index < BNArrayGetCount(array); index++) {
            BNArraySetObjectAtIndex(array, NULL, index);
        }
        BNArraySetCount(array, 0);
    }
}

#pragma mark -
#pragma mark Private Implementations

void BNArraySetCount(BNArray *array, uint64_t count) {
    assert(count < kBNMaxCount);
    
    if (NULL != array) {
        BNSetObjectVar(array, _count, count);

        if (0 == count && NULL != array->_data) {
            free (array->_data);
            array->_data = NULL;
            
            return;
        }
        if (0 == count) {
            array->_data = calloc(kBNExpand, sizeof(*array->_data));
        } else if (0 == (count % kBNExpand)) {
            uint64_t capacity = BNArrayGetCapacity(array, count);
            array->_data = realloc(array->_data, capacity);
            memset(array->_data + count, 0, kBNExpand * sizeof(*array->_data));
            assert(NULL != array->_data);
        }
    }
}

void **BNArrayGetDataField(BNArray *array) {
    return BNGetObjectVar(array, _data);
}

uint64_t BNArrayGetCountField(BNArray *array) {
    return BNGetPrimitiveVar(array, _count);
}

uint64_t BNArrayGetCapacity(BNArray *array, uint64_t count) {
    return (count + kBNExpand) * sizeof(*array->_data);
}
