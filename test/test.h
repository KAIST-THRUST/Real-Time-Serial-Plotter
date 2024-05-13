#ifndef TEST_H
#define TEST_H

#include <Servo.h>

// Modify the constants here.
/*********************************************************************/
#define P_PIN1 A14  // pressure1 pin number
#define P_PIN2 A15  // pressure2 pin number
#define P_PIN3 A16  // pressure3 pin number
#define T_PIN1 A8   // temparature1 pin number
#define T_PIN2 A9   // temparature2 pin number
#define F_PIN A17   // flowmeter pin number
#define SERVO_PIN 9 // servo pin number

#define ROTATION_TIME 1500 // time elapsed when rotating 360 degrees
#define MAX_VOLTAGE 3.3    // maxinmum voltage of ADC
#define ADC_RESOLUTION 10  // resolution of ADC
#define R_MAGNITUDE 150.0  // magnitude of the electric resistance
#define MAX_TIME 10        // maximum execution time, in seconds
#define SENSOR_RATE 50     // sensor rate, in milliseconds
/*********************************************************************/

Servo servo;

unsigned long last_print_time = 0;

#endif
