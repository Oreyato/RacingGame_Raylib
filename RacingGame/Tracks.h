#ifndef TRACKS_H
#define TRACKS_H

#include "raylib.h"
#include <vector>

#include "MathsUtils.h"
using MathsUtils::Vector2Int;

struct Level;

struct Track
{
	Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };

	int type{ 0 };
	// Texture2D texture;

	bool isVisible{ false };
};

class Tracks : public Rectangle
{
public:
	Tracks();
	~Tracks();

	void draw();

	void loadTracksGrid(Level& levelP);

	int trackCoordinatesToIndex(int rowTrackP, int columnTrackP);
	Vector2Int indexToTrackCoordinates(int indexP);
	Vector2 trackCoordinatesToWindowCoordinates(Vector2Int trackCoordP);
	Vector2 indexToWindowCoordinates(int indexP);

	void setTextures(Texture2D roadTextP,
		Texture2D goalTextP,
		Texture2D wallTextP,
		Texture2D grassTextP);

	inline const float getTrackWidth() const { return trackWidth; }
	inline const float getTrackHeight() const { return trackHeight; }
	inline const int getMaxTracks() const { return maxTracks; }

	inline std::vector<Track> getTracks() const { return tracks; }
	inline const int getTrackType(int indexP) const { return tracks[indexP].type; }

private:
	Texture2D roadText{ NULL };
	Texture2D goalText{ NULL };
	Texture2D wallText{ NULL };
	Texture2D grassText{ NULL };

	Texture2D textures[9];

	float trackWidth{ 0.0f };
	float trackHeight{ 0.0f };

	int columnTracks{ 0 };
	int rowTracks{ 0 };
	int maxTracks{ 0 };

	float spacing{ 0.0f };

	std::vector<Track> tracks{ NULL };
};

#endif // TRACKS_H


