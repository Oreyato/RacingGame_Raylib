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
void drawDebug();

// State
int state = 0;

//^ Global init ==================================================
//v Game specific init ===========================================
void manageCamera();
void fillBackground();

void carTrackCollision(Car& carP);
int const getTrackTypeAtPixelCoord(float posX, float posY);
bool AABBAlgorithm(Rectangle a, Rectangle b);
void resetGame();

Camera2D camera;

// Rules ==============================
bool isPlaying = false;

// Levels =============================
Levels levels;

// Cars ===============================
Car carA{ "Red Car", Consts::SIZE_CAR, Consts::SIZE_CAR};
Car carB{ "Blue Car", Consts::SIZE_CAR, Consts::SIZE_CAR};

std::vector<Car*> cars;

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
    levels.setCurrentLevel(3);

    Level currentLevel = levels.getCurrentLevel();

    // Share informations to Track
    track.setTrackGridDimensions(currentLevel);

    // v Textures ===========================
    // Load textures
    Texture2D carATex = LoadTexture("../Ressources/car_01.png");
    Texture2D carBTex = LoadTexture("../Ressources/car_02.png");

    Texture2D roadTex = LoadTexture("../Ressources/road_01.png");
    Texture2D goalTex = LoadTexture("../Ressources/goal_01.png");
    Texture2D wallTex = LoadTexture("../Ressources/wall_01.png");
    Texture2D grassTex = LoadTexture("../Ressources/grass_01.png");

    // Set textures
    carA.setTexture(carATex);
    carB.setTexture(carBTex);
    track.setTextures(roadTex, goalTex, wallTex, grassTex);

    // v Cars ===============================
    // Init B Player bindings
    KeysBinding carBBindings{ KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_KP_0 };
    carB.setBindings(carBBindings);

    // Populate cars vector
    cars.push_back(&carA);
    cars.push_back(&carB);

    // v Set car init position ==============
    // Find starting pos    
    for each (Car* car in cars)
    {
        int iter{ 0 };

        for (int i = 0; i < currentLevel.size; i++)
        {
            if (currentLevel.description[i] == Consts::PLAYERA_START_LEVEL) {
                // Remove the "2" so that it won't create problems
                // for collisions or multiplayer
                currentLevel.description[i] = 0;

                break;
            }
            ++iter;
        }

        // Transform to coordinates
        Vector2 carStartingPos = track.indexToWindowCoordinates(iter);
        // Center the car in the tile
        carStartingPos.x += track.getTrackWidth() / 2.0f;
        carStartingPos.y += track.getTrackWidth() / 2.0f;

        // Send it to car
        car->setStartingPos(carStartingPos);
    }
    // ^ Set car init position ==============

    // Load first level track
    track.loadTracksGrid(currentLevel);
    
    // Camera
    manageCamera();
    // Fill background
    fillBackground();

    state = 3;
    isPlaying = true;
    //^ Game specifics ===============================================
}

float calculateWidthRatio() {
    float trackTotalWidth = track.getTrackTotalWidth();
    return Consts::WIDTH_SCREEN / trackTotalWidth;
}
float calculateHeightRatio() {
    float trackTotalHeight = track.getTrackTotalHeight();
    return Consts::HEIGHT_SCREEN / trackTotalHeight;
}
void manageCamera() {
    // Zoom ============
    float widthRatio = calculateWidthRatio();
    float heightRatio = calculateHeightRatio();

    bool offsetWidth = widthRatio > heightRatio ? true : false;

    float zoomRatio = min(widthRatio, heightRatio);

    camera.zoom = zoomRatio;

    // Offset ==========
    if (offsetWidth) {
        float zoomedWidth = track.getTrackTotalWidth() * heightRatio;
        float screenDiff = Consts::WIDTH_SCREEN - zoomedWidth;

        camera.offset = { screenDiff / 2.0f , 0.0f };
    }
    else {
        float zoomedHeight = track.getTrackTotalHeight() * widthRatio;
        float screenDiff = Consts::HEIGHT_SCREEN - zoomedHeight;

        camera.offset = { 0.0f , screenDiff / 2.0f };
    }

    camera.target = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
}

