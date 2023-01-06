#ifndef TRACKS_H
#define TRACKS_H

#include "raylib.h"
#include <vector>

struct Track
{
	Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };
	bool isVisible{ false };
};

typedef struct Vector2Int {
	int x;
	int y;
} Vector2Int;

class Tracks : public Rectangle
{
public:
	Tracks();
	~Tracks();

	void loadTracksGrid(const std::vector<int>& levelP);

	int trackCoordinatesToIndex(int rowTrackP, int columnTrackP);
	Vector2Int indexToTrackCoordinates(int indexP);
	Vector2 trackCoordinatesToWindowCoordinates(Vector2Int trackCoordP);
	Vector2 indexToWindowCoordinates(int indexP);

	float getTrackWidth() { return trackWidth; }
	float getTrackHeight() { return trackHeight; }
	int getMaxTracks() { return maxTracks; }

	std::vector<Track> getTracks() { return tracks; }

private:
	float trackWidth{ 0.0f };
	float trackHeight{ 0.0f };

	int columnTracks{ 0 };
	int rowTracks{ 0 };
	int maxTracks{ 0 };

	float spacing{ 0.0f };

	std::vector<Track> tracks{ NULL };
};

#endif // TRACKS_H


