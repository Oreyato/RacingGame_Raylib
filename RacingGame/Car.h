#ifndef CAR_H
#define CAR_H

#include "raylib.h"

class Car : public Rectangle
{
public:
	Car();
	Car(float xP, float yP, float widthP, float heightP);
	~Car();

	// ======================================
	void update();
	void screenCollisions();
	void resetCar(float xP, float yP);

	// Getters ==============================
	Rectangle getRect() { return rect; }
	
	float getSize() { return size; }

	float getXSpeed() { return xSpeed; }
	float getYSpeed() { return ySpeed; }

	float getPreviousXPos();
	float getPreviousYPos();

	// Setters ==============================
	void setXSpeed(float xSpeedP) { xSpeed = xSpeedP; }
	void setYSpeed(float ySpeedP) { ySpeed = ySpeedP; }

	void reverseXSpeed();
	void reverseYSpeed();

private:
	Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };

	float size{ 0.0f };
	float width{ 0.0f };
	float height{ 0.0f };

	float xSpeed{ 0.0f };
	float ySpeed{ 0.0f };
};

#endif // CAR_H



