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
   
   int result = 0;
   int high, low;

   while(1) {
      if(*buffer == '\0') {
         break;
      }
      else if(*buffer == '\t') {
         //printf("\n");
         buffer++;
      }
      else if(*buffer == '\n') {
         result += high - low;
         high = 0;
         low = 0;

         //printf("\nChecksum End!\n");
         buffer++;
      }
      else {
         char strvalue[128];
         int pos = 0;
         while(*buffer >= 48 && *buffer <= 57) {
            strvalue[pos] = *buffer; 
            pos++;
            buffer++;
         }
         strvalue[pos] = '\0';
         //printf("%s\n", strvalue);
         int value = str_toint(strvalue);
         if(!high || value > high) {
            high = value;
         }
         if(!low || value < low) {
            low = value;
         }
         //printf("%d", value);
      }
   }

   printf("Part One: %d\n", result);
   return 0;
}
