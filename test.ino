#include <Servo.h>

#define P_PIN1 A10 // pressure1
#define P_PIN2 A11 // pressure2
#define P_PIN3 A12 // pressure3

#define T_PIN1 A0 // temparature1
#define T_PIN2 A1 // temparature2

#define F_PIN A2           // flowmeter
#define SERVO_PIN 9        // servo pin use
#define ROTATION_TIME 1500 // time elapsed when rotating 360 degrees

#define MAX_VOLTAGE 3.3
#define ADC_RESOLUTION 10

Servo servo;

float get_voltage(int raw) {
    return raw * (MAX_VOLTAGE / (pow(2, ADC_RESOLUTION) - 1));
}

float get_temperature(float voltage) {
    return (voltage - 1.25) / 0.005;
}

float get_pressure(float voltage) {
    float current = voltage / 250.0 * 1000; // Convert voltage to current (in mA)
    return ((current - 4.0) * 1000.0 / 16.0);
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

void setup() {
    // analogReadRes(ADC_RESOLUTION);
    servo.attach(9, 500, 2600);
    Serial.begin(9600);
    open_valve();
    close_valve();
    open_valve();
}

void loop() {
    float press1_v, press2_v, press3_v, temp1_v, temp2_v, flow_v;

    press1_v = get_pressure(get_voltage(analogRead(P_PIN1)));
    press2_v = get_pressure(get_voltage(analogRead(P_PIN2)));
    press3_v = get_pressure(get_voltage(analogRead(P_PIN3)));
    temp1_v = get_temperature(get_voltage(analogRead(T_PIN1)));
    temp2_v = get_temperature(get_voltage(analogRead(T_PIN2)));
    flow_v = get_voltage(analogRead(F_PIN));

    // Print in CSV format into the serial.
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

    // Delay 50ms.
    delay(50);
}
