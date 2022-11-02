//
// Created by Derek Roberts on 12/2/21.
//

#include <string.h>
#include "errors.h"
#include "errors.c"
#include "stack.h"
#include "rpn-convert.h"
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

char *infixToPostfix(char inputExpression[], char postfix[], int* status){
    char* token;

    //Check to see if the input status value is a NULL pointer
    if(status == NULL){
        clearStack();
        callStatusMessage(1);
        return "ERROR: NULL POINTER";
    }

    //prime the strtok() algorithm
    *status = SUCCESS;
    token = strtok(inputExpression, " ");

    if(token && !strstr("+-/*^(", token)){
        strcat(postfix, token);
        strcat(postfix, " ");
    }
    else if(token && strstr("(", token)){
        push(createOperatorNode('(', OPERATOR));
    }
    else{
        *status = ERRINCORRECTFORMAT;
        callStatusMessage(3);
        return "ERROR: INCORRECT FORMAT";
    }

    //a while loop that parses the entire expression and remainder tokens
    while((token = strtok(NULL, " "))){

        //if the token is a number
        if(!strstr("+-/*^()", token)) {
            strcat(postfix, token);
            strcat(postfix, " ");
        }

        //if the token is an operator
        else if (strstr("+-/*^", token)){
            node* node = createOperatorNode(*token, OPERATOR);
            while(!stackEmpty() && ((peek()->precedence >= node->precedence) ) && (peek()->contents.operator != '(')){
                strcat(postfix, &pop()->contents.operator);
                strcat(postfix, " ");
            }
            push(node);
        }

        //if the token is a left parenthesis
        else if (strstr("(", token)){
            push(createOperatorNode(*token, OPERATOR));
        }

        //if the token is a right parenthesis
        else if (strstr(")", token)) {
            while(peek()->contents.operator != '('){
                strcat(postfix, &pop()->contents.operator);
                strcat(postfix, " ");
                //if the stack is empty without finding a left parenthesis
                if(stackEmpty()){
                    *status = ERRPARENMISMATCH;
                    callStatusMessage(6);
                    return "ERROR: PARENTHESIS MISMATCH";
                }
            }
            pop();
        }

        //if the token is incorrect
        else{
            *status = ERRUNRECOGNIZEDOPP;
            callStatusMessage(4);
            return "ERROR: UNRECOGNIZED OPERAND";
        }

    }

    //no more tokens but operator stack is still not empty
    while(!stackEmpty()){
        if(peek()->contents.operator == '(' || peek()->contents.operator == ')'){
            *status = ERRINCORRECTFORMAT;
            clearStack();
            callStatusMessage(3);
            return "ERRINCORRECTFORMAT";
        }
        else{
            strcat(postfix, &pop()->contents.operator);
            strcat(postfix, " ");
        }
    }

    return postfix;
}