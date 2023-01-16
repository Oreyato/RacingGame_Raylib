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
void carTrackCollision(Car& carP);
int const getTrackTypeAtPixelCoord(float posX, float posY);
bool AABBAlgorithm(Rectangle a, Rectangle b);
void resetGame();

// Rules ==============================
bool isPlaying = false;

// Levels =============================
Levels levels;

// Car ===============================
// Initial position
float X_POS_CAR = Consts::WIDTH_SCREEN / 2.0f - 80.0f;
float Y_POS_CAR = Consts::HEIGHT_SCREEN - 95.0f;

Car car{ "Red Car", Consts::SIZE_CAR, Consts::SIZE_CAR};
Car carB{ "Blue Car", Consts::SIZE_CAR, Consts::SIZE_CAR};

std::string winner{ "" };

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
    // Load levels
    levels.loadLevels();
    levels.setCurrentLevel(1);

    vector<int>& firstLevel = levels.getCurrentLevel();

    // v Set car init position ==============
    // Find starting pos
    int index[2]{0, 0};
    int iter{ 0 };
    
    for (int i = 0; i < firstLevel.size(); i++)
    {
        if (firstLevel[i] == Consts::PLAYERA_START_LEVEL) {
            index[iter] = i;
            ++iter;

            // Remove the "2" so that it won't create problems
            // for collisions or multiplayer
            firstLevel[i] = 0;
        }
    }
    // Transform to coordinates
    Vector2 carStartingPos = track.indexToWindowCoordinates(index[0]);
    Vector2 carBStartingPos = track.indexToWindowCoordinates(index[1]);

    // Send it to car
    car.setStartingPos(carStartingPos);
    carB.setStartingPos(carBStartingPos);
    // ^ Set car init position ==============

    KeysBinding carBBindings{ KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_KP_0 };

    carB.setBindings(carBBindings);

    // Load first level track
    track.loadTracksGrid(firstLevel);

    // Load textures
    Texture2D carTex = LoadTexture("../Ressources/car_01.png");
    Texture2D carBTex = LoadTexture("../Ressources/car_02.png");

    Texture2D roadTex = LoadTexture("../Ressources/road_01.png");
    Texture2D goalTex = LoadTexture("../Ressources/goal_01.png");
    Texture2D wallTex = LoadTexture("../Ressources/wall_01.png");
    Texture2D grassTex = LoadTexture("../Ressources/grass_01.png");

    // Set textures
    car.setTexture(carTex);
    carB.setTexture(carBTex);
    track.setTextures(roadTex, goalTex, wallTex, grassTex);

    state = 3;
    isPlaying = true;
    //^ Game specifics ===============================================
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
    else if (state == 9) {
        // If the player lose
        if (IsKeyPressed(KEY_R)) {
            resetGame();
        }
    }
    else if (state == 3 && isPlaying)
    {
        // Moving the car according to player input
        car.inputs();
        carB.inputs();

        // Pause button
        if (IsKeyPressed(KEY_P)) {
            isPlaying = !isPlaying;
        }
    }
}

// Game update
void update()
{
    if (state == 0) {
        state = 3;
        isPlaying = true;
    }
    else if (state == 1) {

    }
    else if (state == 2) {

    }
    else if (state == 3 && isPlaying) {
        float dt = GetFrameTime();

        car.update(dt);
        carB.update(dt);

        //v Collisions ===================================================
        int tileType = getTrackTypeAtPixelCoord(car.getNextPos().x, car.getNextPos().y);
        if (tileType == Consts::END_LEVEL) {
            // Finished lap
            isPlaying = false;
            state = 9;
            winner = car.getName();
        }
        else if (tileType == Consts::ROAD_LEVEL) {
            car.setCollide(false);
        }
        else {
            car.setCollide(true);
        }

        int tileBType = getTrackTypeAtPixelCoord(carB.getNextPos().x, carB.getNextPos().y);
        if (tileBType == Consts::END_LEVEL) {
            // Finished lap
            isPlaying = false;
            state = 9;
            winner = carB.getName();
        }
        else if (tileBType == Consts::ROAD_LEVEL) {
            carB.setCollide(false);
        }
        else {
            carB.setCollide(true);
        }

        //^ Collisions ===================================================
    }
    else if (state == 9) {

    }
}

