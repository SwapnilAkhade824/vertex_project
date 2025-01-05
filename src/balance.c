#include "raylib.h"
#include <stdio.h>

int main() {
    // Simulating account data (Placeholder)
    const char *accounts[] = {
        "> Savings Account",
        "> Checking Account",
        "> Business Account"
    };
    const int accountCount = sizeof(accounts) / sizeof(accounts[0]);

    int selectedAccount = -1; // To track selected account (Default: none)
    //int user_id = 123;  // Placeholder for the logged-in user's ID. This should be set after user login.

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Account Balance"); // Page name updated

    SetTargetFPS(60);  // Set FPS to 60

    while (!WindowShouldClose()) { // Main game loop
        BeginDrawing();
        ClearBackground(RAYWHITE);  // Clear the background to white

        // Header Bar
        DrawRectangle(0, 0, screenWidth, 50, DARKBLUE);
        DrawText("Account Balance", 100, 15, 20, RAYWHITE); // Moved right to avoid overlapping with Back button

        // Back Button
        Rectangle backButton = {10, 10, 80, 30};
        DrawRectangleRounded(backButton, 0.2, 10, MAROON);
        DrawText("Back", backButton.x + 10, backButton.y + 7, 16, RAYWHITE);

        if (CheckCollisionPointRec(GetMousePosition(), backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedAccount = -1; // Reset selected account if back button is clicked
        }

        // Display account buttons
        for (int i = 0; i < accountCount; i++) {
            Rectangle accountButton = {200, 100 + i * 70, 400, 50}; // Position and size of each account button
            DrawRectangleRounded(accountButton, 0.2, 10, LIGHTGRAY); // Draw the button with rounded corners
            DrawText(accounts[i], accountButton.x + 20, accountButton.y + 15, 20, DARKGRAY); // Display account name on the button

            // Check if the account button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), accountButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedAccount = i; // Set the selected account index
            }
        }

        // Display the selected account details
        if (selectedAccount >= 0) {
            DrawRectangleRounded((Rectangle){200, 400, 400, 100}, 0.2, 10, DARKGREEN);
            DrawRectangleRoundedLines((Rectangle){200, 400, 400, 100}, 0.2, 10, WHITE);
            DrawText(accounts[selectedAccount], 220, 420, 20, WHITE); // Display account name

            // Placeholder for the balance. need to replace this with the actual balance from the database.
            // Fetch the balance for the selected account from the database using the user_id and selectedAccount.
            // Example query could be:
            // After fetching the balance, replace the hardcoded  "Balance: $0.00" with the actual balance.
            DrawText("Balance: $0.00", 220, 460, 20, WHITE);  // Placeholder balance
        }

        EndDrawing(); // End drawing for the current frame
    }

    CloseWindow(); // Close the Raylib window
    return 0; // Exit the program
}
