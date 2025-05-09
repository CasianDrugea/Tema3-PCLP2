#define UTILS
#include "utils.h"

void exit_program(const char * const error_message)
{
    fprintf(stderr, "%s", error_message);
    exit(-1);
}

void read_int(FILE * restrict f, int * const val) {
    fscanf(f, "%d", val);
    
    return;
}

void write_int(FILE * restrict f, const int val) {
    fprintf(f, "%d\n", val);

    return;
}

const int compare_int_array(const char * const file_read_out, const char * const file_read_ref) {
    FILE * restrict f_read_out = fopen(file_read_out, "r");
    if (!f_read_out) {
        exit_program("fopen() failed!\n");
    }
    FILE * restrict f_read_ref = fopen(file_read_ref, "r");
    if (!f_read_ref) {
        exit_program("fopen() failed!\n");
    }
    int equal_result = 1;
    while (1) {
        int out_val = -1;
        int ref_val = -1;
        read_int(f_read_out, &out_val);
        read_int(f_read_ref, &ref_val);
        if (out_val == -1 && ref_val == -1) {
            break;
        }
        if (out_val != ref_val) {
            equal_result = 0; 
            break;
        }
    }
    fclose(f_read_out);
    fclose(f_read_ref);

    return equal_result;
}

void output_line_center(const char * const line) {
    const int space = LINE_LENGTH;
    const int text_length = strlen(line);
    const int remaining = space - text_length;
    int extra_left = remaining / 2;
    int extra_right = remaining - remaining / 2;
    while (extra_left--) {
        printf("-");
    }
    printf("%s", line);
    while(extra_right--) {
        printf("-");
    }
    printf("\n");

    return;
}
void output_line_margins(const char * const left, const char * const right) {
    const int space = LINE_LENGTH;
    const int left_length = strlen(left);
    const int right_length = strlen(right);
    int remaining = space - left_length - right_length;
    printf("%s", left);
    while (remaining--) {
        printf("-");
    }
    printf("%s", right);
    printf("\n");

    return;
}

