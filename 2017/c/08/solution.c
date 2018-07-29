#include "lib-mmy.h"
#include <stdio.h>
#include <stdlib.h>

int evaluate(HashTable *ht, char* key, char* comparitor, char* strValue) {
    int value = str_toint(strValue);
    if(str_equal(comparitor, "==")) {
        return *(int*)ht_search(ht, key) == value;
    } else if(str_equal(comparitor, "!=")) {
        return *(int*)ht_search(ht, key) != value;
    } else if(str_equal(comparitor, "<")) {
        return *(int*)ht_search(ht, key) < value;
    } else if(str_equal(comparitor, "<=")) {
        return *(int*)ht_search(ht, key) <= value;
    } else if(str_equal(comparitor, ">")) {
        return *(int*)ht_search(ht, key) > value;
    } else if(str_equal(comparitor, ">=")) {
        return *(int*)ht_search(ht, key) >= value;
    }
}

int getMax(HashTable *ht) {
    int maxValue = 0;
    for(int i = 0; i < ht->cap; i++) {
        if(ht->keys[i] && *(int*)(ht->values[i]) > maxValue) {
            maxValue = *(int*)(ht->values[i]);
        }
    }
    return maxValue;
}

int main() {
    FILE* fp = fopen("input", "r");

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);

    int numLines;
    char** data = str_split(buffer, '\n', &numLines);
    numLines--;

    HashTable *ht = ht_create();

    int overallMax = 0;

    for(int i = 0; i < numLines; i++) {
        int lineSize;
        char** line = str_split(data[i], ' ', &lineSize);

        if(!ht_search(ht, line[0])) {
            int *newValue = xmalloc(sizeof(int));
            *newValue = 0;
            ht_insert(ht, line[0], newValue);
        }
        if(!ht_search(ht, line[4])) {
            int *newValue = xmalloc(sizeof(int));
            *newValue = 0;
            ht_insert(ht, line[4], newValue);
        }

        if(evaluate(ht, line[4], line[5], line[6])) {
            int *value = xmalloc(sizeof(int));
            *value = *(int*)ht_search(ht, line[0]);
            if(str_equal(line[1], "inc")) {
                *value += str_toint(line[2]);
            } else if(str_equal(line[1], "dec")) {
                *value -= str_toint(line[2]);
            }
            ht_insert(ht, line[0], value);
        }

        if(getMax(ht) > overallMax) {
            overallMax = getMax(ht);
        }
    }

    char* maxName = 0;
    int maxValue = 0;
    for(int i = 0; i < ht->cap; i++) {
        if(ht->keys[i] && *(int*)(ht->values[i]) > maxValue) {
            maxName = ht->keys[i];
            maxValue = *(int*)(ht->values[i]);
        }
    }
    dbg("Solution 8a, Name: %s, Value: %d", maxName, maxValue);
    dbg("Solution 8b, Value: %d", overallMax);
}
