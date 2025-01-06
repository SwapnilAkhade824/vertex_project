#ifndef LOGIN_FUNCTION_H
#define LOGIN_FUNCTION_H

#include <stdio.h>
#include <string.h>

//Structure to hold customer details
typedef struct {
    char acc_num[49];
    char password[49];
} Customer;

Customer customer;

// Function to check login credentials
void login(const char *acc_num, const char *password) 
{
    // Open the file and handle errors
    FILE *file = fopen("Acc_details.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    char line[256];
    char stored_acc_num[49], stored_password[49];
    int account_found = 0;

    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token != NULL) 
            strcpy(stored_acc_num, token);  
        
        token = strtok(NULL, ",");
        if (token != NULL) 
            strcpy(stored_password, token);  
    
        // Remove trailing newline from password if present
        stored_password[strcspn(stored_password, "\n")] = '\0';

        // Check if the account exists and password matches
        if (strcmp(acc_num, stored_acc_num) == 0 && strcmp(password, stored_password) == 0) {
                printf("Account already exists, try loging in...\n");
            }
            
        }
         fclose(file); 
    }

   
   



#endif
