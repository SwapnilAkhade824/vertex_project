#include <raylib.h>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Crest Bank - Login Page");

    // Load the Crest Bank logo image
    Texture2D logo = LoadTexture("resources/crest_bank_logo.jpg"); // Replace with your saved image path

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Start Drawing
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw the Crest Bank Logo at the top center
        DrawTexture(logo, screenWidth / 2 - logo.width / 2, 20, WHITE);

        // Draw Bank Name
        DrawText("Crest Bank", screenWidth / 2 - MeasureText("Crest Bank", 40) / 2, logo.height + 40, 40, DARKGRAY);

        // Draw Login Box
        int boxWidth = 400;
        int boxHeight = 300;
        int boxX = screenWidth / 2 - boxWidth / 2;
        int boxY = screenHeight / 2 - boxHeight / 2 + 50; // Adjusted down to make space for the logo
        DrawRectangle(boxX, boxY, boxWidth, boxHeight, LIGHTGRAY);
        DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, GRAY);

        // Username Field
        int inputBoxHeight = 30;
        DrawText("Username:", boxX + 20, boxY + 40, 20, BLACK);
        DrawRectangle(boxX + 20, boxY + 70, boxWidth - 40, inputBoxHeight, WHITE);
        DrawRectangleLines(boxX + 20, boxY + 70, boxWidth - 40, inputBoxHeight, DARKGRAY);

        // Password Field
        DrawText("Password:", boxX + 20, boxY + 120, 20, BLACK);
        DrawRectangle(boxX + 20, boxY + 150, boxWidth - 40, inputBoxHeight, WHITE);
        DrawRectangleLines(boxX + 20, boxY + 150, boxWidth - 40, inputBoxHeight, DARKGRAY);

        // Sign In Button
        int buttonWidth = 120;
        int buttonHeight = 40;
        int signInButtonX = boxX + (boxWidth / 2) - (buttonWidth / 2);
        int signInButtonY = boxY + 200;
        DrawRectangle(signInButtonX, signInButtonY, buttonWidth, buttonHeight, DARKBLUE);
        DrawText("Sign In", signInButtonX + (buttonWidth / 2) - MeasureText("Sign In", 20) / 2, signInButtonY + 10, 20, WHITE);

        // Create Account Button
        buttonWidth = 180;
        int createAccountButtonX = boxX + (boxWidth / 2) - (buttonWidth / 2);
        int createAccountButtonY = signInButtonY + buttonHeight + 20; // Added space between buttons
        DrawRectangle(createAccountButtonX, createAccountButtonY, buttonWidth, buttonHeight, DARKGREEN);
        DrawText("Create Account", createAccountButtonX + (buttonWidth / 2) - MeasureText("Create Account", 20) / 2, createAccountButtonY + 10, 20, WHITE);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(logo); // Unload the logo image
    CloseWindow();

    return 0;
}
