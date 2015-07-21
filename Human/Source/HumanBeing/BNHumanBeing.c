//
//  BNHumanBeing.c
//  Human
//
//  Created by BenNovikov on 30.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "BNHumanBeing.h"
#include "BNMacros.h"

#pragma mark -
#pragma mark Private Declarations
static
void BNHumanBeingInitChildrenArray(BNHumanBeing *humanPerson);

static
void BNHumanSetHeadOfFamily(BNHumanBeing *humanPerson, bool value);

static
bool BNHumanIsHeadOfFamily(BNHumanBeing *humanPerson);

static
BNHumanBeing *BNHumanGetPartnerField(BNHumanBeing *humanPerson);

static
void BNHumanSetPartner(BNHumanBeing *humanPerson, BNHumanBeing *humanPartner);

static
void BNHumanSetFather(BNHumanBeing *humanChild, BNHumanBeing *humanPerson);

static
void BNHumanSetMother(BNHumanBeing *humanChild, BNHumanBeing *humanPerson);

static
BNHumanBeing *BNHumanGetMotherField(BNHumanBeing *humanPerson);

static
BNHumanBeing *BNHumanGetFatherField(BNHumanBeing *humanPerson);

static
uint16_t BNHumanGetChildrenCountField(BNHumanBeing *humanPerson);

static
char *BNHumanGetNameField(BNHumanBeing *humanPerson);

static
void BNHumanSetNameField(BNHumanBeing *humanPerson, const char *data);

static
BNHumanGender BNHumanGetGenderField(BNHumanBeing *humanPerson);

static
void BNHumanSetGenderField(BNHumanBeing *humanPerson, BNHumanGender gender);

static
uint64_t BNHumanGetAgeField(BNHumanBeing *humanPerson);

static
void BNHumanSetAgeField(BNHumanBeing *humanPerson, uint64_t age);

static
BNHumanBeing *BNHumanGetChildAtIndex(BNHumanBeing *humanPerson, uint64_t index);

static
void BNHumanRemoveChildAtIndex(BNHumanBeing *humanPerson, uint64_t index);

static
void BNHumanAddChildToArray(BNHumanBeing *humanPerson, BNHumanBeing *humanChild);

static
void BNHumanBeingReleaseChildrenArray(BNHumanBeing *humanPerson);

#pragma mark -
#pragma mark Public Implementations

void __BNHumanBeingDeallocate(void *humanPerson) {
    BNHumanDivorcePartners(humanPerson);
    BNHumanSetName(humanPerson, NULL);
    BNHumanBeingReleaseChildrenArray(humanPerson);
    
    __BNObjectDeallocate(humanPerson);
}

BNHumanBeing *BNHumanBeingCreate(void) {
    BNHumanBeing *humanPerson = BNObjectCreateOfType(BNHumanBeing);
    BNHumanBeingInitChildrenArray(humanPerson);
    
    return humanPerson;
}

BNHumanBeing *BNHumanBeingCreateWithParents(BNHumanBeing *humanMother, BNHumanBeing *humanFather) {
    BNHumanBeing *humanChild = BNHumanBeingCreate();
    BNHumanAddChild(humanMother, humanChild);
    BNHumanAddChild(humanFather, humanChild);
    
    return humanChild;
}

#pragma mark -
#pragma mark Public Accesors

char *BNHumanGetName(BNHumanBeing *humanPerson) {
    return BNHumanGetNameField(humanPerson);
}

void BNHumanSetName(BNHumanBeing *humanPerson, const char *name) {
    BNHumanSetNameField(humanPerson, name);
}

BNHumanGender BNHumanGetGender(BNHumanBeing *humanPerson) {
    return BNHumanGetGenderField(humanPerson);
}

void BNHumanSetGender(BNHumanBeing *humanPerson, BNHumanGender gender) {
    BNHumanSetGenderField(humanPerson, gender);
}

uint64_t BNHumanGetAge(BNHumanBeing *humanPerson) {
    return BNHumanGetAgeField(humanPerson);
}

void BNHumanSetAge(BNHumanBeing *humanPerson, uint64_t age) {
    BNHumanSetAgeField(humanPerson, age);
}

BNHumanBeing *BNHumanGetMother(BNHumanBeing *humanPerson) {
    return BNHumanGetMotherField(humanPerson);
}

BNHumanBeing *BNHumanGetFather(BNHumanBeing *humanPerson) {
    return BNHumanGetFatherField(humanPerson);
}

