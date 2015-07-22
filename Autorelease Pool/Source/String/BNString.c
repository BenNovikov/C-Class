//
//  BNString.c
//  Human
//
//  Created by BenNovikov on 6/10/15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "BNString.h"
#include "BNMacros.h"

#pragma mark -
#pragma mark Private Declarations

static
void BNStringSetDataField(BNString *object, const char *data);

static
char *BNStringGetDataField(BNString *object);

#pragma mark -
#pragma mark Public Implementations

void __BNStringDeallocate(void *object) {
    BNStringSetData(object, NULL);
    
    __BNObjectDeallocate(object);
}

BNString *BNStringCreateWithData(const char *data) {
    BNString *object = BNObjectCreateOfType(BNString);
    BNStringSetData(object, data);
    return object;
}

void BNStringSetData(BNString *object, const char *data) {
    BNStringSetDataField(object, data);
}

char *BNStringGetData(BNString *object) {
    return BNStringGetDataField(object);
}

#pragma mark -
#pragma mark Private Implementations

void BNStringSetDataField(BNString *object, const char *data) {
    if (NULL != object ) {
        size_t tempSize = 0;
        
        if (NULL != data) {
            tempSize = (strlen(data) + 1) * sizeof(char);
            object->_data = realloc (object->_data, tempSize);
            assert(NULL != object->_data);
            memmove ( object->_data, data, tempSize );
        } else {
            
            free(object->_data);
            object->_data = NULL;
        }
    }
}

char *BNStringGetDataField(BNString *object) {
    return BNGetObjectVar(object, _data);
}
