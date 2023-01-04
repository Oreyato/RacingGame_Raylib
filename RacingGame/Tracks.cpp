#include "Tracks.h"

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

void Tracks::initTracksGrid()
{
    for (int i = 0; i < rowTracks; i++)
    {
        for (int j = 0; j < columnTracks; j++)
        {
            // Track position
            int xPos = trackWidth * j;
            int yPos = trackHeight * i;

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
        if (Levels::LEVEL_001[i] == 0) {
            tracks[i].isVisible = false;
        }
    }
}

int Tracks::trackCoordinatesToIndex(int rowTrackP, int columnTrackP)
{
    return rowTrackP * columnTracks + columnTrackP;
}
