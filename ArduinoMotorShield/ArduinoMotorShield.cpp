#include "ArduinoMotorShield.h"

// Constructors ////////////////////////////////////////////////////////////////

ArduinoMotorShield::ArduinoMotorShield()
{
  //Pin map
  _M1DIR = 12;
  _M2DIR = 13;
  _M1FB = A0;
  _M2FB = A1;
  _M1BRK = 9; 
  _M2BRK = 8;
}

ArduinoMotorShield::ArduinoMotorShield(unsigned char M1DIR, unsigned char M1PWM, unsigned char M1FB, unsigned char M1BRK,
                                       unsigned char M2DIR, unsigned char M2PWM, unsigned char M2FB, unsigned char M2BRK)
{
  //Pin map
  //PWM1 and PWM2 cannot be remapped because the library assumes PWM is on timer1
  _M1DIR = M1DIR;
  _M2DIR = M2DIR;
  _M1FB = M1FB; 
  _M2FB = M2FB;
  _M1BRK = M1BRK; 
  _M2BRK = M2BRK;
}

// Public Methods //////////////////////////////////////////////////////////////
void ArduinoMotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_M1DIR,OUTPUT);
  pinMode(_M1PWM,OUTPUT);
  pinMode(_M1FB,INPUT);
  pinMode(_M2DIR,OUTPUT);
  pinMode(_M2PWM,OUTPUT);
  pinMode(_M2FB,INPUT);
  pinMode(_M1BRK,OUTPUT);
  pinMode(_M2BRK,OUTPUT);

  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__)
  // Timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;
  #endif
}
// Set speed for motor 1, speed is a number betwenn -400 and 400
void ArduinoMotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__)
  OCR1A = speed;
  #else
  analogWrite(_M1PWM,speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif
  if (reverse)
    digitalWrite(_M1DIR,HIGH);
  else
    digitalWrite(_M1DIR,LOW);
}

// Set speed for motor 2, speed is a number betwenn -400 and 400
void ArduinoMotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__)
  OCR1B = speed;
  #else
  analogWrite(_M2PWM,speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif
  if (reverse)
    digitalWrite(_M2DIR,HIGH);
  else
    digitalWrite(_M2DIR,LOW);
}

// Set speed for motor 1 and 2
void ArduinoMotorShield::setSpeeds(int m1Speed, int m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}

// Return motor 1 current value in milliamps.
unsigned int ArduinoMotorShield::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M1FB) * 9;
}

// Return motor 2 current value in milliamps.
unsigned int ArduinoMotorShield::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M2FB) * 9;
}

// Return error status
unsigned char ArduinoMotorShield::getFault()
{
  return 0; //!digitalRead(_nSF);
}