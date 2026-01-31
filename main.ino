#include "main.h"

main m(115200);

#define YSTEP 6
#define YDIR 7

#define XSTEP 3
#define ZSTEP 5
#define XDIR 2
#define ZSTEP 4
#define XLIMIT1 9
#define XLIMIT2 8
#define YLIMIT1 11
#define YLIMIT2 10

void setup(){
  Serial.begin(115200);
  m.init(XSTEP, XDIR, YSTEP, YDIR, XLIMIT1, XLIMIT2, YLIMIT1, YLIMIT2, 1);
  m.home();
}

void loop(){
  m.get_from_serial();
}