uint16_t BNHumanGetChildrenCount(BNHumanBeing *humanPerson) {
    return BNHumanGetChildrenCountField(humanPerson);
}

uint64_t BNHumanGetIndexOfChild(BNHumanBeing *humanPerson, BNHumanBeing *humanChild) {
    uint64_t index = 0;
    if (NULL != humanChild && NULL != humanPerson ) {
        do {
            if (humanChild == BNHumanGetChildWithIndex(humanPerson, index)) {
                
                return index;
            }
            index++;
        } while (index < BNHumanGetChildrenCount(humanPerson));
    }

    return 0;
}

void BNHumanAddChild(BNHumanBeing *humanPerson, BNHumanBeing *humanChild) {
    if (NULL != humanPerson && NULL != humanChild) {
<<<<<<< HEAD
        BNHumanAddChildToArray(humanPerson, humanChild);
        
=======
        BNArrayAddObject(humanPerson->_array, humanChild);
>>>>>>> ed570a4c47ac9151021269eab425aa3ba9d69b7b
        if (BNHumanGetGender(humanPerson) == BNHumanGenderMale) {
            BNHumanSetFather(humanChild, humanPerson);
        } else if (BNHumanGetGender(humanPerson) == BNHumanGenderFemale){
            BNHumanSetMother(humanChild, humanPerson);
        }
    }
}

BNHumanBeing *BNHumanGetChildWithIndex(BNHumanBeing *humanPerson, uint64_t index) {
    if (NULL != humanPerson && (0 == index || index < BNHumanGetChildrenCount(humanPerson))) {
        
        return BNHumanGetChildAtIndex(humanPerson, index);
    }
    
    return NULL;
}

