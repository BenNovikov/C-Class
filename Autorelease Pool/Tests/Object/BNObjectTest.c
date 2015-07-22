//
//  BNObjectTest.c
//  Humanity
//
//  Created by BenNovikov on 27.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "BNObject.h"
#include "BNMacros.h"
#include "BNObjectTest.h"

#pragma mark -
#pragma mark Public Implementation

void BNObjectTestRun(void){
    //create an object
    BNObject *object = BNObjectCreateOfType(BNObject);
    assert(NULL != object);
    
    //get the reference count, it must be equal to 1
    assert(1 == BNObjectGetReferenceCount((void *)object));
    
    //retain the object
    BNObject *objectMirror = BNObjectCreateOfType(BNObject);
    objectMirror = BNObjectRetain((void *)object);
    assert(NULL != objectMirror);
    
    //get the reference count, it must equal to 2
    assert(2 == BNObjectGetReferenceCount((void *)objectMirror));
    
    //release the object mirror
    BNObjectRelease(objectMirror);
    
    //release the first one
    BNObjectRelease(object);   
}

