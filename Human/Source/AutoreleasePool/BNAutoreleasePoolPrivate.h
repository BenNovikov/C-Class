//
//  BNAutoreleasePoolPrivate.h
//  Human
//
//  Created by BenNovikov on 07.07.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNAutoreleasePoolPrivate_h
#define Human_BNAutoreleasePoolPrivate_h

#include "BNLinkedList.h"
#include "BNAutoreleasePool.h"

extern
BNLinkedList *BNAutoreleasePoolGetList(BNAutoreleasePool *pool);

#endif
