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

    int x = 0;
    int y = 0;
    int z = 0;

    int max = 0;
    for(int i = 0; i < size; i++) {
        if(str_equal(data[i], "n")) {
            y++, z--;
        } else if(str_equal(data[i], "ne")) {
            x++, z--;
        } else if(str_equal(data[i], "se")) {
            x++, y--;
        } else if(str_equal(data[i], "s")) {
            y--, z++;
        } else if(str_equal(data[i], "sw")) {
            x--, z++;
        } else if(str_equal(data[i], "nw")) {
            x--; y++;
        }

        if(max < (mth_abs(x) + mth_abs(y) + mth_abs(z)) / 2) {
            max = (mth_abs(x) + mth_abs(y) + mth_abs(z)) / 2;
        }
    }

    dbg("Solution 11a 2017: %d", (mth_abs(x) + mth_abs(y) + mth_abs(z)) / 2);
    dbg("Solution 11b 2017: %d", max);
}
