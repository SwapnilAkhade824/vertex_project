#include <raylib.h>
#include <string.h>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Crest Bank - Login Page");

    // Load the Crest Bank logo image
    Texture2D logo = LoadTexture("C:/Dev/raylib-5.5_win64_mingw-w64/logo.jpg"); // Replace with your saved image path

    // Scale the logo to be smaller
    float logoScale = 0.3f; // Adjusted the scale to make the logo smaller
    int logoWidth = logo.width * logoScale;
    int logoHeight = logo.height * logoScale;

    char accountId[30] = ""; // Buffer for Account ID input
    char password[30] = "";  // Buffer for Password input
    int accountIdLength = 0;
    int passwordLength = 0;
    bool accountIdActive = true; // Track active field
    bool passwordActive = false;
    bool loginHovered = false;
    bool createAccountHovered = false;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        // Handle keyboard input for active field
        if (IsKeyPressed(KEY_TAB)) {
            accountIdActive = !accountIdActive;
            passwordActive = !passwordActive;
        }

        if (accountIdActive) {
            if (accountIdLength < 29 && IsKeyPressed(KEY_BACKSPACE) && accountIdLength > 0) {
                accountId[--accountIdLength] = '\0';
            } else if (accountIdLength < 29) {
                int key = GetCharPressed();
                if (key >= 32 && key <= 126) { // Accept printable characters
                    accountId[accountIdLength++] = (char)key;
                    accountId[accountIdLength] = '\0';
                }
            }
        }

        if (passwordActive) {
            if (passwordLength < 29 && IsKeyPressed(KEY_BACKSPACE) && passwordLength > 0) {
                password[--passwordLength] = '\0';
            } else if (passwordLength < 29) {
                int key = GetCharPressed();
                if (key >= 32 && key <= 126) { // Accept printable characters
                    password[passwordLength++] = (char)key;
                    password[passwordLength] = '\0';
                }
            }
        }

        // Check for button hover and click
        int buttonWidth = 120;
        int buttonHeight = 40;
        int boxWidth = 400;
        int boxX = screenWidth / 2 - boxWidth / 2;
        int boxY = (screenHeight - 300) / 2;
        int signInButtonX = boxX + (boxWidth / 2) - (buttonWidth / 2);
        int signInButtonY = boxY + 200;
        loginHovered = CheckCollisionPointRec(mousePosition, (Rectangle){signInButtonX, signInButtonY, buttonWidth, buttonHeight});

        int createAccountButtonWidth = 180;
        int createAccountButtonX = boxX + (boxWidth / 2) - (createAccountButtonWidth / 2);
        int createAccountButtonY = signInButtonY + buttonHeight + 20;
        createAccountHovered = CheckCollisionPointRec(mousePosition, (Rectangle){createAccountButtonX, createAccountButtonY, createAccountButtonWidth, buttonHeight});

        if (loginHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "Log In button clicked with Account ID: %s, Password: %s", accountId, password);
        }

        if (createAccountHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "Create Account button clicked with Account ID: %s, Password: %s", accountId, password);
        }

        // Start Drawing
        BeginDrawing();

        ClearBackground(LIGHTGRAY); // Changed background color to grey

        // Draw the Crest Bank Logo at the top center (scaled)
        int logoX = screenWidth / 2 - logoWidth / 2;
        int logoY = 20; // Position above the box
        DrawTexturePro(logo, 
                       (Rectangle){0, 0, logo.width, logo.height}, 
                       (Rectangle){logoX, logoY, logoWidth, logoHeight}, 
                       (Vector2){0, 0}, 0, WHITE);

        // Draw Bank Name
       // DrawText("Crest Bank", screenWidth / 2 - MeasureText("Crest Bank", 40) / 2, logoY + logoHeight + 10, 40, DARKGRAY);

        // Draw Login Box
        int boxHeight = 300;
        DrawRectangle(boxX, boxY, boxWidth, boxHeight, WHITE); // Changed box background to white
        DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, GRAY);

        // Username Field
        int inputBoxHeight = 30;
        DrawText("Account ID:", boxX + 20, boxY + 40, 20, BLACK);
        DrawRectangle(boxX + 20, boxY + 70, boxWidth - 40, inputBoxHeight, WHITE);
        DrawRectangleLines(boxX + 20, boxY + 70, boxWidth - 40, inputBoxHeight, DARKGRAY);
        DrawText(accountId, boxX + 25, boxY + 75, 20, BLACK);

        // Password Field
        DrawText("Password:", boxX + 20, boxY + 120, 20, BLACK);
        DrawRectangle(boxX + 20, boxY + 150, boxWidth - 40, inputBoxHeight, WHITE);
        DrawRectangleLines(boxX + 20, boxY + 150, boxWidth - 40, inputBoxHeight, DARKGRAY);

        char maskedPassword[30];
        memset(maskedPassword, '*', passwordLength);
        maskedPassword[passwordLength] = '\0';
        DrawText(maskedPassword, boxX + 25, boxY + 155, 20, BLACK);

        // Highlight active field
        if (passwordActive) {
            DrawRectangleLines(boxX + 20, boxY + 150, boxWidth - 40, inputBoxHeight, BLUE);
        } else {
            DrawRectangleLines(boxX + 20, boxY + 70, boxWidth - 40, inputBoxHeight, BLUE);
        }

        // Sign In Button
        DrawRectangle(signInButtonX, signInButtonY, buttonWidth, buttonHeight, loginHovered ? DARKBLUE : BLUE);
        DrawText("Sign In", signInButtonX + (buttonWidth / 2) - MeasureText("Sign In", 20) / 2, signInButtonY + 10, 20, WHITE);

        // Create Account Button
        DrawRectangle(createAccountButtonX, createAccountButtonY, createAccountButtonWidth, buttonHeight, createAccountHovered ? DARKGREEN : GREEN);
        DrawText("Create Account", createAccountButtonX + (createAccountButtonWidth / 2) - MeasureText("Create Account", 20) / 2, createAccountButtonY + 10, 20, WHITE);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(logo); // Unload the logo image
    CloseWindow();

    return 0;
}
