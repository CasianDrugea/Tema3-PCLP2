#define CHECKER
#include "utils/utils.h"

extern void get_words(char *s, char **words, int nof_words);
extern void sort(char **words, int nof_words, int size);

int fault[5] = {NOT_TESTED, NOT_TESTED, NOT_TESTED, NOT_TESTED, NOT_TESTED};
int score;

void task(const char * const file_read, const char * const file_write) {
    FILE * restrict f_read = fopen(file_read, "r");
    if (!f_read) {
        exit_program("fopen() failed!\n");
    }
    FILE * restrict f_write = fopen(file_write, "w");
    if (!f_write) {
        exit_program("fopen() failed!\n");
    }
    int n;
    read_int(f_read, &n);
    char *text = NULL;
    text = calloc(STRING_LENGTH * STRING_LENGTH, sizeof(*text));
    if (!text) {
        exit_program("calloc() failed!\n");
    }
    char **strings = NULL;
    strings = calloc(n, sizeof(*strings));
    if (!strings) {
        exit_program("calloc() failed!\n");
    }
    read_char_array(f_read, text);
    get_words(text, strings, n);
    sort(strings, n, sizeof(char *));
    for (int i = 0; i < n; ++i) {
        write_char_array(f_write, strings[i]);
    }
    free(text);
    free(strings);
    fclose(f_read);
    fclose(f_write);
    
    return;
}

void calculate_score() {
    char file_out[50];
    char file_ref[50];
    char append[2];
    for (int test = 0; test < NOF_TESTS; ++test) {
        fault[test] = NOT_FAILED;
        memset(append, 0, sizeof(append)); 
        memset(file_out, 0, sizeof(file_out));
        memset(file_ref, 0, sizeof(file_ref));
        append[0] = '0';
        sprintf(file_out, OUT_TEMPLATE, append, test);
        sprintf(file_ref, REF_TEMPLATE, append, test);
        const int ret = compare_char_array(file_out, file_ref);
        if (ret) {
            fault[test] = test;
            break;
        }
    }

    return;
}

void task_pre() {
    char file_in[50];
    char file_out[50];
    char append[2];
    for (int test = 0; test < NOF_TESTS; ++test) {
        memset(append, 0, sizeof(append));
        memset(file_in, 0, sizeof(file_in));
        memset(file_out, 0, sizeof(file_out));
        append[0] = '0';
        sprintf(file_in, IN_TEMPLATE, append, test);
        sprintf(file_out, OUT_TEMPLATE, append, test);
        task(file_in, file_out);
    }
    calculate_score();

    return;
}

void compute_total() {
    output_line_center(" TASK 2 ");
    char line[LINE_LENGTH];
    char line_end[LINE_LENGTH];
    for (int test = 0; test < NOF_TESTS; ++test) {
        sprintf(line, "[Test %d] ", test);
        if (fault[test] != NOT_FAILED) {
            sprintf(line_end, " Failed");
            output_line_margins(line, line_end);
        } else {
            output_line_margins(line, " Passed [+5p]");
            score += 5;
        }
    }
    sprintf(line, " TASK 2 SCORE: %d/%d ", score, 25);
    output_line_center(line);

    return;
}

int main(const int argc, const char * const argv[]) {
    if (argc > 1) {
        exit_program("Usage: ./checker \n");
    }
    task_pre();
    compute_total();
    
    return 0;
}
