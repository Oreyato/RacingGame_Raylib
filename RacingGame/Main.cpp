#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>

#include "Consts.h"
#include "Levels.h"

using namespace std;

//v ==============================================================
//v Global init ==================================================
// Methods
void load();
void unload();
void update();
void draw();
void drawUi();

// State
int state = 0;
//^ Global init ==================================================
//v Game specific init ===========================================
bool AABBAlgorithm(Rectangle a, Rectangle b);
int trackCoordinatesToIndex(int rowTrack, int columnTrack);
void resetGame();

// Rules ==============================
int life = Consts::MAX_LIFE;

// ====================================
// Car ===============================
int xSpeedCar = -Consts::SPEED_CAR;
int ySpeedCar = -Consts::SPEED_CAR;

// Initial position
const int X_POS_CAR = Consts::WIDTH_SCREEN / 2 - Consts::SIZE_CAR / 2;
const int Y_POS_CAR = Consts::HEIGHT_SCREEN - 85;

Rectangle car{ X_POS_CAR, Y_POS_CAR, Consts::SIZE_CAR, Consts::SIZE_CAR };

// ====================================
// Tracks =============================
// Single track
struct Track {
    Rectangle rect;
    bool isVisible;
};

Rectangle rect{ 0, 0, Consts::WIDTH_TRACK, Consts::HEIGHT_TRACK };
Track track{ rect, true };

// Creating multiple tracks
const int MAX_TRACKS = Consts::ROW_TRACKS * Consts::COLUMN_TRACKS;

vector<Track> tracks;

//^ Game specific init ===========================================

int main(int argc, char* argv[])
{
    load();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        update();
        draw();
    }

    unload();

    return 0;
}

// Load game
void load()
{
    // Create the window 
    string windowName = "RacingGame";
    InitWindow(Consts::WIDTH_SCREEN, Consts::HEIGHT_SCREEN, windowName.c_str());
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    //v Sounds init ==================================================
    // Enable raylib audio system
    InitAudioDevice();

    //^ Sounds init ==================================================

    //v Game specifics ===============================================
    // Initiate the grid of tracks
    for (int i = 0; i < Consts::ROW_TRACKS; i++)
    {
        for (int j = 0; j < Consts::COLUMN_TRACKS; j++)
        {
            // Track position
            int xPos = Consts::WIDTH_TRACK * j;
            int yPos = Consts::HEIGHT_TRACK * i;

            // Rectangle to fit in the Track struct
            Rectangle rect{ xPos, yPos, Consts::WIDTH_TRACK - Consts::SPACING_TRACKS, Consts::HEIGHT_TRACK - Consts::SPACING_TRACKS };

            // Create the track
            Track track{ rect, true };
            // ... and add it to the tracks vector
            tracks.push_back(track);
        }
    }

    for (int i = 0; i < Consts::COLUMN_TRACKS * Consts::ROW_TRACKS; i++)
    {
        if (Levels::LEVEL_001[i] == 0) {
            tracks[i].isVisible = false;
        }
    }

    //^ Game specifics ===============================================
}

// Unload game
void unload()
{
    CloseWindow();
}

