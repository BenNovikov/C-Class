//
//  BNHumanArrayTest.c
//  Human
//
//  Created by BenNovikov on 31.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <stdio.h>
#include <assert.h>

#include "BNArray.h"
#include "BNMacros.h"
#include "BNArrayTest.h"

#pragma mark -
#pragma mark Private Declarations

static
void BNArraySingleObjectTestExecute(void);

static
void BNArrayMultipleObjectsTestExecute(void);

#pragma mark -
#pragma mark Public Implementations

void BNArrayTestRun(void){
    BNArraySingleObjectTestExecute();
    BNArrayMultipleObjectsTestExecute();
}

#pragma mark -
#pragma mark Private Implementations

void BNArraySingleObjectTestExecute(void){
    //  after array was created
    BNArray *array = BNArrayInit();
    
    //      array must not be NULL
    assert(NULL != array);
    
    //      array retain count must be equal 1
    assert(1 == BNObjectGetReferenceCount(array));
    
    //      array objects count muts be equal 0
    assert(0 == BNArrayGetCount(array));
    
    // after object was created
    BNObject *object = BNObjectCreateOfType(BNObject);
    
    //      object must not be NULL
    assert(NULL != object);
    
    //      object reference count must be equal to 1
    assert(1 == BNObjectGetReferenceCount(object));
    
    //      object index in array must be invalid (object not found)
    assert(0 == BNArrayGetIndexOfObject(array, object));
    
    // after object was added to array
    BNArrayAddObject(array, object);

    //      array count must be equal to 1
    assert(1 == BNArrayGetCount(array));
    
    //      array reference count must not change
    assert(1 == BNObjectGetReferenceCount(array));
    
    //      object index in array must be 0
    assert(0 == BNArrayGetIndexOfObject(array, object));
    
    //      object reference count must be incremented by 1
    assert(2 == BNObjectGetReferenceCount(object));
    
    //      array object at index 0 must be equal to added object
    assert(object == BNArrayGetObjectAtIndex(array, 0));
    
    //      array must contain an object
    assert(true == BNArrayContainsObject(array, object));
    
    // after object was removed from array
    BNArrayRemoveObjectAtIndex(array, 0);
    
    //      array count must be equal to 0
    assert(0 == BNArrayGetCount(array));
    
    //      array reference count must not change
    assert(1 == BNObjectGetReferenceCount(array));
    
    //      object index in array must be invalid (object not found)
    assert(0 == BNArrayGetIndexOfObject(array, object));
    
    //      object reference count must be decremented by 1
    assert(1 == BNObjectGetReferenceCount(object));
    
    //      array must not contain an object
    assert(false == BNArrayContainsObject(array, object));
    
    BNObjectRelease(object);
    BNObjectRelease(array);
}

void BNArrayMultipleObjectsTestExecute(void){
    
    const uint64_t kBNArrayTestSize = 20;

    //  after arrays were created
    BNArray *metaArray[3] = {BNArrayInit(), BNArrayInit(), BNArrayInit()};
    BNObject *staticArray[kBNArrayTestSize];
    
    for (uint64_t counter = 0; counter < 3; counter++) {
        //      arrays must not be NULL
        assert(NULL != metaArray[counter]);
        //      any array retain count must be equal 1
        assert(1 == BNObjectGetReferenceCount(metaArray[counter]));
    }
    
    //  create objects in the array on stack
    for (int64_t index = 0; index < kBNArrayTestSize; index++) {
        staticArray[index] = BNObjectCreateOfType(BNObject);
    }
  
    //      after objects were created add them to the first array
    for (int64_t index = 0; index < kBNArrayTestSize; index++) {
        BNArrayAddObject(metaArray[0], staticArray[index]);
    }
    
    //      check if the 5th object present in array
    assert(BNArrayGetObjectAtIndex(metaArray[0], 5) == staticArray[5]);
    
    //      check all the objects presence in array
    for (int64_t index = 0; index < kBNArrayTestSize; index++) {
        assert(BNArrayContainsObject(metaArray[0], staticArray[index]));
    }
    
    //      indicies of the objects must be the same as in staticArray
    for (int64_t index = 0; index < kBNArrayTestSize; index++) {
        assert(index == BNArrayGetIndexOfObject(metaArray[0], staticArray[index]));
    }
    
    //      set object 9 as object 2 in array
    BNArraySetObjectAtIndex(metaArray[0], BNArrayGetObjectAtIndex(metaArray[0], 9), 2);
    assert(2 == BNArrayGetIndexOfObject(metaArray[0], staticArray[9]));
    
    //      set NULL to object 2 in array
    BNArraySetObjectAtIndex(metaArray[0], NULL, 2);
    assert(NULL == BNArrayGetObjectAtIndex(metaArray[0], 2));

    
    //      remove 2nd object from array
    BNArrayRemoveObjectAtIndex(metaArray[0], 2);
    
    //      index of staticArray[9] in array must be 8
    assert(BNArrayGetObjectAtIndex(metaArray[0], 8) == staticArray[9]);

    //      send objects to the second array
    for (int64_t index = 0; index < kBNArrayTestSize; index++) {
        BNArrayAddObject(metaArray[1], staticArray[index]);
    }
    
    //      check all the objects be present in array
    for (int64_t index = 0; index < kBNArrayTestSize; index++) {
        assert(BNArrayContainsObject(metaArray[1], staticArray[index]));
    }
    
    //      copy objects from the 2nd array to the 3rd
    for (int64_t index = 0; index < kBNArrayTestSize; index++) {
        BNArrayAddObject(metaArray[2], BNArrayGetObjectAtIndex(metaArray[1], index));
    }
    
    // object 1 in 2nd array must be the same as object 1 in the 3rd
    assert(BNArrayGetObjectAtIndex(metaArray[1], 1) == BNArrayGetObjectAtIndex(metaArray[2], 1));
    
    // object 2 in 1st array must be the same as object 3 in the 3rd
    assert(BNArrayGetObjectAtIndex(metaArray[0], 2) == BNArrayGetObjectAtIndex(metaArray[2], 3));
    
    //      remove 20 objects from array
    for (int64_t index = 0; index < 20; index++) {
        BNArrayRemoveObjectAtIndex(metaArray[0], index);
    }
    
    for (uint64_t counter = 0; counter < 3; counter++) {
        //      empty arrays
        BNArrayRemoveAllObjects(metaArray[counter]);
        //      array counts must be equal to 0
        assert(0 == BNArrayGetCount(metaArray[counter]));
        // release arrays
        BNObjectRelease(metaArray[counter]);
    }
}
