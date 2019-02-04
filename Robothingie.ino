#include <NewPing.h>
#include <Servo.h>

#define ECHOPIN 4
#define TRIGPIN 2

#define MOTORLEFT 12
#define MOTORRIGHT 13
#define pwmLeft 3
#define pwmRight 11
#define brakeLeft 9
#define brakeRight 8

#define MAXSPEED 100
#define MAXDISTANCE 200

Servo servo_5;
NewPing sonar(TRIGPIN, ECHOPIN, MAXDISTANCE);
bool goesForward = false;
int distance = 0;

void setup()
{
    pinMode(MOTORLEFT, OUTPUT);
    pinMode(MOTORRIGHT, OUTPUT);
    pinMode(brakeLeft, OUTPUT);
    pinMode(brakeRight, OUTPUT);
    digitalWrite(brakeLeft, 0);
    digitalWrite(brakeRight, 0);
    servo_5.attach(5);
    servo_5.write(95);
    delay(300);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
}

void loop()
{
    int distanceRight = 0;
    int distanceLeft = 0;
    delay(40);

    if (distance <= 15)
    {
        moveStop();
        delay(100);
        moveBackwards();
        delay(300);
        moveStop();
        delay(200);
        distanceRight = lookRight();
        delay(200);
        distanceLeft = lookLeft();
        delay(200);

        if (distanceRight >= distanceLeft)
        {
            turnRight();
            moveStop();
        }
        else
        {
            turnLeft();
            moveStop();
        }
    }
    else
    {
        moveForward();
    }
    distance = readPing();
}

int readPing()
{
    delay(70);
    int cm = sonar.ping_cm();
    if (cm == 0)
    {
        cm = 250;
    }
    return cm;
}

void moveStop()
{
    analogWrite(pwmLeft, 0);
    analogWrite(pwmRight, 0);
}

void turnRight()
{
    digitalWrite(MOTORLEFT, HIGH);
    digitalWrite(MOTORRIGHT, HIGH);
    analogWrite(pwmLeft, MAXSPEED);
    analogWrite(pwmRight, MAXSPEED);
}

void turnLeft()
{
    digitalWrite(MOTORLEFT, LOW);
    digitalWrite(MOTORRIGHT, LOW);
    analogWrite(pwmLeft, MAXSPEED);
    analogWrite(pwmRight, MAXSPEED);
}

void moveForward()
{
    if (!goesForward)
    {
        goesForward = true;
        digitalWrite(MOTORLEFT, LOW);
        digitalWrite(MOTORRIGHT, HIGH);
        for (size_t speed = 0; speed < MAXSPEED; speed + 2)
        {
            analogWrite(pwmLeft, speed);
            analogWrite(pwmRight, speed);
            delay(5);
        }
    }
}

void moveBackwards()
{
    goesForward = false;
    digitalWrite(MOTORLEFT, HIGH);
    digitalWrite(MOTORRIGHT, LOW);

    for (size_t speed = 0; speed < MAXSPEED; speed + 2)
    {
        analogWrite(pwmLeft, speed);
        analogWrite(pwmRight, speed);
        delay(5);
    }
}

int lookLeft()
{
    servo_5.write(15);
    delay(500);
    int distance = readPing();
    servo_5.write(95);
    delay(100);
    return distance;
}

int lookRight()
{
    servo_5.write(165);
    delay(500);
    int distance = readPing();
    servo_5.write(95);
    delay(100);
    return distance;
}