#include "Consts.h"

// Screen
const int Consts::WIDTH_SCREEN{ 1500 };
const int Consts::HEIGHT_SCREEN{ 1000 };

// Rules
const int Consts::MAX_LIFE{ 3 };

// Car
const float Consts::SIZE_CAR{ 32.0f };
const float Consts::ANGLE_CAR{ -90.0f };

const float Consts::MAX_SPEED_CAR{ 250.0f };
const float Consts::MAX_ANGLE_SPEED_CAR{ 4.5f };
const float Consts::MIN_ANGLE_SPEED_CAR{ 0.0f };

const float Consts::ACCELERATION_FACTOR_CAR{ 7.0f };
const float Consts::BREAK_FACTOR_CAR{ 7.5f };
const float Consts::DECELERATION_FACTOR_CAR{ 0.98f };
const float Consts::EPSILON_CAR{ 0.01f };

// Levels
const int Consts::ROAD_LEVEL{ 0 };
const int Consts::WALL_LEVEL{ 1 }; // 9 and 10 create unexpected behaviours for some reason
const int Consts::GOAL_LEVEL{ 4 }; // <--- 9 
const int Consts::GRASS_LEVEL{ 7 };
const int Consts::GRAVEL_LEVEL{ 6 };
const int Consts::PLAYERA_START_LEVEL{ 8 };
const int Consts::PLAYERB_START_LEVEL{ 8 };
const int Consts::END_LEVEL{ 4 }; // <--- 9

// Tracks
const float Consts::WIDTH_TRACK{ 40.0f };
const float Consts::HEIGHT_TRACK{ 40.0f };

const int Consts::BASE_COLUMN_TRACKS{ 20 };
const int Consts::BASE_ROW_TRACKS{ 15 };
const float Consts::SPACING_TRACKS{ 2.0f };