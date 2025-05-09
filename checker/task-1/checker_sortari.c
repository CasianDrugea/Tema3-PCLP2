#define CHECKER
#include "utils/utils.h"

struct node {
    int val;
    struct node* next;
};

struct node *sort(int n, struct node *node);

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
    struct node *nodes = calloc(n, sizeof(*nodes));
    for (int i = 0; i < n; ++i) {
        read_int(f_read, &nodes[i].val);
    }
    const struct node *res = sort(n, nodes);
    while (res != NULL) {
        write_int(f_write, res->val);
        res = res->next;
    }
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
        const int ret = compare_int_array(file_out, file_ref);
        if (!ret) {
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
    output_line_center(" TASK 1 ");
    char line[LINE_LENGTH];
    char line_end[LINE_LENGTH];
    for (int test = 0; test < NOF_TESTS; ++test) {
        sprintf(line, "[Test %d] ", test);
        if (fault[test] != NOT_FAILED) {
            sprintf(line_end, " Failed"); 
            output_line_margins(line, line_end);
        } else {
            output_line_margins(line, " Passed [+4p]");
            score += 4;
        }
    }
    sprintf(line, " TASK 1 SCORE: %d/%d ", score, 20);
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
