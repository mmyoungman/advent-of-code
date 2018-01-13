#include <stdio.h>

int main() {
   int input = 312051;
   int count = 1;
   int inclen = 0;
   int length = 1;
   int x = 0;
   int y = 0;
   int dir = 3; // 0 is east, 1 north, 2 west, 3 south

   while(1) {
      dir = (dir + 1) % 4;
      int target = count + length; 
      while(count < target) {
         switch(dir) {
            case 0: 
               x++; break;
            case 1: 
               y++; break;
            case 2: 
               x--; break;
            default: 
               y--; break;
         }
         count++;
         if(count == input) {
            if(x < 0) x = -x;
            if(y < 0) y = -y;
            printf("Part One: %d\n", x + y);
            return 0;
         }
      }
      if(inclen) {
         length++;
         inclen = 0;
      }
      else inclen = 1;
   }
   return 0;
}
