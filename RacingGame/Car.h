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
	inline const Texture2D& getTexture() { return texture; }

	inline const Rectangle& getRect() { return rect; }
	
	inline inline float getSize() { return size; }

	inline float getXSpeed() { return xSpeed; }
	inline float getYSpeed() { return ySpeed; }

	float getPreviousXPos();
	float getPreviousYPos();

	inline const Vector2& getNextPos() { return nextPos; }

	// Setters ==============================
	inline void setTexture(const Texture2D& texP) { texture = texP; }

	void setStartingPos(Vector2 startingPosP);

	inline void setXSpeed(float xSpeedP) { xSpeed = xSpeedP; }
	inline void setYSpeed(float ySpeedP) { ySpeed = ySpeedP; }

	inline void setCollide(bool collideP) { collide = collideP; }

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

	Vector2 nextPos{ 0.0f, 0.0f };

	float angle{ 0.0f };

	bool collide{ false };
};

#endif // CAR_H



