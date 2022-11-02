//
// Created by Derek Roberts on 11/8/21.
//

#include <string.h>
#include <stdlib.h>
#include "rpn.h"
#include "stack.h"
#include "node.h"
#include "errors.h"

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


//function which evaluates the expression and returns the output
double evaluate (char expression[], int* status){
    char* token;
    double left, right, result;

    //Check to see if the input status value is a NULL pointer
    if(status == NULL){
        clearStack();
        callStatusMessage(1);
        return 0.0;
    }

    //prime the strtok() algorithm
    *status = SUCCESS;
    token = strtok(expression, " ");

    if(token && !strstr("+-/*^", token)){
        push(createNode(strtod(token, NULL), NUMBER));
    }
    else{
        *status = ERRINCORRECTFORMAT;
        callStatusMessage(3);
        return 0.0;
    }

    //a while loop that parses the entire expression and remainder tokens
    while((token = strtok(NULL, " "))){

        //if the token is a number
        if(!strstr("+-/*^", token)) {
            node *node = createNode(strtod(token, NULL), NUMBER);
            push(node);
        }
        //token is an operator
        else{
            node* rightNode;
            node* leftNode;

            //make sure operations won't be performed on an empty stack
            if(stackEmpty()){
                *status = ERRINCORRECTFORMAT;
                clearStack();
                callStatusMessage(3);
                return 0.0;
            }

            //pop the first number which will be on the right
            rightNode = pop();
            //check to make sure there isn't a null pointer and then assign the value in the node
            if(rightNode == NULL){
                *status = ERRNULLPTR;
                callStatusMessage(1);
                return 0.0;
            }
            right = rightNode->contents.value;
            free(rightNode);
            rightNode = NULL;

            //ensures that there are two numbers to perform operations on
            if(stackEmpty()){
                *status = ERRINCORRECTFORMAT;
                callStatusMessage(3);
                return 0.0;
            }

            //pop the second number which will be on the left
            leftNode = pop();
            //check to make sure there isn't a null pointer and then assign the value in the node
            if(leftNode == NULL){
                *status = ERRNULLPTR;
                clearStack();
                callStatusMessage(1);
                return 0.0;
            }
            left = leftNode->contents.value;
            free(leftNode);
            leftNode = NULL;

            //if both numbers have been popped and the stack is still not empty, there are too few operators
            if(!stackEmpty()){
                *status = ERRINCORRECTFORMAT;
                callStatusMessage(3);
                return 0.0;
            }

            //switch statement for the different operators
            switch (*token) {
                case '+':
                    result = add(left, right);
                    break;
                case '-':
                    result = subtract(left, right);
                    break;
                case '*':
                    result = multiply(left, right);
                    break;
                case '/':
                    if(right == 0){
                        //status = error message
                        *status = ERRDIVBY0;
                        //clear stack
                        clearStack();
                        //call status message
                        callStatusMessage(2);
                        //return 0.0
                        return 0.0;
                    }
                    result = divide(left, right);
                    break;
                case '^':
                    result = recursivePower(left, right);
                    break;
                default:
                    *status = ERRUNRECOGNIZEDOPP;
                    clearStack();
                    callStatusMessage(4);
                    return 0.0;
            }
            //free the discarded nodes and push the new result to the stack
            push(createNode(result, NUMBER));
        }
    }
    return peek()->contents.value;
}

//function which adds the two inputs and returns the sum
double add(double val1, double val2){
    double result = val1 + val2;
    return result;
}

//function which subtracts the two inputs and returns the difference
double subtract(double val1, double val2){
    double result = val1 - val2;
    return result;
}

//function that multiplies the two inputs and returns the product
double multiply(double val1, double val2){
    double result = val1 * val2;
    return result;
}

//function that divides the two inputs and returns the quotient
double divide(double val1, double val2){
    double result = val1 / val2;
    return result;
}

//function that raises the first input to the power of the second output and returns the result
double recursivePower(double val1, double val2){
    if (val2 == 1){
        return val1;
    }
    return val1 * recursivePower(val1, val2 - 1);
}