#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   FILE *fp = fopen("input", "r"); 

   fseek(fp, 0, SEEK_END);
   long fsize = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   char *buffer = (char*)malloc(fsize + 1); 
   fread(buffer, fsize, 1, fp); 
   fclose(fp);
   printf("%s\n", buffer);

   return 0;
}
