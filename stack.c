//
// Created by Derek Roberts on 11/8/21.
//


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "node.h"

//define the node implemented as a struct
typedef struct node {
    union {
        double value;
        char operator;
    } contents;
    int type;
    int precedence;
    node *next;
} node;

node* HEAD = NULL;
node* walker = NULL;
node* upstream = NULL;


//Prints the values in the stack
void printStack(void) {
    walker = HEAD;
    while (walker) {
        if (walker->type == NUMBER) {
            printf("%lf\n", walker->contents.value);
        } else if (walker->type == OPERATOR) {
            printf("%c\n", walker->contents.operator);
        }
        walker = walker->next;
    }
}


//helper function that returns TRUE if the stack is empty and FALSE if it contains nodes
    bool stackEmpty(void) {
        if (!HEAD) {
            return true;
        }
        return false;
    }

//function which pushes a new node onto the top of the stack
    void push(node *node) {
        //if the stack is empty simply assign the new node to HEAD
        if (stackEmpty()) {
            HEAD = node;
        } else {
            node->next = HEAD;
            HEAD = node;
        }
    }

//function which pops the top of the stack and returns the node
    node *pop(void) {
        //can't pop a node if the stack is empty
        if (stackEmpty()) {
            printf("Stack is empty");
            return NULL;
        } else {
            node *stackTop = HEAD;
            HEAD = stackTop->next;
            return stackTop;
        }
    }

//function which returns the top node in the stack
    node *peek(void) {
        if (stackEmpty()) {
            printf("There are no nodes in the stack");
            return NULL;
        } else {
            return HEAD;
        }
    }

//function that resets the stack to empty and frees any nodes previously in the stack
    void clearStack(void) {
        if (stackEmpty()) {
            printf("Stack is already empty");
            return;
        } else {
            upstream = HEAD;
            walker = upstream->next;
            //loop which goes down the stack freeing each node
            while (walker != NULL) {
                free(upstream);
                upstream = walker;
                walker = walker->next;
            }
        }
        free(upstream);
        HEAD = NULL;
    }
