#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>


using namespace std;

//Editor Variable
void Update();
void Draw();
void DrawUi();
void Start();

//Setup la taille de l'écran
int const screenWidth = 960;
int const screenHeight = 540;

int main(int argc, char* argv[])
{

    //Créer un écran et on met les fps à 60
    string windowName = "GameWindow";
    InitWindow(screenWidth, screenHeight, windowName.c_str());

    //ToggleFullscreen();
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    Start();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Update();
        // Draw
        Draw();       

    }

    CloseWindow();

    return 0;


}

void Start()
{

}

void Update()
{

}

void Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);


    DrawUi();
    EndDrawing();
}

void DrawUi()
{

}