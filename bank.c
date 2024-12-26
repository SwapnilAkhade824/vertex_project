#include "raylib.h"
#include <string.h>

#define MAX_INPUT_CHARS 50

typedef enum AppState {
    LOGIN,
    HOME
} AppState;

int main() {
    // Screen dimensions
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Banking System with Input Handling");

    // App State
    AppState appState = LOGIN;

    // Input fields
    char username[MAX_INPUT_CHARS + 1] = "";
    char password[MAX_INPUT_CHARS + 1] = "";
    bool isPasswordHidden = true;
    bool usernameActive = false;
    bool passwordActive = false;

    // Mock credentials
    const char *validUsername = "user123";
    const char *validPassword = "password123";

    // Status message
    char statusMessage[100] = "";

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (appState == LOGIN) {
            // Login Page
            DrawText("Login to Banking System", screenWidth / 2 - MeasureText("Login to Banking System", 30) / 2, 50, 30, WHITE);

            // Username Field
            DrawRectangle(300, 150, 200, 40, usernameActive ? LIGHTGRAY : GRAY);
            DrawText("Username:", 200, 160, 20, WHITE);
            DrawText(username, 310, 160, 20, RAYWHITE);

            // Password Field
            DrawRectangle(300, 220, 200, 40, passwordActive ? LIGHTGRAY : GRAY);
            DrawText("Password:", 200, 230, 20, WHITE);
            if (isPasswordHidden) {
                char hiddenPassword[MAX_INPUT_CHARS + 1];
                memset(hiddenPassword, '*', strlen(password));
                hiddenPassword[strlen(password)] = '\0';
                DrawText(hiddenPassword, 310, 230, 20, RAYWHITE);
            } else {
                DrawText(password, 310, 230, 20, RAYWHITE);
            }

            // Login Button
            DrawRectangle(300, 300, 200, 40, BLUE);
            DrawText("Login", 360, 310, 20, WHITE);

            // Status Message
            DrawText(statusMessage, screenWidth / 2 - MeasureText(statusMessage, 20) / 2, 400, 20, RED);

            // Mouse Interaction
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, (Rectangle){300, 150, 200, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                usernameActive = true;
                passwordActive = false;
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){300, 220, 200, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                usernameActive = false;
                passwordActive = true;
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){300, 300, 200, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Validate Login
                if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
                    appState = HOME;
                    strcpy(statusMessage, "Login successful!");
                } else {
                    strcpy(statusMessage, "Invalid username or password!");
                }
            }

            // Keyboard Interaction for Inputs
            int key = GetCharPressed();
            if (usernameActive) {
                if (key >= 32 && key <= 126 && strlen(username) < MAX_INPUT_CHARS) {
                    username[strlen(username)] = (char)key;
                    username[strlen(username) + 1] = '\0';
                }

                if (IsKeyPressed(KEY_BACKSPACE) && strlen(username) > 0) {
                    username[strlen(username) - 1] = '\0';
                }
            } else if (passwordActive) {
                if (key >= 32 && key <= 126 && strlen(password) < MAX_INPUT_CHARS) {
                    password[strlen(password)] = (char)key;
                    password[strlen(password) + 1] = '\0';
                }

                if (IsKeyPressed(KEY_BACKSPACE) && strlen(password) > 0) {
                    password[strlen(password) - 1] = '\0';
                }
            }

            // Toggle Password Visibility
            if (IsKeyPressed(KEY_TAB)) {
                isPasswordHidden = !isPasswordHidden;
            }
        } else if (appState == HOME) {
            // Home Page
            DrawText("Welcome to the Home Page", screenWidth / 2 - MeasureText("Welcome to the Home Page", 30) / 2, 50, 30, WHITE);
            DrawText("Press ESC to logout", 50, screenHeight - 50, 20, LIGHTGRAY);

            if (IsKeyPressed(KEY_ESCAPE)) {
                appState = LOGIN;
                memset(username, 0, sizeof(username));
                memset(password, 0, sizeof(password));
                strcpy(statusMessage, "");
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
