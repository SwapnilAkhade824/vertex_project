
#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_CHARS 20


// Function prototypes from sign.c
void SignUpScreen();
void LoginScreen();

// Integrated main function from both files
int main() {
    // Initialize Window
    InitWindow(800, 600, "Banking Application");
    SetTargetFPS(60);

    int screen = 0; // 0 = login, 1 = sign-up, 2 = exit

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (screen == 0) {
            LoginScreen();
            if (IsKeyPressed(KEY_ONE)) screen = 1; // Navigate to Sign-Up
        } else if (screen == 1) {
            SignUpScreen();
            if (IsKeyPressed(KEY_TWO)) screen = 0; // Navigate to Login
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// Functions from sign.c
#include <raylib.h>
#include <stdio.h>
#include <string.h>

// Define screen dimensions and input limits
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define MAX_NATIONALITY_LENGTH 50

// Global variables for input and UI states
char email[MAX_EMAIL_LENGTH + 1] = {0};
char password[MAX_PASSWORD_LENGTH + 1] = {0};
char fullName[MAX_NAME_LENGTH + 1] = {0};
char address[MAX_ADDRESS_LENGTH + 1] = {0};
char nationality[MAX_NATIONALITY_LENGTH + 1] = {0};
bool isEmailFocused = false;
bool isPasswordFocused = false;
bool isFullNameFocused = false;
bool isAddressFocused = false;
bool isNationalityFocused = false;
bool isPasswordVisible = false;

int main(void) {
    // Initialize the window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Banking App - Sign In");

    // GUI element positions and sizes
    Rectangle fullNameBox = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 160, 300, 40 };
    Rectangle emailBox = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 60, 300, 40 };
    Rectangle passwordBox = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20, 300, 40 };
    Rectangle addressBox = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 80, 300, 40 };
    Rectangle nationalityBox = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 140, 300, 40 };
    Rectangle continueButton = { SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 200, 150, 50 };
    Rectangle togglePasswordButton = { passwordBox.x + passwordBox.width + 10, passwordBox.y, 60, passwordBox.height };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Detect mouse clicks on input fields
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            isFullNameFocused = CheckCollisionPointRec(mousePos, fullNameBox);
            isEmailFocused = CheckCollisionPointRec(mousePos, emailBox);
            isPasswordFocused = CheckCollisionPointRec(mousePos, passwordBox);
            isAddressFocused = CheckCollisionPointRec(mousePos, addressBox);
            isNationalityFocused = CheckCollisionPointRec(mousePos, nationalityBox);
        }

        // Handle input for full name
        if (isFullNameFocused) {
            int key = GetCharPressed();
            while (key > 0) {
                if (strlen(fullName) < MAX_NAME_LENGTH) {
                    char str[2] = { (char)key, '\0' };
                    strcat(fullName, str);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(fullName) > 0) {
                fullName[strlen(fullName) - 1] = '\0'; // Handle backspace
            }
        }

        // Handle input for email
        if (isEmailFocused) {
            int key = GetCharPressed();
            while (key > 0) {
                if (strlen(email) < MAX_EMAIL_LENGTH) {
                    char str[2] = { (char)key, '\0' };
                    strcat(email, str);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(email) > 0) {
                email[strlen(email) - 1] = '\0'; // Handle backspace
            }
        }

        // Handle input for password
        if (isPasswordFocused) {
            int key = GetCharPressed();
            while (key > 0) {
                if (strlen(password) < MAX_PASSWORD_LENGTH) {
                    char str[2] = { (char)key, '\0' };
                    strcat(password, str);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(password) > 0) {
                password[strlen(password) - 1] = '\0'; // Handle backspace
            }
        }

        // Handle input for address
        if (isAddressFocused) {
            int key = GetCharPressed();
            while (key > 0) {
                if (strlen(address) < MAX_ADDRESS_LENGTH) {
                    char str[2] = { (char)key, '\0' };
                    strcat(address, str);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(address) > 0) {
                address[strlen(address) - 1] = '\0'; // Handle backspace
            }
        }

        // Handle input for nationality
        if (isNationalityFocused) {
            int key = GetCharPressed();
            while (key > 0) {
                if (strlen(nationality) < MAX_NATIONALITY_LENGTH) {
                    char str[2] = { (char)key, '\0' };
                    strcat(nationality, str);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(nationality) > 0) {
                nationality[strlen(nationality) - 1] = '\0'; // Handle backspace
            }
        }

        // Toggle password visibility
        if (CheckCollisionPointRec(GetMousePosition(), togglePasswordButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isPasswordVisible = !isPasswordVisible;
        }

        // Handle continue button click
        bool isContinueHovered = CheckCollisionPointRec(GetMousePosition(), continueButton);
        if (isContinueHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (strlen(email) > 0 && strlen(password) > 0) {
                printf("Full Name: %s\n", fullName);
                printf("Email: %s\n", email);
                printf("Password: %s\n", password);
                printf("Address: %s\n", address);
                printf("Nationality: %s\n", nationality);

                // Clear input fields after submission
                memset(fullName, 0, sizeof(fullName));
                memset(email, 0, sizeof(email));
                memset(password, 0, sizeof(password));
                memset(address, 0, sizeof(address));
                memset(nationality, 0, sizeof(nationality));
                isFullNameFocused = false;
                isEmailFocused = false;
                isPasswordFocused = false;
                isAddressFocused = false;
                isNationalityFocused = false;
            }
        }

        // Begin drawing
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        // Draw bank name at the center top (larger font)
        DrawText("Crest Bank", SCREEN_WIDTH / 2 - MeasureText("Crest Bank", 50) / 2, 20, 50, DARKBLUE);

        // Draw full name input box
        DrawRectangleRec(fullNameBox, RAYWHITE);
        DrawRectangleLinesEx(fullNameBox, 2, isFullNameFocused ? BLUE : LIGHTGRAY);
        DrawText("Full Name:", fullNameBox.x - 105, fullNameBox.y + 10, 20, DARKGRAY);
        DrawText(fullName, fullNameBox.x + 10, fullNameBox.y + 10, 20, DARKGRAY);

        // Draw email input box
        DrawRectangleRec(emailBox, RAYWHITE);
        DrawRectangleLinesEx(emailBox, 2, isEmailFocused ? BLUE : LIGHTGRAY);
        DrawText("Email:", emailBox.x - 70, emailBox.y + 10, 20, DARKGRAY);
        DrawText(email, emailBox.x + 10, emailBox.y + 10, 20, DARKGRAY);

        // Draw password input box
        DrawRectangleRec(passwordBox, RAYWHITE);
        DrawRectangleLinesEx(passwordBox, 2, isPasswordFocused ? BLUE : LIGHTGRAY);
        DrawText("Password:", passwordBox.x - 105, passwordBox.y + 10, 20, DARKGRAY); // Proper alignment to avoid overlap

        // Display password as plain text or asterisks
        char passwordDisplay[MAX_PASSWORD_LENGTH + 1] = {0};
        if (isPasswordVisible) {
            strncpy(passwordDisplay, password, MAX_PASSWORD_LENGTH);
        } else {
            for (size_t i = 0; i < strlen(password); i++) {
                passwordDisplay[i] = '*';
            }
        }
        DrawText(passwordDisplay, passwordBox.x + 10, passwordBox.y + 10, 20, DARKGRAY);

        // Draw address input box
        DrawRectangleRec(addressBox, RAYWHITE);
        DrawRectangleLinesEx(addressBox, 2, isAddressFocused ? BLUE : LIGHTGRAY);
        DrawText("Address:", addressBox.x - 95, addressBox.y + 10, 20, DARKGRAY);
        DrawText(address, addressBox.x + 10, addressBox.y + 10, 20, DARKGRAY);

        // Draw nationality input box
        DrawRectangleRec(nationalityBox, RAYWHITE);
        DrawRectangleLinesEx(nationalityBox, 2, isNationalityFocused ? BLUE : LIGHTGRAY);
        DrawText("Nationality:", nationalityBox.x - 115, nationalityBox.y + 10, 20, DARKGRAY);
        DrawText(nationality, nationalityBox.x + 10, nationalityBox.y + 10, 20, DARKGRAY);

        // Draw toggle password visibility button (blue background)
        DrawRectangleRec(togglePasswordButton, BLUE);
        DrawText(isPasswordVisible ? "Hide" : "Show", togglePasswordButton.x + 5, togglePasswordButton.y + 10, 20, WHITE);

        // Draw continue button (blue background)
        DrawRectangleRec(continueButton, isContinueHovered ? DARKBLUE : BLUE);
        DrawText("Continue", continueButton.x + 25, continueButton.y + 15, 20, WHITE);

        // End drawing
        EndDrawing();
    }

    // Deinitialize window
    CloseWindow();

    return 0;
}

// Functions from new.c
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

        // Handle mouse interaction for input fields
        Rectangle accountIdBox = {screenWidth / 2 - 200, 260, 400, 30};
        Rectangle passwordBox = {screenWidth / 2 - 200, 320, 400, 30};

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            accountIdActive = CheckCollisionPointRec(mousePosition, accountIdBox);
            passwordActive = CheckCollisionPointRec(mousePosition, passwordBox);
        }

        // Handle keyboard input for active field
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

        // Draw Login Box
        DrawText("Account ID:", accountIdBox.x, accountIdBox.y - 20, 20, BLACK);
        DrawRectangleRec(accountIdBox, WHITE);
        DrawRectangleLinesEx(accountIdBox, 2, accountIdActive ? BLUE : DARKGRAY);
        DrawText(accountId, accountIdBox.x + 5, accountIdBox.y + 5, 20, BLACK);

        DrawText("Password:", passwordBox.x, passwordBox.y - 20, 20, BLACK);
        DrawRectangleRec(passwordBox, WHITE);
        DrawRectangleLinesEx(passwordBox, 2, passwordActive ? BLUE : DARKGRAY);

        char maskedPassword[30];
        memset(maskedPassword, '*', passwordLength);
        maskedPassword[passwordLength] = '\0';
        DrawText(maskedPassword, passwordBox.x + 5, passwordBox.y + 5, 20, BLACK);

        // Sign In Button
        DrawRectangle(signInButtonX, signInButtonY, buttonWidth, buttonHeight, loginHovered ? DARKBLUE : BLUE);
        DrawText("Login", signInButtonX + (buttonWidth / 2) - MeasureText("Sign In", 20) / 2, signInButtonY + 10, 20, WHITE);

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

