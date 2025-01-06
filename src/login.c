#include <raylib.h>
#include <string.h>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Crest Bank - Login Page");

    Texture2D logo = LoadTexture("C:/Dev/vertex/project/Image/logo.png"); // Ensure path is correct  "C:\Dev\vertex\project\Image\logo.png"


    float logoScale = 0.5f;
    int logoWidth = logo.width * logoScale;
    int logoHeight = logo.height * logoScale;

    char accountId[30] = "";
    char password[30] = "";
    int accountIdLength = 0;
    int passwordLength = 0;
    bool accountIdActive = true;
    bool passwordActive = false;
    bool loginHovered = false;
    bool createAccountHovered = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        Rectangle accountIdBox = {screenWidth / 2 - 200, 260, 400, 30};
        Rectangle passwordBox = {screenWidth / 2 - 200, 320, 400, 30};

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            accountIdActive = CheckCollisionPointRec(mousePosition, accountIdBox);
            passwordActive = CheckCollisionPointRec(mousePosition, passwordBox);
        }

        if (accountIdActive) {
            int key = GetCharPressed();
            if (key >= 32 && key <= 126 && accountIdLength < 29) {
                accountId[accountIdLength++] = (char)key;
                accountId[accountIdLength] = '\0';
            }
            if (IsKeyDown(KEY_BACKSPACE) && accountIdLength > 0) {
                accountId[--accountIdLength] = '\0';
            }
        }

        if (passwordActive) {
            int key = GetCharPressed();
            if (key >= 32 && key <= 126 && passwordLength < 29) {
                password[passwordLength++] = (char)key;
                password[passwordLength] = '\0';
            }
            if (IsKeyDown(KEY_BACKSPACE) && passwordLength > 0) {
                password[--passwordLength] = '\0';
            }
        }

        int buttonWidth = 120;
        int buttonHeight = 40;
        int signInButtonX = screenWidth / 2 - buttonWidth / 2;
        int signInButtonY = 380;
        loginHovered = CheckCollisionPointRec(mousePosition, (Rectangle){signInButtonX, signInButtonY, buttonWidth, buttonHeight});

        int createAccountButtonWidth = 180;
        int createAccountButtonX = screenWidth / 2 - createAccountButtonWidth / 2;
        int createAccountButtonY = signInButtonY + buttonHeight + 20;
        createAccountHovered = CheckCollisionPointRec(mousePosition, (Rectangle){createAccountButtonX, createAccountButtonY, createAccountButtonWidth, buttonHeight});

        if (loginHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "Log In button clicked with Account ID: %s, Password: %s", accountId, password);
        }

        if (createAccountHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "Create Account button clicked");
        }

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        int logoX = screenWidth / 2 - logoWidth / 2;
        int logoY = 20;
        DrawTexturePro(logo, (Rectangle){0, 0, logo.width, logo.height}, 
                       (Rectangle){logoX, logoY, logoWidth, logoHeight}, 
                       (Vector2){0, 0}, 0, WHITE);

        DrawText("Account ID:", accountIdBox.x, accountIdBox.y - 20, 20, BLACK);
        DrawRectangleRec(accountIdBox, WHITE);
        DrawRectangleLinesEx(accountIdBox, 2, accountIdActive ? BLUE : DARKGRAY);
        DrawText(accountId, accountIdBox.x + 5, accountIdBox.y + 5, 20, BLACK);

        DrawText("Password:", passwordBox.x, passwordBox.y - 20, 20, BLACK);
        DrawRectangleRec(passwordBox, WHITE);
        DrawRectangleLinesEx(passwordBox, 2, passwordActive ? BLUE : DARKGRAY);

        char maskedPassword[30];
        strncpy(maskedPassword, "******************************", passwordLength);
        maskedPassword[passwordLength] = '\0';
        DrawText(maskedPassword, passwordBox.x + 5, passwordBox.y + 5, 20, BLACK);

        DrawRectangle(signInButtonX, signInButtonY, buttonWidth, buttonHeight, loginHovered ? DARKBLUE : BLUE);
        DrawText("Login", signInButtonX + (buttonWidth / 2) - MeasureText("Login", 20) / 2, signInButtonY + 10, 20, WHITE);

        DrawRectangle(createAccountButtonX, createAccountButtonY, createAccountButtonWidth, buttonHeight, createAccountHovered ? DARKGREEN : GREEN);
        DrawText("Create Account", createAccountButtonX + (createAccountButtonWidth / 2) - MeasureText("Create Account", 20) / 2, createAccountButtonY + 10, 20, WHITE);

        EndDrawing();
    }

    UnloadTexture(logo);
    CloseWindow();

    return 0;
}
