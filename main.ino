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
  m.add_location("pl1", 200, 1500); // absolute location from 0 0 (use fuction step to mm to choose mm)
  m.add_location("pl2", 200, 3000);
  m.add_location("pl3", 200, 4500);

  m.add_location("pl4", 800, 1500);
  m.add_location("pl5", 800, 3000);
  m.add_location("pl6", 800, 4500);

  m.add_location("pl7", 1400, 1500);
  m.add_location("pl8", 1400, 3000);
  m.add_location("pl9", 1400, 4500);

  m.add_location("pl10", 2200, 1500);
  m.add_location("pl11", 2200, 3000);
  m.add_location("pl12", 2200, 4500);

  m.add_location("pl13", 2800, 1500);
  m.add_location("pl14", 2800, 3000);
  m.add_location("pl15", 2800, 4500);

  Serial.println("Finished defining plants locations.");
  
  m.go_to_locations("pl1");
  delay(200);
  m.go_to_locations("pl2");
  delay(200);
  m.go_to_locations("pl3");
  delay(200);
  m.go_to_locations("pl4");
  delay(200);
  m.go_to_locations("pl5");
  delay(200);
  m.go_to_locations("pl6");
  delay(200);
  m.go_to_locations("pl7");
  delay(200);
  m.go_to_locations("pl8");
  delay(200);
  m.go_to_locations("pl9");
  delay(200);
  m.go_to_locations("pl10");
  delay(200);
  m.go_to_locations("pl11");
  delay(200);
  m.go_to_locations("pl12");
  delay(200);
  m.go_to_locations("pl13");
  delay(200);
  m.go_to_locations("pl14");
  delay(200);
  m.go_to_locations("pl15");
  delay(200);
}

void loop(){
  m.get_from_serial();
}
