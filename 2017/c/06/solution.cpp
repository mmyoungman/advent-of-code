#include "lib-mmy.h"
#include <stdio.h>
#include <stdlib.h>

struct arr {
   int size;
   int capacity;
   char **data;
};

void arr_init(arr *a) {
   a->size = 0;
   a->capacity = 128;
   a->data = (char **)malloc(sizeof(char *) * 128);
}

void arr_append(arr *a, char *str) {
   if (a->size + 1 >= a->capacity) {
      a->capacity *= 2;
      a->data = (char **)realloc(a->data, sizeof(char *) * a->capacity);
   }
   a->data[a->size] = str;
   a->size++;
}

char *arr_get(arr *a, int pos) { return a->data[pos]; }

int arr_strinarr(arr *a, char *str) {
   for (int i = 0; i < a->size; i++) {
      if (str_equal(a->data[i], str)) {
         return 1;
      }
   }
   return 0;
}

int main() {
   FILE *fp = fopen("input", "r");

   fseek(fp, 0, SEEK_END);
   long fsize = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   char *buffer = (char *)malloc(fsize + 1);

   fread(buffer, fsize, 1, fp);
   fclose(fp);

   int cycles = 0;

   int numblocks;
   char **blocks = str_split(buffer, '\t', &numblocks);
   blocks[numblocks - 1][1] = '\0'; // remove trailing \n

   int *intblocks = (int *)malloc(sizeof(int) * numblocks);

   char *blockstate = (char *)malloc(sizeof(char)*256);
   *blockstate = '\0';
   for (int i = 0; i < numblocks; i++) {
      intblocks[i] = str_toint(blocks[i]);
      if (i != 0)
         str_concat(blockstate, ",");
      str_concat(blockstate, blocks[i]);
   }

   arr *a = (arr*) malloc(sizeof(arr));
   arr_init(a);

   while (!arr_strinarr(a, blockstate)) {
      arr_append(a, blockstate);
      cycles++;
      int mpos = -1;
      int max = -1;
      for (int i = 0; i < numblocks; i++) {
         if (intblocks[i] > max) {
            mpos = i;
            max = intblocks[i];
         }
      }

      intblocks[mpos] = 0;

      while (max > 0) {
         mpos++;
         intblocks[mpos % numblocks] += 1;
         max--;
      }

      blockstate = (char*) malloc(sizeof(char)*256);
      *blockstate = '\0';
      for (int i = 0; i < numblocks; i++) {
         char *addition = str_inttostr(intblocks[i]);
         if (i != 0) {
            str_concat(blockstate, ",");
         }
         char *newaddition = str_inttostr(intblocks[i]);
         str_concat(blockstate, newaddition);
      }
   }

   printf("Part One: %d\n", cycles);

   return 0;
}
