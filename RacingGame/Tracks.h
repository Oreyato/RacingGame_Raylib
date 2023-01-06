#ifndef TRACKS_H
#define TRACKS_H

#include "raylib.h"
#include <vector>

#include "MathsUtils.h"
using MathsUtils::Vector2Int;

struct Track
{
	Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };

	int type{ 0 };
	Texture2D texture;

	bool isVisible{ false };
};

class Tracks : public Rectangle
{
public:
	Tracks();
	~Tracks();

	void draw();

	void loadTracksGrid(const std::vector<int>& levelP);

	int trackCoordinatesToIndex(int rowTrackP, int columnTrackP);
	Vector2Int indexToTrackCoordinates(int indexP);
	Vector2 trackCoordinatesToWindowCoordinates(Vector2Int trackCoordP);
	Vector2 indexToWindowCoordinates(int indexP);

	inline void setRoadTexture(Texture2D textP) { roadText = textP; }
	inline void setWallTexture(Texture2D textP) { wallText = textP; }
	void setTracksTextures();

	inline float getTrackWidth() const { return trackWidth; }
	inline float getTrackHeight() const { return trackHeight; }
	inline int getMaxTracks() const { return maxTracks; }

	inline std::vector<Track> getTracks() const { return tracks; }

private:
	Texture2D roadText{ NULL };
	Texture2D wallText{ NULL };

	float trackWidth{ 0.0f };
	float trackHeight{ 0.0f };

	int columnTracks{ 0 };
	int rowTracks{ 0 };
	int maxTracks{ 0 };

	float spacing{ 0.0f };

	std::vector<Track> tracks{ NULL };
};

#endif // TRACKS_H


