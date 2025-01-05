#include <raylib.h>
#include <stdio.h>

// Transaction structure
typedef struct Transaction {
    char type[10];  // "Deposit" or "Withdraw"
    float amount;
} Transaction;

// Button structure
typedef struct Button {
    Rectangle bounds;
    const char *text;
    Color normalColor;
    Color hoverColor;
    bool isHovered;
} Button;

// Function to draw a button and handle clicks
bool DrawButton(Button button) {
    Vector2 mousePoint = GetMousePosition();
    button.isHovered = CheckCollisionPointRec(mousePoint, button.bounds);

    Color color = button.isHovered ? button.hoverColor : button.normalColor;

    DrawRectangleRec(button.bounds, color);
    DrawText(button.text,
             button.bounds.x + button.bounds.width / 2 - MeasureText(button.text, 20) / 2,
             button.bounds.y + button.bounds.height / 2 - 10,
             20,
             WHITE);

    return button.isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Banking App - Advanced UI");

    // Colors
    Color backgroundColor = DARKGRAY;
    Color panelColor = LIGHTGRAY;
    Color textColor = BLACK;

    // Application States
    enum AppState { LOGIN, DASHBOARD, HISTORY } appState = LOGIN;

    // Buttons
    Button loginButton = { { screenWidth / 2 - 100, screenHeight / 2, 200, 50 }, "Login", GRAY, LIGHTGRAY };
    Button depositButton = { { 300, 300, 200, 50 }, "Deposit", GRAY, LIGHTGRAY };
    Button withdrawButton = { { 300, 370, 200, 50 }, "Withdraw", GRAY, LIGHTGRAY };
    Button historyButton = { { 300, 440, 200, 50 }, "History", GRAY, LIGHTGRAY };
    Button logoutButton = { { 300, 510, 200, 50 }, "Logout", RED, MAROON };
    Button backButton = { { 50, 520, 100, 40 }, "Back", GRAY, LIGHTGRAY };

    // Account and Transactions
    float accountBalance = 1500.0f;
    Transaction transactions[10];
    int transactionCount = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(backgroundColor);

        // Login Screen
        if (appState == LOGIN) {
            DrawText("Welcome to MyBank", screenWidth / 2 - MeasureText("Welcome to MyBank", 30) / 2, 150, 30, WHITE);

            if (DrawButton(loginButton)) {
                appState = DASHBOARD;
            }
        }

        // Dashboard Screen
        else if (appState == DASHBOARD) {
            // Header
            DrawRectangle(0, 0, screenWidth, 80, BLUE);
            DrawText("Banking Dashboard",
                     screenWidth / 2 - MeasureText("Banking Dashboard", 30) / 2,
                     25,
                     30,
                     WHITE);

            // Account Balance
            DrawRectangle(50, 100, screenWidth - 100, 150, panelColor);
            DrawText("Account Balance:",
                     100,
                     130,
                     20,
                     textColor);
            char balanceText[50];
            snprintf(balanceText, 50, "$ %.2f", accountBalance);
            DrawText(balanceText,
                     screenWidth - 250,
                     130,
                     30,
                     GREEN);

            // Buttons
            if (DrawButton(depositButton)) {
                accountBalance += 100.0f;  // Simulate deposit
                if (transactionCount < 10) {
                    Transaction t = {"Deposit", 100.0f};
                    transactions[transactionCount++] = t;
                }
            }
            if (DrawButton(withdrawButton)) {
                if (accountBalance >= 100.0f) {
                    accountBalance -= 100.0f;  // Simulate withdrawal
                    if (transactionCount < 10) {
                        Transaction t = {"Withdraw", 100.0f};
                        transactions[transactionCount++] = t;
                    }
                }
            }
            if (DrawButton(historyButton)) {
                appState = HISTORY;
            }
            if (DrawButton(logoutButton)) {
                appState = LOGIN;
            }
        }

        // Transaction History Screen
        else if (appState == HISTORY) {
            DrawRectangle(0, 0, screenWidth, 80, BLUE);
            DrawText("Transaction History",
                     screenWidth / 2 - MeasureText("Transaction History", 30) / 2,
                     25,
                     30,
                     WHITE);

            // Transactions List
            DrawRectangle(50, 100, screenWidth - 100, 400, panelColor);
            for (int i = 0; i < transactionCount; i++) {
                char transactionText[100];
                snprintf(transactionText, 100, "%s: $%.2f", transactions[i].type, transactions[i].amount);
                DrawText(transactionText, 70, 120 + i * 30, 20, textColor);
            }

            if (DrawButton(backButton)) {
                appState = DASHBOARD;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
