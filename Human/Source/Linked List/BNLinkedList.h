//
//  BNLinkedList.h
//  Human
//
//  Created by BenNovikov on 06.06.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNLinkedList_h
#define Human_BNLinkedList_h

#include <stdbool.h>

#include "BNObject.h"

typedef struct BNLinkedListNode BNLinkedListNode;
typedef struct BNLinkedListEnumerator   BNLinkedListEnumerator;

typedef struct BNLinkedList BNLinkedList;

struct BNLinkedList {
    BNObject _super;
    
    BNLinkedListNode *_head;    
    uint64_t _count;
    uint64_t _mutations;
};

extern
BNLinkedList *BNLinkedListCreate(void);

extern
void __BNLinkedListDeallocate(void *object);

extern
BNLinkedListEnumerator *BNLinkedListEnumeratorFromList(BNLinkedList *list);

extern
BNObject *BNLinkedListGetFirstObject(BNLinkedList *list);

extern
void BNLinkedListRemoveFirstObject(BNLinkedList *list);

extern
BNObject *BNLinkedListGetObjectBeforeObject(BNLinkedList *list, void *object);

extern
BNObject *BNLinkedListGetObjectAfterObject(BNLinkedList *list, void *object);

extern
bool BNLinkedListIsEmpty(BNLinkedList *list);

extern
void BNLinkedListAddObject(BNLinkedList *list, void *object);

extern
void BNLinkedListRemoveObject(BNLinkedList *list, void *object);

extern
void BNLinkedListRemoveAllObjects(BNLinkedList *list);

extern
bool BNLinkedListContainsObject(BNLinkedList *list, void *object);

extern
void BNLinkedListSetHead(BNLinkedList *list, BNLinkedListNode *head);

extern
void *BNLinkedListGetHead(BNLinkedList *list);

extern
uint64_t BNLinkedListGetCount(BNLinkedList *list);

extern
uint64_t BNLinkedListGetMutations(BNLinkedList *list);

extern
void *BNLinkedListGetContextWithObject(BNLinkedList *list, void *object);

#endif
