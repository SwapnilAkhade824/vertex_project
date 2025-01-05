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