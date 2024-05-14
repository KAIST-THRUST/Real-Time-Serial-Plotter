#include "test.h"

NonBlockingServo::NonBlockingServo() {
  target_degree = 0;
  current_degree = 0;
  prev_move_time = millis();
}

void NonBlockingServo::write(int pin) {
  servo.write(pin);
}

void NonBlockingServo::attach(int pin) {
  servo.attach(pin);
}

void NonBlockingServo::rotate(int degree) {
  target_degree = degree;
  write(target_degree);
  prev_move_time = millis();
}

bool NonBlockingServo::isrotating() {
  int time_interval = millis() - prev_move_time;
  int degree_difference = abs(target_degree - current_degree);
  if (time_interval * ROTATION_SPEED > degree_difference) {
    return false;
  }
  return true;
}
