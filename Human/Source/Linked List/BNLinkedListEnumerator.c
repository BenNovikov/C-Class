//
//  BNLinkedListEnumerator.c
//  Human
//
//  Created by BenNovikov on 6/8/15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>

#include "BNLinkedListEnumeratorPrivate.h"
#include "BNLinkedListEnumerator.h"
#include "BNLinkedListNode.h"
#include "BNLinkedList.h"

#pragma mark -
#pragma mark Private Declarations
static
BNLinkedList *BNLinkedListEnumeratorGetList(BNLinkedListEnumerator *enumerator);

static
void BNLinkedListEnumeratorSetList(BNLinkedListEnumerator *enumerator, BNLinkedList *list);

static
void BNLinkedListEnumeratorSetNode(BNLinkedListEnumerator *enumerator, BNLinkedListNode *node);

static
uint64_t BNLinkedListEnumeratorGetMutations(BNLinkedListEnumerator *enumerator);

static
void BNLinkedListEnumeratorMutate(BNLinkedListEnumerator *enumerator, uint64_t mutations);

static
bool BNLinkedListEnumeratorIsItValid(BNLinkedListEnumerator *enumerator);

static
void BNLinkedListEnumeratorSetValid(BNLinkedListEnumerator *enumerator, bool valid);

#pragma mark -
#pragma mark Public Implementations

void __BNLinkedListEnumeratorDeallocate(void *object) {
    BNLinkedListEnumeratorSetList(object, NULL);
    BNLinkedListEnumeratorSetNode(object, NULL);

    __BNObjectDeallocate(object);
}

BNLinkedListEnumerator *BNLinkedListEnumeratorCreateWithList(BNLinkedList *list) {
    if (NULL != list && false == BNLinkedListIsEmpty(list)) {
        BNLinkedListEnumerator *enumerator = BNObjectCreateOfType(BNLinkedListEnumerator);
        BNLinkedListEnumeratorSetList(enumerator, list);
        BNLinkedListEnumeratorSetNode(enumerator, BNLinkedListGetHead(list));
        BNLinkedListEnumeratorMutate(enumerator, BNLinkedListGetMutations(list));
        BNLinkedListEnumeratorSetValid(enumerator, true);
        return enumerator;
    } else {
        return NULL;
    }
}

void *BNLinkedListEnumeratorGetNextObject(BNLinkedListEnumerator *enumerator) {
    if (NULL != enumerator
        && false == BNLinkedListIsEmpty(BNLinkedListEnumeratorGetList(enumerator))
        && true == BNLinkedListEnumeratorIsItValid(enumerator)
        && BNLinkedListGetMutations(BNLinkedListEnumeratorGetList(enumerator)) == BNLinkedListEnumeratorGetMutations(enumerator))
    {
        BNLinkedListNode *currentNext = BNLinkedListEnumeratorGetNode(enumerator);
        BNLinkedListNode *result = currentNext;
        if (NULL != currentNext) {
            currentNext = BNLinkedListNodeGetNextNode(currentNext);
            BNLinkedListEnumeratorSetValid(enumerator, true);
            BNLinkedListEnumeratorSetNode(enumerator, currentNext);            
        }
        return BNLinkedListNodeGetObject(result);
    }
    BNLinkedListEnumeratorSetValid(enumerator, false);
    return NULL;
}

bool BNLinkedListEnumeratorIsValid(BNLinkedListEnumerator *enumerator) {
    return BNGetPrimitiveVar(enumerator, _valid);
}

#pragma mark -
#pragma mark Private Implementations

BNLinkedList *BNLinkedListEnumeratorGetList(BNLinkedListEnumerator *enumerator) {
    return BNGetObjectVar(enumerator, _list);
}

void BNLinkedListEnumeratorSetList(BNLinkedListEnumerator *enumerator, BNLinkedList *list) {
    BNRetainSetter(enumerator, _list, list);
}

BNLinkedListNode *BNLinkedListEnumeratorGetNode(BNLinkedListEnumerator *enumerator) {
    return BNGetObjectVar(enumerator, _node);
}

void BNLinkedListEnumeratorSetNode(BNLinkedListEnumerator *enumerator, BNLinkedListNode *node) {
    BNRetainSetter(enumerator, _node, node);
}

uint64_t BNLinkedListEnumeratorGetMutations(BNLinkedListEnumerator *enumerator) {
    return BNGetPrimitiveVar(enumerator, _mutations);
}

void BNLinkedListEnumeratorMutate(BNLinkedListEnumerator *enumerator, uint64_t mutations) {
    BNSetObjectVar(enumerator, _mutations, mutations);
}

bool BNLinkedListEnumeratorIsItValid(BNLinkedListEnumerator *enumerator) {
    return BNGetPrimitiveVar(enumerator, _valid);
}

void BNLinkedListEnumeratorSetValid(BNLinkedListEnumerator *enumerator, bool valid) {
    BNSetObjectVar(enumerator, _valid, valid);
}
