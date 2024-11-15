#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef CHECKER
const char * const IN_TASK_1_TEMPLATE   =           "in/check_palindrome-%s%d.in";
const char * const IN_TASK_2_TEMPLATE   =       "in/composite_palindrome-%s%d.in";
const char * const OUT_TASK_1_TEMPLATE  =         "out/check_palindrome-%s%d.out";
const char * const OUT_TASK_2_TEMPLATE  =     "out/composite_palindrome-%s%d.out";
const char * const REF_TASK_1_TEMPLATE  =         "ref/check_palindrome-%s%d.ref";
const char * const REF_TASK_2_TEMPLATE  =     "ref/composite_palindrome-%s%d.ref";
const int NOF_TESTS_TASK_1              =                                      30;
const int NOF_TESTS_TASK_2              =                                      50;
const int NOT_TESTED                    =                                      -2;
const int NOT_FAILED                    =                                      -1;
const int FIRST_TASK                    =                                       0;
const int SECOND_TASK                   =                                       1;
const int STRING_LENGTH                 =                                      10;
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
