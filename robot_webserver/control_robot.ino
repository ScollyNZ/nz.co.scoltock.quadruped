
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


// intialize PWM board
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


// Each servo will have different limits depending on how the leg is assembled.
// Each leg is a pair of limits, the first being the foot height, the second the leg position
uint16_t servoMins[] = {130, 110, 350, 160, 250, 110, 290, 130};
uint16_t servoMaxs[] = {340, 470, 590, 560, 460, 470, 500, 570};

bool PWMinitialised = false;

void initPWM(){
  if (!PWMinitialised){
    pwm.begin();
    pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
    PWMinitialised = true;
  }
}

void initControlMode(){
  delay(5000);  //Delay to allow serial comms control to be set up
  //switch to serial control mode if there is any data in the buffer
  if (Serial.available() > 0)  
    serialControlMode();
}

// servoNumber is 0 - 7
// position is 1 to 100
// pauseMs - optional, milliseconds to pause once position set
void setServoPosition(uint8_t servoNumber, uint8_t position, int pauseMs = 0)
{
  //Enforce limits to avoid overruns
  if (position < 1) position=1;
  if (position > 100) position = 100;

  //Calculate actual pulse width required based on limits for given servo
  uint16_t pulseLength = calculatePulseLength(servoNumber, position);

  //Push value of IIC to PWM board
  pwm.setPWM(servoNumber,0,pulseLength);

  //if (delay > 0){
    //unsigned long now = millis();
    //while(millis() - now < pauseMs){
    //  Serial.print(".");  //something to induce a delay
    //}
  delay(pauseMs);
  //}
}



uint16_t calculatePulseLength(uint8_t servoNumber, uint8_t position)
{
  //retrieve range for given servo
  uint16_t range = (servoMaxs[servoNumber] - servoMins[servoNumber]);
  //calculate actual position required based on percentage of total range
  float percentPosition = (position / 100.0);

  return (range * percentPosition) + servoMins[servoNumber];
}


void autoMode() {
  delay(250);
  return;
  //switch to serial control mode if there is any data in the buffer
  if (Serial.available() > 0)  
    serialControlMode();

  int fullHeight = 50;  //How high to stand up. 100 is full height and difficult to balance
  
  // Stand Up
  setServoPosition(0,fullHeight);
  setServoPosition(2,fullHeight);
  setServoPosition(4,fullHeight);
  setServoPosition(6,fullHeight);
  delay(3000);
   
  // Rotate and Centre Legs
  centerLeg(0,fullHeight,30);
  centerLeg(1,fullHeight,70);
  centerLeg(2,fullHeight,30);
  centerLeg(3,fullHeight,70);
  

  // Sit Down
  setServoPosition(0,0);
  setServoPosition(2,0);
  setServoPosition(4,0);
  setServoPosition(6,0);
  delay(3000);
    
}

// foot = 0 to 3
void centerLeg(int foot,int fullHeight,int position )
{
  if (foot >= 0 && foot <= 3)
  {
    int pauseLen = 200;
    setServoPosition(foot*2,0);  //lift foot
    delay(pauseLen);
    setServoPosition((foot*2)+1,position); //center leg
    delay(pauseLen);
    setServoPosition(foot*2,fullHeight); //land foot
    delay(pauseLen);
  }
}


void serialControlMode()
{
  int incoming = 0;
  String incomingPosition = "";
  bool exitLoop = false;
  Serial.write("Entering Serial Control Mode. Send 'x' to exit\n");

  while(!exitLoop)
  {
    if (Serial.available()>0)
    {
      incoming = Serial.read();
      if (incoming=='x')
      {
        Serial.println("Returning to loop mode\n");
        exitLoop = true;
      }
      if (incoming >='0' && incoming <='9')
        incomingPosition += char(incoming); 
        Serial.println(incomingPosition);
        if (incomingPosition.length() == 3)
        {
          moveToStringPosition(incomingPosition);
          incomingPosition="";
        }           
    }
    else
    {
      delay(250);
    }
  }
  Serial.println("exiting serial mode");
}

// Moves based on an encoded string
// String must be 3 chars, digits only, 1st char is servo number, 2nd and 3rd position
void moveToStringPosition(String position)
{
  Serial.write("Moving to ");
  Serial.println(position);

  int servo = position[0] - '0'; // Substract the ACSII value of '0' to make '0' == 0
  int servoPosition = ((position[1] - '0')*10) + int(position[2]-'0');

  Serial.print("Moving Servo ");
  Serial.print(servo);
  Serial.print(" to ");
  Serial.println(servoPosition);
  
  setServoPosition(servo, servoPosition);
}

void doPressup()
{
  initPWM();
  Serial.println("doing pressup");
  setServoPosition(0,100);
  setServoPosition(2,100);
  setServoPosition(4,100);
  setServoPosition(6,100,3000);

  Serial.println("Step 1");
  setServoPosition(0, 0);
  setServoPosition(2, 0);
  setServoPosition(4, 0);
  setServoPosition(6, 0, 1000);
  
  Serial.println("Step 2");
  setServoPosition(0,50);
  setServoPosition(2,50);
  setServoPosition(4,50);
  setServoPosition(6,50, 2000);
  
  Serial.println("Step 3");
  setServoPosition(0,100);
  setServoPosition(2,100);
  setServoPosition(4,100);
  setServoPosition(6,100, 3000);

  Serial.println("Step 4");
  setServoPosition(0,0);
  setServoPosition(2,0);
  setServoPosition(4,0);
  setServoPosition(6,0, 2000);

  Serial.println("pressup done");
}
