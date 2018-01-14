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

   int numpassphrases;
   char **passphrases = str_split(buffer, '\n', &numpassphrases);
   int numvalidphrases = 0;

   for(int i = 0; i < numpassphrases; i++) {
      if(str_len(passphrases[i]) < 1) continue;

      int numwords;
      char **words = str_split(passphrases[i], ' ', &numwords);

      for(int j = 0; j < numwords; j++) {
         for(int k = 0; k < str_len(words[j]); k++) {
            for(int l = 0; l < str_len(words[j]); l++) {
               if(l == k) continue;
               else {
                  if(words[j][k] > words[j][l]) {
                     char temp = words[j][k];
                     words[j][k] = words[j][l];
                     words[j][l] = temp;
                  }
               }
            }
         }
      }

      int valid = 1;
      for(int j = 0; j < numwords; j++) {
         for(int k = 0; k < numwords; k++) {
            if(j == k) continue;
            else {
               if(str_equal(words[j], words[k])) {
                  valid = 0;
               }
            }
         }
      }
      if(valid) {
         numvalidphrases++;
      }
   }

   printf("Part One: %d\n", numvalidphrases);
   return 0;
}
