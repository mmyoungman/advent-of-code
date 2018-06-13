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

int getValueFromName(char* name, pipe* pipes) {
   for(int i = 0; i < arr_len(pipes); i++) {
      if(str_equal(pipes[i].name, name)) return getValue(i, pipes);
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

   log_info("Solution Part One: %d, %s", index, pipes[index].name);

   // With this info you can work out which pipe needs to be changed and to what...
   while(1) {
      if(arr_len(pipes[index].children) == 0) {
         log_info("solution Part Two: %d, %s", index, pipes[index].name);
         return 0;
      }
      else if(arr_len(pipes[index].children) == 1) {
         for(int i = 0; i < arr_len(pipes); i++) {
            if(str_equal(pipes[i].name, pipes[index].children[0])) {
               index = i;
               continue;
            }
         }
      }

      // if all children have the same weight, return current index
      int value = getValueFromName(pipes[index].children[0], pipes);
      for(int i = 1; i < arr_len(pipes[index].children); i++) {
         if(value != getValueFromName(pipes[index].children[i], pipes)) {
            break;
         }
         if(i == arr_len(pipes[index].children) - 1) {
            log_info("Solution Part Two: %d, %s", index, pipes[index].name); 
            return 0;
         }
      }

      if(arr_len(pipes[index].children) == 2) {
         dbg("NO! I REFUSE TO WORK OUT WHICH ONE IS THE ODD ONE OUT!");
         dbg("Refusal to work with pipe: %d, %s", index, pipes[index].name);
         return 1;
      } else { // no of children > 2
         // Get the weights of the children
         int* weights = 0;
         for(int i = 0; i < arr_len(pipes[index].children); i++) {
            for(int j = 0; j < arr_len(pipes); j++) {
               if(str_equal(pipes[index].children[i], pipes[j].name)) {
                  arr_push(weights, getValue(j, pipes));
                  break;
               }
            }
         }
         // Find the odd one out
         int oddOne = 0;
         while(1) {
            for(int i = 0; i < arr_len(pipes[index].children); i++) {
               if(i != oddOne && weights[oddOne] == weights[i]) {
                  oddOne++;
                  continue;
               }
            }
            if(oddOne < arr_len(pipes[index].children)) {
               for(int i = 0; i < arr_len(pipes); i++) {
                  if(str_equal(pipes[index].children[oddOne], pipes[i].name)) {
                     index = i;
                     goto end2;
                  }
               }
            } else {
               log_info("(Part) Solution Part Two: %d, %s", index, pipes[index].name);
               return 0;
            }
         }
         end2: ;
      }
   }
}
