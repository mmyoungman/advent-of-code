#include "lib-mmy.h"

int main() {
    FILE* fp = fopen("input", "r");

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);

    int size;
    char** data = str_split(str_rstrip(buffer, '\n'), ',', &size);

    int lengths[size];
    for(int i = 0; i < size; i++) {
        lengths[i] = str_toint(data[i]);
    }

    int list[256];
    for(int i = 0; i < 256; i++) {
        list[i] = i;
    }

    int pos = 0;
    int skip = 0;

    for(int i = 0; i < size; i++) {
        int end = pos + lengths[i] - 1;
        for(int j = pos; j < end; j++, end--) {
            int temp = list[j%256];
            list[j%256] = list[end%256];
            list[end%256] = temp;
        }
        pos = (pos + lengths[i] + skip) % 256;
        skip++;
    }
    dbg("Solution 10a: %d", list[0] * list[1]);
}
