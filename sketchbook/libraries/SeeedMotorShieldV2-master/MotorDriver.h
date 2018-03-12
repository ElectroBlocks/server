// new motor shield library
// by loovee
// 2016-3-11
#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__

#include <Arduino.h>
/******Pins definitions*************/
#define MOTORSHIELD_IN1	8
#define MOTORSHIELD_IN2	11
#define MOTORSHIELD_IN3	12
#define MOTORSHIELD_IN4	13
#define SPEEDPIN_A		9
#define SPEEDPIN_B		10
/**************Motor ID**********************/
#define MOTORA 			0
#define MOTORB 			1

#define SPD_BUFF_STEPS        100

/**Class for Motor Shield**/
class MotorDriver
{

private:
    int speed0;
    int speed1;

    // motor pin numbers:
    int motor_pin_a_plus;
    int motor_pin_a_minus;
    int motor_pin_b_plus;
    int motor_pin_b_minus;

public:

    void begin();

    // motor_num: 0, 1
    // speed: 0~100
    void speed(int motor_id, int _speed);
    void stop(unsigned char motor_id);
    void brake(unsigned char motor_id);

};


#endif