<<<<<<< HEAD
void BNHumanDeleteChildWithIndex(BNHumanBeing *humanPerson, uint16_t index) {
    if (NULL != humanPerson && index < BNHumanGetChildrenCount(humanPerson)) {
        BNHumanBeing *humanChild = BNHumanGetChildAtIndex(humanPerson, index);
    
        if (NULL != humanChild) {
            BNHumanRemoveChildAtIndex(humanPerson, index);
            
            if (BNHumanGetGender(humanPerson) == BNHumanGenderMale) {
                BNHumanSetFather(humanChild, NULL);
            } else if (BNHumanGetGender(humanPerson) == BNHumanGenderFemale) {
                BNHumanSetMother(humanChild, NULL);
            }
=======
void BNHumanDeleteChildWithIndex(BNHumanBeing *humanPerson, uint16_t index){
    BNHumanBeing *humanChild = BNArrayGetObjectAtIndex(humanPerson->_array, index);
    if (NULL != humanPerson && NULL != humanChild && index < BNHumanGetChildrenCount(humanPerson)) {
        BNArrayRemoveObjectAtIndex(humanPerson->_array, index);
        if (BNHumanGetGender(humanPerson) == BNHumanGenderMale) {
            humanChild->_father = NULL;
        } else if (BNHumanGetGender(humanPerson) == BNHumanGenderFemale){
            humanChild->_mother = NULL;
>>>>>>> ed570a4c47ac9151021269eab425aa3ba9d69b7b
        }
    }
}

BNHumanBeing *BNHumanGetPartner(BNHumanBeing *humanPerson) {
    return BNHumanGetPartnerField(humanPerson) ;
}

bool BNHumanMarryPartners(BNHumanBeing *humanPerson, BNHumanBeing *humanPartner) {
    bool result = false;
    if (NULL != humanPerson
        && NULL != humanPartner
        && NULL == BNHumanGetPartner(humanPerson)
        && NULL == BNHumanGetPartner(humanPartner)
        && humanPerson != humanPartner)
    {
            BNHumanSetHeadOfFamily(humanPerson, true);
            BNHumanSetHeadOfFamily(humanPartner, false);
            BNObjectRetain(humanPartner);
            BNHumanSetPartner(humanPerson, humanPartner);
            BNHumanSetPartner(humanPartner, humanPerson);
            result = true;
    }
    
    return result;
}

bool BNHumanDivorcePartners(BNHumanBeing *humanPerson) {
    BNHumanBeing *humanPartner = BNHumanGetPartner(humanPerson);
    bool result = false;
    if (NULL != humanPerson
        && NULL != humanPartner
        && NULL != BNHumanGetPartner(humanPerson)
        && NULL != BNHumanGetPartner(humanPartner)
        && humanPerson != humanPartner)
    {
        if (!BNHumanIsHeadOfFamily(humanPerson)) {
            BNHumanBeing *temp = humanPerson;
            humanPerson = humanPartner;
            humanPartner = temp;
        }
            BNHumanSetHeadOfFamily(humanPerson, false);
            BNHumanSetHeadOfFamily(humanPartner, false);
            BNHumanSetPartner(humanPerson, NULL);
            BNHumanSetPartner(humanPartner, NULL);
            BNObjectRelease(humanPartner);
            result = true;
    }
    
    return result;
}

#pragma mark -
#pragma mark Private Implementations

void BNHumanBeingInitChildrenArray(BNHumanBeing *humanPerson) {
    BNSetObjectVar(humanPerson, _children, BNArrayInit());
}

void BNHumanSetHeadOfFamily(BNHumanBeing *humanPerson, bool value) {
    BNSetObjectVar(humanPerson, _headOfFamily, value);
}

bool BNHumanIsHeadOfFamily(BNHumanBeing *humanPerson) {
    return BNGetObjectVar(humanPerson, _headOfFamily) ? true : false;
}

BNHumanBeing *BNHumanGetPartnerField(BNHumanBeing *humanPerson) {
    return BNGetObjectVar(humanPerson, _partner);
}

void BNHumanSetPartner(BNHumanBeing *humanPerson, BNHumanBeing *humanPartner) {
    BNSetObjectVar(humanPerson, _partner, humanPartner);
}

void BNHumanSetFather(BNHumanBeing *humanChild, BNHumanBeing *humanPerson) {
    BNSetObjectVar(humanChild, _father, humanPerson);
}

void BNHumanSetMother(BNHumanBeing *humanChild, BNHumanBeing *humanPerson) {
    BNSetObjectVar(humanChild, _father, humanPerson);
}

BNHumanBeing *BNHumanGetMotherField(BNHumanBeing *humanPerson) {
    return BNGetObjectVar(humanPerson, _mother);
}

BNHumanBeing *BNHumanGetFatherField(BNHumanBeing *humanPerson) {
    return BNGetObjectVar(humanPerson, _father);
}

uint16_t BNHumanGetChildrenCountField(BNHumanBeing *humanPerson) {
    return BNArrayGetCount(BNGetPrimitiveVar(humanPerson, _children));
}

char *BNHumanGetNameField(BNHumanBeing *humanPerson) {
    return BNStringGetData(BNGetObjectVar(humanPerson, _name));
}

void BNHumanSetNameField(BNHumanBeing *humanPerson, const char *name){
    BNRetainSetter(humanPerson, _name, (NULL == name ? NULL : BNStringCreateWithData(name)));
}

BNHumanGender BNHumanGetGenderField(BNHumanBeing *humanPerson) {
    return BNGetPrimitiveVar(humanPerson, _gender);
}

void BNHumanSetGenderField(BNHumanBeing *humanPerson, BNHumanGender gender) {
    BNSetObjectVar(humanPerson, _gender, gender);
}

uint64_t BNHumanGetAgeField(BNHumanBeing *humanPerson) {
    return BNGetPrimitiveVar(humanPerson, _age);
}

void BNHumanSetAgeField(BNHumanBeing *humanPerson, uint64_t age) {
    BNSetObjectVar(humanPerson, _age, age);
}

BNHumanBeing *BNHumanGetChildAtIndex(BNHumanBeing *humanPerson, uint64_t index) {
    return BNArrayGetObjectAtIndex(humanPerson->_children, index);
}

void BNHumanRemoveChildAtIndex(BNHumanBeing *humanPerson, uint64_t index) {
    BNArrayRemoveObjectAtIndex(humanPerson->_children, index);
}

void BNHumanAddChildToArray(BNHumanBeing *humanPerson, BNHumanBeing *humanChild) {
    BNArrayAddObject(humanPerson->_children, humanChild);
}

void BNHumanBeingReleaseChildrenArray(BNHumanBeing *humanPerson) {
    
    for (int16_t index = 0; index < BNHumanGetChildrenCount(humanPerson); index++) {
        BNHumanDeleteChildWithIndex(humanPerson, index);
    }
    humanPerson->_children = NULL;
    BNObjectRelease(humanPerson->_children);
}
