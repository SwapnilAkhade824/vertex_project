#include <raylib.h>
#include <string.h>

#define MAX_INPUT_CHARS 50

typedef enum AppState {
    LOGIN,
    HOME
} AppState;

typedef struct Account {
    char name[MAX_INPUT_CHARS];
    char accountNo[MAX_INPUT_CHARS];
    char ifscCode[MAX_INPUT_CHARS];
    float balance;
} Account;

int main() {
    // Screen dimensions
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Banking System");

    // App State
    AppState appState = LOGIN;

    // User inputs
    char username[MAX_INPUT_CHARS + 1] = "";
    char password[MAX_INPUT_CHARS + 1] = "";
    bool isPasswordHidden = true;
    bool usernameActive = false;
    bool passwordActive = false;

    // Mock credentials
    const char *validUsername = "user123";
    const char *validPassword = "password123";

    // Account details (only shown after login)
    Account userAccount = {"John Doe", "123456789", "IFSC0001", 1000.0};

    // Status message
    char statusMessage[100] = "";

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (appState == LOGIN) {
            // Login Page
            DrawText("Login to Banking System", screenWidth / 2 - MeasureText("Login to Banking System", 30) / 2, 50, 30, WHITE);

            // Username Field
            DrawRectangle(300, 150, 200, 40, usernameActive ? LIGHTGRAY : GRAY);
            DrawText("Username:", 200, 160, 20, WHITE);
            DrawText(username, 310, 160, 20, DARKGRAY);

            // Password Field
            DrawRectangle(300, 220, 200, 40, passwordActive ? LIGHTGRAY : GRAY);
            DrawText("Password:", 200, 230, 20, WHITE);
            if (isPasswordHidden) {
                char hiddenPassword[MAX_INPUT_CHARS + 1];
                memset(hiddenPassword, '*', strlen(password));
                hiddenPassword[strlen(password)] = '\0';
                DrawText(hiddenPassword, 310, 230, 20, RAYWHITE);
            } else {
                DrawText(password, 310, 230, 20, DARKGRAY);
            }

            // Login Button
            DrawRectangle(300, 300, 200, 40, BLUE);
            DrawText("Login", 360, 310, 20, WHITE);

            // Create Account Button
            DrawRectangle(300, 370, 200, 40, GREEN);
            DrawText("Create Account", 340, 380, 20, WHITE);

            // Status Message
            DrawText(statusMessage, screenWidth / 2 - MeasureText(statusMessage, 20) / 2, 450, 20, RED);

            // Mouse Interaction
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, (Rectangle){300, 150, 200, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                usernameActive = true;
                passwordActive = false;
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){300, 220, 200, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                usernameActive = false;
                passwordActive = true;
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){300, 300, 200, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Validate Login
                if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
                    appState = HOME;
                    strcpy(statusMessage, "Login successful!");
                } else {
                    strcpy(statusMessage, "Invalid username or password!");
                }
            }

            // Create Account Request
            if (CheckCollisionPointRec(mousePos, (Rectangle){300, 370, 200, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                strcpy(statusMessage, "Account creation requested. Awaiting admin approval.");
            }

            // Keyboard Interaction for Inputs
            int key = GetCharPressed();
            if (usernameActive) {
                if (key >= 32 && key <= 126 && strlen(username) < MAX_INPUT_CHARS) {
                    username[strlen(username)] = (char)key;
                    username[strlen(username) + 1] = '\0';
                }

                if (IsKeyPressed(KEY_BACKSPACE) && strlen(username) > 0) {
                    username[strlen(username) - 1] = '\0';
                }
            } else if (passwordActive) {
                if (key >= 32 && key <= 126 && strlen(password) < MAX_INPUT_CHARS) {
                    password[strlen(password)] = (char)key;
                    password[strlen(password) + 1] = '\0';
                }

                if (IsKeyPressed(KEY_BACKSPACE) && strlen(password) > 0) {
                    password[strlen(password) - 1] = '\0';
                }
            }

            // Toggle Password Visibility
            if (IsKeyPressed(KEY_TAB)) {
                isPasswordHidden = !isPasswordHidden;
            }
        } else if (appState == HOME) {
            // Home Page
            DrawText("Welcome to the Home Page", screenWidth / 2 - MeasureText("Welcome to the Home Page", 30) / 2, 50, 30, WHITE);
            DrawText("Account Information", 50, 100, 20, WHITE);

            // Account details
            DrawText(TextFormat("Name: %s", userAccount.name), 50, 140, 20, WHITE);
            DrawText(TextFormat("Account No: %s", userAccount.accountNo), 50, 170, 20, WHITE);
            DrawText(TextFormat("IFSC Code: %s", userAccount.ifscCode), 50, 200, 20, WHITE);
            DrawText(TextFormat("Balance: %.2f", userAccount.balance), 50, 230, 20, WHITE);

            // Service Options
            DrawText("Services: Transaction History, Loan Services, FD Creation", 50, 270, 20, LIGHTGRAY);
            DrawText("Press ESC to logout", 50, screenHeight - 50, 20, LIGHTGRAY);

            // Logout
            if (IsKeyPressed(KEY_ESCAPE)) {
                appState = LOGIN;
                memset(username, 0, sizeof(username));
                memset(password, 0, sizeof(password));
                strcpy(statusMessage, "");
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
