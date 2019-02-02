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

const char bothSpeed = 200;
const char turnSpeed = 120;

float disF, disR, disL;

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

    

    servoForward(95);
    disF = rangeCalc();
    delay(500);
    servoLeft(20);
    disL = rangeCalc();
    delay(500);
    servoForward(95);
    disF = rangeCalc();
    delay(500);
    servoRight(165);
    disR = rangeCalc();
    delay(500);

    if (rangeCalc() < 30)
    {
        if (disR < 30 && disL < 30 && disF < 30) 
        {
            reverse();
        }
        else if (disL > disR)
        {
            turnLeft();
        }
        else if (disR > disL)
        {
            turnRight();
        }
    }
    else
    {
        forward();
    }

    
}

float rangeCalc()
{
    digitalWrite(TRIGPIN, LOW);
    delay(2);
    digitalWrite(TRIGPIN, HIGH);
    delay(10);
    digitalWrite(TRIGPIN, LOW);
    float distance = pulseIn(ECHOPIN, HIGH);
    distance = distance / 58;

    return distance;
}

void turnRight()
{
    digitalWrite(dirLeft, HIGH);
    digitalWrite(dirRight, HIGH);
    analogWrite(pwmLeft, turnSpeed);
    analogWrite(pwmRight, turnSpeed);
}

void turnLeft()
{
    digitalWrite(dirLeft, LOW);
    digitalWrite(dirRight, LOW);
    analogWrite(pwmLeft, turnSpeed);
    analogWrite(pwmRight, turnSpeed);
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
