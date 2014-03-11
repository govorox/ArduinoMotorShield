#ifndef ArduinoMotorShield_h
#define ArduinoMotorShield_h

#include <Arduino.h>

class ArduinoMotorShield
{
  public:  
    // CONSTRUCTORS
    ArduinoMotorShield(); // Default pin selection.
    ArduinoMotorShield(unsigned char M1DIR, unsigned char M1PWM, unsigned char M1FB, unsigned char M1BRK,
                       unsigned char M2DIR, unsigned char M2PWM, unsigned char M2FB, unsigned char M2BRK); // User-defined pin selection. 
    
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ. 
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setSpeeds(int m1Speed, int m2Speed); // Set speed for both M1 and M2.
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1. 
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
    unsigned char getFault(); // Get fault reading.
    
  private:
    //unsigned char _nD2;
    unsigned char _M1DIR;
    unsigned char _M2DIR;
    static const unsigned char _M1PWM = 3;
    static const unsigned char _M2PWM = 11;
    //unsigned char _nSF;
    unsigned char _M1FB;
    unsigned char _M2FB;
    unsigned char _M1BRK;
    unsigned char _M2BRK;
};

#endif