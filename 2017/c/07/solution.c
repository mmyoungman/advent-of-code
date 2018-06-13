#include "lib-mmy.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct pipe {
   char* name;
   int weight;
   char** children;
} pipe;

int getValue(int i, pipe* pipes) {
   if(arr_len(pipes[i].children) == 0) return pipes[i].weight;
   else {
      int result = pipes[i].weight;
      for(int j = 0; j < arr_len(pipes[i].children); j++) {
         for(int k = 0; k < arr_len(pipes); k++) {
            if(str_equal(pipes[i].children[j], pipes[k].name)) {
               result += getValue(k, pipes);
               break;
            }
         }
      }
      return result;
   }
}

int main() {
   FILE* fp = fopen("input", "r");

   fseek(fp, 0, SEEK_END);
   long fsize = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   char *buffer = (char *)malloc(fsize + 1);
   fread(buffer, fsize, 1, fp);
   fclose(fp);

   int numPipes;
   char** pipesData = str_split(buffer, '\n', &numPipes);
   numPipes--; // Because the last array element is a blank line

   pipe* pipes = NULL;

   for(int i = 0; i < numPipes; i++) {
      pipe* p = alloc(sizeof(pipe));

      int numDetails; 
      char** pipeDetails = str_split(pipesData[i], ' ', &numDetails);

      p->name = str_copy(pipeDetails[0]);

      char* weightStr = str_strip(pipeDetails[1], "()");
      p->weight = str_toint(weightStr);

      int numChildren = (numDetails <= 2) ? 0 : numDetails - 3;
      for(int j = 0; j < numChildren; j++) {
         arr_push(p->children, str_rstrip(pipeDetails[3 + j], ','));
      }

      arr_push(pipes, *p);
   }

   int index = -1;
   int newIndex = 0;
   while(index != newIndex) {
      index = newIndex;
      for(int i = 0; i < arr_len(pipes); i++) {
         for(int j = 0; j < arr_len(pipes[i].children); j++) {
            if(str_equal(pipes[index].name, pipes[i].children[j])) {
               newIndex = i;
               goto end;
            }
         }
      }
      end: ;
   }

   log_info("Solution Part One: %s", pipes[index].name);

   // With this info you can work out which pipe needs to be changed and to what...
   for(int i = 0; i < arr_len(pipes); i++) {
      if(arr_len(pipes[i].children) <= 0) continue;
      else {
         int* weights = 0;
         for(int j = 0; j < arr_len(pipes[i].children); j++) {
            for(int k = 0; k < arr_len(pipes); k++) {
               if(str_equal(pipes[i].children[j], pipes[k].name)) {
                  arr_push(weights, getValue(k, pipes));
               }
            }
         }
         for(int j = 0; j < arr_len(weights); j++) {
            if(weights[0] != weights[j]) {
               for(int k = 0; k < arr_len(weights); k++) {
                  printf("%s %d, ", pipes[i].children[k], weights[k]);
               }
               printf("\n");
               //dbg("Pipe name: %s, Weight: %d", pipes[i].children[j], weights[j]);
            }
         }
      }
   }
}
