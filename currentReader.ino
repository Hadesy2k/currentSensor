float zero_sensor;  // calibrate sensor with null current
float effective_voltage = 230;   // Singapore: 230V


void setup(void) {
    // Serial speed
    Serial.begin(9600);
    zero_sensor = getSensorValue(A0);  // A0 analog pin
}


void loop() {
    float sensor_value = getSensorValue(A0);  // A0 analog pin
    int power = getPower(sensor_value);
    Serial.println("Power: " + String(power) + "W");
}


int getPower(float sensor_value) {
    float amplitude_current = (float)(sensor_value-zero_sensor)/1024*5/185*1000000;
    float effective_value = amplitude_current / 1.414;
    float effective_power = abs(effective_value*effective_voltage/1000);

    int power = (int)effective_power;
    return power;
}


float getSensorValue(int pin) {
    // current sensor use Analog
    int sensorValue;
    float avgSensor = 0;
    int nb_measurements = 500;

    for (int i=0; i<nb_measurements; i++) {
        sensorValue = analogRead(pin);
        avgSensor = avgSensor + float(sensorValue);
    }

    avgSensor = avgSensor / float(nb_measurements);
    return avgSensor;
}
