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

  int fabric[1024][1024];

  for(int x = 0; x < 1024; x++) {
    for(int y = 0; y < 1024; y++) {
      fabric[x][y] = 0;
    }
  }

  int **claims = 0;
  for(int i = 0; i < dataSize; i++) {
    int splitSize;
    char **line = str_split(data[i], ' ', &splitSize);
    line[2] = str_rstrip(line[2], ':');
    char **position = str_split(line[2], ',', &splitSize);
    char **size = str_split(line[3], 'x', &splitSize);

    int *claim = 0;
    arr_push(claim, str_toint(position[0])); // posX
    arr_push(claim, str_toint(size[0])); // lenX
    arr_push(claim, str_toint(position[1])); // posY
    arr_push(claim, str_toint(size[1])); // lenY

    arr_push(claims, claim);
  }

  for(int i = 0; i < dataSize; i++) {
    for(int x = claims[i][0]; x < (claims[i][0] + claims[i][1]); x++) {
      for(int y = claims[i][2]; y < (claims[i][2] + claims[i][3]); y++) {
        fabric[x][y]++;
      }
    }
  }

  int solutionA = 0;
  for(int x = 0; x < 1024; x++) {
    for(int y = 0; y < 1024; y++) {
      if(fabric[x][y] >= 2) {
        solutionA++;
      }
    }
  }
  log_info("Solution 2018 03a: %d", solutionA);

  for(int i = 0; i < dataSize; i++) {
    int noOverlap = 1;
    for(int x = claims[i][0]; x < (claims[i][0] + claims[i][1]); x++) {
      for(int y = claims[i][2]; y < (claims[i][2] + claims[i][3]); y++) {
        if(fabric[x][y] != 1) { noOverlap = 0; }
      }
    }
    if(noOverlap) {
      log_info("Solution 2018 03b: %d", i + 1);
      return 0;
    }
  }
}