// Game update
void update()
{
    if (state == 1) {
        // If the player win
        if (IsKeyDown(KEY_R)) {
            resetGame();
        }
    }
    else if (state == 2) {
        // If the player lose
        if (IsKeyDown(KEY_R)) {
            resetGame();
        }
    }
    else {
        // Default game
        //v Car ==========================================================
        car.x += xSpeedCar;
        car.y += ySpeedCar;

        // Testing if the car goes out of screen
        // ... from the top
        if (car.y <= 0) {
            // Reverse speed along the y axis
            ySpeedCar *= -1;
            // Reset car position
            car.y = 0;
        }
        // ... from the bottom (disappearing completely)
        else if (car.y >= Consts::HEIGHT_SCREEN) {
            // Reverse speed along the y axis
            ySpeedCar *= -1;
            // Reset car x position a bit above the paddle
            car.y = Consts::HEIGHT_SCREEN - 150;
            // Reset car y position at the center of the screen
            car.x = Consts::WIDTH_SCREEN / 2 - car.width / 2;

            // Remove one life
            life -= 1;

            // Test if there are no remaining life
            if (life <= 0) {
                // Change the game state to 2 (game over)
                state = 2;
            }
        }
        // ... from the left or the right
        else if (car.x <= 0) {
            // Reverse speed along the x axix
            xSpeedCar *= -1;
            // Reset car position 
            car.x = 0;
        }
        // ... from the left or the right
        else if (car.x >= Consts::WIDTH_SCREEN - car.width) {
            // Reverse speed along the x axix
            xSpeedCar *= -1;
            // Reset car position 
            car.x = Consts::WIDTH_SCREEN - car.width;
        }
        
        // Moving the car according to player input
        // Moving left 
        if (IsKeyDown(KEY_A)) {
        }
        // Moving right
        else if (IsKeyDown(KEY_D)) {
        }
        //^ Car ==========================================================
        //v Collisions ===================================================
        // Testing if the car collides with the tracks
        //// Translate car coordinates into tracks coordinates
        //int columnTrack = (car.x + Consts::SIZE_CAR / 2) / Consts::WIDTH_TRACK;
        //int rowTrack = car.y / Consts::HEIGHT_TRACK;
        //// Search for the track index
        //int index = trackCoordinatesToIndex(rowTrack, columnTrack);
        //// Is the car where a track should be (non visible)? 
        //if (index >= 0 && index < MAX_TRACKS && tracks[index].isVisible) {
        //    // Reverse car speed along the y axis
        //    ySpeedCar *= -1;
        //}
        
        // HEAVY COLLISION SYSTEM
        for (Track& track : tracks)
        {
            if (!track.isVisible) {
                continue;
            }

            if (AABBAlgorithm(car, track.rect)) {
                // Reverse car speed along the y axis
                ySpeedCar *= -1;
            }
        }
        //^ Collisions ===================================================
    }
}

// Draw game
void draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (state == 0)
    {
        // Draw car
        DrawRectangleRec(car, WHITE);
        // Draw all tracks
        for (Track& track : tracks)
        {
            if (track.isVisible) {
                DrawRectangleRec(track.rect, GREEN);
            }
        }

        drawUi();
    }
    else if (state == 1) {
        DrawText("You won", 300, 200, 50, LIGHTGRAY);

        DrawText("Press R to try again", 350, 300, 20, LIGHTGRAY);
        DrawText("Press ESC to quit", 350, 350, 20, LIGHTGRAY);
    }
    else if (state == 2) {
        DrawText("You lose...", 300, 200, 50, LIGHTGRAY);

        DrawText("Press R to try again", 350, 300, 20, LIGHTGRAY);
        DrawText("Press ESC to quit", 350, 350, 20, LIGHTGRAY);
    }

    EndDrawing();
}

// Draw UI
void drawUi()
{
    DrawText("Life:", 10, 10, 20, WHITE);
    DrawText(to_string(life).c_str(), 60, 10, 20, WHITE);
}

bool AABBAlgorithm(Rectangle a, Rectangle b) {
    // Initiate rectangle a variables
    int xMinA = a.x;
    int yMinA = a.y;
    int xMaxA = a.x + a.width;
    int yMaxA = a.y + a.height;
    // Initiate rectangle b variables
    int xMinB = b.x;
    int yMinB = b.y;
    int xMaxB = b.x + b.width;
    int yMaxB = b.y + b.height;

    return (!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
}

int trackCoordinatesToIndex(int rowTrack, int columnTrack) {
    return rowTrack * Consts::COLUMN_TRACKS + columnTrack;
}

void resetGame() {
    // Car
    car.x = X_POS_CAR;
    car.y = Y_POS_CAR;
    xSpeedCar = Consts::SPEED_CAR;
    ySpeedCar = Consts::SPEED_CAR;

    // Tracks
    for (Track& track : tracks) {
        if (track.isVisible) {
            continue;
        }

        track.isVisible = true;
    }

    // Game
    life = Consts::MAX_LIFE;
    state = 0;
}