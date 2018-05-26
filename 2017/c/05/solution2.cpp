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

   // printf("%s\n", buffer);

   int numinstructs;
   char **instructs = str_split(buffer, '\n', &numinstructs);
   numinstructs--; // because input file has empty line as last line
   int numsteps = 0;
   int pos = 0;

   int *intinstructs = (int*) malloc(sizeof(int) * numinstructs);
   for(int i = 0; i < numinstructs; i++) {
      intinstructs[i] = str_toint(instructs[i]);
   }

   while(pos >= 0 && pos < numinstructs) {
      int jump = intinstructs[pos];
      if(intinstructs[pos] > 2) intinstructs[pos]--;
      else intinstructs[pos]++;
      pos += jump;
      numsteps++;
   }

   printf("Part Two: %d\n", numsteps);
   return 0;
}
