#include <Servo.h>

const int ECHOPIN = 4;
const int TRIGPIN = 2;

Servo servo_5;

const int dirLeft = 12;
const int dirRight = 13;
const int pwmLeft = 3;
const int pwmRight = 11;
const int brakeLeft = 9;
const int brakeRight = 8;

float dis, disR, disL;

const char bothSpeed = 200;
const char turnSpeed = 100;
const char quarterSpeed = (bothSpeed / 4);

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
    
    // servoLeft();
    // servoForward();
    // servoRight();
    // servoForward();

    // while (digitalRead(sensorSignal) == HIGH)
    //  {
    //  digitalWrite(ledRight, HIGH);
    //  digitalWrite(ledLeft, HIGH);
    //   if (rangeCalc() < 50)
    //   {
    //       turnRight();
    //   }
    //    else
     //   {
        //    forward();
         //   digitalWrite(ledRight, HIGH);
         //   digitalWrite(ledLeft, HIGH);
     //   }
  //  }
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
    

    digitalWrite(dirLeft, LOW);
    digitalWrite(dirRight, HIGH);

    analogWrite(pwmLeft, bothSpeed);
    analogWrite(pwmRight, bothSpeed);
}

void servoForward()
{
    servo_5.write(95);
    delay(500);
}

void servoLeft()
{
    servo_5.write(20);
    delay(500);
}

void servoRight()
{
    servo_5.write(165);
    delay(500);
}
