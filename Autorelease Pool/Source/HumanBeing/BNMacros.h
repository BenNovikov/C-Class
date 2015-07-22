//
//  BNMacros.h
//  Human
//
//  Created by BenNovikov on 03.06.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNMacros_h
#define Human_BNMacros_h

#define BNObjectLaunchTest(test)\
    printf("Test %s started...\n", #test);\
    test;\
    printf("...Test %s finished\n", #test)

#define BNSetObjectVar(object, iVar, newVar) \
    if(NULL != object) { object->iVar = newVar;}

#define BNGetObjectVar(object, iVar) \
    (NULL != object) ? (typeof(object->iVar))(object->iVar) : NULL

#define BNGetPrimitiveVar(object, iVar) \
    (NULL != object) ? object->iVar : 0

#define BNRetainSetter(object, iVar, newVar) \
    if(NULL != object && object->iVar != newVar){ \
            BNObjectRetain(newVar); \
            BNObjectRelease(object->iVar); \
            object->iVar = newVar; \
    }

#endif
