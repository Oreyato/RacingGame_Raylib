#ifndef CAR_H
#define CAR_H

#include "raylib.h"
#include <string>

struct KeysBinding
{
	int forward{ 87 };
	int backward{ 83 };
	int leftRot{ 65 };
	int rightRot{ 68 };
	
	int breakKey{ 32 };
};

class Car : public Rectangle
{
public:
	Car(std::string nameP);
	Car(std::string nameP, float widthP, float heightP);
	~Car();

	// ======================================
	void load();

	void update(float dtP);
	void screenCollisions();

	void inputs();

	void draw();

	void reset();

	void unload();

	// Getters ==============================
	inline const std::string getName() { return name; }

	inline const Texture2D& getTexture() { return texture; }

	inline const Rectangle& getRect() { return rect; }
	
	inline inline float getSize() { return size; }

	inline float getXSpeed() { return xSpeed; }
	inline float getYSpeed() { return ySpeed; }

	float getPreviousXPos();
	float getPreviousYPos();

	inline const Vector2& getNextPos() { return nextPos; }

	// Setters ==============================
	inline void setName(std::string nameP) { name = nameP; }

	inline void setTexture(const Texture2D& texP) { texture = texP; }

	void setStartingPos(Vector2 startingPosP);

	inline void setXSpeed(float xSpeedP) { xSpeed = xSpeedP; }
	inline void setYSpeed(float ySpeedP) { ySpeed = ySpeedP; }

	inline void setBindings(KeysBinding newBindingsP) { bindings = newBindingsP; }

	inline void setCollide(bool collideP) { collide = collideP; }

	void reverseXSpeed();
	void reverseYSpeed();

private:
	std::string name{ "" };

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

	KeysBinding bindings;

	bool collide{ false };
};

#endif // CAR_H



