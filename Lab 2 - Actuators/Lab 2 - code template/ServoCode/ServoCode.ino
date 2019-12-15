#include <Servo.h>
#define SERVOPIN 10
Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position
int dir = 0; // variable to store the servo direction
void setup() {
    Serial.begin(115200);
    myservo.attach(SERVOPIN); // initialises the servo by attatching the servo on pin
//...10 to the servo object
}
void loop() {
//TODO: Change the range to sweep 0-90 deg
    if(dir == 0) //if forwards
    {
        if(pos<180) //keep moving forwards
        {
            pos++;
        }else //start moving backwards
        {
            dir = 1;
            pos = 179;
        }
    }else //if backwards
    {
        if(pos>0) //keep moving backwards
        {
            pos--;
        }else //start moving forwards
        {
            dir = 0;
            pos = 1;
        }
    }
//TODO: Send the updated position command to the servo
    Serial.print("Position="); //print to the serial monitor
    Serial.println(pos); //prints the position to the serial monitor + a new
//...line
    delay(15); // waits 15ms for the servo to reach the position
}
