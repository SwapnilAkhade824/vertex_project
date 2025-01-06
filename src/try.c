#include<stdio.h>
#include<stdlib.h>
#include "admin.h"
#include<string.h>


void inputAccountData(Account *account) {
    
    account->accountNumber = generateUniqueId();
    printf("Your Account Number would be : %lld\n", account->accountNumber);

    
    // while (getchar() != '\n');

    printf("Enter Full Name: ");
    fgets(account->fullName, MAX_LENGTH, stdin);
    removeNewline(account->fullName);

    printf("Enter Gender (M/F): ");
    fgets(account->gender, sizeof(account->gender), stdin);
    removeNewline(account->gender);

    while (getchar() != '\n');

    printf("Enter Address: ");
    fgets(account->address, MAX_LENGTH, stdin);
    removeNewline(account->address);

    printf("Enter Email ID: ");
    fgets(account->email, MAX_LENGTH, stdin);
    removeNewline(account->email);

    printf("Enter Nationality: ");
    fgets(account->nationality, MAX_LENGTH, stdin);
    removeNewline(account->nationality);

    printf("Enter Phone Number: ");
    fgets(account->phoneNumber, sizeof(account->phoneNumber), stdin);
    removeNewline(account->phoneNumber);

    writeToCSV(account);
}
    


int main() {
	Account *account = malloc(sizeof(Account));

    inputAccountData(account);
    return 0;
}