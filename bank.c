#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
    // Initialize the window and raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crest Bank");

    // Define button properties
    Rectangle accountInfoButton = {SCREEN_WIDTH / 2 - 100, 250, 200, 50};
    Rectangle servicesButton = {SCREEN_WIDTH / 2 - 100, 320, 200, 50};
    Rectangle logoutButton = {SCREEN_WIDTH - 120, SCREEN_HEIGHT - 60, 100, 40};

    // Main game loop
    while (!WindowShouldClose())
    {
        // Check for button interactions
        Vector2 mousePoint = GetMousePosition();

        bool accountInfoHovered = CheckCollisionPointRec(mousePoint, accountInfoButton);
        bool servicesHovered = CheckCollisionPointRec(mousePoint, servicesButton);
        bool logoutHovered = CheckCollisionPointRec(mousePoint, logoutButton);

        if (accountInfoHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Perform Account Info action
            TraceLog(LOG_INFO, "Account Information button clicked!");
        }

        if (servicesHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Perform Services action
            TraceLog(LOG_INFO, "Services button clicked!");
        }

        if (logoutHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Perform Logout action
            TraceLog(LOG_INFO, "Logout button clicked! Exiting...");
            break;
        }

        // Start drawing
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw the header
        DrawText("Crest Bank", SCREEN_WIDTH / 2 - MeasureText("Crest Bank", 40) / 2, 50, 40, DARKBLUE);
        DrawText("HOMEPAGE", SCREEN_WIDTH / 2 - MeasureText("HOMEPAGE", 20) / 2, 100, 20, DARKGRAY);

        // Draw buttons
        DrawRectangleRec(accountInfoButton, accountInfoHovered ? LIGHTGRAY : SKYBLUE);
        DrawRectangleRec(servicesButton, servicesHovered ? LIGHTGRAY : SKYBLUE);
        DrawRectangleRec(logoutButton, logoutHovered ? LIGHTGRAY : RED);

        // Draw button text
        DrawText("Account Information", SCREEN_WIDTH / 2 - MeasureText("Account Information", 20) / 2, 265, 20, DARKBLUE);
        DrawText("Services", SCREEN_WIDTH / 2 - MeasureText("Services", 20) / 2, 335, 20, DARKBLUE);
        DrawText("Log Out", SCREEN_WIDTH - 110, SCREEN_HEIGHT - 50, 20, WHITE);

        EndDrawing();
    }

    // Close the window and raylib
    CloseWindow();

    return 0;
}
