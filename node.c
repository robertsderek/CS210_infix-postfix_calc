//
// Created by Derek Roberts on 12/2/21.
//

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "node.h"
#include "stack.h"

typedef struct node {
    union {
        double value;
        char operator;
    } contents;
    int type;
    int precedence;
    node *next;
} node;


node *createNode(double value, int type) {
    node *newNode = (struct node*) malloc(sizeof(node));
    if (newNode) {
        newNode->contents.value = value;
        newNode->type = type;
        newNode->next = NULL;
        newNode->precedence = 0;
    } else {
        puts("Unable to allocate memory for a node.\n");
        exit(-1);
    }
    return newNode;
}

node *createNumberNode(double value, int type) {
    node *newNode = (struct node*) malloc(sizeof(node));
    if (newNode) {
        newNode->contents.value = value;
        newNode->type = type;
        newNode->next = NULL;
        newNode->precedence = 0;
    } else {
        puts("Unable to allocate memory for a node.\n");
        exit(-1);
    }
    return newNode;
}

node *createOperatorNode(char operator, int type) {
    node *newNode = (struct node*) malloc(sizeof(node));
    if (newNode) {
        newNode->contents.operator = operator;
        newNode->type = type;
        newNode->next = NULL;
        if(operator == '^'){
            newNode->precedence = 3;
        }
        else if(operator == '*' || operator == '/'){
            newNode->precedence = 2;
        }
        else if(operator == '+' || operator == '-'){
            newNode->precedence = 1;
        }
        else if(operator == '(' || operator == ')'){
            newNode->precedence = 0;
        }
        else{
            callStatusMessage(4);
            return 0;
        }
    } else {
        puts("Unable to allocate memory for a node.\n");
        exit(-1);
    }
    return newNode;
}


