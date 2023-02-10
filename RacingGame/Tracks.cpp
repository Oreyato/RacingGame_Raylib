#include "Tracks.h"

#include <iostream>
#include "raylib.h"

#include "Consts.h"
#include "Levels.h"

Tracks::Tracks()
{
	trackWidth = Consts::WIDTH_TRACK;
	trackHeight = Consts::HEIGHT_TRACK;

	columnTracks = 1;
    rowTracks = 1;
	maxTracks = columnTracks * rowTracks;

	spacing = Consts::SPACING_TRACKS;

    textures.resize(9);
}

Tracks::~Tracks()
{
}

void Tracks::draw()
{
    for each (Tile track in tracks) {
        DrawTexture(textures[track.type][0], track.rect.x, track.rect.y, WHITE);
    }
}

void Tracks::loadTracksGrid(Level& levelP, Vector2& offsetP)
{
    for (int eachRow = 0; eachRow < rowTracks; eachRow++)
    {
        for (int eachColumn = 0; eachColumn < columnTracks; eachColumn++)
        {
            // Tile position
            int xPos = offsetP.x + trackWidth * eachColumn;
            int yPos = offsetP.y + trackHeight * eachRow;

            // Rectangle to fit in the Tile struct
            Rectangle rect{ xPos, yPos, trackWidth - spacing, trackHeight - spacing };

            // Create the track
            Tile track{ rect, true };
            // ... and add it to the tracks vector
            tracks.push_back(track);
        }
    }

    for (int i = 0; i < maxTracks; i++)
    {   
        tracks[i].type = levelP.description[i];
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

void Tracks::setTextures(std::vector<Texture2D> roadTextsP,
    std::vector<Texture2D> goalTextsP,
    std::vector<Texture2D> wallTextsP,
    std::vector<Texture2D> grassTextsP)
{
    textures[Consts::ROAD_LEVEL] = roadTextsP;
    textures[Consts::GOAL_LEVEL] = goalTextsP;
    textures[Consts::WALL_LEVEL] = wallTextsP;
    textures[Consts::GRASS_LEVEL] = grassTextsP;
}

void Tracks::setTrackGridDimensions(const Level& currentLevelP)
{
    rowTracks = currentLevelP.rowNb;
    columnTracks = currentLevelP.colNb;

    maxTracks = rowTracks * columnTracks;
}
