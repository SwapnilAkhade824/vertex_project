#include <raylib.h>

// Define a button structure for reuse
typedef struct Button {
    Rectangle bounds;
    const char *text;
    Color normalColor;
    Color hoverColor;
    bool isHovered;
} Button;

// Function to draw a button
bool DrawButton(Button button) {
    // Check if the mouse is over the button
    Vector2 mousePoint = GetMousePosition();
    button.isHovered = CheckCollisionPointRec(mousePoint, button.bounds);

    // Set color based on hover state
    Color color = button.isHovered ? button.hoverColor : button.normalColor;

    // Draw button background and text
    DrawRectangleRec(button.bounds, color);
    DrawText(button.text, 
             button.bounds.x + button.bounds.width / 2 - MeasureText(button.text, 20) / 2, 
             button.bounds.y + button.bounds.height / 2 - 10, 
             20, 
             WHITE);

    // Return true if clicked
    return button.isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Best UI Page with Raylib");

    // Define colors
    Color backgroundColor = DARKGRAY;

    // Define buttons
    Button button1 = { { screenWidth / 2 - 100, screenHeight / 2 - 60, 200, 50 }, "Start", GRAY, LIGHTGRAY };
    Button button2 = { { screenWidth / 2 - 100, screenHeight / 2 + 10, 200, 50 }, "Quit", GRAY, LIGHTGRAY };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update logic
        if (DrawButton(button1)) {
            backgroundColor = BLUE;  // Change background on "Start" button click
        }
        if (DrawButton(button2)) {
            break;  // Exit on "Quit" button click
        }

        // Draw UI
        BeginDrawing();
        ClearBackground(backgroundColor);

        // Draw header
        DrawText("Welcome to the Best UI Page", 
                 screenWidth / 2 - MeasureText("Welcome to the Best UI Page", 30) / 2, 
                 50, 
                 30, 
                 RAYWHITE);

        // Draw buttons (already drawn in update logic)

        EndDrawing();
    }

    CloseWindow();  // Close window and OpenGL context

    return 0;
}
