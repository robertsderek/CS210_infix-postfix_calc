//
// Created by Derek Roberts on 11/11/21.
//

#include "errors.h"
#include <stdio.h>

//array containing the different error messages corresponding to their status value
const char *errorMessages[] = {
        "SUCCESS",
        "ERROR: INCORRECT NULL POINTER",
        "ERROR: ATTEMPTING TO DIVIDE BY 0",
        "ERROR: INCORRECT FORMAT",
        "ERROR: UNRECOGNIZED OPERAND",
        "ERROR: INPUT FILE NULL",
        "ERROR: PARENTHESIS MISMATCH"
};

//0 = SUCCESS
//1 = ERROR: INCORRECT NULL POINTER
//2 = ERROR: ATTEMPTING TO DIVIDE BY 0
//3 = ERROR: INCORRECT FORMAT
//4 = ERROR: UNRECOGNIZED OPERAND
//5 = ERROR: INPUT FILE NULL
//6 = ERROR: PARENTHESIS MISMATCH


void callStatusMessage(int input){
    printf("\n%s\n", errorMessages[input]);
}
