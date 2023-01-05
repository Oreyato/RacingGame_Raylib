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
void carTrackCollision();
bool AABBAlgorithm(Rectangle a, Rectangle b);
void resetGame();

// ====================================
// Rules ==============================
int life = Consts::MAX_LIFE;
bool isPlaying = false;

// ====================================
// Car ===============================
// Initial position
float X_POS_CAR = Consts::WIDTH_SCREEN / 2.0f - 80.0f;
float Y_POS_CAR = Consts::HEIGHT_SCREEN - 60.0f;

Car car{ X_POS_CAR, Y_POS_CAR, (float) Consts::SIZE_CAR, (float) Consts::SIZE_CAR };

// ====================================
// Tracks =============================
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
    track.initTracksGrid();

    // Load textures
    Texture2D carTex = LoadTexture("../Ressources/car_01.png");

    // Set textures
    car.setTexture(carTex);

    isPlaying = true;
    //^ Game specifics ===============================================
}

// Unload game
void unload()
{
    car.unload();

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
        car.update();

        //^ Car ==========================================================
        //v Collisions ===================================================
        carTrackCollision();

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
        // DrawRectangleRec(car.getRect(), WHITE);
        car.draw();

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

void carTrackCollision() {
    // Testing if the car collides with the tracks
    vector<Track> tracks = track.getTracks();
    // Translate car coordinates into tracks coordinates
    int columnTrack = floor((car.getRect().x + car.getSize() / 2) / track.getTrackWidth());
    int rowTrack = floor((car.getRect().y + car.getSize() / 2) / track.getTrackHeight());
    // Search for the track index
    int index = track.trackCoordinatesToIndex(rowTrack, columnTrack);
    // Is the car where a track should be (non visible)? 
    if (index >= 0 && index < track.getMaxTracks()) {
        if (tracks[index].isVisible)
        {
            // Find which track side the car is colliding with
            // using car's previous position
            float prevCarX = car.getPreviousXPos();
            float prevCarY = car.getPreviousYPos();

            int prevColTrack = floor((prevCarX + car.getSize() / 2) / track.getTrackWidth());
            int prevRowTrack = floor((prevCarY + car.getSize() / 2) / track.getTrackHeight());

            bool bothTestsFailed = true;

            // Car came from the left/right
            if (prevColTrack != columnTrack) {
                int adjacentTrackIndex = track.trackCoordinatesToIndex(rowTrack, prevColTrack);

                if (!tracks[adjacentTrackIndex].isVisible) {
                    car.reverseXSpeed();

                    bothTestsFailed = false;
                }
            }
            // Car came from the top/bottom
            if (prevRowTrack != rowTrack) {
                int adjacentTrackIndex = track.trackCoordinatesToIndex(prevRowTrack, columnTrack);

                if (!tracks[adjacentTrackIndex].isVisible) {
                    car.reverseYSpeed();

                    bothTestsFailed = false;
                }
            }
            // Perfectly hitting the corner 
            if (bothTestsFailed) {
                car.reverseXSpeed();
                car.reverseYSpeed();
            }

            // cout << "x: " << columnTrack << " | y: " << rowTrack << endl;
        }
    }
}

bool AABBAlgorithm(Rectangle a, Rectangle b) {
    // Initiate rectangle a variables
    float xMinA = a.x;
    float yMinA = a.y;
    float xMaxA = a.x + a.width;
    float yMaxA = a.y + a.height;
    // Initiate rectangle b variables
    float xMinB = b.x;
    float yMinB = b.y;
    float xMaxB = b.x + b.width;
    float yMaxB = b.y + b.height;

    return (!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
}

void resetGame() {
    // Car
    car.resetCar(X_POS_CAR, Y_POS_CAR);

    // Game
    life = Consts::MAX_LIFE;
    state = 0;
}