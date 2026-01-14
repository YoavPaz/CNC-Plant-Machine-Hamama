#ifndef MAIN_H
#define MAIN_H

struct Location{
  String name;
  int Step_X;
  int Step_Y;
};

class main{
  public:
  main(int bdrate);
  bool init(int XStep, int XDir, int YStep, int YDir, int LimitX1, int LimitX2, int LimitY1, int LimitY2, int ScalingFactor);
  bool home();
  bool add_location(String name, int x_mm, int y_mm);
  void go_to(int XSteps, int YSteps);
  void send_pulse(int pin, int time_on, int time_off);
  void update_dir(int sx, int sy);
  void go_to_locations(String locName);
  void get_from_serial();
  Location get_location_from_string(String line);
  private:
  int _ScalingFactor;

  int _XStep;
  int _XDir;

  int _YStep;
  int _YDir;

  int _LimitX1;
  int _LimitX2;
  int _LimitY1;
  int _LimitY2;

  int _Cx;
  int _Cy;

  const int TIME_OFF = 1000;

  static const int MAX_LOCATIONS = 20;
  Location locations[MAX_LOCATIONS];
  int currentLocationNum = 0;
};

#endif
