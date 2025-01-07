#ifndef HFILE_H
#define HFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>
#include <raygui.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// Enum for screen states
typedef enum Screen {
    SCREEN_MAIN,
    SCREEN_ACCOUNT_DETAILS,
    SCREEN_DEPOSIT,
    SCREEN_WITHDRAW,
    SCREEN_SEND_MONEY,
    SCREEN_LOGOUT
} Screen;


    #define RAYGUI_IMPLEMENTATION
// Declare currentScreen globally
extern Screen currentScreen;

// Raylib colors
#define DARKGRAY CLITERAL(Color){ 80, 80, 80, 255 }

// In homepage.c
Screen currentScreen = SCREEN_MAIN;

// Struct to represent a bank account
struct BankAccount {
    int accountNumber;
    char accountHolder[100];
    char dob[11]; // YYYY-MM-DD format
    char aadhaarCard[13]; // 12-digit Aadhaar number
    float balance;
};

// Global variables for GUI states
static struct BankAccount currentAccount;
static char message[256] = "";
static int inputState = 0;
static char inputBuffer[256] = "";


// Function declarations
int GuiTextBox(Rectangle bounds, char *text, int textSize, bool editMode);    
int formatDate(char *dobInput, char *formattedDob);
void createAccount();
void deposit();
void withdraw();
void displayAccount();
void transferFunds();
void logTransaction(int fromAccountNumber, int toAccountNumber, float amount);

// Function to validate and format the date
int formatDate(char *dobInput, char *formattedDob) {
    int year, month, day;

    if (strlen(dobInput) != 8 || sscanf(dobInput, "%4d%2d%2d", &year, &month, &day) != 3) {
        return 0; // Invalid format
    }

    if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1) {
        return 0; // Invalid date ranges
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (day > daysInMonth[month - 1]) {
        return 0; // Invalid day
    }

    sprintf(formattedDob, "%04d-%02d-%02d", year, month, day);
    return 1; // Valid date
}

// GUI: Function to create a new account
void createAccount() {
    static int step = 0;
    static struct BankAccount newAccount;

    DrawText("Create New Account", 20, 20, 20, DARKGRAY);

    switch (step) {
        case 0:
            DrawText("Enter Account Number:", 20, 60, 20, DARKGRAY);
            if (GuiTextBox((Rectangle){20, 100, 200, 30}, inputBuffer, 256, true)) {
                newAccount.accountNumber = atoi(inputBuffer);
                inputBuffer[0] = '\0';
                step++;
            }
            break;

        case 1:
            DrawText("Enter Account Holder Name:", 20, 60, 20, DARKGRAY);
            if (GuiTextBox((Rectangle){20, 100, 200, 30}, inputBuffer, 256, true)) {
                strcpy(newAccount.accountHolder, inputBuffer);
                inputBuffer[0] = '\0';
                step++;
            }
            break;

        case 2:
            DrawText("Enter Date of Birth (YYYYMMDD):", 20, 60, 20, DARKGRAY);
            if (GuiTextBox((Rectangle){20, 100, 200, 30}, inputBuffer, 256, true)) {
                char formattedDob[11];
                if (formatDate(inputBuffer, formattedDob)) {
                    strcpy(newAccount.dob, formattedDob);
                    inputBuffer[0] = '\0';
                    step++;
                } else {
                    DrawText("Invalid date format. Try again.", 20, 140, 20, RED);
                }
            }
            break;

        case 3:
            DrawText("Enter Aadhaar Card Number:", 20, 60, 20, DARKGRAY);
            if (GuiTextBox((Rectangle){20, 100, 200, 30}, inputBuffer, 256, true)) {
                strcpy(newAccount.aadhaarCard, inputBuffer);
                newAccount.balance = 0.0;
                inputBuffer[0] = '\0';
                step++;
            }
            break;

        case 4: {
            FILE *file = fopen("../database/accounts.csv", "a");
            if (file != NULL) {
                fprintf(file, "%d,%s,%s,%s,%.2f\n", newAccount.accountNumber, newAccount.accountHolder, newAccount.dob, newAccount.aadhaarCard, newAccount.balance);
                fclose(file);
                strcpy(message, "Account created successfully!");
            } else {
                strcpy(message, "Error opening file.");
            }
            step = 0;
        } break;
    }

    DrawText(message, 20, 200, 20, DARKGRAY);
}

// Function for deposit
void deposit() {
    static char accountNumberInput[20] = {0};
    static char amountInput[20] = {0};
    static bool submitted = false;
    static char message[100] = {0};

    // BeginDrawing();
    // ClearBackground(RAYWHITE);

    DrawText("Deposit Money", SCREEN_WIDTH / 2 - MeasureText("Deposit Money", 30) / 2, 30, 30, DARKGRAY);

    DrawText("Account Number:", 200, 150, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 150, 200, 30}, accountNumberInput, 20, !submitted);

    DrawText("Amount:", 200, 200, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 200, 200, 30}, amountInput, 20, !submitted);

    if (GuiButton((Rectangle){300, 300, 100, 30}, "Submit")) {
        int accountNumber = atoi(accountNumberInput);
        float amount = atof(amountInput);

        if (accountNumber > 0 && amount > 0) {
            // Add backend deposit logic here
            snprintf(message, sizeof(message), "Deposited %.2f to Account %d", amount, accountNumber);
        } else {
            strcpy(message, "Invalid input. Please try again.");
        }
        submitted = true;
    }

    if (submitted) {
        DrawText(message, 200, 400, 20, RED);
    }

    if (GuiButton((Rectangle){300, 500, 100, 30}, "Back")) {
        currentScreen = SCREEN_MAIN;
        memset(accountNumberInput, 0, sizeof(accountNumberInput));
        memset(amountInput, 0, sizeof(amountInput));
        submitted = false;
    }

    EndDrawing();
}

