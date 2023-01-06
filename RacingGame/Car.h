#ifndef CAR_H
#define CAR_H

#include "raylib.h"

class Car : public Rectangle
{
public:
	Car();
	Car(float widthP, float heightP);
	~Car();

	// ======================================
	void load();

	void update(float dtP);
	void screenCollisions();

	void inputs();

	void draw();

	void resetCar(float xP, float yP);

	void unload();

	// Getters ==============================
	inline Texture2D getTexture() { return texture; }

	inline Rectangle getRect() { return rect; }
	
	inline inline float getSize() { return size; }

	inline float getXSpeed() { return xSpeed; }
	inline float getYSpeed() { return ySpeed; }

	float getPreviousXPos();
	float getPreviousYPos();

	// Setters ==============================
	inline void setTexture(const Texture2D& texP) { texture = texP; }

	void setStartingPos(Vector2 startingPosP);

	inline void setXSpeed(float xSpeedP) { xSpeed = xSpeedP; }
	inline void setYSpeed(float ySpeedP) { ySpeed = ySpeedP; }

	void reverseXSpeed();
	void reverseYSpeed();

private:
	Texture2D texture{ NULL };

	Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };

	Vector2 startingPos{ 0.0f, 0.0f };

	float size{ 0.0f };
	float scale{ 1.0f };
	float width{ 0.0f };
	float height{ 0.0f };

	float speed{ 0.0f };
	float xSpeed{ 0.0f };
	float ySpeed{ 0.0f };

	float angle{ 0.0f };
};

#endif // CAR_H



