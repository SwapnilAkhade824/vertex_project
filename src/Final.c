
#include "raylib.h"
#include <stdio.h>
#include <string.h>

// Function prototypes
void showBalancePage();
void showTransactionPage();

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Bank Application");

    SetTargetFPS(60); // Set FPS to 60
    int currentPage = 0; // 0 = Menu, 1 = Balance Page, 2 = Transaction Page

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentPage == 0) {
            // Main menu
            DrawText("Bank Application", 300, 50, 30, DARKBLUE);
            Rectangle balanceButton = {200, 200, 400, 50};
            Rectangle transactionButton = {200, 300, 400, 50};

            DrawRectangleRec(balanceButton, LIGHTGRAY);
            DrawRectangleRec(transactionButton, LIGHTGRAY);
            DrawText("View Balance", 310, 215, 20, BLACK);
            DrawText("Make Transaction", 270, 315, 20, BLACK);

            if (CheckCollisionPointRec(GetMousePosition(), balanceButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                currentPage = 1;
            } else if (CheckCollisionPointRec(GetMousePosition(), transactionButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                currentPage = 2;
            }
        } else if (currentPage == 1) {
            showBalancePage();
            if (IsKeyPressed(KEY_BACKSPACE)) currentPage = 0; // Go back to menu
        } else if (currentPage == 2) {
            showTransactionPage();
            if (IsKeyPressed(KEY_BACKSPACE)) currentPage = 0; // Go back to menu
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void showBalancePage() {
    const char *accounts[] = {"> Savings Account", "> Checking Account", "> Business Account"};
    const int accountCount = sizeof(accounts) / sizeof(accounts[0]);
    static int selectedAccount = -1; // To track selected account

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, 800, 50, DARKBLUE);
    DrawText("Account Balance", 100, 15, 20, RAYWHITE);

    // Back button
    Rectangle backButton = {10, 10, 80, 30};
    DrawRectangleRounded(backButton, 0.2, 10, MAROON);
    DrawText("Back", backButton.x + 10, backButton.y + 7, 16, RAYWHITE);

    // Handle back button click
    if (CheckCollisionPointRec(GetMousePosition(), backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedAccount = -1; // Reset selection
        return;
    }

    // Display account buttons
    for (int i = 0; i < accountCount; i++) {
        Rectangle accountButton = {200, 100 + i * 70, 400, 50};
        DrawRectangleRounded(accountButton, 0.2, 10, LIGHTGRAY);
        DrawText(accounts[i], accountButton.x + 20, accountButton.y + 15, 20, DARKGRAY);

        if (CheckCollisionPointRec(GetMousePosition(), accountButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedAccount = i;
        }
    }

    // Display selected account details
    if (selectedAccount >= 0) {
        DrawRectangleRounded((Rectangle){200, 400, 400, 100}, 0.2, 10, DARKGREEN);
        DrawText(accounts[selectedAccount], 220, 420, 20, WHITE);
        DrawText("Balance: $0.00", 220, 460, 20, WHITE); // Placeholder balance
    }

    EndDrawing();
}

void showTransactionPage() {
    static char accountNumber[50] = "";
    static char amount[50] = "";
    static char transactionMessage[100] = "";
    static bool transactionSent = false;
    static int activeTextBox = -1; // 0 = Account Number, 1 = Amount
    static float cursorBlinkTime = 0.0f;
    const float cursorBlinkSpeed = 0.5f;

    Rectangle accountNumberRec = {200, 150, 400, 40};
    Rectangle amountRec = {200, 250, 400, 40};
    Rectangle sendButtonRec = {300, 350, 200, 50};

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Transaction Page", 300, 50, 30, DARKBLUE);
    DrawText("Account Number:", 200, 120, 20, DARKGRAY);
    DrawText("Amount:", 200, 220, 20, DARKGRAY);

    DrawRectangleRec(accountNumberRec, LIGHTGRAY);
    DrawRectangleRec(amountRec, LIGHTGRAY);
    DrawRectangleRec(sendButtonRec, DARKGRAY);
    DrawText("Send", 380, 360, 30, WHITE);

    DrawText(accountNumber, accountNumberRec.x + 10, accountNumberRec.y + 10, 20, BLACK);
    DrawText(amount, amountRec.x + 10, amountRec.y + 10, 20, BLACK);

    // Blinking cursor
    cursorBlinkTime += GetFrameTime();
    if (cursorBlinkTime >= cursorBlinkSpeed) cursorBlinkTime = 0.0f;

    if (activeTextBox == 0 && cursorBlinkTime < cursorBlinkSpeed / 2.0f) {
        DrawLine(accountNumberRec.x + 10 + MeasureText(accountNumber, 20), accountNumberRec.y + 10,
                 accountNumberRec.x + 10 + MeasureText(accountNumber, 20), accountNumberRec.y + 30, BLACK);
    } else if (activeTextBox == 1 && cursorBlinkTime < cursorBlinkSpeed / 2.0f) {
        DrawLine(amountRec.x + 10 + MeasureText(amount, 20), amountRec.y + 10,
                 amountRec.x + 10 + MeasureText(amount, 20), amountRec.y + 30, BLACK);
    }

    // Handle input and button logic
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), accountNumberRec)) activeTextBox = 0;
        else if (CheckCollisionPointRec(GetMousePosition(), amountRec)) activeTextBox = 1;
        else activeTextBox = -1;
    }

    if (activeTextBox == 0 && IsKeyPressed(KEY_BACKSPACE) && strlen(accountNumber) > 0) {
        accountNumber[strlen(accountNumber) - 1] = '\0';
    } else if (activeTextBox == 1 && IsKeyPressed(KEY_BACKSPACE) && strlen(amount) > 0) {
        amount[strlen(amount) - 1] = '\0';
    }

    int key = GetCharPressed();
    while (key > 0) {
        if (activeTextBox == 0 && strlen(accountNumber) < sizeof(accountNumber) - 1) {
            accountNumber[strlen(accountNumber)] = (char)key;
            accountNumber[strlen(accountNumber) + 1] = '\0';
        } else if (activeTextBox == 1 && strlen(amount) < sizeof(amount) - 1) {
            amount[strlen(amount)] = (char)key;
            amount[strlen(amount) + 1] = '\0';
        }
        key = GetCharPressed();
    }

    if (CheckCollisionPointRec(GetMousePosition(), sendButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        snprintf(transactionMessage, sizeof(transactionMessage), "%s rupees sent successfully!", amount);
        transactionSent = true;
    }

    if (transactionSent) DrawText(transactionMessage, 250, 420, 20, GREEN);

    EndDrawing();
}
