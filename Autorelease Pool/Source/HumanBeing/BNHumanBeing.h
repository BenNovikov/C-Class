//
//  BNHumanBeing.h
//  Human
//
//  Created by BenNovikov on 30.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#ifndef Human_BNHumanBeing_h
#define Human_BNHumanBeing_h

#include <stdbool.h>

#include "BNObject.h"
#include "BNString.h"
#include "BNArray.h"

typedef enum {
    BNHumanGenderUndefined,
    BNHumanGenderMale,
    BNHumanGenderFemale
} BNHumanGender;


typedef struct BNHumanBeing BNHumanBeing;

struct BNHumanBeing {
    BNObject _super;
    
    BNArray *_children;
    BNString *_name;
    BNHumanBeing *_father;
    BNHumanBeing *_mother;
    BNHumanBeing *_partner;
    BNHumanGender _gender;
    uint64_t _age;
    bool _headOfFamily;
};

extern
BNHumanBeing *BNHumanBeingCreate(void);

extern
BNHumanBeing *BNHumanBeingCreateWithParents(BNHumanBeing *humanMother, BNHumanBeing *humanFather);

extern
void __BNHumanBeingDeallocate(void *object);

extern
char *BNHumanGetName(BNHumanBeing *humanPerson);

extern
void BNHumanSetName(BNHumanBeing *humanPerson, const char *data);

extern
BNHumanGender BNHumanGetGender(BNHumanBeing *humanPerson);

extern
void BNHumanSetGender(BNHumanBeing *humanPerson, BNHumanGender gender);

extern
uint64_t BNHumanGetAge(BNHumanBeing *humanPerson);

extern
void BNHumanSetAge(BNHumanBeing *humanPerson, uint64_t age);

extern
BNHumanBeing *BNHumanGetMother(BNHumanBeing *humanPerson);

extern
BNHumanBeing *BNHumanGetFather(BNHumanBeing *humanPerson);

extern
uint16_t BNHumanGetChildrenCount(BNHumanBeing *humanPerson);

extern
uint64_t BNHumanGetIndexOfChild(BNHumanBeing *humanPerson, BNHumanBeing *humanChild);

extern
void BNHumanAddChild(BNHumanBeing *humanPerson, BNHumanBeing *humanChild);

extern
BNHumanBeing *BNHumanGetChildWithIndex(BNHumanBeing *humanPerson, uint64_t index);

extern
void BNHumanAddChildWithIndex(BNHumanBeing *humanPerson, BNHumanBeing *humanChild, uint16_t index);

extern
void BNHumanDeleteChildWithIndex(BNHumanBeing *humanPerson, uint16_t index);

extern
BNHumanBeing *BNHumanGetPartner(BNHumanBeing *humanPerson);

bool BNHumanMarryPartners(BNHumanBeing *humanPerson, BNHumanBeing *humanPartner);

bool BNHumanDivorcePartners(BNHumanBeing *humanPerson);

#endif
