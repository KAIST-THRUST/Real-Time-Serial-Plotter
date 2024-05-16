#include "test.h"

static NonBlockingServo serv;
static unsigned long last_print_time = 0;
static int degree = 0;

void setup() {
  // analogReadRes(ADC_RESOLUTION);
  Serial.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
  serv.attach(SERVO_PIN);
  serv.write(0);
}

void loop() {
  /* Servo part. */
  /*******************************************************************/
  // Read data from serial if sent
  if (Serial.available()) {
    Serial.readBytes((char *)&degree, 1);
  }
  // Rotate servo if it is not rotating
  if (!serv.isrotating()) {
    serv.rotate(degree);
  }
  /*******************************************************************/

  /* Sensor update part. */
  /*******************************************************************/
  unsigned long current_time = millis();
  // Update every SENSOR_RATE time.
  if (current_time - last_print_time >= SENSOR_RATE &&
      last_print_time < MAX_TIME * 1000) {
    print_value_to_serial(current_time);
    last_print_time = current_time;
  }
  // // If time is out, then turn on the LED on the board.
  // else if (last_print_time > MAX_TIME * 1000) {
  //   digitalWrite(LED_BUILTIN, HIGH);
  // }
  /*******************************************************************/
}
