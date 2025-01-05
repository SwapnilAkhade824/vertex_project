#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BankAccount {
    int accountNumber;
    char accountHolder[100];
    char dob[11];  // For storing date in YYYY-MM-DD format
    char aadhaarCard[13];  // Assuming Aadhaar number is a 12-digit number
    float balance;
};


// Function to validate and format the date
int formatDate(char *dobInput, char *formattedDob) {
    int year, month, day;

    // Ensure the input is 8 digits long
    if (strlen(dobInput) != 8 || sscanf(dobInput, "%4d%2d%2d", &year, &month, &day) != 3) {
        return 0; // Invalid format
    }

    // Validate the year, month, and day ranges
    if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1) {
        return 0; // Invalid date ranges
    }

    // Days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust for leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (day > daysInMonth[month - 1]) {
        return 0; // Invalid day
    }

    // Format the date as YYYY-MM-DD
    sprintf(formattedDob, "%04d-%02d-%02d", year, month, day);
    return 1; // Date is valid
}

// Function to create a new account
void createAccount() {
    struct BankAccount account;
    char dobInput[9], formattedDob[11];

    printf("Enter account number: ");
    scanf("%d", &account.accountNumber);
    printf("Enter account holder name: ");
    scanf("%s", account.accountHolder);
    
    // Accept and format the date of birth
    do {
        printf("Enter Date of Birth (YYYYMMDD): ");
        scanf("%s", dobInput);
        if (!formatDate(dobInput, formattedDob)) {
            printf("Invalid date. Please try again.\n");
        }
    } while (!formatDate(dobInput, formattedDob));
    
    strcpy(account.dob, formattedDob); // Save formatted date
    printf("Enter Aadhaar card number: ");
    scanf("%s", account.aadhaarCard);
    account.balance = 0.0;

    FILE *file = fopen("accounts.csv", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    // Write account data in CSV format
    fprintf(file, "%d,%s,%s,%s,%.2f\n", account.accountNumber, account.accountHolder, account.dob, account.aadhaarCard, account.balance);
    fclose(file);
    printf("Account created successfully.\n");
}

// Function to deposit an amount into an account
void deposit() {
    int accountNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    FILE *file = fopen("accounts.csv", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct BankAccount account;
    struct BankAccount accounts[100];  // Assuming we have a max of 100 accounts
    int accountCount = 0;
    int found = 0;

    // Read all accounts from the file
    while (fscanf(file, "%d,%99[^,],%10[^,],%12[^,],%f\n", &account.accountNumber, account.accountHolder, account.dob, account.aadhaarCard, &account.balance) != EOF) {
        accounts[accountCount++] = account;
    }
    fclose(file);

    // Find the account and deposit money
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts[i].balance += amount;
            found = 1;
            break;
        }
    }

    // If account found, rewrite the file with the updated balance
    if (found) {
        file = fopen("accounts.csv", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        // Write all accounts back to the file
        for (int i = 0; i < accountCount; i++) {
            fprintf(file, "%d,%s,%s,%s,%.2f\n", accounts[i].accountNumber, accounts[i].accountHolder, accounts[i].dob, accounts[i].aadhaarCard, accounts[i].balance);
        }
        fclose(file);
        printf("Amount deposited successfully.\n");
    } else {
        printf("Account not found.\n");
    }
}

// Function to withdraw an amount from an account
void withdraw() {
    int accountNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    FILE *file = fopen("accounts.csv", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct BankAccount account;
    struct BankAccount accounts[100];
    int accountCount = 0;
    int found = 0;

    // Read all accounts from the file
    while (fscanf(file, "%d,%99[^,],%10[^,],%12[^,],%f\n", &account.accountNumber, account.accountHolder, account.dob, account.aadhaarCard, &account.balance) != EOF) {
        accounts[accountCount++] = account;
    }
    fclose(file);

    // Find the account and withdraw money
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                found = 1;
            } else {
                printf("Insufficient balance.\n");
                found = -1;
            }
            break;
        }
    }

    // If account found, rewrite the file with the updated balance
    if (found == 1) {
        file = fopen("accounts.csv", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        // Write all accounts back to the file
        for (int i = 0; i < accountCount; i++) {
            fprintf(file, "%d,%s,%s,%s,%.2f\n", accounts[i].accountNumber, accounts[i].accountHolder, accounts[i].dob, accounts[i].aadhaarCard, accounts[i].balance);
        }
        fclose(file);
        printf("Amount withdrawn successfully.\n");
    } else if (found == -1) {
        // Handled in the insufficient balance case
    } else {
        printf("Account not found.\n");
    }
}

// Function to display details of a specific account
void displayAccount() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    FILE *file = fopen("accounts.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct BankAccount account;
    int found = 0;
    while (fscanf(file, "%d,%99[^,],%10[^,],%12[^,],%f\n", &account.accountNumber, account.accountHolder, account.dob, account.aadhaarCard, &account.balance) != EOF) {
        if (account.accountNumber == accountNumber) {
            printf("Account Number: %d\n", account.accountNumber);
            printf("Account Holder: %s\n", account.accountHolder);
            printf("Date of Birth: %s\n", account.dob);
            printf("Aadhaar Card: %s\n", account.aadhaarCard);
            printf("Balance: %.2f\n", account.balance);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Account not found.\n");
    }
}

// Function to list all accounts
void listAccounts() {
    FILE *file = fopen("accounts.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct BankAccount account;
    int found = 0;
    printf("\nList of all accounts:\n");
    while (fscanf(file, "%d,%99[^,],%10[^,],%12[^,],%f\n", &account.accountNumber, account.accountHolder, account.dob, account.aadhaarCard, &account.balance) != EOF) {
        printf("\nAccount Number: %d\n", account.accountNumber);
        printf("Account Holder: %s\n", account.accountHolder);
        printf("Date of Birth: %s\n", account.dob);
        printf("Aadhaar Card: %s\n", account.aadhaarCard);
        printf("Balance: %.2f\n", account.balance);
        found = 1;
    }
    fclose(file);

    if (!found) {
        printf("No accounts found.\n");
    }
}