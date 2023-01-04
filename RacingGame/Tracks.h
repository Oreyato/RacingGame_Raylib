#ifndef TRACKS_H
#define TRACKS_H

#include "raylib.h"
#include <vector>

struct Track
{
	Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };
	bool isVisible{ false };
};

class Tracks : public Rectangle
{
public:
	Tracks();
	~Tracks();

	void initTracksGrid();
	void loadLevel(int levelIndexP);

	int trackCoordinatesToIndex(int rowTrackP, int columnTrackP);

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


