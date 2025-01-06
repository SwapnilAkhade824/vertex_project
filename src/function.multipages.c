#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\Dev\vertex\project\include\transaction.h"


int main() {
    int choice;
do {
    printf("\nBank Account System\n");
    printf("1. Create Account\n");
    printf("2. Deposit Amount\n");
    printf("3. Withdraw Amount\n");
    printf("4. Display Account Details\n");
    printf("5. Transfer Funds\n");  // New option for transferring funds
    printf("6. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            displayAccount();
            break;
        case 5:
            transferFunds();  // Call transfer function
            break;
        case 6:
            printf("Thank you for using the Bank Account System.\n");
            break;
        default:
            printf("Invalid choice.\n");
    }
} while (choice != 6);
}