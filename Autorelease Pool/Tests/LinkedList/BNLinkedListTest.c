//
//  BNLinkedListTest.c
//  Human
//
//  Created by BenNovikov on 19.06.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//
#include <stdio.h>
#include <assert.h>

#include "BNString.h"
#include "BNLinkedList.h"
#include "BNLinkedListNode.h"
#include "BNLinkedListEnumerator.h"
#include "BNLinkedListTest.h"

#pragma mark -
#pragma mark Private Declaration
void BNLinkedListNodeTest(void);

void BNLinkedListTest(void);

#pragma mark -
#pragma mark Public Implementation
void BNLinkedListTestRun(void){
    BNLinkedListNodeTest();
    BNLinkedListTest();
}

#pragma mark -
#pragma mark Private Implementation
void BNLinkedListNodeTest(void){
    //after an object was created
    BNObject *object = BNObjectCreateOfType(BNObject);
    
    //    create a node with object
    BNLinkedListNode *node = BNLinkedListNodeCreateWithObject(object);
    
    //    create nextNode with the same object
    BNLinkedListNode *nextNode = BNLinkedListNodeCreateWithObject(object);
    
    //    set nextNode next to the node
    BNLinkedListNodeSetNextNode(node, nextNode);
    
    //    get next node to the node, it must be nextNode
    assert(BNLinkedListNodeGetNextNode(node) == nextNode);    
  
    //    get the object from the node and from nextNode, it must be the same object
    assert(BNLinkedListNodeGetObject(node) == BNLinkedListNodeGetObject(nextNode));
    
    //    after newObject was created
    BNObject *newObject = BNObjectCreateOfType(BNObject);
    
    //        set newObject to nextNode
    BNLinkedListNodeSetObject(nextNode, newObject);
    
    //        get the object from the node and from nextNode, it must be different objects there
    assert(BNLinkedListNodeGetObject(node) != BNLinkedListNodeGetObject(nextNode));    

    BNObjectRelease(newObject);
    BNObjectRelease(nextNode);
    BNObjectRelease(node);
    BNObjectRelease(object);
}

void BNLinkedListTest(void) {
    //after list was created
    BNLinkedList *list = BNLinkedListCreate();
    
    //  it should be empty
    assert(true == BNLinkedListIsEmpty(list));
    
    //  try to delete all objects from empty list
    BNLinkedListRemoveAllObjects(list);
    
    //  create an object
    BNObject *singleObject = BNObjectCreateOfType(BNObject);
    
    //      it should be out of list
    assert(false == BNLinkedListContainsObject(list, singleObject));
    
    //      add it to the head of list
    BNLinkedListAddObject(list, singleObject);
    
    //      now it has to be in list
    assert(true == BNLinkedListContainsObject(list, singleObject));
    
    //      the list has to be not empty now
    assert(false == BNLinkedListIsEmpty(list));
    
    //  delete all objects from non-empty list
    BNLinkedListRemoveAllObjects(list);
    
    //      the list has to be empty
    assert(true == BNLinkedListIsEmpty(list));
    
    //  create some new objects
    uint16_t const objectsNumber = 5000;
    static BNString *object[objectsNumber];
    char text[7 + snprintf(0,0,"%+d", objectsNumber)];
    for (uint64_t index = 0; index < objectsNumber; index++) {
        sprintf(text, "object#%llu", index);
        object[index] = BNStringCreateWithData(text);
    }
    
    //      add created objects to list
    //          check them to be in list
    for (uint64_t index = 0; index < objectsNumber; index++) {
        BNLinkedListAddObject (list, object[index]);
        assert(true == BNLinkedListContainsObject(list, object[index]));
    }
    
    //      remove object from list
    BNLinkedListRemoveObject(list, object[0]);
    
    //      it should be out list
    assert(false == BNLinkedListContainsObject(list, object[0]));
    
    //      check other objects to be in list
    for (uint64_t index = 1; index < objectsNumber; index++) {
        assert(true == BNLinkedListContainsObject(list, object[index]));
    }
    
    //      is object3 before object2 in list?
    assert(object[objectsNumber - 1] == (BNString *)BNLinkedListGetObjectBeforeObject(list, object[objectsNumber - 2]));
    
    //      let's remove head object
    BNLinkedListRemoveFirstObject(list);
    
    //      it should be object -1 out of list
    assert(false == BNLinkedListContainsObject(list, object[objectsNumber - 1]));
    
    //      it's object -2 is the first in the list
    assert(object[objectsNumber - 2] == (BNString *)BNLinkedListGetFirstObject(list));
    
    for (uint64_t index = 0; index < objectsNumber; index++) {
        BNObjectRelease(object[index]);
    }
    BNObjectRelease(singleObject);
    BNObjectRelease(list);
}
