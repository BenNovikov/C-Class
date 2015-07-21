//
//  BNLinkedListNode.h
//  Human
//
//  Created by BenNovikov on 06.06.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNLinkedListNode_h
#define Human_BNLinkedListNode_h

#include "BNObject.h"
#include "BNMacros.h"

typedef struct BNLinkedListNode BNLinkedListNode;

struct BNLinkedListNode {
    BNObject _super;
    
    BNLinkedListNode *_nextNode;    
    void * _object;
};

extern
void __BNLinkedListNodeDeallocate(void *object);

extern
BNLinkedListNode *BNLinkedListNodeCreateWithObject(void *object);

extern
BNLinkedListNode *BNLinkedListNodeGetNextNode(BNLinkedListNode *node);

extern
void BNLinkedListNodeSetNextNode(BNLinkedListNode *node, BNLinkedListNode *nextNode);

extern
BNObject *BNLinkedListNodeGetObject(BNLinkedListNode *node);

extern
void BNLinkedListNodeSetObject(BNLinkedListNode *node, void *object);

#endif
