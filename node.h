//
// Created by Derek Roberts on 12/2/21.
//

#ifndef PS4_NODE_H
#define PS4_NODE_H

//prototype for a node implemented as a struct
typedef struct node node;

//prototype for a function createNode which creates a new node with a given value
node *createNode(double value, int type);

node *createNumberNode(double value, int type);
node *createOperatorNode(char operator, int type);

enum TYPE  {OPERATOR, NUMBER, OPAREN, CPAREN};
enum ASSOCIATIVITY {LEFT, RIGHT};


#endif //PS4_NODE_H
