#include "raylib.h"
#include <stdio.h>

// Structure to hold account data
typedef struct {
    const char *accountName;
    float balance;
} Account;

// Function to fetch the balance for the selected account (without using SQLite)
float getBalanceFromMemory(int selectedAccount) {
    // Simulated account balances stored in memory
    Account accounts[] = {
        {"Savings Account", 1000.50f},
        {"Checking Account", 2500.75f},
        {"Business Account", 50000.00f}
    };
    
    // Return the balance for the selected account
    return accounts[selectedAccount].balance;
}

int main() {
    // Simulated account names
    const char *accounts[] = {
        "> Savings Account",
        "> Checking Account",
        "> Business Account"
    };
    const int accountCount = sizeof(accounts) / sizeof(accounts[0]);

    int selectedAccount = -1; // To track selected account (Default: none)
    int user_id = 123;  // Placeholder for the logged-in user's ID. This should be set after user login.

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Account Balance");

    SetTargetFPS(60);  // Set FPS to 60

    while (!WindowShouldClose()) { // Main game loop
        BeginDrawing();
        ClearBackground(RAYWHITE);  // Clear the background to white

        // Header Bar
        DrawRectangle(0, 0, screenWidth, 50, DARKBLUE);
        DrawText("Account Balance", 100, 15, 20, RAYWHITE);

        // Back Button
        Rectangle backButton = {10, 10, 80, 30};
        DrawRectangleRounded(backButton, 0.2, 10, MAROON);
        DrawText("Back", backButton.x + 10, backButton.y + 7, 16, RAYWHITE);

        if (CheckCollisionPointRec(GetMousePosition(), backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedAccount = -1; // Reset selected account if back button is clicked
        }

        // Display account buttons
        for (int i = 0; i < accountCount; i++) {
            Rectangle accountButton = {200, 100 + i * 70, 400, 50};
            DrawRectangleRounded(accountButton, 0.2, 10, LIGHTGRAY); // Draw the button with rounded corners
            DrawText(accounts[i], accountButton.x + 20, accountButton.y + 15, 20, DARKGRAY); // Display account name

            // Check if the account button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), accountButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedAccount = i; // Set the selected account index
            }
        }

        // Display the selected account details
        if (selectedAccount >= 0) {
            // Fetch the balance from the simulated memory
            float balance = getBalanceFromMemory(selectedAccount);

            // Display the selected account details
            DrawRectangleRounded((Rectangle){200, 400, 400, 100}, 0.2, 10, DARKGREEN);
            DrawRectangleRoundedLines((Rectangle){200, 400, 400, 100}, 0.2, 10, WHITE);
            DrawText(accounts[selectedAccount], 220, 420, 20, WHITE); // Display account name

            // Format the balance text
            char balanceText[64];
            snprintf(balanceText, sizeof(balanceText), "Balance: $%.2f", balance);

            // Display the actual balance fetched from memory
            DrawText(balanceText, 220, 460, 20, WHITE); // Display actual balance
        }

        EndDrawing(); // End drawing for the current frame
    }

    CloseWindow(); // Close the Raylib window
    return 0; // Exit the program
}
