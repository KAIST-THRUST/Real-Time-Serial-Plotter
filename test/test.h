#ifndef TEST_H
#define TEST_H

#include <Servo.h>

// Modify the constants here.
/*********************************************************************/
#define P_PIN1 A14  // pressure1 pin number
#define P_PIN2 A15  // pressure2 pin number
#define P_PIN3 A16  // pressure3 pin number
#define T_PIN1 A8   // temperature1 pin number
#define T_PIN2 A9   // temperature2 pin number
#define F_PIN A17   // flowmeter pin number
#define SERVO_PIN 9 // servo pin number

#define ROTATION_SPEED 0.2 // rotation speed in (degree/ms)
#define MAX_VOLTAGE 3.3    // maximum voltage of ADC
#define ADC_RESOLUTION 10  // resolution of ADC
#define R_MAGNITUDE 150.0  // magnitude of the electric resistance
#define MAX_TIME 3600        // maximum execution time, in seconds
#define SENSOR_RATE 25     // sensor rate, in milliseconds
/*********************************************************************/

class NonBlockingServo {
private:
  Servo servo;
  int target_degree;
  int current_degree;
  unsigned long prev_move_time;

public:
  NonBlockingServo();
  void write(int degree);
  void attach(int pin);
  void rotate(int degree);
  bool isrotating();
};

void print_value_to_serial(unsigned long time);

#endif
