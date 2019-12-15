/*
 * Lab 1 MECH2110
 * Analog to Digital Conversion, Potentiometer
 */
#define pot A0
void setup() {
//start serial connection
    Serial.begin(9600);
//TODO: configure A0 as an input (NOT INPUT_PULLUP!)
//TODO: Initialise pin 13 (LED) as an output.
}
//global variables to store reading
int reading =0;
float voltage = 0;
void loop() {
    delay(500);
//TODO: Use analogRead to read the potentiometer
// Print the conversion to the serial monitor
    Serial.print("reading =");
    Serial.println(reading);
//TODO: Convert Reading to voltage
// Print the voltage to the serial monitor
//TODO: If the voltage is less than 1 Volt turn on the LED,
// otherwise turn it off.
}
