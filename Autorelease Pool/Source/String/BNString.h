//
//  BNString.h
//  Human
//
//  Created by BenNovikov on 6/10/15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNString_h
#define Human_BNString_h

#include "BNObject.h"

typedef struct BNString BNString;

struct BNString {
    BNObject _super;
    char *_data;
};

extern
void __BNStringDeallocate(void *object);

extern
BNString *BNStringCreateWithData(const char *data);

extern
void BNStringSetData(BNString *object, const char *data);

extern
char *BNStringGetData(BNString *object);

#endif
