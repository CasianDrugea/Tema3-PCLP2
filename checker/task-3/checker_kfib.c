#define CHECKER
#include "utils/utils.h"

extern const int kfib(int n, int K);

int fault[5] = {NOT_TESTED, NOT_TESTED, NOT_TESTED, NOT_TESTED, NOT_TESTED};
int score;
int nof_tested_groups = NOF_GROUPS;

void task(const char * const file_read, const char * const file_write) {
    FILE * restrict f_read = fopen(file_read, "r");
    if (!f_read) {
        exit_program("fopen() failed!\n");
    }
    FILE * restrict f_write = fopen(file_write, "w");
    if (!f_write) {
        exit_program("fopen() failed!\n");
    }
    int n, k;
    read_int(f_read, &n);
    read_int(f_read, &k);
    const int res = kfib(n, k);
    write_int(f_write, res);
    fclose(f_read);
    fclose(f_write);
    
    return;
}

void calculate_score() {
    char file_out[50];
    char file_ref[50];
    char append[2];
    for (int group = 0; group < nof_tested_groups; ++group) {
        fault[group] = NOT_FAILED;
        for (int test = group * 5; test < (group + 1) * 5; ++test) {
            memset(append, 0, sizeof(append)); 
            memset(file_out, 0, sizeof(file_out));
            memset(file_ref, 0, sizeof(file_ref));
            if  (test < 10) {
                append[0] = '0';
            }
            sprintf(file_out, OUT_TEMPLATE, append, test);
            sprintf(file_ref, REF_TEMPLATE, append, test);
            const int ret = compare_int(file_out, file_ref);
            if (!ret) {
                fault[group] = test;
                break;
            }
        }
    }

    return;
}

void task_pre() {
    char file_in[50];
    char file_out[50];
    char append[2];
    for (int test = 0; test < nof_tested_groups * 5; ++test) {
        memset(append, 0, sizeof(append));
        memset(file_in, 0, sizeof(file_in));
        memset(file_out, 0, sizeof(file_out));
        if (test < 10) {
            append[0] = '0';
        }
        sprintf(file_in, IN_TEMPLATE, append, test);
        sprintf(file_out, OUT_TEMPLATE, append, test);
        task(file_in, file_out);
    }
    calculate_score();

    return;
}

void compute_total() {
    output_line_center(" TASK 3 ");
    char line[LINE_LENGTH];
    char line_end[LINE_LENGTH];
    for (int group = 0; group < NOF_GROUPS; ++group) {
        sprintf(line, "[Group %d] ", group);
        if (fault[group] == NOT_TESTED) {
            output_line_margins(line, " Skipped");
        } else if (fault[group] != NOT_FAILED) {
            sprintf(line_end, " Failed at test %s%d", fault[group] >= 10 ? "" : "0", fault[group]);
            output_line_margins(line, line_end);
        } else {
            output_line_margins(line, " Passed [+5p]");
            score += 5;
        }
    }
    sprintf(line, " TASK 3 SCORE: %d/%d ", score, 20);
    output_line_center(line);

    return;
}

int main(const int argc, const char * const argv[]) {
    if (argc > 2) {
        exit_program("Usage: ./checker \n");
    }
    if (argc == 2) {
        if (strlen(argv[1]) > 1) {
            exit_program("Usage: ./checker [1/2/3/4]\n");
        }
        nof_tested_groups = atoi(argv[1]);
        
        if (nof_tested_groups > NOF_GROUPS || nof_tested_groups < 1) {
            exit_program("Usage: ./checker [1/2/3/4]\n");
        }
    }
    task_pre();
    compute_total();
    
    return 0;
}
