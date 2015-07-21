//
//  BNLinkedListNode.c
//  Human
//
//  Created by BenNovikov on 07.06.15.
//  Copyright (c) 2015 ___Basic_Notation___. All rights reserved.
//

#include <stdio.h>

#include "BNLinkedListNode.h"

#pragma mark -
#pragma mark Private Declaration

static
BNLinkedListNode *BNLinkedListNodeGetNextNodeField(BNLinkedListNode *node);

static
void BNLinkedListNodeSetNextNodeField(BNLinkedListNode *node, BNLinkedListNode *nextNode);

static
BNObject *BNLinkedListNodeGetObjectField(BNLinkedListNode *node);

static
void BNLinkedListNodeSetObjectFiled(BNLinkedListNode *node, void *object);

#pragma mark -
#pragma mark Public Implementations

void __BNLinkedListNodeDeallocate(void *object) {
    BNLinkedListNodeSetNextNode(object, NULL);
    BNLinkedListNodeSetObject(object, NULL);
    
    __BNObjectDeallocate(object);
}

BNLinkedListNode *BNLinkedListNodeCreateWithObject(void *object) {
    BNLinkedListNode *node = BNObjectCreateOfType(BNLinkedListNode);
    BNLinkedListNodeSetObject(node, object);
    
    return node;
}

BNLinkedListNode *BNLinkedListNodeGetNextNode(BNLinkedListNode *node) {
    return BNLinkedListNodeGetNextNodeField(node);
}

void BNLinkedListNodeSetNextNode(BNLinkedListNode *node, BNLinkedListNode *nextNode) {
    BNLinkedListNodeSetNextNodeField(node, nextNode);
}

BNObject *BNLinkedListNodeGetObject(BNLinkedListNode *node) {
    return BNLinkedListNodeGetObjectField(node);
}

<<<<<<< HEAD
void BNLinkedListNodeSetObject(BNLinkedListNode *node, void *object) {
    if ((BNLinkedListNodeGetObjectField(node)) != object) {
        BNLinkedListNodeSetObjectFiled(node, object);
=======
void BNLinkedListNodeSetObject(BNLinkedListNode *node, void *object){
    if (NULL != node) {
        node->_object = object;
        if (NULL != object) {
            BNObjectRetain(object);
        } else {
            node->_object = object;
        }
        
>>>>>>> ed570a4c47ac9151021269eab425aa3ba9d69b7b
    }
    
}

<<<<<<< HEAD
#pragma mark -
#pragma mark Private Implementation

BNLinkedListNode *BNLinkedListNodeGetNextNodeField(BNLinkedListNode *node) {
    return BNGetObjectVar(node, _nextNode);
}

void BNLinkedListNodeSetNextNodeField(BNLinkedListNode *node, BNLinkedListNode *nextNode) {
    BNRetainSetter(node, _nextNode, nextNode);
}

BNObject *BNLinkedListNodeGetObjectField(BNLinkedListNode *node) {
    return BNGetObjectVar(node, _object);
=======
void __BNLinkedListNodeDeallocate(void *object){
    BNLinkedListNodeSetObject(NULL, object);
    BNObjectRelease(object);
>>>>>>> ed570a4c47ac9151021269eab425aa3ba9d69b7b
}

void BNLinkedListNodeSetObjectFiled(BNLinkedListNode *node, void *object) {
    BNRetainSetter(node, _object, object);
}