// Function for withdraw
void withdraw() {
    static char accountNumberInput[20] = {0};
    static char amountInput[20] = {0};
    static bool submitted = false;
    static char message[100] = {0};

    // BeginDrawing();
    // ClearBackground(RAYWHITE);

    DrawText("Withdraw Money", SCREEN_WIDTH / 2 - MeasureText("Withdraw Money", 30) / 2, 30, 30, DARKGRAY);

    DrawText("Account Number:", 200, 150, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 150, 200, 30}, accountNumberInput, 20, !submitted);

    DrawText("Amount:", 200, 200, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 200, 200, 30}, amountInput, 20, !submitted);

    if (GuiButton((Rectangle){300, 300, 100, 30}, "Submit")) {
        int accountNumber = atoi(accountNumberInput);
        float amount = atof(amountInput);

        if (accountNumber > 0 && amount > 0) {
            // Add backend withdraw logic here
            snprintf(message, sizeof(message), "Withdrew %.2f from Account %d", amount, accountNumber);
        } else {
            strcpy(message, "Invalid input. Please try again.");
        }
        submitted = true;
    }

    if (submitted) {
        DrawText(message, 200, 400, 20, RED);
    }

    if (GuiButton((Rectangle){300, 500, 100, 30}, "Back")) {
        currentScreen = SCREEN_MAIN;
        memset(accountNumberInput, 0, sizeof(accountNumberInput));
        memset(amountInput, 0, sizeof(amountInput));
        submitted = false;
    }

    EndDrawing();
}

// Function for displaying account details
void displayAccount() {
    static char accountNumberInput[20] = {0};
    static bool submitted = false;
    static char accountDetails[300] = {0};

    // BeginDrawing();
    // ClearBackground(RAYWHITE);

    DrawText("Display Account Details", SCREEN_WIDTH / 2 - MeasureText("Display Account Details", 30) / 2, 30, 30, DARKGRAY);

    DrawText("Account Number:", 200, 150, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 150, 200, 30}, accountNumberInput, 20, !submitted);

    if (GuiButton((Rectangle){300, 300, 100, 30}, "Submit")) {
        int accountNumber = atoi(accountNumberInput);
        if (accountNumber > 0) {
            // Add backend logic for fetching account details
            snprintf(accountDetails, sizeof(accountDetails), "Details of Account: %d", accountNumber);  // Placeholder
        } else {
            strcpy(accountDetails, "Invalid account number.");
        }
        submitted = true;
    }

    if (submitted) {
        DrawText(accountDetails, 200, 400, 20, RED);
    }

    if (GuiButton((Rectangle){300, 500, 100, 30}, "Back")) {
        currentScreen = SCREEN_MAIN;
        memset(accountNumberInput, 0, sizeof(accountNumberInput));
        submitted = false;
    }

    EndDrawing();
}

// Function for transferring funds
void transferFunds() {
    static char fromAccountInput[20] = {0};
    static char toAccountInput[20] = {0};
    static char amountInput[20] = {0};
    static bool submitted = false;
    static char message[100] = {0};

    // BeginDrawing();
    // ClearBackground(RAYWHITE);

    DrawText("Transfer Funds", SCREEN_WIDTH / 2 - MeasureText("Transfer Funds", 30) / 2, 30, 30, DARKGRAY);

    DrawText("From Account Number:", 150, 150, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 150, 200, 30}, fromAccountInput, 20, !submitted);

    DrawText("To Account Number:", 150, 200, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 200, 200, 30}, toAccountInput, 20, !submitted);

    DrawText("Amount:", 150, 250, 20, DARKGRAY);
    GuiTextBox((Rectangle){400, 250, 200, 30}, amountInput, 20, !submitted);

    if (GuiButton((Rectangle){300, 350, 100, 30}, "Submit")) {
        int fromAccount = atoi(fromAccountInput);
        int toAccount = atoi(toAccountInput);
        float amount = atof(amountInput);

        if (fromAccount > 0 && toAccount > 0 && amount > 0) {
            // Add backend logic for transferring funds
            snprintf(message, sizeof(message), "Transferred %.2f from %d to %d", amount, fromAccount, toAccount);
        } else {
            strcpy(message, "Invalid input. Please try again.");
        }
        submitted = true;
    }

    if (submitted) {
        DrawText(message, 200, 400, 20, RED);
    }

    if (GuiButton((Rectangle){300, 500, 100, 30}, "Back")) {
        currentScreen = SCREEN_MAIN;
        memset(fromAccountInput, 0, sizeof(fromAccountInput));
        memset(toAccountInput, 0, sizeof(toAccountInput));
        memset(amountInput, 0, sizeof(amountInput));
        submitted = false;
    }

    EndDrawing();
}

#endif
