#include <string.h>
#include "parser.h"
#include <assert.h>
#include <stdlib.h>

#define MAX_PARAMETERS 9

static MtmErrorCode callCurrentFunction(FILE* output, EscapeTechnion system,
                                        char* commandens[MAX_PARAMETERS]);
static MtmErrorCode convertEscapeTechnionErrorCode(EscapeTechnionErrorCode
                                                   system_error);


MtmErrorCode parserGetParameters(int argc, const char * argv[], FILE** input,
                                 FILE** output){
    *input = stdin;
    *output = stdout;
    const char* input_file = NULL;
    const char* output_file = NULL;
    bool input_sign = false;
    bool output_sign = false;
    for (int i=1; i < argc; i++){
        if (strcmp(argv[i], "-i") == 0 && input_sign == false){
            if (argv[i+1] == 0){
                return MTM_INVALID_COMMAND_LINE_PARAMETERS;
            }
            input_file = argv[i+1];
            input_sign = true;
            i++;
            continue;
        } else if  (strcmp(argv[i], "-o") == 0 && output_sign == false){
            if (argv[i+1] == 0){
                return MTM_INVALID_COMMAND_LINE_PARAMETERS;
            }
            output_file = argv[i+1];
            output_sign = true;
            i++;
            continue;
        } else {
            return MTM_INVALID_COMMAND_LINE_PARAMETERS;
        }
    }
    if (output_file != NULL){
    *output = fopen(output_file, "w");
        if (*output == NULL){
            return MTM_CANNOT_OPEN_FILE;
        }
    }
    if (input_file != NULL){
        *input = fopen(input_file, "r");
        if (*input == NULL){
            return MTM_CANNOT_OPEN_FILE;
        }
    }
    return MTM_SUCCESS;
}

MtmErrorCode parserGetInput(FILE* input, FILE* output, EscapeTechnion system){
    assert(input != NULL);
    char buffer[MAX_LEN+1];
    char delims[5] = " \t\r\n";  // " /t/n"
    
    while (fgets(buffer, MAX_LEN+1, input) != 0) {
        char* commands[MAX_PARAMETERS];
        int i = 0;
        commands[i] = strtok(buffer, delims);
        if (commands[i] == 0 || *commands[i] == '#'){
            continue;
        }
        
        while (commands[i] != 0) {
            i++;
            commands[i] = strtok(NULL, delims);
        }
        
        MtmErrorCode mtm_error = callCurrentFunction(output, system, commands);
        if (mtm_error != MTM_SUCCESS){
            if (mtm_error == MTM_OUT_OF_MEMORY){
                return mtm_error;
            } else{
                mtmPrintErrorMessage(stderr, mtm_error);
            }
        }
    }
    return MTM_SUCCESS;
}

static MtmErrorCode callCurrentFunction(FILE* output, EscapeTechnion system,
                                        char* commandes[MAX_PARAMETERS]){
    assert(commandes != NULL);
    EscapeTechnionErrorCode system_error = ESCAPE_TECHNION_SUCCESS;
    if (strcmp(commandes[0], "company") == 0){
        if (strcmp(commandes[1], "add") == 0){
            system_error = escapeTechnionAddCompany(system, commandes[2],
                                                    atoi(commandes[3]));
        } else if (strcmp(commandes[1], "remove") == 0){
            system_error = escapeTechnionRemoveCompany(system, commandes[2]);
        }
    } else if (strcmp(commandes[0], "room") == 0){
        if (strcmp(commandes[1], "add") == 0){
            system_error = escapeTechnionAddRoom(system, commandes[2],
                                atoi(commandes[3]), atoi(commandes[4]),
                                atoi(commandes[5]), commandes[6],
                                atoi(commandes[7]));
        } else if (strcmp(commandes[1], "remove") == 0){
            system_error = escapeTechnionRemoveRoom(system, atoi(commandes[2]),
                                                    atoi(commandes[3]));
        }
    } else if (strcmp(commandes[0], "escaper") == 0){
        if (strcmp(commandes[1], "add") == 0){
            system_error = escapeTechnionAddEscaper(system, commandes[2],
                                        atoi(commandes[3]), atoi(commandes[4]));
        } else if (strcmp(commandes[1], "remove") == 0){
            system_error = escapeTechnionRemoveEscaper(system, commandes[2]);
        } else if (strcmp(commandes[1], "order") == 0){
            system_error = escapeTechnionAddOrder(system, commandes[2],
                                    atoi(commandes[3]), atoi(commandes[4]),
                                    commandes[5], atoi(commandes[6]));
        } else if (strcmp(commandes[1], "recommend") == 0){
            system_error = escapeTechnionRecommendedOrder(system, commandes[2],
                                                          atoi(commandes[3]));
        }
    } else if (strcmp(commandes[0], "report") == 0){
        if (strcmp(commandes[1], "day") == 0){
            system_error = escapeTechnionReportDay(system, output);
        } else if (strcmp(commandes[1], "best") == 0){
            system_error = escapeTechnionReportBest(system, output);
        }
    } else {
        assert(0);
    }
    return convertEscapeTechnionErrorCode(system_error);
}


static MtmErrorCode convertEscapeTechnionErrorCode(EscapeTechnionErrorCode
                                                   system_error){
    switch (system_error){
        case ESCAPE_TECHNION_OUT_OF_MEMORY:
            return MTM_OUT_OF_MEMORY;
            break;
        case ESCAPE_TECHNION_NULL_PARAMETER:
            return MTM_NULL_PARAMETER;
            break;
        case ESCAPE_TECHNION_INVALID_PARAMETER:
            return MTM_INVALID_PARAMETER;
            break;
        case ESCAPE_TECHNION_EMAIL_ALREADY_EXISTS:
            return MTM_EMAIL_ALREADY_EXISTS;
            break;
        case ESCAPE_TECHNION_COMPANY_EMAIL_DOES_NOT_EXIST:
            return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
            break;
        case ESCAPE_TECHNION_CLIENT_EMAIL_DOES_NOT_EXIST:
            return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
            break;
        case ESCAPE_TECHNION_ID_ALREADY_EXIST:
            return MTM_ID_ALREADY_EXIST;
            break;
        case ESCAPE_TECHNION_ID_DOES_NOT_EXIST:
            return MTM_ID_DOES_NOT_EXIST;
            break;
        case ESCAPE_TECHNION_CLIENT_IN_ROOM:
            return MTM_CLIENT_IN_ROOM;
            break;
        case ESCAPE_TECHNION_ROOM_NOT_AVAILABLE:
            return MTM_ROOM_NOT_AVAILABLE;
            break;
        case ESCAPE_TECHNION_RESERVATION_EXISTS:
            return MTM_RESERVATION_EXISTS;
            break;
        case ESCAPE_TECHNION_NO_ROOMS_AVAILABLE:
            return MTM_NO_ROOMS_AVAILABLE;
            break;
        case ESCAPE_TECHNION_SUCCESS:
            return MTM_SUCCESS;
            break;
    }
    assert(0);
    return MTM_SUCCESS;
}
