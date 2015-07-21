//
//  BNHumanArray.h
//  Human
//
//  Created by BenNovikov on 31.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_Array_h
#define Human_Array_h
#include <stdbool.h>

#include "BNObject.h"

//returned if object or index not found
extern
const uint64_t kBNNotFound;

typedef struct BNArray BNArray;

extern
void __BNArrayDeallocate(void *object);

extern
void *BNArrayInit();

extern
uint64_t BNArrayGetCount(void *array);

extern
uint64_t BNArrayGetIndexOfObject(void *array, void *object);

extern
bool BNArrayContainsObject(void *array, void *object);

extern
void BNArrayAddObject(void *array, void *object);

extern
void *BNArrayGetObjectAtIndex(void *array, uint64_t index);

extern
void BNArraySetObjectAtIndex(void *array, void *object, uint64_t index);

extern
void BNArrayRemoveObjectAtIndex(void *array, uint64_t index);

extern
void BNArrayRemoveAllObjects(void *array);

#endif
