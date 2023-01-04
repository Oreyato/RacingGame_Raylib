#ifndef CAR_H
#define CAR_H

#include "raylib.h"

class Car : public Rectangle
{
public:
	Car();
	Car(float xP, float yP, float widthP, float heightP);
	~Car();

	// Getters ==============================
	float getXPos() { return xPos; }
	float getYPos() { return yPos; }
	
	float getXSpeed() { return xSpeed; }
	float getYSpeed() { return ySpeed; }

	// Setters ==============================
	void setXPos(float xPosP) { xPos = xPosP; }
	void setyPos(float yPosP) { yPos = yPosP; }

	void setXSpeed(float xSpeedP) { xSpeed = xSpeedP; }
	void setySpeed(float ySpeedP) { ySpeed = ySpeedP; }

	// ======================================
	void reverseXSpeed() { xSpeed *= -1; }
	void reverseYSpeed() { ySpeed *= -1; }

private:
	float size{ 0.0f };
	float width{ 0.0f };
	float height{ 0.0f };

	float xSpeed{ 0.0f };
	float ySpeed{ 0.0f };

	float xPos{ 0.0f };
	float yPos{ 0.0f };
};

#endif // CAR_H



