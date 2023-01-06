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
	static const float MIN_ANGLE_SPEED_CAR;

	static const float ACCELERATION_FACTOR_CAR;
	static const float BREAK_FACTOR_CAR;
	static const float DECELERATION_FACTOR_CAR;
	static const float EPSILON_CAR;

	// Levels
	static const int ROAD_LEVEL;
	static const int ROAD_WALL;
	static const int ROAD_PLAYERA_START;
	static const int ROAD_PLAYERB_START;
	static const int ROAD_END;

	// Tracks
	static const float WIDTH_TRACK;
	static const float HEIGHT_TRACK;

	static const int COLUMN_TRACKS;
	static const int ROW_TRACKS;
	static const float SPACING_TRACKS;
};

#endif // CONSTS_H
