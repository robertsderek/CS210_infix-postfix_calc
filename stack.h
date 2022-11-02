//
// Created by Derek Roberts on 11/8/21.
//

#ifndef PS4_STACK_H
#define PS4_STACK_H

#endif //PS4_STACK_H

#include <stdbool.h>


//prototype for a node implemented as a struct
typedef struct node node;

//prototype for the function printStack
void printStack(void);

//prototype for the function stackEmpty
bool stackEmpty(void);

//prototype for the push function
void push(node*);

//prototype for the pop function
node* pop(void);

//prototype for the peek function
node* peek(void);

//prototype for the clearStack function
void clearStack(void);