#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Button struct for simplicity
typedef struct Button {
    Rectangle bounds;
    const char *text;
    bool clicked;
} Button;

// Function to check if a button is clicked
bool IsButtonClicked(Button button) {
    Vector2 mousePoint = GetMousePosition();
    return CheckCollisionPointRec(mousePoint, button.bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

int main(void) {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crest Bank - Navigation UI");

    SetTargetFPS(60);

    // Bank name
    const char *bankName = "Crest Bank";

    // Buttons
    Button buttons[5] = {
        {{20, 150, 200, 50}, "Account Details", false},
        {{20, 220, 200, 50}, "Deposit/Withdraw", false},
        {{20, 290, 200, 50}, "Check Balance", false},
        {{20, 360, 200, 50}, "Send Money", false},
        {{20, 430, 200, 50}, "Logout", false}
    };

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        for (int i = 0; i < 5; i++) {
            buttons[i].clicked = IsButtonClicked(buttons[i]);
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw navigation bar background
        DrawRectangle(10, 100, 240, 450, LIGHTGRAY);
        DrawRectangleLines(10, 100, 240, 450, BLACK);

        // Draw bank name
        DrawText(bankName, SCREEN_WIDTH / 2 - MeasureText(bankName, 40) / 2, 30, 40, DARKGRAY);

        // Draw buttons
        for (int i = 0; i < 5; i++) {
            Color buttonColor = buttons[i].clicked ? DARKGRAY : GRAY;
            DrawRectangleRec(buttons[i].bounds, buttonColor);
            DrawRectangleLinesEx(buttons[i].bounds, 2, BLACK);
            DrawText(buttons[i].text, 
                     buttons[i].bounds.x + buttons[i].bounds.width / 2 - MeasureText(buttons[i].text, 20) / 2, 
                     buttons[i].bounds.y + buttons[i].bounds.height / 2 - 10, 20, WHITE);
        }

        EndDrawing();
    }

    // Deinitialization
    CloseWindow();

    return 0;
}
