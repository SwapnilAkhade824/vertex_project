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

// Raygui implementation
#define RAYGUI_IMPLEMENTATION

// Declare currentScreen globally in the corresponding .c file


// Raylib color for DARKGRAY
#define DARKGRAY CLITERAL(Color){ 80, 80, 80, 255 }

// Struct to represent a bank account
typedef struct BankAccount {
    int accountNumber;
    char accountHolder[100];
    char dob[11]; // YYYY-MM-DD format
    char aadhaarCard[13]; // 12-digit Aadhaar number
    float balance;
} BankAccount;

// Global variables for GUI states
extern BankAccount currentAccount;  // This should be declared and initialized in the .c file
extern char message[256];           // Used for status messages
extern int inputState;              // Tracks input state for various forms
extern char inputBuffer[256];       // Used for text input in forms

// Function declarations for various functionalities
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

#endif // HFILE_H
