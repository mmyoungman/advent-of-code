#include "lib-mmy.h"

int main() {
  FILE* fp = fopen("input", "r");
  if(fp == 0) {
    log_err("input file wasn't successfully opened!");
    return -1;
  }

  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buffer = malloc(fsize + 1);
  fread(buffer, fsize, 1, fp);
  fclose(fp);

  int dataSize;
  char** data = str_split(buffer, '\n', &dataSize);
  dataSize--;

  int twos = 0;
  int threes = 0;

  for(int i = 0; i < dataSize; i++) {
    HashTable *t = ht_create();

    for(int j = 0; j < str_len(data[i]); j++) {
      char *charStr = str_copy_char(data[i][j]);
      if(!ht_search(t, charStr)) {
        int *newValue = xmalloc(sizeof(int));
        *newValue = 1;
        ht_insert(t, charStr, newValue);
      } else {
        int *value = ht_search(t, charStr);
        (*value)++;
      }
      free(charStr);
    }

    int isTwo = 0;
    int isThree = 0;

    for(int j = 'a'; j <= 'z'; j++) {
      char *charStr = str_copy_char(j);
      int *value = ht_search(t, charStr);
      if(value) {
        if(*value == 2) { isTwo++; }
        if(*value == 3) { isThree++; }
      }
      free(charStr);
    }

    if(isTwo) { twos++; }
    if(isThree) { threes++; }

    ht_free(t);
  }
  
  log_info("Solution 2018 02a: %d", twos * threes);

  for(int i = 0; i < dataSize; i++) {
    for(int j = i; j < dataSize; j++) {
      if(i == j) continue;
      int numDiffs = 0;
      int charDiffPlace = 0;
      for(int k = 0; k < str_len(data[i]); k++) {
        if(data[i][k] != data[j][k]) { 
          numDiffs++;
          charDiffPlace = k;
        } 
      }
      if(numDiffs == 1) {
        log_info("Solution 2018 02b:");
        for(int k = 0; k < str_len(data[i]); k++) {
          if(k == charDiffPlace) continue;
          printf("%c", data[i][k]);
        }
        printf("\n");
        return 0;
      }
    }
  }
}
