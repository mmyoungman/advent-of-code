#include "lib-mmy.h"

typedef struct Pipe {
    int this;
    int *conn;
} Pipe;

int arr_contains(int *arr, int arrLen, int x) {
    for(int i = 0; i < arrLen; i++) {
        if(arr[i] == x) { return x; }
    }
    return -1;
}

int pipeInGroups(int p, int **groups, int numGroups) {
    for(int i = 0; i < numGroups; i++) {
        for(int j = 0; j < arr_len(groups[i]); j++) {
            if(p == groups[i][j]) { return p; }
        }
    }
    return -1;
}

int main() {
    FILE* fp = fopen("input", "r");

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);

    int size;
    char** data = str_split(buffer, '\n', &size);
    size--;

    Pipe *pipes = 0;
    for(int i = 0; i < size; i++) {
        int lineSize;
        char** line = str_split(data[i], ' ', &lineSize);
        Pipe p;
        p.this = str_toint(line[0]);
        p.conn = 0;
        for(int j = 2; j < lineSize; j++) {
            arr_push(p.conn, str_toint(str_rstrip(line[j], ',')));
        }
        arr_push(pipes, p);
    }

    int **groups = 0;
    int *group;

    for(int i = 0; i < arr_len(pipes); i++) {
        int p = pipeInGroups(pipes[i].this, groups, arr_len(groups));
        if(-1 == p) {
            group = 0;
            arr_push(group, pipes[i].this);
            for(int i = 0; i < arr_len(group); i++) {
                for(int j = 0; j < arr_len(pipes); j++) {
                    if(pipes[j].this == group[i]) {
                        for(int k = 0; k < arr_len(pipes[j].conn); k++) {
                            if(-1 == arr_contains(group, arr_len(group), pipes[j].conn[k]))
                                arr_push(group, pipes[j].conn[k]);
                        }
                    }
                }
            }
            arr_push(groups, group);
        }
    }
    dbg("Solution 12a: %d", arr_len(groups[0]));
    dbg("Solution 12b: %d", arr_len(groups));
}
