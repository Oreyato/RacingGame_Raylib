#ifndef CONSTS_H
#define CONSTS_H

class Consts
{
public:
	// Screen
	static const int WIDTH_SCREEN;
	static const int HEIGHT_SCREEN;

	// Rules
	static const int MAX_LIFE;

	// Car
	static const float SIZE_CAR;
	static const float ANGLE_CAR;

	static const float MAX_SPEED_CAR;
	static const float MAX_ANGLE_SPEED_CAR;
	static const float ACCELERATION_FACTOR_CAR;
	static const float BREAK_FACTOR_CAR;
	static const float DECELERATION_FACTOR_CAR;
	static const float EPSILON_CAR;


	// Tracks
	static const float WIDTH_TRACK;
	static const float HEIGHT_TRACK;

	static const int COLUMN_TRACKS;
	static const int ROW_TRACKS;
	static const float SPACING_TRACKS;
};

#endif // CONSTS_H
