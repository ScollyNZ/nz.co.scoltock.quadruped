/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>



// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  290 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // this is the 'maximum' pulse length count (out of 4096)

uint16_t servoMins[] = {130, 130, 340, 170, 290, 130, 290, 130};
uint16_t servoMaxs[] = {340, 490, 580, 570, 500, 490, 500, 570};

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

// servoNumber is 0 - 7
// position is 1 to 100
void setServoPosition(uint8_t servoNumber, uint8_t position)
{
  if (position < 1) position=1;
  if (position > 100) position = 100;
  uint16_t pulseLength = calculatePulseLength(servoNumber, position);

  
  pwm.setPWM(servoNumber,0,pulseLength);
  Serial.print(servoNumber);
  Serial.print(":");
  Serial.print(pulseLength);
  Serial.println("");
}

uint16_t calculatePulseLength(uint8_t servoNumber, uint8_t position)
{
uint16_t range = (servoMaxs[servoNumber] - servoMins[servoNumber]);
float percentPosition = (position / 100.0);

Serial.print(range);
Serial.print("::");
Serial.print(percentPosition);


  
return (range * percentPosition) + servoMins[servoNumber];
}


void loop() {
  setServoPosition(0, 0);
  setServoPosition(2, 0);
  setServoPosition(4, 0);
  setServoPosition(6, 0);
  delay(1000);
  setServoPosition(0,50);
  setServoPosition(2,50);
  setServoPosition(4,50);
  setServoPosition(5,50);
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
  
  



  
  // Drive each servo one at a time
  //Serial.println(servonum);
  //for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
  //  pwm.setPWM(servonum, 0, pulselen);
  //  Serial.println(pulselen);
  //  delay(30);
  //}

  //delay(500);
  //pwm.setPWM(servonum, 0, SERVOMIN);


  //delay(500);

  //servonum ++;
  //if (servonum > 7) servonum = 0;
}
