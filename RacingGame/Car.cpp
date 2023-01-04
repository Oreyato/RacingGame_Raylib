#include "Car.h"

#include "Consts.h"

Car::Car()
{
	width = Consts::SIZE_CAR;
	height = Consts::SIZE_CAR;

	xSpeed = Consts::SPEED_CAR;
	ySpeed = Consts::SPEED_CAR;
}

Car::Car(float xP, float yP, float widthP, float heightP) :
	xPos{xP},
	yPos{yP},
	width{widthP},
	height{heightP}
{
	xSpeed = Consts::SPEED_CAR;
	ySpeed = Consts::SPEED_CAR;
}

Car::~Car()
{
}
