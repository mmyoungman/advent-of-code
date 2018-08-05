#include "lib-mmy.h"

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

    int *layer = 0;
    int *depth = 0;

    int severity = 0;
    for(int i = 0; i < size; i++) {
        int lineSize;
        char **line = str_split(data[i], ' ', &lineSize);

        arr_push(layer, str_toint(str_rstrip(line[0], ':')));
        arr_push(depth, str_toint(line[1]));
        
        if(layer[i] % (2 * (depth[i] - 1)) == 0) {
            severity += layer[i] * depth[i];
        }

    }
    dbg("Solution 2017 13a: %d", severity);

    int delay = 0;
    while(1) {
        int caught = 0;
        for(int i = 0; i < size; i++) {
            if((layer[i] + delay) % (2 * (depth[i] - 1)) == 0) {
                caught = 1;
                break;
            }
        }
        if(caught) delay += 1;
        else break;
    }
    dbg("Solution 2017 13b: %d", delay);
}