// Draw game
void draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (state == 1) {
        DrawText("You won", 300, 200, 50, LIGHTGRAY);

        DrawText("Press R to try again", 350, 300, 20, LIGHTGRAY);
        DrawText("Press ESC to quit", 350, 350, 20, LIGHTGRAY);
    }
    else if (state == 2) {
        DrawText("You lose...", 300, 200, 50, LIGHTGRAY);

        DrawText("Press R to try again", 350, 300, 20, LIGHTGRAY);
        DrawText("Press ESC to quit", 350, 350, 20, LIGHTGRAY);
    }
    else if (state == 3)
    {
        // Draw all tracks
        for (Track& track : track.getTracks())
        {
            if (track.isVisible) {
                DrawRectangleRec(track.rect, GREEN);
            }
        }

        // Draw track
        track.draw();

        // Draw car
        car.draw();
        carB.draw();

        drawUi();
    }
    else if (state == 9) {
        float baseXPos{ Consts::WIDTH_SCREEN / 8.0f };
        float baseYPos{ Consts::HEIGHT_SCREEN / 8.0f };

        float offset{ Consts::WIDTH_SCREEN / 15.0f };
        int offsetCounter{ 0 };

        DrawText("The finish line",
            baseXPos + offset * offsetCounter, 
            baseYPos + offset * offsetCounter,
            50,
            GOLD);
        ++offsetCounter;

        DrawText("has been crossed",
            baseXPos + offset * offsetCounter,
            baseYPos + offset * offsetCounter,
            50,
            GOLD);
        ++offsetCounter;

        std::string winnerText = "by \"" + winner + "\"";

        DrawText(winnerText.c_str(),
            baseXPos + offset * offsetCounter,
            baseYPos + offset * offsetCounter,
            50,
            GOLD);
        ++offsetCounter;

        DrawText("Press \"R\" to restart",
            baseXPos + offset * offsetCounter,
            baseYPos + offset * (offsetCounter + 2),
            25,
            LIGHTGRAY);
        ++offsetCounter;
    }

    EndDrawing();
}
// Draw UI
void drawUi()
{
    if (state == 3) {
        DrawText(to_string(isPlaying).c_str(), 10, 10, 20, WHITE);
        //DrawText(to_string(life).c_str(), 60, 10, 20, WHITE);

        //v Draw tiles number ============================================
        int index = 0;

        for each (Track track in track.getTracks())
        {
            DrawText(to_string(index).c_str(), track.rect.x, track.rect.y, 10, BLACK);
            ++index;
        }
        //^ Draw tiles number ============================================
    }
}

void carTrackCollision(Car& carP) {
    // Testing if the car collides with the tracks
    vector<Track> tracks = track.getTracks();
    // Translate car coordinates into tracks coordinates
    int columnTrack = floor((carP.getRect().x + carP.getSize() / 2) / track.getTrackWidth());
    int rowTrack = floor((carP.getRect().y + carP.getSize() / 2) / track.getTrackHeight());

    // Check first whether the carP is within any part of the track wall
    if (columnTrack < 0 || columnTrack >= Consts::COLUMN_TRACKS || rowTrack < 0 || rowTrack >= Consts::ROW_TRACKS) {
        return;
    }

    // Search for the track index
    int index = track.trackCoordinatesToIndex(rowTrack, columnTrack);
    // Is the carP where a track should be (non visible)? 
    if (index >= 0 && index < track.getMaxTracks()) {
        if (tracks[index].isVisible)
        {
            // Find which track side the carP is colliding with
            // using carP's previous position
            float prevCarX = carP.getPreviousXPos();
            float prevCarY = carP.getPreviousYPos();

            float carSize = carP.getSize();
            float trackWidth = track.getTrackWidth();

            int prevColTrack = floor((prevCarX + carSize / 2) / trackWidth);
            int prevRowTrack = floor((prevCarY + carSize / 2) / track.getTrackHeight());

            bool bothTestsFailed = true;

            // Car came from the left/right
            if (prevColTrack != columnTrack) {
                int adjacentTrackIndex = track.trackCoordinatesToIndex(rowTrack, prevColTrack);

                if (!tracks[adjacentTrackIndex].isVisible) {
                    carP.reverseXSpeed();

                    bothTestsFailed = false;
                }
            }
            // Car came from the top/bottom
            if (prevRowTrack != rowTrack) {
                int adjacentTrackIndex = track.trackCoordinatesToIndex(prevRowTrack, columnTrack);

                if (!tracks[adjacentTrackIndex].isVisible) {
                    carP.reverseYSpeed();

                    bothTestsFailed = false;
                }
            }
            // Perfectly hitting the corner 
            if (bothTestsFailed) {
                carP.reverseXSpeed();
                carP.reverseYSpeed();
            }

            // cout << "x: " << columnTrack << " | y: " << rowTrack << endl;
        }
    }
}

int const getTrackTypeAtPixelCoord(float posX, float posY) {
    int tileCol = floor(posX / Consts::WIDTH_TRACK);
    int tileRow = floor(posY / Consts::HEIGHT_TRACK);

    // Check first whether the car is within any part of the track wall
    if (tileCol < 0 || tileCol >= Consts::COLUMN_TRACKS || tileRow < 0 || tileRow >= Consts::ROW_TRACKS) {
        // To avoid invalid array access, treat out of bounds as wall
        return Consts::WALL_LEVEL;
    }

    // Search for the track index
    int index = track.trackCoordinatesToIndex(tileRow, tileCol);

    // std::cout << "Tile index: " << index << std::endl;
    
    return track.getTrackType(index);
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
    car.resetCar();
    carB.resetCar();

    // Game
    state = 0;
}

// Unload game
void unload()
{
    car.unload();

    CloseWindow();
}