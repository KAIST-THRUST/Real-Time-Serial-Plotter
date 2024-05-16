#include "test.h"

float get_voltage(int raw) {
  return raw * (MAX_VOLTAGE / (pow(2, ADC_RESOLUTION) - 1));
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

void print_value_to_serial(unsigned long time) {
  float press1_v, press2_v, press3_v, temp1_v, temp2_v, flow_v;

  press1_v = get_pressure(get_voltage(analogRead(P_PIN1)));
  press2_v = get_pressure(get_voltage(analogRead(P_PIN2)));
  press3_v = get_pressure(get_voltage(analogRead(P_PIN3)));
  temp1_v = tc1.readTempC();
  temp2_v = tc2.readTempC();
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