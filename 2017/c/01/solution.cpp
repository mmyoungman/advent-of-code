#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   FILE *fp = fopen("input", "r"); 

   fseek(fp, 0, SEEK_END);
   long fsize = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   char *buffer = (char*)malloc(fsize + 1); 
   fgets(buffer, fsize, fp); 
   fclose(fp);
   // printf("%s", buffer);

   int result = 0;
   char *pos = buffer;

   while(true) {
      if(*(pos + 1) == '\0') {
         if(*buffer == *pos) {
            result += *pos - 48;
         }
         break;
      }
      else if(*pos == *(pos + 1)) {
         result += *pos - 48;
      }
      pos++;
   }

   printf("Part One: %d\n", result);

   result = 0;
   pos = buffer;
   char *pos2 = buffer + (strlen(buffer)/2);

   while(true) {
      if(*pos == *pos2) {
         result += *pos - 48;
      }

      if(*(pos + 1) == '\0') {
         break;
      }
      else {
         if(*(pos2 + 1) == '\0') {
            pos2 = buffer;
         }
         else {
            pos2++;
         }
         pos++;
      }
   }

   printf("Part Two: %d\n", result);

   return 0;
}
