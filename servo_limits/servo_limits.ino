
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// intialize PWM board
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


// Each servo will have different limits depending on how the leg is assembled.
// Each leg is a pair of limits, the first being the foot height, the second the leg position
uint16_t servoMins[] = {130, 110, 350, 160, 290, 110, 290, 130};
uint16_t servoMaxs[] = {340, 470, 590, 560, 500, 470, 500, 570};

void setup() {
  Serial.begin(9600);
  Serial.println("Quadruped running");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

// servoNumber is 0 - 7
// position is 1 to 100
void setServoPosition(uint8_t servoNumber, uint8_t position)
{
  //Enforce limits to avoid overruns
  if (position < 1) position=1;
  if (position > 100) position = 100;

  //Calculate actual pulse width required based on limits for given servo
  uint16_t pulseLength = calculatePulseLength(servoNumber, position);

  //Push value of IIC to PWM board
  pwm.setPWM(servoNumber,0,pulseLength);
}



uint16_t calculatePulseLength(uint8_t servoNumber, uint8_t position)
{
  //retrieve range for given servo
  uint16_t range = (servoMaxs[servoNumber] - servoMins[servoNumber]);
  //calculate actual position required based on percentage of total range
  float percentPosition = (position / 100.0);

  return (range * percentPosition) + servoMins[servoNumber];
}


void loop() {

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


void doPressup()
{
  setServoPosition(0,100);
  setServoPosition(2,100);
  setServoPosition(4,100);
  setServoPosition(6,100);
  delay(3000);
  setServoPosition(0, 0);
  setServoPosition(2, 0);
  setServoPosition(4, 0);
  setServoPosition(6, 0);
  delay(1000);
  setServoPosition(0,50);
  setServoPosition(2,50);
  setServoPosition(4,50);
  setServoPosition(6,50);
  delay(2000);
  setServoPosition(0,100);
  setServoPosition(2,100);
  setServoPosition(4,100);
  setServoPosition(6,100);
  delay(3000);
  setServoPosition(0,50);
  setServoPosition(2,50);
  setServoPosition(4,50);
  setServoPosition(6,50);
  delay(2000);
}
