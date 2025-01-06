#include "raylib.h"
#include "hfile.h"
#include "transaction.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_CHARS 30

// Enum for different application screens
typedef enum {
    LOGIN_SCREEN,
    SIGNUP_SCREEN,
    BALANCE_SCREEN,
    TRANSACTION_SCREEN,
    MAIN_MENU
} AppScreen;

// Global variables for user data
char loggedInUser[MAX_INPUT_CHARS] = "";

// Function declarations
void ShowLoginScreen(AppScreen *currentScreen);
void ShowSignupScreen(AppScreen *currentScreen);
void ShowBalanceScreen(AppScreen *currentScreen);
void ShowTransactionScreen(AppScreen *currentScreen);
void ShowMainMenu(AppScreen *currentScreen);

int main() {
    // Initialize the Raylib window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Banking Application");
    SetTargetFPS(60);

    // Current application screen
    AppScreen currentScreen = MAIN_MENU;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case LOGIN_SCREEN:
                ShowLoginScreen(&currentScreen);
                break;
            case SIGNUP_SCREEN:
                ShowSignupScreen(&currentScreen);
                break;
            case BALANCE_SCREEN:
                ShowBalanceScreen(&currentScreen);
                break;
            case TRANSACTION_SCREEN:
                ShowTransactionScreen(&currentScreen);
                break;
            case MAIN_MENU:
                ShowMainMenu(&currentScreen);
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ShowLoginScreen(AppScreen *currentScreen) {
    static char accountId[MAX_INPUT_CHARS] = "";
    static char password[MAX_INPUT_CHARS] = "";
    static bool accountIdActive = true;
    static bool passwordActive = false;
    static char errorMessage[100] = "";

    DrawText("Login Screen", 320, 50, 40, DARKBLUE);

    Rectangle accountIdBox = {200, 200, 400, 40};
    Rectangle passwordBox = {200, 300, 400, 40};
    Rectangle loginButton = {300, 400, 200, 50};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        accountIdActive = CheckCollisionPointRec(mousePos, accountIdBox);
        passwordActive = CheckCollisionPointRec(mousePos, passwordBox);
    }

    if (accountIdActive) {
        int key = GetCharPressed();
        while (key > 0 && strlen(accountId) < MAX_INPUT_CHARS - 1) {
            accountId[strlen(accountId)] = (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(accountId) > 0) {
            accountId[strlen(accountId) - 1] = '\0';
        }
    }

    if (passwordActive) {
        int key = GetCharPressed();
        while (key > 0 && strlen(password) < MAX_INPUT_CHARS - 1) {
            password[strlen(password)] = (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(password) > 0) {
            password[strlen(password) - 1] = '\0';
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), loginButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (strlen(accountId) > 0 && strlen(password) > 0) {
            strcpy(loggedInUser, accountId);
            *currentScreen = MAIN_MENU;
            strcpy(errorMessage, ""); // Clear error message
        } else {
            strcpy(errorMessage, "Error: Please enter valid credentials!");
        }
    }

    DrawRectangleRec(accountIdBox, accountIdActive ? LIGHTGRAY : GRAY);
    DrawText(accountId, accountIdBox.x + 10, accountIdBox.y + 10, 20, BLACK);

    DrawRectangleRec(passwordBox, passwordActive ? LIGHTGRAY : GRAY);
    char maskedPassword[MAX_INPUT_CHARS] = "";
    memset(maskedPassword, '*', strlen(password));
    DrawText(maskedPassword, passwordBox.x + 10, passwordBox.y + 10, 20, BLACK);

    DrawRectangleRec(loginButton, DARKGRAY);
    DrawText("Login", loginButton.x + 60, loginButton.y + 15, 20, WHITE);

    if (strlen(errorMessage) > 0) {
        DrawText(errorMessage, 250, 500, 20, RED);
    }
}

void ShowSignupScreen(AppScreen *currentScreen) {
    DrawText("Signup Screen (WIP)", 320, 50, 40, DARKBLUE);
    createAccount(); // Call the function from hfile.h
    DrawText("Press BACKSPACE to return", 250, 300, 20, DARKGRAY);

    if (IsKeyPressed(KEY_BACKSPACE)) {
        *currentScreen = MAIN_MENU;
    }
}

void ShowBalanceScreen(AppScreen *currentScreen) {
    DrawText("Balance Screen (WIP)", 320, 50, 40, DARKBLUE);
    displayAccount(); // Call the function from hfile.h
    DrawText("Press BACKSPACE to return", 250, 300, 20, DARKGRAY);

    if (IsKeyPressed(KEY_BACKSPACE)) {
        *currentScreen = MAIN_MENU;
    }
}

void ShowTransactionScreen(AppScreen *currentScreen) {
    DrawText("Transaction Screen", 320, 50, 40, DARKBLUE);
    transferFunds(); // Call the function from transaction.h
    DrawText("Press BACKSPACE to return", 250, 300, 20, DARKGRAY);

    if (IsKeyPressed(KEY_BACKSPACE)) {
        *currentScreen = MAIN_MENU;
    }
}

void ShowMainMenu(AppScreen *currentScreen) {
    DrawText("Main Menu", 350, 50, 40, DARKBLUE);

    // Define button areas
    Rectangle loginButton = {100, 200, 200, 40};
    Rectangle signupButton = {100, 250, 200, 40};
    Rectangle balanceButton = {100, 300, 200, 40};
    Rectangle transactionButton = {100, 350, 200, 40};
    Rectangle exitButton = {100, 400, 200, 40};

    // Draw buttons and their labels
    DrawRectangleRec(loginButton, LIGHTGRAY);
    DrawText("Login", loginButton.x + 50, loginButton.y + 10, 20, DARKGRAY);

    DrawRectangleRec(signupButton, LIGHTGRAY);
    DrawText("Signup", signupButton.x + 50, signupButton.y + 10, 20, DARKGRAY);

    DrawRectangleRec(balanceButton, LIGHTGRAY);
    DrawText("View Balance", balanceButton.x + 20, balanceButton.y + 10, 20, DARKGRAY);

    DrawRectangleRec(transactionButton, LIGHTGRAY);
    DrawText("Transactions", transactionButton.x + 20, transactionButton.y + 10, 20, DARKGRAY);

    DrawRectangleRec(exitButton, LIGHTGRAY);
    DrawText("Exit", exitButton.x + 70, exitButton.y + 10, 20, DARKGRAY);

    // Handle mouse input for button clicks
    if (CheckCollisionPointRec(GetMousePosition(), loginButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *currentScreen = LOGIN_SCREEN;
    } else if (CheckCollisionPointRec(GetMousePosition(), signupButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *currentScreen = SIGNUP_SCREEN;
    } else if (CheckCollisionPointRec(GetMousePosition(), balanceButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *currentScreen = BALANCE_SCREEN;
    } else if (CheckCollisionPointRec(GetMousePosition(), transactionButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *currentScreen = TRANSACTION_SCREEN;
    } else if (CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        CloseWindow();
        exit(0);
    }
}
