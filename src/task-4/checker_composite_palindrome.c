#define CHECKER
#include "utils/utils.h"

extern const int check_palindrome(const char * const str, const int len);
extern char * const composite_palindrome(const char * const * const strs, const int len);

int fault[6] = {NOT_TESTED, NOT_TESTED, NOT_TESTED, NOT_TESTED, NOT_TESTED, NOT_TESTED};
int score;

void task_1(const char * const file_read, const char * const file_write) {
    FILE * restrict f_read = fopen(file_read, "r");
    if (!f_read) {
        exit_program("fopen() failed!\n");
    }
    char str[10] = {0};
    read_char_array(f_read, str);
    const int res = check_palindrome(str, (int)strlen(str));
    FILE * restrict f_write = fopen(file_write, "w");
    if (!f_write) {
        exit_program("fopen() failed!\n");
    }
    write_int(f_write, res);
    fclose(f_read);
    fclose(f_write);

    return;
}

void task_2(const char * const file_read, const char * const file_write) {
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
    char **strings = NULL;
    strings = calloc(n, sizeof(*strings));
    if (!strings) {
        exit_program("calloc() failed!\n");
    }
    for (int i = 0; i < n; ++i) {
        strings[i] = calloc(STRING_LENGTH, sizeof(*strings[i]));
        if (!strings[i]) {
            exit_program("calloc() failed!\n");
        }
    }
    for (int i = 0; i < n; ++i) {
        read_char_array(f_read, strings[i]);
    }
    char * const res = composite_palindrome((const char * const * const)strings, n);
    write_char_array(f_write, res);
    free(res);
    for (int i = 0; i < n; ++i) {
        free(strings[i]);
    }
    free(strings);
    fclose(f_read);
    fclose(f_write);
    
    return;
}

void calculate_score_1() {
    char file_out[50];
    char file_ref[50];
    char append[2];
    fault[FIRST_TASK] = NOT_FAILED;
    for (int test = 0; test < NOF_TESTS_TASK_1; ++test) {
        memset(append, 0, sizeof(append)); 
        memset(file_out, 0, sizeof(file_out));
        memset(file_ref, 0, sizeof(file_ref));
        if (test < 10) {
            append[0] = '0';
        }
        sprintf(file_out, OUT_TASK_1_TEMPLATE, append, test);
        sprintf(file_ref, REF_TASK_1_TEMPLATE, append, test);
        const int ret = compare_int(file_out, file_ref);
        if (!ret) {
            fault[FIRST_TASK] = test;
            break;
        }
    }

    return;
}


void calculate_score_2() {
    char file_out[50];
    char file_ref[50];
    char append[2];
    for (int group = 0; group < 5; ++group) {
        fault[SECOND_TASK + group] = NOT_FAILED;
        for (int test = group * 10; test < (group + 1) * 10; ++test) {
            memset(append, 0, sizeof(append)); 
            memset(file_out, 0, sizeof(file_out));
            memset(file_ref, 0, sizeof(file_ref));
            if  (test < 10) {
                append[0] = '0';
            }
            sprintf(file_out, OUT_TASK_2_TEMPLATE, append, test);
            sprintf(file_ref, REF_TASK_2_TEMPLATE, append, test);
            const int ret = compare_char_array(file_out, file_ref);
            if (ret) {
                fault[SECOND_TASK + group] = test;
                break;
            }
        }
    }

    return;
}

void task_pre_1() {
    char file_in[50];
    char file_out[50];
    char append[2];
    for (int test = 0; test < NOF_TESTS_TASK_1; ++test) {
        memset(append, 0, sizeof(append)); 
        memset(file_in, 0, sizeof(file_in));
        memset(file_out, 0, sizeof(file_out));
        if (test < 10) {
            append[0] = '0';
        }
        sprintf(file_in, IN_TASK_1_TEMPLATE, append, test);
        sprintf(file_out, OUT_TASK_1_TEMPLATE, append, test);
        task_1(file_in, file_out);
    }
    calculate_score_1();
    
    return;
}

void task_pre_2() {
    char file_in[50];
    char file_out[50];
    char append[2];
    for (int test = 0; test < NOF_TESTS_TASK_2; ++test) {
        memset(append, 0, sizeof(append));
        memset(file_in, 0, sizeof(file_in));
        memset(file_out, 0, sizeof(file_out));
        if (test < 10) {
            append[0] = '0';
        }
        sprintf(file_in, IN_TASK_2_TEMPLATE, append, test);
        sprintf(file_out, OUT_TASK_2_TEMPLATE, append, test);
        task_2(file_in, file_out);
    }
    calculate_score_2();

    return;
}

void compute_total() {
    output_line_center(" TASK 4 ");
    char line[LINE_LENGTH];
    if (fault[FIRST_TASK] == NOT_TESTED) {
        output_line_margins("Subtask 1 [Group 0] ", " Skipped");
    } else if (fault[FIRST_TASK] != NOT_FAILED) {
        sprintf(line, " Failed at test %s%d", fault[FIRST_TASK] >= 10 ? "" : "0", fault[FIRST_TASK]);
        output_line_margins("Subtask 1 [Group 0] ", line);
    } else {
        output_line_margins("Subtask 1 [Group 0] ", " Passed [+5p]");
        score += 5;
    }
    char line_end[LINE_LENGTH];
    for (int group = 0; group < 5; ++group) {
        sprintf(line, "Subtask 2 [Group %d] ", group);
        if (fault[SECOND_TASK + group] == NOT_TESTED) {
            output_line_margins(line, " Skipped");
        } else if (fault[SECOND_TASK + group] != NOT_FAILED) {
            sprintf(line_end, " Failed at test %s%d", fault[SECOND_TASK + group] >= 10 ? "" : "0", fault[SECOND_TASK + group]);
            output_line_margins(line, line_end);
        } else {
            output_line_margins(line, " Passed [+6p]");
            score += 6;
        }
    }
    sprintf(line, " TASK 4 SCORE: %d/%d ", score, 35);
    output_line_center(line);

    return;
}

int main(const int argc, const char * const argv[]) {
    if (argc > 2) {
        exit_program("Usage: ./checker [1/2]\n");
    }
    if (argc == 2) {
        if (strlen(argv[1]) > 1) {
            exit_program("Usage: ./checker [1/2]\n");
        }
        const int task_type = atoi(argv[1]);
        if (task_type == 1) {
            task_pre_1();
        } else if (task_type == 2) {
            task_pre_2();
        } else {
            exit_program("Usage: ./checker [1/2]\n");
        }
        compute_total();
    } else {
        task_pre_1();
        task_pre_2();
        compute_total();
    }

    return 0;
}
