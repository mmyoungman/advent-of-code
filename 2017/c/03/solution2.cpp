#include <stdio.h>
#include <stdlib.h>

struct coord {
   int x;
   int y;
   long value;
};

coord createcoord(int x, int y, long value) {
   coord *res = (coord*)malloc(sizeof(coord));
   res->x = x;
   res->y = y;
   res->value = value;
   return *res;
}

struct carray {
   int pos;
   int len;
   coord *coords;
};

void addtoarray(carray *ca, coord c) {
   if(ca->pos >= ca->len) {
      ca->len += 1024;
      ca->coords = (coord*) realloc(ca->coords, sizeof(coord) * ca->len);
   }
   ca->coords[ca->pos] = c;
   ca->pos++;
}

long getvalue(carray *ca, int x, int y ) {
   for(int i = 0; i <= ca->pos; i++) {
      if(x == ca->coords[i].x && y == ca->coords[i].y) {
         return ca->coords[i].value;
      }
   }
   return 0;
}

int main() {
   carray *ca = (carray*)malloc(sizeof(carray));
   ca->pos = 0;
   ca->len = 1024;
   ca->coords = (coord*)malloc(sizeof(coord) * 1024);

   int dir = 3; // 0 is east, 1 north, 2 west, 3 south
   int input = 312051;
   int inclen = 0;
   int count = 1;
   int length = 1;
   coord pos = createcoord(0, 0, 1);
   addtoarray(ca, createcoord(0, 0, 1));

   while(1) {
      dir = (dir + 1) % 4;
      int target = count + length;
      while(count < target) {
         switch(dir) {
            case 0:
               pos.x++; break;
            case 1:
               pos.y++; break;
            case 2:
               pos.x--; break;
            default:
               pos.y--; break;
         }
         count++;

         long value = 0;
         value += getvalue(ca, pos.x+1, pos.y);
         value += getvalue(ca, pos.x+1, pos.y+1);
         value += getvalue(ca, pos.x, pos.y+1);
         value += getvalue(ca, pos.x-1, pos.y+1);
         value += getvalue(ca, pos.x-1, pos.y);
         value += getvalue(ca, pos.x-1, pos.y-1);
         value += getvalue(ca, pos.x, pos.y-1);
         value += getvalue(ca, pos.x+1, pos.y-1);

         if(value > input) {
            printf("Part Two: %ld\n", value);
            return 0;
         }
         addtoarray(ca, createcoord(pos.x, pos.y, value));
      }

      if(inclen) {
         length++;
         inclen = 0;
      }
      else inclen = 1;
   }
   return 0;
}
