#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // For date and time
#include "hfile.h"

// Declare the logTransaction function in the header file
void logTransaction(int fromAccountNumber, int toAccountNumber, float amount);

void transferFunds() {
    int fromAccountNumber, toAccountNumber;
    float amount;
    printf("Enter account number to transfer from: ");
    scanf("%d", &fromAccountNumber);
    printf("Enter account number to transfer to: ");
    scanf("%d", &toAccountNumber);
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    FILE *file = fopen("accounts.csv", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct BankAccount account;
    struct BankAccount accounts[100];
    int accountCount = 0;
    int fromFound = 0, toFound = 0;

    // Read all accounts into memory (CSV format)
    while (fscanf(file, "%d,%99[^,],%10[^,],%12[^,],%f\n", &account.accountNumber, account.accountHolder, account.dob, account.aadhaarCard, &account.balance) != EOF) {
        accounts[accountCount++] = account;
    }
    fclose(file);

    // Find the 'from' and 'to' accounts
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == fromAccountNumber) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                fromFound = 1;
            } else {
                printf("Insufficient balance in the source account.\n");
                fromFound = -1;
            }
        }
        if (accounts[i].accountNumber == toAccountNumber) {
            accounts[i].balance += amount;
            toFound = 1;
        }
    }

    if (fromFound == 1 && toFound == 1) {
        // Update the accounts file with the new balances (CSV format)
        file = fopen("accounts.csv", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        for (int i = 0; i < accountCount; i++) {
            fprintf(file, "%d,%s,%s,%s,%.2f\n", accounts[i].accountNumber, accounts[i].accountHolder, accounts[i].dob, accounts[i].aadhaarCard, accounts[i].balance);
        }
        fclose(file);
        printf("Transfer successful.\n");

        // Log the transaction in the transfer_log.csv file
        logTransaction(fromAccountNumber, toAccountNumber, amount);
    } else if (fromFound == -1) {
        // Insufficient balance handled earlier
    } else {
        printf("Account not found.\n");
    }
}

void logTransaction(int fromAccountNumber, int toAccountNumber, float amount) {
    // Get the current date and time
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);

    // Open the transaction log file in append mode
    FILE *logFile = fopen("transfer_log.csv", "a");
    if (logFile == NULL) {
        printf("Error opening log file.\n");
        return;
    }

    // Write the transaction details to the CSV file
    fprintf(logFile, "%d,%d,%.2f,%s\n", fromAccountNumber, toAccountNumber, amount, timeStr);

    fclose(logFile);
}
