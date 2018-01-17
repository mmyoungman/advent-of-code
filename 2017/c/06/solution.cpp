#include <stdio.h>
#include <stdlib.h>
#include "lib-mmy.h"

int main() {
   FILE *fp = fopen("input", "r"); 

   fseek(fp, 0, SEEK_END);
   long fsize = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   char *buffer = (char*)malloc(fsize + 1); 

   fread(buffer, fsize, 1, fp); 
   fclose(fp);

   int cycles = 0;

   int numblocks;
   char **blocks = str_split(buffer, '\t', &numblocks);
   blocks[numblocks-1][1] = '\0'; // remove trailing \n

   int *intblocks = (int*) malloc(sizeof(int) * numblocks);
   char *blockstate = (char*) malloc(sizeof(char));
   *blockstate = '\0';

   for(int i = 0; i < numblocks; i++) {
      intblocks[i] = str_toint(blocks[i]); 
      blockstate = (char*) realloc(blockstate, sizeof(char) * (str_len(blockstate) + str_len(blocks[i]) + 1));
      if(i != 0) str_concat(blockstate, ",");
      str_concat(blockstate, str_inttostr(intblocks[i]));
   }

   printf("%s\n", blockstate);

   // arr *a;
   // arr_init(a);


   // while intblocks hasn't been in this state before
   cycles++;
   int mpos = -1;
   int max = -1;
   for(int i = 0; i < numblocks; i++) {
      if(intblocks[i] > max) {
         mpos = i;
         max = intblocks[i];
      }
   }

   while(max > 0) {
      mpos++;
      intblocks[mpos % numblocks] += 1;
      max--;
   }
   // end while


   printf("Part One: %d\n", cycles);

   return 0;
}
