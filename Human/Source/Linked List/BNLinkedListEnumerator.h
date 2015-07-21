//
//  BNLinkedListEnumerator.h
//  Human
//
//  Created by BenNovikov on 06.06.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNLinkedListEnumerator_h
#define Human_BNLinkedListEnumerator_h

#include <stdbool.h>

#include "BNObject.h"

typedef struct BNLinkedListEnumerator BNLinkedListEnumerator;
typedef struct BNLinkedListNode BNLinkedListNode;
typedef struct BNLinkedList BNLinkedList;

struct BNLinkedListEnumerator{
    BNObject _super;
    
    BNLinkedList *_list;
    BNLinkedListNode *_node;
    uint64_t _mutations;    
    bool _valid;
};

extern
void __BNLinkedListEnumeratorDeallocate(void *object);

extern
BNLinkedListEnumerator *BNLinkedListEnumeratorCreateWithList(BNLinkedList *list);

extern
void *BNLinkedListEnumeratorGetNextObject(BNLinkedListEnumerator *enumerator);

extern
bool BNLinkedListEnumeratorIsValid(BNLinkedListEnumerator *enumerator);


#endif
