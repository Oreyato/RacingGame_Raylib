#ifndef TRACKS_H
#define TRACKS_H

#include "raylib.h"
#include <vector>

#include "MathsUtils.h"
using MathsUtils::Vector2Int;

struct Level;

struct Tile
{
	Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };

	int type{ 0 };

	bool isVisible{ false };
};

class Tracks : public Rectangle
{
public:
	Tracks();
	~Tracks();

	void draw();

	void loadTracksGrid(Level& levelP, Vector2& offsetP = Vector2{ 0.0f, 0.0f});

	int trackCoordinatesToIndex(int rowTrackP, int columnTrackP);
	Vector2Int indexToTrackCoordinates(int indexP);
	Vector2 trackCoordinatesToWindowCoordinates(Vector2Int trackCoordP);
	Vector2 indexToWindowCoordinates(int indexP);

	void setTextures(std::vector<Texture2D> roadTextsP,
		std::vector<Texture2D> goalTextsP,
		std::vector<Texture2D> wallTextsP,
		std::vector<Texture2D> grassTextsP);

	void setTrackGridDimensions(const Level& currentLevelP);

	inline const float getTrackWidth() const { return trackWidth; }
	inline const float getTrackHeight() const { return trackHeight; }

	inline const int getColumnTracks() const { return columnTracks; }
	inline const int getRowTracks() const { return rowTracks; }
	inline const int getMaxTracks() const { return maxTracks; }

	inline const float getTrackTotalWidth() const { return columnTracks * trackWidth; }
	inline const float getTrackTotalHeight() const { return rowTracks * trackHeight; }

	inline std::vector<Tile> getTracks() const { return tracks; }
	inline const int getTrackType(int indexP) const { return tracks[indexP].type; }

private:
	Texture2D roadText{ NULL };
	Texture2D goalText{ NULL };
	Texture2D wallText{ NULL };
	Texture2D grassText{ NULL };

	std::vector<std::vector<Texture2D>> textures;

	float trackWidth{ 0.0f };
	float trackHeight{ 0.0f };

	int columnTracks{ 1 };
	int rowTracks{ 1 };
	int maxTracks{ 1 };

	float spacing{ 0.0f };

	std::vector<Tile> tracks{ NULL };
};

#endif // TRACKS_H


