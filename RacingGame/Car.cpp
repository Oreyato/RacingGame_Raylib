#include "Car.h"

#include <iostream>
using std::cout;
using std::endl;

#include <math.h>

#include "Maths.h"
#include "Consts.h"

Car::Car()
{
    rect = { 0.0f, 0.0f, Consts::SIZE_CAR, Consts::SIZE_CAR };

    xSpeed = Consts::MAX_SPEED_CAR;
    ySpeed = -Consts::MAX_SPEED_CAR;
}

Car::Car(float widthP, float heightP) :
    rect{ startingPos.x, startingPos.y, widthP, heightP }
{
    size = Consts::SIZE_CAR;

    xSpeed = Consts::MAX_SPEED_CAR;
    ySpeed = -Consts::MAX_SPEED_CAR;

    angle = Consts::ANGLE_CAR;
}

Car::~Car()
{
   
}

void Car::load()
{

}

void Car::update(float dtP)
{
    // Gradual deceleration - updating speed
    if ((speed > 0.0f + Consts::EPSILON_CAR) || (speed < 0.0f - Consts::EPSILON_CAR))
    {
        speed *= Consts::DECELERATION_FACTOR_CAR;
    }

    // Updating position
    rect.x += cos(Maths::degToRad(angle)) * speed * dtP;
    rect.y += sin(Maths::degToRad(angle)) * speed * dtP;

    screenCollisions();
    
}
void Car::screenCollisions()
{
    // Testing if the car goes out of screen
    // ... from the top
    if (rect.y <= 0) {
        // Reset car position
        rect.y = 0;
    }
    // ... from the bottom
    else if (rect.y >= Consts::HEIGHT_SCREEN - size) {
        // Reset car position 
        rect.y = Consts::HEIGHT_SCREEN - size;
    }
    // ... from the left
    if (rect.x <= 0) {
        // Reset car position 
        rect.x = 0;
    }
    // ... from the right
    else if (rect.x >= Consts::WIDTH_SCREEN - size) {
        // Reset car position 
        rect.x = Consts::WIDTH_SCREEN - size;
    }
}

void Car::inputs() {
    float speedRatio = speed / Consts::MAX_SPEED_CAR;
    if (abs(speedRatio) < Consts::MIN_ANGLE_SPEED_CAR) {
        speedRatio = Consts::MIN_ANGLE_SPEED_CAR;
    }

    // Rotating left 
    if (IsKeyDown(KEY_A)) {
        angle -= Consts::MAX_ANGLE_SPEED_CAR * speedRatio;
    }
    // Rotating right
    if (IsKeyDown(KEY_D)) {
        angle += Consts::MAX_ANGLE_SPEED_CAR * speedRatio;
    }

    // Moving forward
    if (IsKeyDown(KEY_W)) {
        if (speed < Consts::MAX_SPEED_CAR) {
            speed += Consts::ACCELERATION_FACTOR_CAR;
        }
    }
    // Moving backward
    if (IsKeyDown(KEY_S)) {
        if (speed > -Consts::MAX_SPEED_CAR / 2.0f) {
            speed -= Consts::ACCELERATION_FACTOR_CAR / 2.0f;
        }
    }
    // Using the break
    if (IsKeyDown(KEY_SPACE)) {
        if (speed > 0.0f + Consts::EPSILON_CAR) {
            speed -= Consts::BREAK_FACTOR_CAR;
        }
        else if (speed < 0.0f - Consts::EPSILON_CAR) {
            speed += Consts::BREAK_FACTOR_CAR;
        }
    }
}

void Car::draw()
{
    float halfSize = size / 2.0f;

    Rectangle originRect{ 0.0f, 0.0f, size, size };
    Rectangle destRect{ rect.x + halfSize, rect.y + halfSize, size, size };
    Vector2 origin{ halfSize, halfSize };

    DrawTextureTiled(texture, originRect, destRect, origin, angle, scale, WHITE);
}

void Car::resetCar(float xP, float yP)
{
    rect.x = startingPos.x;
    rect.y = startingPos.y;
    xSpeed = Consts::MAX_SPEED_CAR;
    ySpeed = -Consts::MAX_SPEED_CAR;
    angle = Consts::ANGLE_CAR;
}

void Car::unload()
{
    UnloadTexture(texture);
}

float Car::getPreviousXPos()
{
    return rect.x - xSpeed;
}
float Car::getPreviousYPos()
{
    return rect.y - ySpeed;
}

void Car::setStartingPos(Vector2 startingPosP) {
    startingPos = startingPosP;

    rect.x = startingPos.x;
    rect.y = startingPos.y;
}

void Car::reverseXSpeed()
{
    xSpeed *= -1;
}
void Car::reverseYSpeed()
{
    ySpeed *= -1;
}
