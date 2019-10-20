#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "parser.h"
#include "mtm_ex3.h"
#include "escape_technion.h"


int main(int argc, const char * argv[]) {
    FILE* input = stdin;
    FILE* output = stdout;
    MtmErrorCode mtm_error = MTM_SUCCESS;
    mtm_error = parserGetParameters(argc, argv, &input, &output);
    if (mtm_error != MTM_SUCCESS){
        mtmPrintErrorMessage(stderr, mtm_error);
        if (input != NULL){
            fclose(input);
        }
        if (output != NULL){
            fclose(output);
        }
        return 0;
    }
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    EscapeTechnion system = escapeTechnionCreate(&system_error);
    if (system_error != ESCAPE_TECHNION_SUCCESS){
        mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
        fclose(input);
        fclose(output);
        return 0;
    }
    mtm_error = parserGetInput(input, output, system);
    if (mtm_error != MTM_SUCCESS){
        assert(mtm_error == MTM_OUT_OF_MEMORY);
        mtmPrintErrorMessage(stderr, mtm_error);
    }
    escapeTechnionDestroy(system);
    fclose(input);
    fclose(output);
    return 0;
}

