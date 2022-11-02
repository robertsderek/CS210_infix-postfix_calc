#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "rpn.h"
#include "errors.h"
#include "rpn-convert.h"

#define MAX_LENGTH 100
int main(int argc, char *argv[]) {
    int status;
    char inputExpression[MAX_LENGTH] = {0};
    char postfix[MAX_LENGTH] = {0};
    double result;
    //Open files specified on command line (input, output)
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");
    if(inputFile == NULL){
        status = ERRINPUTNULL;
        callStatusMessage(5);
        return ERRINPUTNULL;
    }

    //While the file is not empty
    while (fgets(inputExpression, 100, inputFile)) {
        //Need to trim off the trailing \n
        inputExpression[strcspn(inputExpression, "\n")] = 0;
        printf("%s\n", inputExpression);
        fprintf(outputFile, "Infix: %s\n", inputExpression);
        infixToPostfix(inputExpression, postfix, &status);
        fprintf(outputFile, "Postfix: %s\n", postfix);
        result = evaluate(postfix, &status);
        fprintf(outputFile, "Result: %f\n\n", result);
        memset(postfix, 0, MAX_LENGTH);
    }
    fclose(inputFile);
    fclose(outputFile);

    return 0;

}
