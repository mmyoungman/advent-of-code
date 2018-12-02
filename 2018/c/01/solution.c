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

  int *input_arr = 0;

  for(int i = 0; i < size; i++) {
    arr_push(input_arr, str_toint(data[i]));
  }

  int freq = 0;
  for(int i = 0; i < arr_len(input_arr); i++) {
    freq += input_arr[i];
  }

  log_info("Solution 2018 01a: %d", freq);

  freq = 0;
  HashTable *t = ht_create();
  int *value = xmalloc(sizeof(int));
  *value = 1;

  while(1) {
    for(int i = 0; i < arr_len(input_arr); i++) {
      char *freqStr = str_inttostr(freq);
      ht_insert(t, freqStr, value);
      free(freqStr);

      freq += input_arr[i];

      freqStr = str_inttostr(freq);
      if(ht_search(t, freqStr)) {
        log_info("Solution 2018 01b: %d", freq);
        return 0;
      }
      free(freqStr);
    }
  }
}
