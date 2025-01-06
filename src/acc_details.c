#include "raylib.h"
#include <stdio.h>
#include <string.h>

// Struct to hold account details
typedef struct {
    char accountHolderName[50];
    char accountNumber[20];
    char email[50];
} BankAccount;

int main(void) {
    // Initialize Raylib window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Crest Bank - Account Details");

    // Account details (hardcoded for this example)
    BankAccount account = {
        "John Doe",          // Name
        "1234567890123456",  // Account number
        "john.doe@example.com" // Email
    };

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Start drawing
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Bank name and title
        DrawText("Crest Bank", screenWidth / 2 - MeasureText("Crest Bank", 40) / 2, 50, 40, DARKBLUE);
        DrawText("Account Details", screenWidth / 2 - MeasureText("Account Details", 30) / 2, 110, 30, DARKGRAY);

        // Display account details
        DrawText("Account Holder:", 200, 200, 20, BLACK);
        DrawText(account.accountHolderName, 400, 200, 20, DARKGREEN);

        DrawText("Account Number:", 200, 250, 20, BLACK);
        DrawText(account.accountNumber, 400, 250, 20, DARKGREEN);

        DrawText("Email ID:", 200, 300, 20, BLACK);
        DrawText(account.email, 400, 300, 20, DARKGREEN);

        // Footer
        DrawText("Thank you for banking with Crest Bank!", 
                 screenWidth / 2 - MeasureText("Thank you for banking with Crest Bank!", 20) / 2, 
                 screenHeight - 50, 
                 20, 
                 GRAY);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
