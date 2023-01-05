#include "Car.h"

#include "Consts.h"

Car::Car()
{
    rect = { 0.0f, 0.0f, Consts::SIZE_CAR, Consts::SIZE_CAR };

    xSpeed = Consts::MAX_SPEED_CAR;
    ySpeed = -Consts::MAX_SPEED_CAR;
}

Car::Car(float xP, float yP, float widthP, float heightP) :
    rect{ xP, yP, widthP, heightP }
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

void Car::update()
{
    /*rect.x += xSpeed;
    rect.y += ySpeed;*/

    screenCollisions();
    
}
void Car::screenCollisions()
{
    // Testing if the car goes out of screen
    // ... from the top
    if (rect.y <= 0) {
        // Reverse speed along the y axis
        ySpeed *= -1;
        // Reset car position
        rect.y = 0;
    }
    // ... from the bottom
    else if (rect.y >= Consts::HEIGHT_SCREEN - rect.width) {
        // Reverse speed along the y axis
        ySpeed *= -1;
    }
    // ... from the left
    else if (rect.x <= 0) {
        // Reverse speed along the x axis
        xSpeed *= -1;
        // Reset car position 
        rect.x = 0;
    }
    // ... from the right
    else if (rect.x >= Consts::WIDTH_SCREEN - rect.width) {
        // Reverse speed along the x axis
        xSpeed *= -1;
        // Reset car position 
        rect.x = Consts::WIDTH_SCREEN - rect.width;
    }
}

void Car::inputs() {
    // Rotating left 
    if (IsKeyDown(KEY_A)) {
        angle -= Consts::MAX_ANGLE_SPEED_CAR;
    }
    // Rotating right
    if (IsKeyDown(KEY_D)) {
        angle += Consts::MAX_ANGLE_SPEED_CAR;
    }

    // Moving forward
    if (IsKeyDown(KEY_W)) {

    }
    // Moving backward
    else if (IsKeyDown(KEY_S)) {

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
    rect.x = xP;
    rect.y = yP;
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

void Car::reverseXSpeed()
{
    xSpeed *= -1;
}
void Car::reverseYSpeed()
{
    ySpeed *= -1;
}
