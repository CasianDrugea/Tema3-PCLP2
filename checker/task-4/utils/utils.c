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

void read_char_array(FILE * restrict f, char * const str) {
    fscanf(f, "%s", str);

    return;
}

void write_int(FILE * restrict f, const int val) {
    fprintf(f, "%d\n", val);

    return;
}

void write_char_array(FILE * restrict f, const char * const str) {
    fprintf(f, "%s\n", str);

    return;
}

const int compare_int(const char * const file_read_out, const char * const file_read_ref) {
    FILE * restrict f_read_out = fopen(file_read_out, "r");
    if (!f_read_out) {
        exit_program("fopen() failed!\n");
    }
    int out = -1;
    read_int(f_read_out, &out);
    FILE * restrict f_read_ref = fopen(file_read_ref, "r");
    if (!f_read_ref) {
        exit_program("fopen() failed!\n");
    }
    int ref = -1;
    read_int(f_read_ref, &ref);
    fclose(f_read_out);
    fclose(f_read_ref);

    return ref == out;
}

const int compare_char_array(const char * const file_read_out, const char * const file_read_ref) {
    FILE * restrict f_read_out = fopen(file_read_out, "r");
    if (!f_read_out) {
        exit_program("fopen() failed!\n");
    }
    char out[150];
    read_char_array(f_read_out, out);
    FILE * restrict f_read_ref = fopen(file_read_ref, "r");
    if (!f_read_ref) {
        exit_program("fopen() failed!\n");
    }
    char ref[150];
    read_char_array(f_read_ref, ref);
    fclose(f_read_out);
    fclose(f_read_ref);

    return strcmp(out, ref);
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

