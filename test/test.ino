#include "test.h"

static NonBlockingServo ser;
static unsigned long last_print_time = 0;
static int degree = 0;

void setup() {
  // analogReadRes(ADC_RESOLUTION);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  ser.attach(SERVO_PIN);
  ser.write(0);
}

void loop() {
  if (Serial.available())
    degree = Serial.parseInt();
  if (ser.isavailable())
    ser.rotate(degree);
  unsigned long current_time = millis();
  // Update every SENSOR_RATE time.
  if (current_time - last_print_time >= SENSOR_RATE &&
      last_print_time < MAX_TIME * 1000) {
    print_value_to_serial(current_time);
    last_print_time = current_time;
  }
  // If time is out, then turn on the LED on the board.
  else if (last_print_time > MAX_TIME * 1000) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
