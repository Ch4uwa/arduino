#include <Servo.h>

Servo servo_5;

const int ECHOPIN = 4;
const int TRIGPIN = 2;

const int dirLeft = 12;
const int dirRight = 13;
const int pwmLeft = 3;
const int pwmRight = 11;
const int brakeLeft = 9;
const int brakeRight = 8;

const char bothSpeed = 100;
const char turnSpeed = 120;

float disF, disR, disL;

const int rangeLimit = 30;

void setup()
{
    servo_5.attach(5);
    pinMode(dirLeft, OUTPUT);
    pinMode(dirRight, OUTPUT);
    pinMode(brakeLeft, OUTPUT);
    pinMode(brakeRight, OUTPUT);

    pinMode(ECHOPIN, INPUT);
    pinMode(TRIGPIN, OUTPUT);

    digitalWrite(brakeLeft, 0);
    digitalWrite(brakeRight, 0);
}

void loop()
{

    if (rangeCalc() < rangeLimit)
    {
        
        if (disL > disR)
        {
            turnLeft();
        }
        else if (disR > disL)
        {
            turnRight();
        }
        else
        {
            turnRight();
        }
    }
    else
    {
        forward();
    }
    
    servoLeft(20);
    delay(300);
    disL = rangeCalc();
    servoRight(165);
    delay(300);
    disR = rangeCalc();
    servoForward(95);
    delay(300);
    disF = rangeCalc();
}


float rangeCalc()
{
    digitalWrite(TRIGPIN, LOW);
    delay(2);
    digitalWrite(TRIGPIN, HIGH);
    delay(10);
    digitalWrite(TRIGPIN, LOW);
    float distance = 0.01723 * pulseIn(ECHOPIN, HIGH);

    return distance;
}

void turnRight()
{
    digitalWrite(dirLeft, HIGH);
    digitalWrite(dirRight, HIGH);
    analogWrite(pwmLeft, bothSpeed);
    analogWrite(pwmRight, bothSpeed);
}

void turnLeft()
{
    digitalWrite(dirLeft, LOW);
    digitalWrite(dirRight, LOW);
    analogWrite(pwmLeft, bothSpeed);
    analogWrite(pwmRight, bothSpeed);
}

void forward()
{
    digitalWrite(dirLeft, LOW);
    digitalWrite(dirRight, HIGH);
    analogWrite(pwmLeft, bothSpeed);
    analogWrite(pwmRight, bothSpeed);
}

void reverse()
{
    digitalWrite(dirLeft, HIGH);
    digitalWrite(dirRight, LOW);
    analogWrite(pwmLeft, bothSpeed);
    analogWrite(pwmRight, bothSpeed);
}

void servoForward(short pos)
{
    servo_5.write(pos);
}

void servoLeft(short pos)
{
    servo_5.write(pos);
}

void servoRight(short pos)
{
    servo_5.write(pos);
}
