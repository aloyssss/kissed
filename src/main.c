#define KISSED_IMPLEMENTATION
#include "kissed.h"

int main(void) 
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Minimal Text Editor");

    // Load the default font
    Font font = LoadFont("./assets/consolas.ttf");
    int fontSize = 20;
    Color textColor = WHITE;

    const char *sampleText = "This is a sample text to demonstrate basic text rendering and wrapping in a minimal text editor using Raylib.";

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Render the sample text with wrapping
        DrawTextBoxed(font, sampleText, (Rectangle){4, 4, screenWidth - 4, screenHeight - 4 }, fontSize, 2.0f, 1, textColor);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}