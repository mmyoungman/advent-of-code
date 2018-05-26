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
   char* pipeChildren[numPipes];

   for(int i = 0; i < numPipes; i++) {
      int numDetails; 
      char** pipeDetails = str_split(pipes[i], ' ', &numDetails);
      for(int j = 0; j < str_len(pipeDetails[0])+1; j++) {
         pipeNames[i][j] = pipeDetails[0][j];
      }

      str_lstrip(pipeDetails[1], '(');
      str_rstrip(pipeDetails[1], ')');
      pipeWeights[i] = str_toint(pipeDetails[1]);

      if(numDetails == 2) { pipeChldNum[i] = 0; }
      else { pipeChldNum[i] = numDetails - 3; }

      // TODO: Store children names, which will need a dynamic array of strings

      // pipeChildren[i] = (char*)malloc(sizeof(char*) * 12 * pipeChldNum[i]);
      // for(int j = 0; j < pipeChldNum[i]; j++) {

      // } 

      dbg("Pipe name: %s, weight: %d, numChld: %d", 
          pipeNames[i], pipeWeights[i], pipeChldNum[i]);
   }
}
