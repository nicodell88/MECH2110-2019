/*
 * Lab 1 MECH2110
 * Ultrasonic Sensor Task
 */
#define TRIG 4
#define ECHO 3
#define SPEED_OF_SOUND 340.29 // m/s
void setup() {
// initialize serial communication:
    Serial.begin(9600);
//TODO: initialize sonar sensor pins
}
// establish variables for duration of the ping,
// and the distance in mm
long duration;
float mm;
void loop() {
// The PING))) is triggered by a HIGH pulse of 10 microseconds,
// for the HC-SR04 sensor
//pulse the trigger pin high for 10 microseconds
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
//TODO: Read the pulse duration into the variable duration
//TODO: Convert the time into a distance in mm and store in mm,
//print result
    Serial.print(mm);
    Serial.println("mm");
    delay(100);
}
