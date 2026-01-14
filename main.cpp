#include <Arduino.h>
#include "main.h"

main::main(int bdrate){
  Serial.begin(bdrate);
}

bool main::init(int XStep, int XDir, int YStep, int YDir, int LimitX1, int LimitX2, int LimitY1, int LimitY2, int ScalingFactor){
  _XStep = XStep;
  _YStep = YStep;
  _XDir = XDir;
  _YDir = YDir;
  _LimitX1 = LimitX1;
  _LimitX2 = LimitX2;
  _LimitY1 = LimitY1;
  _LimitY2 = LimitY2;
  _ScalingFactor = ScalingFactor;

  pinMode(_LimitX1, INPUT_PULLUP);
  pinMode(_LimitY1, INPUT_PULLUP);
  pinMode(_LimitX2, INPUT_PULLUP);
  pinMode(_LimitY2, INPUT_PULLUP);
  pinMode(_XStep, OUTPUT);
  pinMode(_YStep, OUTPUT);
  pinMode(_XDir, OUTPUT);
  pinMode(_YDir, OUTPUT);

  return true;
}

bool main::home(){
  bool completed_x = false;
  bool completed_y = false;

  /*Directions */
  digitalWrite(_XDir, LOW);
  digitalWrite(_YDir, HIGH);
  Serial.println("homing!");
  /*Pulses*/
  for (int i = 0; i < 1000000000; i++){
    digitalWrite(_XStep, HIGH);
    delayMicroseconds(10);
    digitalWrite(_XStep, LOW);
    delayMicroseconds(TIME_OFF);


    if (digitalRead(_LimitX1) == LOW){ // when hit limit!
      Serial.println("HIT SWITCH");
      completed_x = true;
      break;
    }
  }

  for (int i = 0; i < 1000000000; i++){
    digitalWrite(_YStep, HIGH);
    delayMicroseconds(10);
    digitalWrite(_YStep, LOW);
    delayMicroseconds(TIME_OFF);

    if (digitalRead(_LimitY1) == LOW){ // when hit limit!
      completed_y = true;
      break;
    }
  }

  /*Debug Prints*/
  Serial.print("Completed X: ");
  Serial.println(completed_x);
  Serial.print("Completed Y: ");
  Serial.println(completed_y);
  _Cx = 0;
  _Cy = 0;
  return (completed_x && completed_y);
}

bool main::add_location(String name, int x_mm, int y_mm){
  int XSteps = x_mm/_ScalingFactor;
  int YSteps = y_mm/_ScalingFactor;

  Location loc = {name, XSteps, YSteps};

  locations[currentLocationNum] = loc;
  Serial.print("Added location at index: ");
  Serial.print(currentLocationNum);
  Serial.println(", with information:");
  Serial.print("Name: ");
  Serial.println(name);
  Serial.print("XStep: ");
  Serial.println(XSteps);
  Serial.print("YStep: ");
  Serial.println(YSteps);

  currentLocationNum++;
  return true;
}

void main::send_pulse(int pin, int time_on, int time_off){
  digitalWrite(pin, HIGH);
  delayMicroseconds(time_on);
  digitalWrite(pin, LOW);
  delayMicroseconds(time_off);
}

void main::update_dir(int sx, int sy){
  if (sx > 0) digitalWrite(_XDir, HIGH);
  if (sx < 0) digitalWrite(_XDir, LOW);
  if (sy > 0) digitalWrite(_YDir, LOW);
  if (sy < 0) digitalWrite(_YDir, HIGH);
}

void main::go_to(int XSteps, int YSteps){
  main::update_dir(XSteps, YSteps);

  for (int i = 0; i < abs(XSteps); i++) main::send_pulse(_XStep, 10, TIME_OFF);
  for (int i = 0; i < abs(YSteps); i++) main::send_pulse(_YStep, 10, TIME_OFF);

  _Cx += XSteps;
  _Cy += YSteps;
}

void main::go_to_locations(String locName){
  for (int locIndex = 0; locIndex < currentLocationNum; locIndex++){
    if (locations[locIndex].name != locName) continue;
    int x = locations[locIndex].Step_X;
    int y = locations[locIndex].Step_Y;

    int needed_x_steps = x - _Cx;
    int needed_y_steps = y - _Cy;
    
    Serial.println("Going to location.");

    go_to(needed_x_steps, needed_y_steps);
  }
}

// format: A plant1 500 1200 (name x y)
Location main::get_location_from_string(String line){
  Location loc;

  int firstSpace  = line.indexOf(' ');
  int secondSpace = line.indexOf(' ', firstSpace + 1);
  int thirdSpace  = line.indexOf(' ', secondSpace + 1);

  loc.name   = line.substring(firstSpace + 1, secondSpace);
  loc.Step_X = line.substring(secondSpace + 1, thirdSpace).toInt();
  loc.Step_Y = line.substring(thirdSpace + 1).toInt();

  return loc;
}

void main::get_from_serial(){
  if (Serial.available() > 0){
    String line = Serial.readString();
    line.trim();

    if (line.length() == 0) return;

    char letter = line[0];

    if (letter == 'A'){ // add location
      Location extraction = main::get_location_from_string(line);
      main::add_location(extraction.name, extraction.Step_X, extraction.Step_Y);
    }
    else if (letter == 'L'){ // location list
      Serial.println("List:");
      for (int i = 0; i < currentLocationNum; i++){
        Location loc = locations[i];
        Serial.print("Loc ");
        Serial.print(i);
        Serial.println(":");
        Serial.println(loc.name);
        Serial.println(loc.Step_X);
        Serial.println(loc.Step_Y);
        Serial.println("---------------------");
      }
    }
    else if (letter == 'G'){ // goto location
      int spaceIndex = line.indexOf(' ');
      String name = line.substring(spaceIndex + 1);
      main::go_to_locations(name);
    }
    else if (letter == 'R'){ // remove last location
      currentLocationNum--;
    }
    else{
      Serial.println("Command not found. Self distructing in 5 seconds.");
    }
  }
}
