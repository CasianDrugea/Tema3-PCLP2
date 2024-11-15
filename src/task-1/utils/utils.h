#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef CHECKER
const char * const IN_TEMPLATE          =                       "in/sortari-%s%d.in";
const char * const OUT_TEMPLATE         =                     "out/sortari-%s%d.out";
const char * const REF_TEMPLATE         =                     "ref/sortari-%s%d.ref";
const int NOT_TESTED                    =                                      -2;
const int NOT_FAILED                    =                                      -1;
const int NOF_GROUPS                    =                                       4;
const int NOF_TESTS                     =                                       5;
#endif

#define LINE_LENGTH 65

void exit_program(const char * const error_message);
void read_int(FILE * restrict f, int * const val);
void write_int(FILE * restrict f, const int val);
const int compare_int_array(const char * const file_read_out, const char * const file_read_ref);
void output_line_center(const char * const line);
void output_line_margins(const char * const left, const char * const right);
