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

   int numpassphrases;
   char **passphrases = str_split(buffer, '\n', &numpassphrases);
   int numvalidphrases = 0;

   for(int i = 0; i < numpassphrases; i++) {
      if(str_len(passphrases[i]) < 1) continue; // because of the empty line at the end of input file

      int numwords;
      char **words = str_split(passphrases[i], ' ', &numwords);

      for(int j = 0; j < numwords; j++) {
         str_sort(words[j]);
      }

      int valid = 1;
      for(int j = 0; j < numwords; j++) {
         for(int k = j+1; k < numwords; k++) {
            if (str_equal(words[j], words[k])) {
               valid = 0;
            }
         }
      }
      if(valid) {
         numvalidphrases++;
      }
   }

   printf("Part Two: %d\n", numvalidphrases);
   return 0;
}
