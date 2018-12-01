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

  int freq = 0;
  for(int i = 0; i < size; i++) {
    if(data[i][0] == '+') {
      freq += str_toint(str_lstrip(data[i], '+'));
    } else { // it is '-'
      freq += str_toint(data[i]);
    }
  }

  dbg("Solution 2018 01a: %d", freq);

  freq = 0;
  int *freq_arr = 0;

  while(1) {
    for(int i = 0; i < size; i++) {
      arr_push(freq_arr, freq);

      if(data[i][0] == '+') {
        freq += str_toint(str_lstrip(data[i], '+'));
      } else { // it is '-'
        freq += str_toint(data[i]);
      }

      for(int j = 0; j < arr_len(freq_arr); j++) {
        if(freq_arr[j] == freq) {
          dbg("Solution 2018 01b: %d", freq);
          return 0; 
        }
      }
    }
  }
}
