//
//  BNLinkedList.c
//  Human
//
//  Created by BenNovikov on 06.06.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>

#include "BNLinkedList.h"
#include "BNLinkedListNode.h"
#include "BNLinkedListEnumerator.h"
#include "BNLinkedListEnumeratorPrivate.h"

#pragma mark -
#pragma mark Private Declaration

static
void *BNLinkedListGetHeadField(BNLinkedList *list);

static
void BNLinkedListSetHeadField(BNLinkedList *list, BNLinkedListNode *head);

static
uint64_t BNLinkedListGetCountField(BNLinkedList *list);

static
void BNLinkedListSetCountField(BNLinkedList *list, uint64_t count);

static
uint64_t BNLinkedListGetMutationsField(BNLinkedList *list);

static
void *BNLinkedListGetPreviousObjectNode(BNLinkedList *list, void *object);

static
void BNLinkedListMutate(BNLinkedList *list);

#pragma mark -
#pragma mark Public Implementations

BNLinkedList *BNLinkedListCreate(void) {
    BNLinkedList *list = BNObjectCreateOfType(BNLinkedList);
    BNLinkedListSetCountField(list, 0);
    
    return list;
}

void __BNLinkedListDeallocate(void *object) {
    BNLinkedListRemoveAllObjects(object);
    
    __BNObjectDeallocate(object);
}

BNLinkedListEnumerator *BNLinkedListCreateEnumeratorFromList(BNLinkedList *list) {
    return BNLinkedListEnumeratorCreateWithList(list);
}

BNObject *BNLinkedListGetFirstObject(BNLinkedList *list) {
    return BNLinkedListNodeGetObject(BNLinkedListGetHeadField(list));
}

void BNLinkedListRemoveFirstObject(BNLinkedList *list) {
    BNLinkedListNode *head = BNLinkedListGetHead(list);
    BNLinkedListNode *next = BNLinkedListNodeGetNextNode(head);
    BNObjectRelease(head);
    head = NULL;
    BNLinkedListSetHead(list, next);
    
    BNLinkedListSetCountField(list, BNLinkedListGetCountField(list) - 1);
}

BNObject *BNLinkedListGetObjectBeforeObject(BNLinkedList *list, void *object) {
    return (NULL == BNLinkedListNodeGetNextNode(BNLinkedListGetHead(list))) ? NULL :
        BNLinkedListNodeGetObject(BNLinkedListGetPreviousObjectNode(list, object));
}

BNObject *BNLinkedListGetObjectAfterObject(BNLinkedList *list, void *object) {
    if (NULL != list && NULL != object && false == BNLinkedListIsEmpty(list)) {
        BNLinkedListEnumerator *enumerator = BNLinkedListCreateEnumeratorFromList(list);
        BNObject *nextObject;
        do {
            nextObject = BNLinkedListEnumeratorGetNextObject(enumerator);
            if (object == nextObject) {
                BNObjectRelease(enumerator);
                return nextObject;
            }
        } while (NULL != nextObject);
        BNObjectRelease(enumerator);
    }
    return NULL;
}

bool BNLinkedListIsEmpty(BNLinkedList *list) {
    return NULL == (BNLinkedListGetHeadField(list));
}

void BNLinkedListAddObject(BNLinkedList *list, void *object) {
    BNLinkedListNode *node = BNLinkedListNodeCreateWithObject(object);
    BNLinkedListNodeSetNextNode(node, BNLinkedListGetHead(list));
    BNLinkedListSetHead(list, node);
    
    BNLinkedListSetCountField(list, BNLinkedListGetCountField(list) + 1);
}

void BNLinkedListRemoveObject(BNLinkedList *list, void *object) {
    BNLinkedListNode *previousNode = BNLinkedListGetPreviousObjectNode(list, object);
    BNLinkedListNode *objectNode = BNLinkedListNodeGetNextNode(previousNode);
    if (NULL != objectNode) {
        BNLinkedListNodeSetNextNode(previousNode, NULL);
        BNLinkedListNodeSetObject(objectNode, NULL);
        BNObjectRelease(objectNode);
        
        BNLinkedListSetCountField(list, BNLinkedListGetCountField(list) - 1);
        BNLinkedListMutate(list);
    }
}

void BNLinkedListRemoveAllObjects(BNLinkedList *list) {
    if (NULL != list && false == BNLinkedListIsEmpty(list)) {
        do {
            BNLinkedListRemoveFirstObject(list);
        } while (false == BNLinkedListIsEmpty(list));
    }
}

bool BNLinkedListContainsObject(BNLinkedList *list, void *object) {
    return (object == BNLinkedListNodeGetObject(BNLinkedListGetHead(list))
            || NULL != BNLinkedListNodeGetNextNode(BNLinkedListGetPreviousObjectNode(list, object)));
}

void BNLinkedListSetHead(BNLinkedList *list, BNLinkedListNode *head) {
    BNLinkedListSetHeadField(list, head);
    
    BNLinkedListMutate(list);
}

void *BNLinkedListGetHead(BNLinkedList *list) {
    return BNLinkedListGetHeadField(list);
}

uint64_t BNLinkedListGetCount(BNLinkedList *list) {
    return BNLinkedListGetCountField(list);
}

uint64_t BNLinkedListGetMutations(BNLinkedList *list) {
    return BNLinkedListGetMutationsField(list);
}

void *BNLinkedListGetContextWithObject(BNLinkedList *list, void *object) {
    
    return NULL;
}

#pragma mark -
#pragma mark Private Implementation

void *BNLinkedListGetHeadField(BNLinkedList *list) {
    return BNGetObjectVar(list, _head);
}

void BNLinkedListSetHeadField(BNLinkedList *list, BNLinkedListNode *head) {
    BNRetainSetter(list, _head, head);
}

uint64_t BNLinkedListGetCountField(BNLinkedList *list) {
    return BNGetPrimitiveVar(list, _count);
}

void BNLinkedListSetCountField(BNLinkedList *list, uint64_t count) {
    BNSetObjectVar(list, _count, count);
}

uint64_t BNLinkedListGetMutationsField(BNLinkedList *list) {
    return BNGetPrimitiveVar(list, _mutations);
}

void *BNLinkedListGetPreviousObjectNode(BNLinkedList *list, void *object) {
    if (NULL != list && NULL != object && false == BNLinkedListIsEmpty(list)) {
        BNLinkedListEnumerator *enumerator = BNLinkedListCreateEnumeratorFromList(list);
        BNObject *nextObject;
        BNLinkedListNode *objectNode = NULL;
        BNLinkedListNode *previousNode = NULL;
        do {
            previousNode = objectNode;
            objectNode = BNLinkedListEnumeratorGetNode(enumerator);
            nextObject = BNLinkedListEnumeratorGetNextObject(enumerator);
            if (object == nextObject) {
                BNObjectRelease(enumerator);
                return previousNode;
            }
        } while (NULL != nextObject);
        BNObjectRelease(enumerator);
    }
    return NULL;
}

void BNLinkedListMutate(BNLinkedList *list) {
    BNSetObjectVar(list, _mutations, BNLinkedListGetMutations(list) + 1);
}
