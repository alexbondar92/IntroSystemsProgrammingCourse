#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include "mtm_ex3.h"
#include "escape_technion.h"


/**
 * Getting the inLine parameters.
 *
 * checks if there is a input and output file to read/write to.
 * for input file <-i> flag is needed and after that the file path
 * for output file <-o> flag is needed and after that the file path
 * the defualt is stdin and stdout channel.
 * @param argc is the number of parameters
 * @param argv is the array of the parameters
 * @param input the input FILE to read from
 * @param output the output FILE to write to
 * @return
 * 	MTM_INVALID_COMMAND_LINE_PARAMETERS - in case of invalid parameters
 *  MTM_CANNOT_OPEN_FILE - in case of problem with opening files
 *  MTM_SUCCESS - in case of success
 */
MtmErrorCode parserGetParameters(int argc, const char * argv[], FILE** input,
                                 FILE** output);

/**
 * Getting the inLine parameters.
 *
 * checks if there is a input and output file to read/write to.
 * for input file <-i> flag is needed and after that the file path
 * for output file <-o> flag is needed and after that the file path
 * the defualt is stdin and stdout channel.
 * @param input the input FILE to read from
 * @param output the output FILE to write to
 * @param system the main System of the program.
 * @return
 * 	MTM_INVALID_COMMAND_LINE_PARAMETERS - in case of invalid parameters
 *  MTM_OUT_OF_MEMORY - in case of memory problem
 *  MTM_SUCCESS - in case of success
 */
MtmErrorCode parserGetInput(FILE* input, FILE* output, EscapeTechnion system);


#endif /* PARSER_H_ */
