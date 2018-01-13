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

   //printf("%s\n", buffer);
   
   int numchecksums;
   char **checksums = str_split(buffer, '\n', &numchecksums);

   int result = 0;
   for(int i = 0; i < numchecksums; i++) {
      int numvalues;
      char **values = str_split(checksums[i], '\t', &numvalues);
      for(int j = 0; j < numvalues; j++) {
         for(int k = 0; k < numvalues; k++) {
            if(j == k) {
               continue;
            }
            if(str_toint(values[j]) % str_toint(values[k]) == 0) {
               result += str_toint(values[j]) / str_toint(values[k]);
               break;
            }
         }
      }
   }

   printf("Part Two: %d\n", result);

   return 0;
}
