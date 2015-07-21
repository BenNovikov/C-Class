//
//  BNAutoreleasePool.h
//  Human
//
//  Created by BenNovikov on 06.07.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNAutoreleasePool_h
#define Human_BNAutoreleasePool_h

typedef struct BNAutoreleasePool BNAutoreleasePool;

extern
const uint64_t kBNStackCapacity;

extern
BNAutoreleasePool *BNAutoreleasePoolCreate(BNAutoreleasePool *previousPool);

extern
void __BNAutoreleasePoolDeallocate(void *pool);

extern
void BNAutoreleasePoolAddObject(BNAutoreleasePool *pool, void *object);

extern
void BNAutoreleasePoolDrain(BNAutoreleasePool *pool);

#endif
