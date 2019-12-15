#include <AccelStepper.h>
#define CONSTANT_SPEED 0
#define SLOWING_DOWN 1
#define STOPPED 2
#define ECHO 8
#define TRIG 9
#define SPEED_OF_SOUND 340.29 // m/s
int state = CONSTANT_SPEED;
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
float distance=0;
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
    distance = 0.5 * duration * 1e-6 * SPEED_OF_SOUND *1e3;
    Serial.print(distance);
    switch(state){
        case CONSTANT_SPEED:
            Serial.println(" Constant Speed");
            myStepper.setSpeed(200);//Task for this state
//TODO: insert test condition here
            break;
        case SLOWING_DOWN:
            Serial.println(" Slowing Down");
//TODO: set speed here
            if(distance>200){//test condition to transition back to previous state
                state = CONSTANT_SPEED;
            }else if(distance<100){//test condition to transition to next state
                state = STOPPED;
            }
            break;
        case STOPPED:
            Serial.println(" Stopped");
//TODO: set speed to 0
//TODO: insert test condition here.
            break;
    }
    myStepper.runSpeed();
}
