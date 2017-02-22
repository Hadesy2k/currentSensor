float zero_sensor;  // calibrate sensor with null current
float effective_voltage = 230;   // Singapore: 230V
int Relay = 3;  // analog pin


void setup(void) {
    // Serial speed
    Serial.begin(9600);
    zero_sensor = getSensorValue(A0);  // A0 analog pin

    pinMode(13, OUTPUT);         //Set Pin13 as output
    digitalWrite(13, HIGH);     //Set Pin13 High
    pinMode(Relay, OUTPUT);     //Set Pin3 as output
}


void loop() {
    digitalWrite(Relay, HIGH);   //Turn off relay
    delay(4000);

    digitalWrite(Relay, LOW);    //Turn on relay
    float sensor_value = getSensorValue(A0);  // A0 analog pin

    float current = fabs(getCurrent(sensor_value, 0.0, 1023.0, 0.01, 5.0));
    current = current * 10;
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" A");


    int power = getPower(sensor_value);
    Serial.println("Power: " + String(power) + "W\n");
    delay(4000);
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

float getCurrent(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
