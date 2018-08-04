#include "lib-mmy.h"

int arr_contains(int *arr, int arrLen, int x) {
    for(int i = 0; i < arrLen; i++) {
        if(arr[i] == x)
            return 1;
    }
    return 0;
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

    typedef struct Pipe {
        int this;
        int *conn;
    } Pipe;

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

    for(int i = 0; i < arr_len(pipes); i++) {
        //dbg("pipes[%d]: %d ->", i, pipes[i].this);
        for(int j = 0; j < arr_len(pipes[i].conn); j++) {
            //dbg("%d", pipes[i].conn[j]);
        }
    }

    int oldLen = 1;
    int newLen = 0;
    int *zeroGroup = 0;
    arr_push(zeroGroup, 0);

    for(int i = 0; i < arr_len(zeroGroup); i++) {
        for(int j = 0; j < arr_len(pipes); j++) {
            if(pipes[j].this == zeroGroup[i]) {
                for(int k = 0; k < arr_len(pipes[j].conn); k++) {
                    if(!arr_contains(zeroGroup, arr_len(zeroGroup), pipes[j].conn[k]))
                        arr_push(zeroGroup, pipes[j].conn[k]);
                }
            }
        }
    }
    dbg("Solution 12a: %d", arr_len(zeroGroup));
}
