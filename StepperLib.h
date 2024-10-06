#include <Arduino.h>

#ifndef STEPPER_LIB_H
#define STEPPER_LIB_H

struct driveInputs {
  int _dir;
  int _speed;
  int _steps;
  int _ramp;
  int _override;
};

class stepper_motor {
public:
  //constructor
  stepper_motor(const int EN_pin, const int dir_pin, const int step_pin, const int ENC_pin, const int max_angle);
  stepper_motor();
  //methods
  void PinSet(const int EN_pin, const int dir_pin, const int step_pin, const int ENC_pin, const int max_angle);
  void drive_motor();
  long enc_update();
  long get_step_enc();
  long get_step_cal();
  void homming();
  void overrideON();
  void overrideOFF();
  void setSlave( stepper_motor& stepperMaster, bool motor_inverse);
  void setDrive(const int steps, const uint32_t& dir, const uint32_t& speed, const uint32_t& ramp);


private:
  // Parameter pointers
  driveInputs drive_variables;
  driveInputs* _driveVarPointer= &drive_variables;

  //I/O Pins
  int _full_turn_steps;
  int _EN_pin;
  int _dir_pin;
  int _step_pin;
  int _ENC_pin;

  //drive parameters
  int _slaveMode = 0;
  int _motor_inverse = 0;
  int _max_angle=40000;
  uint32_t _timer;
  int _step_position = 0;
  int flip_flop=0;
};

#endif
