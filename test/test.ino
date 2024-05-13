#include "test.h"

float get_voltage(int raw) {
  return raw * (MAX_VOLTAGE / (pow(2, ADC_RESOLUTION) - 1));
}

float get_temperature(float voltage) {
  return (voltage - 1.25) / 0.005;
}

float get_pressure(float voltage) {
  // Convert voltage to current (in mA)
  float current = voltage / R_MAGNITUDE * 1000.0;
  return ((current - 4.0) * 68.95 / 16.0);
}

// 4~20mA = 0~833g/s
float get_flow(float voltage) {
  // Convert voltage to current (in mA)
  float current = voltage / R_MAGNITUDE * 1000.0;
  return ((current - 4.0) * 833.0 / 16.0);
}

void open_valve() {
  int current_degree = servo.read();
  servo.write(90);
  delay(ROTATION_TIME * abs(current_degree - 90) / 360);
}

void close_valve() {
  int current_degree = servo.read();
  servo.write(0);
  delay(ROTATION_TIME * abs(current_degree) / 360);
}

void print_value_to_serial(unsigned long time) {
  float press1_v, press2_v, press3_v, temp1_v, temp2_v, flow_v;

  press1_v = get_pressure(get_voltage(analogRead(P_PIN1)));
  press2_v = get_pressure(get_voltage(analogRead(P_PIN2)));
  press3_v = get_pressure(get_voltage(analogRead(P_PIN3)));
  temp1_v = get_temperature(get_voltage(analogRead(T_PIN1)));
  temp2_v = get_temperature(get_voltage(analogRead(T_PIN2)));
  flow_v = get_flow(get_voltage(analogRead(F_PIN)));

  // Print in CSV format into the serial.
  Serial.print(time);
  Serial.print(",");
  Serial.print(press1_v);
  Serial.print(",");
  Serial.print(press2_v);
  Serial.print(",");
  Serial.print(press3_v);
  Serial.print(",");
  Serial.print(temp1_v);
  Serial.print(",");
  Serial.print(temp2_v);
  Serial.print(",");
  Serial.println(flow_v);
}

void setup() {
  // analogReadRes(ADC_RESOLUTION);
  servo.attach(9, 500, 2600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  open_valve();
  close_valve();
  open_valve();
}

void loop() {
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
