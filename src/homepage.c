#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/hfile.h"
#include <raylib.h>
#include <raygui.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define RAYGUI_IMPLEMENTATION

// Screen enumeration is declared in hfile.h, no need to declare it again here

// Function Declarations
int GuiTextBox(Rectangle bounds, char *text, int textSize, bool editMode);    
void showAccountDetails();
void deposit();
void withdraw();
void sendMoney();
void Logout();

// Button struct for simplicity
typedef struct Button {
    Rectangle bounds;
    const char *text;
    bool clicked;
} Button;

// Function declarations for UI transitions
void ShowAccountDetailsGUI();
void DepositGUI();
void WithdrawGUI();
void SendMoneyGUI();
void LogoutGUI();

// Function to check if a button is clicked
bool IsButtonClicked(Button button) {
    Vector2 mousePoint = GetMousePosition();
    return CheckCollisionPointRec(mousePoint, button.bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

// Declare transition-related variables
static bool isTransitioning = false;
static float transitionAlpha = 0.0f; // 0.0 (transparent) to 1.0 (opaque)
static Screen nextScreen;
static Screen previousScreen; // To store the previous screen when transitioning
static Screen currentScreen = SCREEN_MAIN;  // Start with the main screen
extern Screen currentScreen;

// Function to start a transition
void StartTransition(Screen targetScreen) {
    if (currentScreen != targetScreen) {
        isTransitioning = true;
        previousScreen = currentScreen; // Store the previous screen before transitioning
        nextScreen = targetScreen; // Set the target screen
        transitionAlpha = 0.0f; // Start transition at full transparency
    }
}

// Function to update the transition effect
void UpdateTransition() {
    if (isTransitioning) {
        transitionAlpha += 0.05f; // Increase alpha to create fade effect

        // When fully opaque, change screen and fade out
        if (transitionAlpha >= 1.0f) {
            currentScreen = nextScreen; // Switch to the next screen
            transitionAlpha = 1.0f;    // Ensure fully opaque
            isTransitioning = false;  // End the transition
        }
    }
}

// Function to draw the transition effect
void DrawTransition() {
    if (isTransitioning) {
        // Draw a full-screen rectangle with transitionAlpha to fade in/out
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, transitionAlpha));
    }
}

void drawMainScreen() {
    const char *bankName = "Crest Bank";

    // Dynamically center buttons
    int buttonWidth = 300;
    int buttonHeight = 50;
    int buttonSpacing = 20;
    int totalHeight = (5 * buttonHeight) + (4 * buttonSpacing);
    int startY = (SCREEN_HEIGHT - totalHeight) / 2;

    const char *buttonLabels[] = {
        "Account Details",
        "Deposit",
        "Withdraw",
        "Send Money",
        "Logout"
    };

    // Draw bank name
    DrawText(bankName, SCREEN_WIDTH / 2 - MeasureText(bankName, 40) / 2, 50, 40, DARKGRAY);

    // Draw buttons and handle clicks
    for (int i = 0; i < 5; i++) {
        Rectangle buttonBounds = {
            (SCREEN_WIDTH - buttonWidth) / 2,
            startY + i * (buttonHeight + buttonSpacing),
            buttonWidth,
            buttonHeight
        };

        // Highlight button if hovered
        Color buttonColor = CheckCollisionPointRec(GetMousePosition(), buttonBounds) ? GRAY : LIGHTGRAY;
        DrawRectangleRec(buttonBounds, buttonColor);
        DrawRectangleLinesEx(buttonBounds, 2, BLACK);

        // Draw button text
        DrawText(
            buttonLabels[i],
            buttonBounds.x + buttonBounds.width / 2 - MeasureText(buttonLabels[i], 20) / 2,
            buttonBounds.y + buttonBounds.height / 2 - 10,
            20,
            BLACK
        );

        // Check for click and start transition
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buttonBounds)) {
            StartTransition((Screen)(i + 1)); // Transition to the corresponding screen
        }
    }
}

int main(void) {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crest Bank - Navigation UI");
    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose()) {
        // Update logic
        if (isTransitioning) {
            UpdateTransition();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Render current screen
        switch (currentScreen) {
            case SCREEN_MAIN:
                drawMainScreen();
                break;
            case SCREEN_ACCOUNT_DETAILS:
                displayAccount();
                break;
            case SCREEN_DEPOSIT:
                deposit();
                break;
            case SCREEN_WITHDRAW:
                withdraw();
                break;
            case SCREEN_SEND_MONEY:
                transferFunds();
                break;
            case SCREEN_LOGOUT:
                DrawText("Logging Out...", SCREEN_WIDTH / 2 - MeasureText("Logging Out...", 20) / 2, SCREEN_HEIGHT / 2, 20, DARKGRAY);
                break;
        }

        // Draw transition effect (if active)
        DrawTransition();

        EndDrawing();
    }

    // Deinitialization
    CloseWindow();
    return 0;
}

// Screen-specific function implementations
void ShowAccountDetailsGUI() {
    displayAccount();
}

void DepositGUI() {
    deposit();
}

void WithdrawGUI() {
    withdraw();
}

void SendMoneyGUI() {
    transferFunds();
}

void LogoutGUI() {
    DrawText("Logging Out...", SCREEN_WIDTH / 2 - MeasureText("Logging Out...", 20) / 2, SCREEN_HEIGHT / 2, 20, DARKGRAY);
}
