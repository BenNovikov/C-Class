//
//  BNHumanBeingTest.c
//  Human
//
//  Created by BenNovikov on 31.05.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "BNHumanBeing.h"
#include "BNMacros.h"
#include "BNHumanBeingTest.h"

#pragma mark -
#pragma mark Private Declarations

static
void BNHumanBeingTestsExecute(void);

#pragma mark -
#pragma mark Public Implementations

void BNHumanBeingTestRun(void){
    BNHumanBeingTestsExecute();
}

#pragma mark -
#pragma mark Private Implementations

void BNHumanBeingTestsExecute(void){
    
    //with human objects created
    //  humanMother must exist
    BNHumanBeing *humanMother = BNHumanBeingCreate();
    assert(NULL != humanMother);
    
    //  humanFather must exist
    BNHumanBeing *humanFather = BNHumanBeingCreate();
    assert(NULL != humanFather);
    
    //  set names
    BNHumanSetName(humanMother, "Eve");
    BNHumanSetName(humanMother, NULL);
    BNHumanSetName(humanFather, "Adam");
    
    //  get names, must be (null), Adam
    printf("NULL and a name returned: %s, %s\n", BNHumanGetName(humanMother), BNHumanGetName(humanFather));
    
    //  set mother's name back
    BNHumanSetName(humanMother, "Eve");
    printf("Two names returned: %s, %s\n", BNHumanGetName(humanMother), BNHumanGetName(humanFather));
    
    //  set gender
    BNHumanSetGender(humanMother, BNHumanGenderFemale);
    assert(BNHumanGenderFemale == BNHumanGetGender(humanMother));
    BNHumanSetGender(humanFather, BNHumanGenderMale);
    assert(BNHumanGenderMale == BNHumanGetGender(humanFather));
    
    //  create a new human with parents
    BNHumanBeing *firstChild = BNHumanBeingCreateWithParents(humanMother, humanFather);
    BNHumanSetName(firstChild, "Cain");
    printf("1st child is Cain: %s    ", BNHumanGetName(firstChild));
   
    //  create another human with parents
    BNHumanBeing *secondChild = BNHumanBeingCreateWithParents(humanMother, humanFather);
    BNHumanSetName(secondChild, "Abel");
    printf("2nd child is Abel: %s\n", BNHumanGetName(secondChild));
    
    //  parents must have 2 children after second one was born
    assert(2 == BNHumanGetChildrenCount(humanMother));
    assert(2 == BNHumanGetChildrenCount(humanFather));
    
    //  delete parents from second child
    BNHumanDeleteChildWithIndex(humanMother, BNHumanGetIndexOfChild(humanMother, secondChild));
    BNHumanDeleteChildWithIndex(humanFather, BNHumanGetIndexOfChild(humanFather, secondChild));
    assert(1 == BNObjectGetReferenceCount(secondChild));
    
    // let him die
    BNObjectRelease(secondChild);
    assert(0 == BNObjectGetReferenceCount(secondChild));
    
    //  parents must have only 1 child after death of second one
    assert(1 == BNHumanGetChildrenCount(humanMother));
    assert(1 == BNHumanGetChildrenCount(humanFather));
    
    //  index == 0 will be returned if there is no such a child in the list of children
    assert(0 == BNHumanGetIndexOfChild(humanMother, secondChild));
    assert(0 == BNHumanGetIndexOfChild(humanFather, secondChild));
    
    //  index == 0 will be returned for the first child
    uint64_t index = BNHumanGetIndexOfChild(humanMother, firstChild);
    assert(0 == index && BNHumanGetChildWithIndex(humanMother, index));
    index = BNHumanGetIndexOfChild(humanFather, firstChild);
    assert(0 == index && BNHumanGetChildWithIndex(humanFather, index));
    
    //  for nonexistent person BNHumanGetIndexOfChild returns 0 by convention,
    //      so the following constuction returns the name of the first child:
    char *name = BNHumanGetName(BNHumanGetChildWithIndex(humanMother, BNHumanGetIndexOfChild(humanMother,secondChild)));
    printf(" (!) Check if the child is present in parent's list to avoid geting name of the first child when asking for any nonexistent object. First child's name returned instead of deleted Abel: %s\n", name);
    
    //The number of Adam's children, as says the old tradition, was 33 sons and 23 daughters
    //  test multiple children with array implied
    BNHumanBeing *juniorChildren[56];
    for (uint64_t index = 0; index < 56; index++) {
        juniorChildren[index] = BNHumanBeingCreateWithParents(humanMother, humanFather);
    }
    
    //  parents will have 57 children each
    assert(57 == BNHumanGetChildrenCount(humanMother));
    assert(57 == BNHumanGetChildrenCount(humanFather));
    
    //  marry parents
    BNHumanMarryPartners(humanFather, humanMother);
    assert(humanFather == BNHumanGetPartner(humanMother));
    assert(humanMother == BNHumanGetPartner(humanFather));
    
    //  divorce parents
    BNHumanDivorcePartners(humanFather);
    assert(NULL == BNHumanGetPartner(humanMother));
    assert(NULL == BNHumanGetPartner(humanFather));
    
    //  release parents to free memory
    BNObjectRelease(firstChild);
    for (uint64_t index = 0; index < 56; index++) {
        BNObjectRelease(juniorChildren[index]);
    }
    BNObjectRelease(humanMother);
    BNObjectRelease(humanFather);
}
