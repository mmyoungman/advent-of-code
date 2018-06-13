#include "lib-mmy.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
   FILE *fp = fopen("input", "r");

   fseek(fp, 0, SEEK_END);
   long fsize = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   char *buffer = (char *)malloc(fsize + 1);
   fread(buffer, fsize, 1, fp);
   fclose(fp);

   int numPipes;
   char **pipes = str_split(buffer, '\n', &numPipes);
   numPipes--; // Because the last split is a blank line

   char pipeNames[numPipes][16];
   int pipeWeights[numPipes];
   int pipeChldNum[numPipes];
   char** pipeChildren[numPipes]; // I'm assuming this memory is initialised to zero

   for(int i = 0; i < numPipes; i++) {
      int numDetails; 
      char** pipeDetails = str_split(pipes[i], ' ', &numDetails);
      for(int j = 0; j < str_len(pipeDetails[0])+1; j++) {
         pipeNames[i][j] = pipeDetails[0][j];
      }        

      pipeDetails[1] = str_lstrip(pipeDetails[1], '(');
      str_rstrip(pipeDetails[1], ')');
      pipeWeights[i] = str_toint(pipeDetails[1]);

      if(numDetails == 2) { pipeChldNum[i] = 0; }
      else { pipeChldNum[i] = numDetails - 3; }

      for(int j = 0; j < pipeChldNum[i]; j++) {
         arr_push(pipeChildren[i], str_rstrip(pipeDetails[3 + j], ','));
      }
   }

   int index = -1;
   int newIndex = 0;
   while(index != newIndex) {
      index = newIndex;
      for(int i = 0; i < numPipes; i++) {
         for(int j = 0; j < arr_len(pipeChildren[i]); j++) {
            if(str_equal(pipeNames[index], pipeChildren[i][j])) {
               newIndex = i;
               goto end;
            }
         }
      }
      end: ;
   }

   log_info("Solution Part One: %s", pipeNames[index]);
}
