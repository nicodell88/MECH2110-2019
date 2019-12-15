#include <AccelStepper.h>
#define ECHO 8
#define TRIG 9
#define SPEED_OF_SOUND 340.29 // m/s
//Declare stepper motor here using: AccelStepper
//e.g. AccelStepper myMotor(4,4,5,6,7); declares a stepper motor names myMotor
//...with a 4 wire interface connected to pins 4-7
AccelStepper myStepper(4,4,5,6,7);
void setup() {
// put your setup code here, to run once:
    pinMode(ECHO,INPUT);
    pinMode(TRIG,OUTPUT);
    Serial.begin(9600);
}
//variables for duration,distance,speed
long duration=0;
float mm=0;
int stepsPerSec=0;
void loop() {
// put your main code here, to run repeatedly:
// Read in a distance from the ultrasonic distance sensor:
// The PING))) is triggered by a HIGH pulse of 10 microseconds.
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
//read length of time pulse
    duration = pulseIn(ECHO, HIGH);
// convert the time into a distance
    mm = 0.5 * duration * 1e-6 * SPEED_OF_SOUND *1e3;
    Serial.print(mm);
    /*fill the if else chain:
- Runs the motors at full speed if the distance is greater than 200mm
- Runs the motors at a speed proportional to the distance read when between 100
//... and 200 mm away
- Stop the motors when less than 100mm away
     */
    if(/*insert test condition for distance > 200*/)
    {
//set motors full speed(200)
        Serial.println(" Contstant Speed");
    }else if(/*test condition for distance >100*/)
    {
        stepsPerSec = 200*(mm-100)/100;
        myStepper.setSpeed(stepsPerSec);
        Serial.println(" Slowing Down");
    }else if(/*test condition for <100*/)
    {
//set motor speed to 0
        Serial.println(" Stopped");
    }
    myStepper.runSpeed();
}
