//
//  AutoreleaseStack.h
//  Human
//
//  Created by BenNovikov on 03.07.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_AutoreleaseStack_h
#define Human_AutoreleaseStack_h

#include <stdbool.h>

typedef struct BNAutoreleaseStack BNAutoreleaseStack;

typedef enum {
    BNAutoreleaseStackPoppedNULL,
    BNAutoreleaseStackPoppedObject,
}  BNAutoreleaseStackPopType;

extern
BNAutoreleaseStack *BNAutoreleaseStackCreateWithCapacity(uint64_t capacity);

extern
void __BNAutoreleaseStackDeallocate(void *stack);

extern
uint64_t BNAutoreleaseStackGetCount(BNAutoreleaseStack *stack);

extern
void BNAutoreleaseStackPush(void *stack, void *object);

extern
BNAutoreleaseStackPopType BNAutoreleaseStackPop(void *stack);

extern
BNAutoreleaseStackPopType BNAutoreleaseStackPopUntilEmpty(void *stack);

extern
bool BNAutoreleaseStackIsFull(void *stack);

extern
bool BNAutoreleaseStackIsEmpty(void *stack);

#endif
