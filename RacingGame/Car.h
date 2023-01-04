#ifndef CAR_H
#define CAR_H

#include "Rectangle.h"

class Car : public Rectangle
{
public:
	Car();
	Car(float xP, float yP, float widthP, float heightP);
	~Car();

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



