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


	void inputs();
	void setNextPos(float dtP);
	void update(float dtP);
	void screenCollisions();

	void draw();

	void resetCar();

	void unload();

	// Getters ==============================
	inline const std::string getName() { return name; }

	inline const Texture2D& getTexture() { return texture; }

	inline const Rectangle& getRect() { return rect; }
	
	inline inline float getSize() { return size; }

	inline const Vector2& getNextPos() { return nextPos; }

	// Setters ==============================
	inline void setName(std::string nameP) { name = nameP; }

	inline void setTexture(const Texture2D& texP) { texture = texP; }

	void setStartingPos(Vector2 startingPosP);

	inline void setBindings(KeysBinding newBindingsP) { bindings = newBindingsP; }

	inline void setCollide(bool collideP) { collide = collideP; }

	inline void bounceCar() { speed *= -1.0f * 0.25f; }

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

	Vector2 nextPos{ 0.0f, 0.0f };

	float angle{ 0.0f };

	KeysBinding bindings;

	bool collide{ false };
};

#endif // CAR_H



