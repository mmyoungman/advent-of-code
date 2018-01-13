#include <fcntl.h>
#include <stdio.h>

int strlen(char* str) {
  char* strPtr = str;
  while(*strPtr != '\0') { strPtr++; }
  return strPtr - str;
}

int main() {
   int fd = open("input", O_RDONLY);
   if(fd < 0) {
      return 1;
   }
   
   int chunkLen = 1024;
   char chunk[chunkLen];
   int bytesRead;
   while(1) {
      bytesRead = read(fd, &chunk, chunkLen);
      if(bytesRead < 0) { // error
         return 1;
      }
      else if(bytesRead == 0) { // nothing left to be read
         break;
      }
      else if(bytesRead == chunkLen) { // read chunkLen characters
         // Do something?
      }
      else { // i.e. less than chunkLen left to be read and not zero remaining
         chunk[bytesRead] = '\0';
      }
   }

   int res = close(fd);
   if(res < 0) {
      return 1;
   }

   return 0;
}
