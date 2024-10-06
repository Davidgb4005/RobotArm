#include <Arduino.h>
#include "Stepper_lib.h"
stepper_motor::stepper_motor(const int EN_pin, const int dir_pin, const int step_pin, const int ENC_pin, const int max_angle) {


  _EN_pin = EN_pin;
  _dir_pin = dir_pin;
  _step_pin = step_pin;
  pinMode(EN_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, INPUT_PULLUP);
  digitalWrite(EN_pin, 0);
}
stepper_motor::stepper_motor() {
}

void stepper_motor::PinSet(const int EN_pin, const int dir_pin, const int step_pin, const int ENC_pin, const int max_angle) {
  _EN_pin = EN_pin;
  _dir_pin = dir_pin;
  _step_pin = step_pin;
  _max_angle = max_angle;
  pinMode(EN_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, INPUT_PULLUP);
  digitalWrite(EN_pin, 0);
}

void stepper_motor::setDrive(const int steps, const uint32_t& dir, const uint32_t& speed, const uint32_t& ramp) {
  _driveVarPointer->_steps = steps;
  _driveVarPointer->_dir = dir;
  _driveVarPointer->_speed = speed;
  _driveVarPointer->_ramp = ramp;
}

void stepper_motor::setSlave(stepper_motor& stepperMaster, bool motor_inverse) {
  _driveVarPointer = &(stepperMaster.drive_variables);
  _slaveMode = 1;
  _motor_inverse = motor_inverse;
}

void stepper_motor::drive_motor() {
  if (_motor_inverse == 0) {
    digitalWrite(_dir_pin, _driveVarPointer->_dir);
  } else {
    digitalWrite(_dir_pin, abs(_driveVarPointer->_dir - 1));
  }
  int speed = _driveVarPointer->_speed + _driveVarPointer->_ramp/20;

  if ((_timer + speed) < micros() && _driveVarPointer->_steps > 0 && ((50 <= _step_position && _driveVarPointer->_dir == 0) || (_step_position < _max_angle - 50 && _driveVarPointer->_dir == 1) or _driveVarPointer->_override == 1)) {
    if (_driveVarPointer->_ramp>0 && _driveVarPointer->_steps>2000 && _slaveMode != 1){
     _driveVarPointer-> _ramp--;
    }
    if (_driveVarPointer->_steps<2000 && _slaveMode != 1){
      _driveVarPointer->_ramp++;
    }
    digitalWrite(_step_pin, flip_flop);
    flip_flop = abs(flip_flop - 1);
    _timer = micros();
    if (_driveVarPointer->_dir == 1) {
      _step_position = _step_position + 1;
    }
    if (_driveVarPointer->_dir == 0) {
      _step_position = _step_position - 1;
    }
    if (_slaveMode != 1) {
      _driveVarPointer->_steps = _driveVarPointer->_steps - 1;
    }
  }
}
void stepper_motor::homming() {
}
void stepper_motor::overrideON() {
  _driveVarPointer->_override = 1;
}
void stepper_motor::overrideOFF() {
    _driveVarPointer->_override = 0;
}
