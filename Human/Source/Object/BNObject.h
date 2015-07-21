//
//  BNObject.h
//  Humanity
//
//  Created by BenNovikov on 27.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNObject_h
#define Human_BNObject_h

typedef void (*BNObjectDeallocatorCallback)(void *);
typedef struct BNObject BNObject;

struct BNObject {
    uint64_t _referenceCount;
    BNObjectDeallocatorCallback _deallocator;
};

extern
void *__BNObjectCreate(size_t objectSize, BNObjectDeallocatorCallback deallocateCallback);

#define BNObjectCreateOfType(type) \
    __BNObjectCreate(sizeof(type), (BNObjectDeallocatorCallback)__##type##Deallocate)

extern
void *BNObjectRetain(void *object);

extern
void BNObjectRelease(void *object);

extern
uint64_t BNObjectGetReferenceCount(void *object);

extern
void __BNObjectDeallocate(void *object);

#endif
