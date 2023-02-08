#include "Car.h"

#include <iostream>
using std::cout;
using std::endl;

#include <math.h>

#include "MathsUtils.h"
#include "Consts.h"

Car::Car(std::string nameP) :
    name{ nameP }
{
    rect = { 0.0f, 0.0f, Consts::SIZE_CAR, Consts::SIZE_CAR };
}

Car::Car(std::string nameP, float widthP, float heightP) :
    name{ nameP },
    rect{ startingPos.x, startingPos.y, widthP, heightP }
{
    size = Consts::SIZE_CAR;

    angle = Consts::ANGLE_CAR;
}

Car::~Car()
{
   
}


void Car::load()
{

}


void Car::inputs() {
    float speedRatio = speed / Consts::MAX_SPEED_CAR;

    if (abs(speedRatio) < Consts::MIN_ANGLE_SPEED_CAR) {
        speedRatio = Consts::MIN_ANGLE_SPEED_CAR;
    }

    // Rotating left 
    if (IsKeyDown(bindings.leftRot)) {
        angle -= Consts::MAX_ANGLE_SPEED_CAR * speedRatio;
    }
    // Rotating right
    if (IsKeyDown(bindings.rightRot)) {
        angle += Consts::MAX_ANGLE_SPEED_CAR * speedRatio;
    }

    // Moving forward
    if (IsKeyDown(bindings.forward)) {
        if (speed < Consts::MAX_SPEED_CAR) {
            speed += Consts::ACCELERATION_FACTOR_CAR;
        }
    }
    // Moving backward
    if (IsKeyDown(bindings.backward)) {
        if (speed > -Consts::MAX_SPEED_CAR / 2.0f) {
            speed -= Consts::ACCELERATION_FACTOR_CAR / 2.0f;
        }
    }
    // Using the break
    if (IsKeyDown(bindings.breakKey)) {
        if (speed > 0.0f + Consts::EPSILON_CAR) {
            speed -= Consts::BREAK_FACTOR_CAR;
        }
        else if (speed < 0.0f - Consts::EPSILON_CAR) {
            speed += Consts::BREAK_FACTOR_CAR;
        }
    }
}

void Car::setNextPos(float dtP)
{
    // Calculate next position
    nextPos.x = rect.x + cos(MathsUtils::degToRad(angle)) * std::copysignf(1.0f, speed) * size / 2.0f;
    nextPos.y = rect.y + sin(MathsUtils::degToRad(angle)) * std::copysignf(1.0f, speed) * size / 2.0f;
}

void Car::update(float dtP)
{
    // Gradual deceleration - updating speed
    if ((speed > 0.0f + Consts::EPSILON_CAR) || (speed < 0.0f - Consts::EPSILON_CAR))
    {
        speed *= Consts::DECELERATION_FACTOR_CAR;
    }

    // screenCollisions();

    rect.x += cos(MathsUtils::degToRad(angle)) * speed * dtP;
    rect.y += sin(MathsUtils::degToRad(angle)) * speed * dtP;
}
void Car::screenCollisions()
{
    // Testing if the car goes out of screen
    // ... from the top
    if (rect.y <= 0 + size / 2.0f) {
        // Reset car position
        rect.y = size / 2.0f;
        bounceCar();
    }
    // ... from the bottom
    else if (rect.y >= Consts::HEIGHT_SCREEN - size / 2.0f) {
        // Reset car position 
        rect.y = Consts::HEIGHT_SCREEN - size / 2.0f;
        bounceCar();
    }
    // ... from the left
    if (rect.x <= 0 + size / 2.0f) {
        // Reset car position 
        rect.x = size / 2.0f;
        bounceCar();
    }
    // ... from the right
    else if (rect.x >= Consts::WIDTH_SCREEN - size/2.0f) {
        // Reset car position 
        rect.x = Consts::WIDTH_SCREEN - size / 2.0f;
        bounceCar();
    }
}

void Car::draw()
{
    float halfSize = size / 2.0f;

    Rectangle originRect{ 0.0f, 0.0f, size, size };
    Rectangle destRect{ rect.x, rect.y, size, size };
    Vector2 origin{ halfSize, halfSize };

    DrawTextureTiled(texture, originRect, destRect, origin, angle, scale, WHITE);
}

void Car::resetCar()
{
    rect.x = startingPos.x;
    rect.y = startingPos.y;

    scale = 1.0f;

    speed = 0.0f;
    
    nextPos = { rect.x, rect.y };

    angle = Consts::ANGLE_CAR;

    collide = false;
}

void Car::unload()
{
    UnloadTexture(texture);
}

void Car::setStartingPos(Vector2 startingPosP) {
    startingPos = startingPosP;

    rect.x = startingPos.x;
    rect.y = startingPos.y;

    nextPos.x = rect.x;
    nextPos.y = rect.y;
}