void fillBackground() {

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
        // Moving cars according to players inputs
        for each (Car* car in cars)
        {
            car->inputs();
        }

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

        for each (Car* car in cars)
        {
            car->setNextPos(dt);

            //v Collisions ===================================================
            int tileType = getTrackTypeAtPixelCoord(car->getNextPos().x, car->getNextPos().y);
            if (tileType == Consts::GOAL_LEVEL) {
                // Finished lap
                isPlaying = false;
                state = 9;
                winner = car->getName();
            }
            else if (tileType == Consts::ROAD_LEVEL) {
                car->update(dt);
            }
            else {
                car->bounceCar();
            }

            //^ Collisions ===================================================
        }
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
        BeginMode2D(camera);
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
        for each (Car* car in cars) {
            car->draw();
        }
        EndMode2D();

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

    // drawDebug();

    EndDrawing();
}
// Draw UI
void drawUi()
{
    if (state == 3) {
        //DrawText(to_string(isPlaying).c_str(), 10, 10, 20, WHITE);
        //DrawText(to_string(life).c_str(), 60, 10, 20, WHITE);
    }
}

void drawDebug() {
    //v Draw tiles number ============================================
    //int index = 0;

    //for each (Track track in track.getTracks())
    //{
    //    DrawText(to_string(index).c_str(), track.rect.x, track.rect.y, 10, BLACK);
    //    ++index;
    //}
    //^ Draw tiles number ============================================
    //v Draw car position ============================================
    DrawRectangle(cars[0]->getRect().x, cars[0]->getRect().y, 5, 5, SKYBLUE);
    DrawRectangle(cars[0]->getNextPos().x, cars[0]->getNextPos().y, 3, 3, RED);
    
    //^ Draw car position ============================================
}

// DEPRECIATED
void carTrackCollision(Car& carP) {
    //// Testing if the car collides with the tracks
    //vector<Track> tracks = track.getTracks();
    //// Translate car coordinates into tracks coordinates
    //int columnTrack = floor((carP.getRect().x + carP.getSize() / 2) / track.getTrackWidth());
    //int rowTrack = floor((carP.getRect().y + carP.getSize() / 2) / track.getTrackHeight());

    //// Check first whether the carP is within any part of the track wall
    //if (columnTrack < 0 || columnTrack >= Consts::COLUMN_TRACKS || rowTrack < 0 || rowTrack >= Consts::ROW_TRACKS) {
    //    return;
    //}

    //// Search for the track index
    //int index = track.trackCoordinatesToIndex(rowTrack, columnTrack);
    //// Is the carP where a track should be (non visible)? 
    //if (index >= 0 && index < track.getMaxTracks()) {
    //    if (tracks[index].isVisible)
    //    {
    //        // Find which track side the carP is colliding with
    //        // using carP's previous position
    //        float prevCarX = carP.getPreviousXPos();
    //        float prevCarY = carP.getPreviousYPos();

    //        float carSize = carP.getSize();
    //        float trackWidth = track.getTrackWidth();

    //        int prevColTrack = floor((prevCarX + carSize / 2) / trackWidth);
    //        int prevRowTrack = floor((prevCarY + carSize / 2) / track.getTrackHeight());

    //        bool bothTestsFailed = true;

    //        // Car came from the left/right
    //        if (prevColTrack != columnTrack) {
    //            int adjacentTrackIndex = track.trackCoordinatesToIndex(rowTrack, prevColTrack);

    //            if (!tracks[adjacentTrackIndex].isVisible) {
    //                carP.reverseXSpeed();

    //                bothTestsFailed = false;
    //            }
    //        }
    //        // Car came from the top/bottom
    //        if (prevRowTrack != rowTrack) {
    //            int adjacentTrackIndex = track.trackCoordinatesToIndex(prevRowTrack, columnTrack);

    //            if (!tracks[adjacentTrackIndex].isVisible) {
    //                carP.reverseYSpeed();

    //                bothTestsFailed = false;
    //            }
    //        }
    //        // Perfectly hitting the corner 
    //        if (bothTestsFailed) {
    //            carP.reverseXSpeed();
    //            carP.reverseYSpeed();
    //        }

    //        // cout << "x: " << columnTrack << "r | y: " << rowTrack << endl;
    //    }
    //}
}

int const getTrackTypeAtPixelCoord(float posX, float posY) {
    int tileCol = posX / track.getTrackWidth();
    int tileRow = posY / track.getTrackHeight();

    tileCol = floor(tileCol);
    tileRow = floor(tileRow);

    // Check first whether the car is within any part of the track wall
    if (tileCol < 0 || tileCol >= track.getColumnTracks() || tileRow < 0 || tileRow >= track.getRowTracks()) {
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
    for each (Car* car in cars)
    {
        car->resetCar();
    }

    // Game
    state = 0;
}

// Unload game
void unload()
{
    for each (Car* car in cars)
    {
        car->unload();
    }

    CloseWindow();
}