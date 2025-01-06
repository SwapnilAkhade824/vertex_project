#include <stdio.h>
#include <string.h>
#include "C:\Dev\vertex\project\include\login_function.h"

int main() {
    char acc_num[49], password[49];

    // Prompt the user for account number and password
    printf("Enter account number: ");
    scanf("%s", acc_num);

    printf("Enter password: ");
    scanf("%s", password);

    // Call the login function to check the credentials
    login(acc_num, password);

    return 0;
}
