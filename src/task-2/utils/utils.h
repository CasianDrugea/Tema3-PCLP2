#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef CHECKER
const char * const IN_TEMPLATE          =                   "in/operatii-%s%d.in";
const char * const OUT_TEMPLATE         =                 "out/operatii-%s%d.out";
const char * const REF_TEMPLATE         =                 "ref/operatii-%s%d.ref";
const int NOF_TESTS                     =                                       5;
const int NOT_TESTED                    =                                      -2;
const int NOT_FAILED                    =                                      -1;
const int STRING_LENGTH                 =                                     100;
#endif

#define LINE_LENGTH 65

void exit_program(const char * const error_message);
void read_int(FILE * restrict f, int * const val);
void read_char_array(FILE * restrict f, char * const str);
void write_int(FILE * restrict f, const int val);
void write_char_array(FILE * restrict f, const char * const str);
const int compare_int(const char * const file_read_out, const char * const file_read_ref);
const int compare_char_array(const char * const file_read_out, const char * const file_read_ref);
void output_line_center(const char * const line);
void output_line_margins(const char * const left, const char * const right);
