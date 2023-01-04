#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>

#include "Consts.h"
#include "Levels.h"

#include "Tracks.h"
#include "Car.h"

using namespace std;

#pragma region globals
//v ==============================================================
//v Global init ==================================================
// Methods
void load();
void unload();
void inputs();
void update();
void draw();
void drawUi();

// State
int state = 0;
//^ Global init ==================================================
//v Game specific init ===========================================
bool AABBAlgorithm(Rectangle a, Rectangle b);
void resetGame();

// Rules ==============================
int life = Consts::MAX_LIFE;
bool isPlaying = false;

// ====================================
// Car ===============================
int xSpeedCar = -Consts::SPEED_CAR;
int ySpeedCar = -Consts::SPEED_CAR;

// Initial position
const int X_POS_CAR = Consts::WIDTH_SCREEN / 2 - 80;
const int Y_POS_CAR = Consts::HEIGHT_SCREEN - 60;

Rectangle car{ X_POS_CAR, Y_POS_CAR, Consts::SIZE_CAR, Consts::SIZE_CAR };

// ====================================
// Tracks =============================
Rectangle rect{ 0, 0, Consts::WIDTH_TRACK, Consts::HEIGHT_TRACK };

Tracks track;

//^ Game specific init ===========================================
#pragma endregion

int main(int argc, char* argv[])
{
    load();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        inputs();
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
    SetWindowPosition(25, 50);
    SetTargetFPS(60);

    //v Sounds init ==================================================
    // Enable raylib audio system
    InitAudioDevice();

    //^ Sounds init ==================================================

    //v Game specifics ===============================================
    //// Initiate the grid of tracks
    //for (int i = 0; i < Consts::ROW_TRACKS; i++)
    //{
    //    for (int j = 0; j < Consts::COLUMN_TRACKS; j++)
    //    {
    //        // Track position
    //        int xPos = Consts::WIDTH_TRACK * j;
    //        int yPos = Consts::HEIGHT_TRACK * i;

    //        // Rectangle to fit in the Track struct
    //        Rectangle rect{ xPos, yPos, Consts::WIDTH_TRACK - Consts::SPACING_TRACKS, Consts::HEIGHT_TRACK - Consts::SPACING_TRACKS };

    //        // Create the track
    //        Track track{ rect, true };
    //        // ... and add it to the tracks vector
    //        tracks.push_back(track);
    //    }
    //}

    //for (int i = 0; i < MAX_TRACKS; i++)
    //{
    //    if (Levels::LEVEL_001[i] == 0) {
    //        tracks[i].isVisible = false;
    //    }
    //}

    track.initTracksGrid();

    isPlaying = true;
    //^ Game specifics ===============================================
}

// Unload game
void unload()
{
    CloseWindow();
}

// Handle inputs
void inputs() {
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
        // Moving the car according to player input
        // Moving left 
        if (IsKeyDown(KEY_A)) {
        }
        // Moving right
        else if (IsKeyDown(KEY_D)) {
        }
        if (IsKeyPressed(KEY_SPACE)) {
            isPlaying = !isPlaying;
        }
    }
}

// Game update
void update()
{
    if (state == 1) {

    }
    else if (state == 2) {

    }
    else if (isPlaying) {
        // Default game
        //v Car ==========================================================
        #pragma region Car screen boundaries
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
        // ... from the bottom
        else if (car.y >= Consts::HEIGHT_SCREEN - car.width) {
            // Reverse speed along the y axis
            ySpeedCar *= -1;
        }
        // ... from the left
        else if (car.x <= 0) {
            // Reverse speed along the x axis
            xSpeedCar *= -1;
            // Reset car position 
            car.x = 0;
        }
        // ... from the right
        else if (car.x >= Consts::WIDTH_SCREEN - car.width) {
            // Reverse speed along the x axis
            xSpeedCar *= -1;
            // Reset car position 
            car.x = Consts::WIDTH_SCREEN - car.width;
        }
        #pragma endregion

        //^ Car ==========================================================
        //v Collisions ===================================================
        #pragma region Car / tracks collisions
        // Testing if the car collides with the tracks
        vector<Track> tracks = track.getTracks();
        // Translate car coordinates into tracks coordinates
        int columnTrack = floor((car.x + Consts::SIZE_CAR / 2) / Consts::WIDTH_TRACK);
        int rowTrack = floor((car.y + Consts::SIZE_CAR / 2) / Consts::HEIGHT_TRACK);
        // Search for the track index
        int index = track.trackCoordinatesToIndex(rowTrack, columnTrack);
        // Is the car where a track should be (non visible)? 
        if (index >= 0 && index < track.getMaxTracks()) {
            if (tracks[index].isVisible)
            {
                // Find which track side the car is colliding with
                // using car's previous position
                float prevCarX = car.x - xSpeedCar;
                float prevCarY = car.y - ySpeedCar;

                int prevColTrack = floor((prevCarX + Consts::SIZE_CAR / 2) / Consts::WIDTH_TRACK);
                int prevRowTrack = floor((prevCarY + Consts::SIZE_CAR / 2) / Consts::HEIGHT_TRACK);

                bool bothTestsFailed = true;

                // Car came from the left/right
                if (prevColTrack != columnTrack) {
                    int adjacentTrackIndex = track.trackCoordinatesToIndex(rowTrack, prevColTrack);

                    if (!tracks[adjacentTrackIndex].isVisible) {
                        xSpeedCar *= -1;

                        bothTestsFailed = false;
                    }
                }
                // Car came from the top/bottom
                if (prevRowTrack != rowTrack) {
                    int adjacentTrackIndex = track.trackCoordinatesToIndex(prevRowTrack, columnTrack);

                    if (!tracks[adjacentTrackIndex].isVisible) {
                        ySpeedCar *= -1;

                        bothTestsFailed = false;
                    }
                }
                // Perfectly hitting the corner 
                if (bothTestsFailed) {
                    xSpeedCar *= -1;
                    ySpeedCar *= -1;
                }

                cout << "x: " << columnTrack << " | y: " << rowTrack << endl;
            }
        }
        #pragma endregion

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
        for (Track& track : track.getTracks())
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
    //DrawText("Life:", 10, 10, 20, WHITE);
    //DrawText(to_string(life).c_str(), 60, 10, 20, WHITE);
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

void resetGame() {
    // Car
    car.x = X_POS_CAR;
    car.y = Y_POS_CAR;
    xSpeedCar = Consts::SPEED_CAR;
    ySpeedCar = Consts::SPEED_CAR;

    // Game
    life = Consts::MAX_LIFE;
    state = 0;
}