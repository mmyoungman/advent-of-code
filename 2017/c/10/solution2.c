#include "lib-mmy.h"

int main() {
    FILE* fp = fopen("input", "r");

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);

    char* data = str_rstrip(buffer, '\n');
    int size = str_len(data);

    int lengths[size + 5];
    for(int i = 0; i < size; i++) {
        lengths[i] = data[i];
    }
    lengths[size + 0] = 17;
    lengths[size + 1] = 31;
    lengths[size + 2] = 73;
    lengths[size + 3] = 47;
    lengths[size + 4] = 23;
    size += 5;

    int list[256];
    for(int i = 0; i < 256; i++) {
        list[i] = i;
    }

    int pos = 0;
    int skip = 0;

    for(int round = 0; round < 64; round++) {
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
    }

    printf("Solution 10b: ");
    for(int i = 0; i < 256; i += 16) {
        int newValue = 0;
        for(int j = 0; j < 16; j++) {
            newValue ^= list[i+j];
        }
        printf("%02x", newValue);
    }
    printf("\n");
}
