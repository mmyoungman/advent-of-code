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

}
