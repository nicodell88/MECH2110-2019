
#include <SoftwareSerial.h>   // We need this even if we're not using a SoftwareSerial object
// Due to the way the Arduino IDE compiles
#include "SerialCommand.h"
SerialCommand SCmd;   // The demo SerialCommand object

int pwmL = 0;
int pwmR = 0;

float yLeft = 0;
float yRight = 0;
float yFront = 0;
void setup()
{
  Serial.begin(115200);

  // Setup callbacks for SerialCommand commands
  SCmd.addCommand("sensorL", set_yLeft);      // sets Left sensor measurements
  SCmd.addCommand("sensorR", set_yRight);     // sets Right sensor measurements
  SCmd.addCommand("sensorF", set_yFront);       // sets Front sensor measurements
  SCmd.addCommand("ctrl?", get_ctrl);      // gets ctrl alloc

}

void loop()
{
  SCmd.readSerial();     // We don't do much, just process serial commands
}


void set_yLeft(void)
{
  char *arg;
  arg = SCmd.next();
  yLeft = atof(arg);
}

void set_yRight(void)
{
  char *arg;
  arg = SCmd.next();
  yRight = atof(arg);
}

void set_yFront(void)
{
  char *arg;
  arg = SCmd.next();
  yFront = atof(arg);
}

void get_ctrl(void)
{
  ctrlAlloc();
  char string[50];
  sprintf(string, "%d,%d", pwmL, pwmR);
  Serial.println(string);
}



//////////////////////////////////////////////////////////
/*
   Edit the variable: states below by inserting the names
   of your states

   Edit the function ctrAlloc with your navigation algorithm
*/
//////////////////////////////////////////////////////////
//Define states
enum states {FORWARD, REVERSE, ETC} state = FORWARD;

void ctrlAlloc(void)
{
  switch (state) {
    case FORWARD:
      pwmL = 130;
      pwmR = 100;
      //Transition condition
      if (yFront < 200)
      {
        state = REVERSE;
      }
      break;
    case REVERSE:
      pwmL = -55;
      pwmR = -50;
      //Transition condition
      //no transition in example
      break;
  }
}
