#include "Tracks.h"

#include <iostream>
#include "raylib.h"

#include "Consts.h"
#include "Levels.h"

Tracks::Tracks()
{
	trackWidth = Consts::WIDTH_TRACK;
	trackHeight = Consts::HEIGHT_TRACK;

	columnTracks = Consts::COLUMN_TRACKS;
    rowTracks = Consts::ROW_TRACKS;
	maxTracks = columnTracks * rowTracks;

	spacing = Consts::SPACING_TRACKS;
}

Tracks::~Tracks()
{
}

void Tracks::draw()
{
    for each (Track track in tracks) {
        DrawTexture(textures[track.type], track.rect.x, track.rect.y, WHITE);
    }
}

void Tracks::loadTracksGrid(const std::vector<int>& levelP)
{
    for (int eachRow = 0; eachRow < rowTracks; eachRow++)
    {
        for (int eachColumn = 0; eachColumn < columnTracks; eachColumn++)
        {
            // Track position
            int xPos = trackWidth * eachColumn;
            int yPos = trackHeight * eachRow;

            // Rectangle to fit in the Track struct
            Rectangle rect{ xPos, yPos, trackWidth - spacing, trackHeight - spacing };

            // Create the track
            Track track{ rect, true };
            // ... and add it to the tracks vector
            tracks.push_back(track);
        }
    }

    for (int i = 0; i < maxTracks; i++)
    {   
        tracks[i].type = levelP[i];

        if (levelP[i] == Consts::ROAD_LEVEL) {
            tracks[i].isVisible = false;
        }
    }
}

int Tracks::trackCoordinatesToIndex(int rowTrackP, int columnTrackP)
{
    return rowTrackP * columnTracks + columnTrackP;
}

Vector2Int Tracks::indexToTrackCoordinates(int indexP) {
    int row = floor(indexP / columnTracks);
    int column = indexP % columnTracks;

    return Vector2Int{ column, row };
}
Vector2 Tracks::trackCoordinatesToWindowCoordinates(Vector2Int trackCoordP) {
    float xPos = trackCoordP.x * trackWidth;
    float yPos = trackCoordP.y * trackHeight;

    return Vector2{ xPos, yPos };
}
Vector2 Tracks::indexToWindowCoordinates(int indexP) {
    return trackCoordinatesToWindowCoordinates(indexToTrackCoordinates(indexP));
}

void Tracks::setTextures(Texture2D roadTextP, Texture2D goalTextP, Texture2D wallTextP, Texture2D grassTextP)
{
    textures[Consts::ROAD_LEVEL] = roadTextP;
    textures[Consts::GOAL_LEVEL] = goalTextP;
    textures[Consts::WALL_LEVEL] = wallTextP;
    textures[Consts::GRASS_LEVEL] = grassTextP;
}