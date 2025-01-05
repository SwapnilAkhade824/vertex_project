#include "raylib.h"
#include <string.h>
#include <stdio.h>  // Include stdio.h for snprintf

int main(void) {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Transaction Page");

    // Variables to hold input text
    char accountNumber[50] = "";
    char amount[50] = "";
    char transactionMessage[100] = "";

    // Set up the text box rectangle dimensions
    Rectangle accountNumberRec = {200, 150, 400, 40};
    Rectangle amountRec = {200, 250, 400, 40};
    Rectangle sendButtonRec = {300, 350, 200, 50};

    // Active text box: 0 = account number, 1 = amount
    int activeTextBox = -1;

    // Flag for showing "Transaction Sent!" message
    bool transactionSent = false;

    // Set window FPS
    SetTargetFPS(60);

    // Cursor blinking time variables
    float cursorBlinkTime = 0.0f;
    const float cursorBlinkSpeed = 0.5f;

    while (!WindowShouldClose()) {
        // Handle mouse clicks to focus on the correct text box
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), accountNumberRec)) {
                activeTextBox = 0;  // Focus on account number
            } else if (CheckCollisionPointRec(GetMousePosition(), amountRec)) {
                activeTextBox = 1;  // Focus on amount
            } else {
                activeTextBox = -1;  // Unfocus
            }
        }

        // Handle text input for the focused text box
        if (activeTextBox == 0) {
            // Handle backspace key
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(accountNumber) > 0) {
                accountNumber[strlen(accountNumber) - 1] = '\0'; // Remove last character
            }

            // Handle character input for account number
            int key = GetCharPressed();
            while (key > 0) {
                if (strlen(accountNumber) < sizeof(accountNumber) - 1) {
                    char inputChar = (char)key;
                    accountNumber[strlen(accountNumber)] = inputChar;
                    accountNumber[strlen(accountNumber) + 1] = '\0'; // Null-terminate string
                }
                key = GetCharPressed();
            }
        } else if (activeTextBox == 1) {
            // Handle backspace key
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(amount) > 0) {
                amount[strlen(amount) - 1] = '\0'; // Remove last character
            }

            // Handle character input for amount
            int key = GetCharPressed();
            while (key > 0) {
                if (strlen(amount) < sizeof(amount) - 1) {
                    char inputChar = (char)key;
                    amount[strlen(amount)] = inputChar;
                    amount[strlen(amount) + 1] = '\0'; // Null-terminate string
                }
                key = GetCharPressed();
            }
        }

        // Check if the "Send" button was pressed
        bool buttonPressed = CheckCollisionPointRec(GetMousePosition(), sendButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (buttonPressed && strlen(amount) > 0) {
            // Update the "Transaction Sent!" message with the entered amount
            snprintf(transactionMessage, sizeof(transactionMessage), "%s rupees sent successfully!", amount);
            transactionSent = true;
        }

        // Update cursor blinking
        cursorBlinkTime += GetFrameTime();
        if (cursorBlinkTime >= cursorBlinkSpeed) {
            cursorBlinkTime = 0.0f; // Reset the blink timer
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the bank name
        DrawText("Crest Bank", 320, 50, 40, DARKBLUE);

        // Draw input labels
        DrawText("Account Number:", 200, 120, 20, DARKGRAY);
        DrawText("Amount:", 200, 220, 20, DARKGRAY);

        // Draw the text boxes
        DrawRectangleRec(accountNumberRec, LIGHTGRAY);
        DrawRectangleRec(amountRec, LIGHTGRAY);

        // Draw the "Send" button
        DrawRectangleRec(sendButtonRec, DARKGRAY);
        DrawText("Send", 380, 360, 30, WHITE);

        // Draw the text in the text boxes
        DrawText(accountNumber, accountNumberRec.x + 10, accountNumberRec.y + 10, 20, BLACK);
        DrawText(amount, amountRec.x + 10, amountRec.y + 10, 20, BLACK);

        // Draw the cursor in the active text box (blinking effect)
        if (activeTextBox == 0 && cursorBlinkTime < cursorBlinkSpeed / 2.0f) {
            DrawLine(accountNumberRec.x + 10 + MeasureText(accountNumber, 20), accountNumberRec.y + 10, 
                     accountNumberRec.x + 10 + MeasureText(accountNumber, 20), accountNumberRec.y + 30, BLACK);
        } else if (activeTextBox == 1 && cursorBlinkTime < cursorBlinkSpeed / 2.0f) {
            DrawLine(amountRec.x + 10 + MeasureText(amount, 20), amountRec.y + 10, 
                     amountRec.x + 10 + MeasureText(amount, 20), amountRec.y + 30, BLACK);
        }

        // Show the transaction message if the transaction is successful
        if (transactionSent) {
            DrawText(transactionMessage, 250, 420, 20, GREEN);
        }

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
