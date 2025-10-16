#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tENTERED INTO CONTACT LIST\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    
    printf("%-15s  %-15s  %-30s \n", "Name", "Phone", "Email"); // To print table column titless
    printf("---------------------------------------------------\n");
    for( int i=0;i<addressBook->contactCount;i++)// To list out the contacts one by one
    {
        printf("%-15s\t%-15s\t%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

/*void saveAndExit(AddressBook *addressBook) 
{
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tENTERED INTO SAVE CONTACT\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}*/


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tENTERED INTO CREATE CONTACT\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    if (addressBook->contactCount >= 100)  // Checks if address book is full
    {
        printf("Address book is full. Cannot add more contacts.\n");  
        return;
    }

    Contact newContact;  // New struct named newContact created
    int validName =0;    // Flag to check if the name is valid or not
    while(!validName)
    {
        printf("Enter contact name (only alphabets): ");
        scanf(" %49[^\n]", newContact.name);    // read the new name
        validName = 1;
        for (int i = 0; newContact.name[i] != '\0'; i++)  // Checks if the name has upper and lowercase letters and contains spaces
        {
            if (!((newContact.name[i] >= 'A' && newContact.name[i] <= 'Z') || (newContact.name[i] >= 'a' && newContact.name[i] <= 'z') || newContact.name[i] == ' '))
            {
                validName = 0; // If not valid flag set to 0
                printf("Invalid name. Only alphabets and spaces are allowed.\n");
                break;
            }
        }
    } 

    int validPhone = 0; // flag to check if phone number is valid or not
    while (!validPhone) 
    {
    printf("Enter phone number (10 digits): ");
    scanf(" %19[^\n]", newContact.phone); // reads new phone number

    if (strlen(newContact.phone) != 10)  // to check if new number is exactly 10 digits long
    {
        printf("Invalid phone number. It must be exactly 10 digits.\n");
    } 
    else 
    {
        validPhone = 1; 
        for (int i = 0; newContact.phone[i] != '\0'; i++)  
        {
            if (!(newContact.phone[i] >= '0' && newContact.phone[i] <= '9')) // checks if number has only digits from 0 to 9
            {
                printf("Invalid phone number. Only digits are allowed.\n");
                validPhone = 0; // invalid if number has anything else other than digits
                break;
            }
        }
    }

    if (validPhone) 
    {
        // Check if the phone number already exists
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].phone, newContact.phone) == 0) 
            {
                printf("Phone number already exists.\n");
                validPhone = 0; // Invalid if the phone number already exists
                break;
            }
        }
    }
}

int validEmail = 0; //flag to check email is valid or not
while (!validEmail) 
{
    int atFound = 0, dotFound = 0; // flags for '@' and '.'
    printf("Enter email (must be lowercase, contain '@', and '.'): ");
    scanf(" %49[^\n]", newContact.email);

    // Check for invalid characters
    validEmail = 1; // Assume valid email
    for (int i = 0; newContact.email[i] != '\0'; i++) 
    {    // checks if email has only alphabets ,numbers,@ and .
        if (!((newContact.email[i] >= 'a' && newContact.email[i] <= 'z') || (newContact.email[i] >= '0' && newContact.email[i] <= '9') ||  newContact.email[i] == '@' || newContact.email[i] == '.')) 
        { 
            printf("Invalid email. Only lowercase letters, digits, '@', and '.' are allowed.\n");
            validEmail = 0; // Invalid email
            break;
        }
        
        if (newContact.email[i] == ' ') 
        {
            printf("Invalid email. No spaces are allowed.\n");
            validEmail = 0; // Invalid if it contains spaces
            break;
        }

        if (newContact.email[i] == '@')  // to check if more than one @ is in the email
        {
            if (atFound) 
            {
                printf("Invalid email. Only one '@' is allowed.\n");
                validEmail = 0;
                break;   
            }
            atFound = 1;
        }

        if (newContact.email[i] == '.' && atFound) 
        {
            dotFound = 1; // Both '.' and '@' are found
        }

        if (newContact.email[i] == '.' && !atFound) // checks if '.' appears before '@'
        {
            printf("Invalid email. '.' cannot appear before '@'.\n");
            validEmail = 0;
            break;
        }
    }

    if (validEmail && (!atFound || !dotFound)) // 
    {
        printf("Invalid email. It must contain both '.' and '@'.\n");
        validEmail = 0; // Invalid if '@' or '.' is not found
    }

}

    addressBook->contacts[addressBook->contactCount] = newContact;// new contact is added to addressbook
    addressBook->contactCount++;

    printf("Contact added successfully.\n");
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tENTERED INTO SEARCH CONTACT\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    char searched[50];
    int i, sch, flag = 1;
    printf("Search by\n1.Name\n2.Ph no:\n3.email\n");
    scanf("%d", &sch);

    switch(sch)
    { 
        case 1:
        {
            printf("Enter the name or starting few letters: ");
            getchar();  //to consume newline left by the input
            scanf("%49[^\n]", searched);  

            
            for (i = 0; i < addressBook->contactCount; i++)
            {
                
                if (strncmp(addressBook->contacts[i].name, searched, strlen(searched)) == 0) // compares input with already existing contact name
                {
                    
                    printf("Contact found - ");
                    printf("%-15s\t%-15s\t%-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag = 0;  // Set flag to 0 indicating that we found a match
                }
            }

            if (flag == 1)
            { 
                printf("No contacts found with the given name or starting letters.\n");
            }
            break;
        }

        case 2:
        {
            printf("Enter the Phone no: or first few digits : ");
            getchar();  
            scanf("%49[^\n]", searched);  

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strncmp(addressBook->contacts[i].phone, searched, strlen(searched)) == 0) // To compare input with already existing contact phone number
                {
                    
                    printf("Contact found - ");
                    printf("%-15s\t%-15s\t%-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag = 0;  
                }
            }

            if (flag == 1)
            { 
                printf("No contacts found with the given phone number.\n");
            }
            break;
        }

        case 3:
        {
            printf("Enter the email or first few characters : ");
            getchar();  
            scanf("%49[^\n]", searched);  

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strncmp(addressBook->contacts[i].email, searched, strlen(searched)) == 0)// To compare input with already existing emails
                {
                    printf("Contact found - ");
                    printf("%-15s\t%-15s\t%-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag = 0;  
                }
            }

            if (flag == 1)
            { 
                printf("No contacts found with the given email.\n");
            }
            break;
        }

        default:
        {
            printf("Invalid Input\n");
        }
    }
}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tENTERED INTO EDIT CONTACT\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    char searched[50];
    int i,sch,flag=1;
    printf("Search by\n1.Name\n2.Ph no:\n3.email\n");
    scanf("%d",&sch);
    switch(sch)
    { 
        case 1:
        {
            printf("Enter the name (or partial name): ");
            getchar();
            scanf("%49[^\n]", searched);
            int matchingIndexes[100], matchCount = 0; // new array to add matching contacts

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strncmp(addressBook->contacts[i].name, searched, strlen(searched)) == 0)// To compare input with already existing names in the addressbook
                {
                    matchingIndexes[matchCount++] = i; // if input matches array is updated
                    printf("%d. %-15s\t%-15s\t%-30s\n", matchCount, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                }
            }

            if (matchCount == 0)// input doesnot match with contacts in addressbook
            {
                printf("No contacts found with the name \"%s\".\n", searched);
            }
            else
            {
                int choice;
                printf("Enter the number of the contact you want to edit: ");
                scanf("%d", &choice);
                printf("\n");
                if (choice > 0 && choice <= matchCount)
                {
                    int selectedIndex = matchingIndexes[choice - 1];// matched contact is selected
                    int editChoice;
                    printf("Contact selected - %-15s\t%-15s\t%-30s\n", addressBook->contacts[selectedIndex].name, addressBook->contacts[selectedIndex].phone, addressBook->contacts[selectedIndex].email);
                    printf("\n");
                    printf("Which detail do you want to edit?\n");
                    printf("1. Name\n2. Phone\n3. Email\n");
                    printf("Enter the number: ");
                    scanf("%d", &editChoice);

                    switch (editChoice)
                    {
                        case 1:
                        {
                        printf("Enter new name: ");
                        char newName[50];
                        getchar(); // to consume the newline character
                        scanf("%49[^\n]", newName);
                        // Check if the new name contains only alphabetic characters or spaces
                         int validName = 1;  // assume the name is valid
                        for (int i = 0; newName[i] != '\0'; i++) 
                        {
                          if (!((newName[i] >= 'A' && newName[i] <= 'Z') || (newName[i] >= 'a' && newName[i] <= 'z') || newName[i] == ' ')) 
                          {
                          validName = 0;  // invalid name found
                          break;
                          }
                        }

                        if (validName) 
                        {
                        // If the new name is valid, update the contact name
                        strcpy(addressBook->contacts[selectedIndex].name, newName);
                        printf("Name updated successfully!\n");
                        } 
                        else 
                        {
                        // If the new name contains invalid characters, display an error
                        printf("Invalid name! Name must contain only letters and spaces.\n");
                        }
                        break;
                        }

                        case 2:
                        {
                        printf("Enter new phone number: ");
                        char newPhone[20];
                        int isValidPhone = 1;  // Assume the phone number is valid
                        getchar();  // To consume the newline character
                        scanf("%19[^\n]", newPhone);

                        // Check if the phone number contains only digits and is exactly 10 digits long
                        int length = 0;
                        for (int i = 0; newPhone[i] != '\0'; i++) 
                        {
                            if (newPhone[i] < '0' || newPhone[i] > '9') 
                            {
                            isValidPhone = 0;  // Invalid phone number 
                            break;
                            }
                        length++;
                        }

                        if (length != 10) // Check if the phone number length is not 10 digits
                        {
                        isValidPhone = 0;
                        }

                        for (int i = 0; i < addressBook->contactCount; i++) // Check if the phone number already exists in the contact list
                        {
                           if (strcmp(addressBook->contacts[i].phone, newPhone) == 0) 
                           {
                            printf("Phone number already exists for contact: %s\n", addressBook->contacts[i].name);
                            isValidPhone = 0;  // Mark as invalid because it's already present
                            break;
                           }
                        }

                        // If valid, update the contact's phone number
                        if (isValidPhone) 
                        {
                        strcpy(addressBook->contacts[selectedIndex].phone, newPhone);
                        printf("Phone number updated successfully!\n");
                        }
                        else 
                        {
                        printf("Invalid phone number! Must be exactly 10 digits and should not already exist.\n");
                        }
                        break;
                        }

                        case 3:
                       {
                        printf("Enter new email: ");
                        char newEmail[50];
                        int isValidEmail = 1;  // Assume email is valid
                        int atFound = 0, dotFound = 0;
                        getchar();  // To consume the newline character
                        scanf("%49[^\n]", newEmail);

                        for (int i = 0; newEmail[i] != '\0'; i++) // Check if the email contains only lowercase letters, digits, '@', and '.'
                        {
                          if (!((newEmail[i] >= 'a' && newEmail[i] <= 'z') || (newEmail[i] >= '0' && newEmail[i] <= '9') ||newEmail[i] == '@' || newEmail[i] == '.')) 
                          {
                          printf("Invalid email. Only lowercase letters, digits, '@', and '.' are allowed.\n");
                          isValidEmail = 0;  // Invalid email
                          break;
                          }

                          if (newEmail[i] == ' ') // Check for spaces
                          {
                          printf("Invalid email. No spaces are allowed.\n");
                          isValidEmail = 0;  // Invalid email if spaces are found
                          break;
                          }

                          if (newEmail[i] == '@') // Check for '@' symbol
                          {
                           if (atFound) 
                             {  // Ensure only one '@'
                              printf("Invalid email. Only one '@' is allowed.\n");
                              isValidEmail = 0;
                              break;
                             }
                           atFound = 1;  // Mark that '@' is found
                          }
                       
                          if (newEmail[i] == '.' && atFound) // Ensure '.' appears after '@'
                          {
                          dotFound = 1;  // Mark that '.' is found after '@'
                          }
                          
                          if (newEmail[i] == '.' && !atFound) // Check if '.' appears before '@'
                          {
                          printf("Invalid email. '.' cannot appear before '@'.\n");
                          isValidEmail = 0;
                          break;
                          }
                        }
                          
                        if (isValidEmail && (!atFound || !dotFound))// Final validation: Must contain both '@' and '.'
                         {
                          printf("Invalid email. It must contain both '@' and '.'.\n");
                          isValidEmail = 0;  // Invalid email if missing '@' or '.'
                         }
                        
                        if (isValidEmail) // If valid, update the contact's email
                         {
                         strcpy(addressBook->contacts[selectedIndex].email, newEmail);
                        printf("Email updated successfully!\n");
                         } 
                         else 
                         {
                         printf("Email not updated due to invalid input.\n");
                         }
                         break;
                       }

                        default:
                            printf("Invalid input. No changes made.\n");
                    }
                }
                else
                {
                    printf("Invalid choice.\n");
                }
            }
            break;
        }

        case 2:
       {
        printf("Enter the Phone no: ");
        getchar();
        scanf("%49[^\n]", searched);
    
        int found = 0;  // Flag to track if the contact is found
        for (i = 0; i < addressBook->contactCount; i++) 
        {
          if (strcmp(addressBook->contacts[i].phone, searched) == 0) 
          {
            found = 1;
            int selectedIndex = i; // Assign the selected index to the found contact
            
            printf("Contact found - ");
            printf("%-15s\t%-15s\t%-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            
            int editChoice;
            printf("Which detail do you want to edit?\n");
            printf("1. Name\n2. Phone\n3. Email\n");
            printf("Enter the number: ");
            scanf(" %d", &editChoice);

            switch (editChoice) 
            {
                case 1:
                {
                    printf("Enter new name: ");
                    char newName[50];
                    getchar();  // To consume the newline character
                    scanf("%49[^\n]", newName);
                                      
                    int validName = 1;  // Assume the name is valid
                    for (int i = 0; newName[i] != '\0'; i++) 
                    { // Check if the new name contains only alphabetic characters or spaces
                        if (!((newName[i] >= 'A' && newName[i] <= 'Z') || (newName[i] >= 'a' && newName[i] <= 'z') || newName[i] == ' ')) 
                        {
                            validName = 0;  // Invalid name found
                            break;
                        }
                    }

                    if (validName) 
                    {                        
                        strcpy(addressBook->contacts[selectedIndex].name, newName);// If the new name is valid, update the contact name
                        printf("Name updated successfully!\n");
                    } 
                    else 
                    {                       
                        printf("Invalid name! Name must contain only letters and spaces.\n");// If the new name contains invalid characters, display an error
                    }
                    break;
                }

                case 2:
                {
                    printf("Enter new phone number: ");
                    char newPhone[20];
                    int isValidPhone = 1;  // Assume the phone number is valid
                    getchar();  // To consume the newline character
                    scanf("%19[^\n]", newPhone);
                    
                    int length = 0; 
                    for (int i = 0; newPhone[i] != '\0'; i++) 
                    {
                        if (newPhone[i] < '0' || newPhone[i] > '9') // Check if the phone number contains only digits
                        {
                            isValidPhone = 0;  // Invalid phone number (non-digit character found)
                            break;
                        }
                        length++;
                    }
                    
                    if (length != 10) // Check if the phone number length is not 10 digits
                    {
                        isValidPhone = 0;
                    }
                    
                    for (int i = 0; i < addressBook->contactCount; i++) // Check if the phone number already exists in the contact list
                    {
                        if (strcmp(addressBook->contacts[i].phone, newPhone) == 0) 
                        {
                            printf("Phone number already exists for contact: %s\n", addressBook->contacts[i].name);
                            isValidPhone = 0;  // Mark as invalid because it's already present
                            break;
                        }
                    }
                    
                    if (isValidPhone) // If valid, update the contact's phone number
                    {
                        strcpy(addressBook->contacts[selectedIndex].phone, newPhone);
                        printf("Phone number updated successfully!\n");
                    }
                    else 
                    {
                        printf("Invalid phone number! Must be exactly 10 digits and should not already exist.\n");
                    }
                    break;
                }

                case 3:
                {
                    printf("Enter new email: ");
                    char newEmail[50];
                    int isValidEmail = 1;  // Assume email is valid
                    int atFound = 0, dotFound = 0;
                    getchar();  // To consume the newline character
                    scanf("%49[^\n]", newEmail);
                    
                    for (int i = 0; newEmail[i] != '\0'; i++) 
                    { // Check if the email contains only lowercase letters, digits, '@', and '.'
                        if (!((newEmail[i] >= 'a' && newEmail[i] <= 'z') || (newEmail[i] >= '0' && newEmail[i] <= '9') || newEmail[i] == '@' || newEmail[i] == '.')) 
                        {
                            printf("Invalid email. Only lowercase letters, digits, '@', and '.' are allowed.\n");
                            isValidEmail = 0;  // Invalid email
                            break;
                        }
                        
                        if (newEmail[i] == ' ') // Check for spaces
                        {
                            printf("Invalid email. No spaces are allowed.\n");
                            isValidEmail = 0;  // Invalid email if spaces are found
                            break;
                        }
                        
                        if (newEmail[i] == '@') // Check for '@' symbol
                        {
                            if (atFound) 
                            {  // Ensure only one '@'
                                printf("Invalid email. Only one '@' is allowed.\n");
                                isValidEmail = 0;
                                break;
                            }
                            atFound = 1;  // Mark that '@' is found
                        }
                        
                        if (newEmail[i] == '.' && atFound) // Ensure '.' appears after '@'
                        {
                            dotFound = 1;  // Mark that '.' is found after '@'
                        }
                        
                        if (newEmail[i] == '.' && !atFound) // Check if '.' appears before '@'
                        {
                            printf("Invalid email. '.' cannot appear before '@'.\n");
                            isValidEmail = 0;
                            break;
                        }
                    }
                    
                    if (isValidEmail && (!atFound || !dotFound)) // Final validation: Must contain both '@' and '.'
                    {
                        printf("Invalid email. It must contain both '@' and '.'.\n");
                        isValidEmail = 0;  // Invalid email if missing '@' or '.'
                    }
                    
                    if (isValidEmail) // If valid, update the contact's email
                    {
                        strcpy(addressBook->contacts[selectedIndex].email, newEmail);
                        printf("Email updated successfully!\n");
                    } 
                    else 
                    {
                        printf("Email not updated due to invalid input.\n");
                    }
                    break;
                }

                default:
                {
                    printf("Invalid input. No changes were made.\n");
                }
            }
            break;
        }
    }

    if (!found) 
    {
        printf("Contact not found.\n");
    }
    break;
}
        case 3:
        {
         printf("Enter the email: ");
        getchar();
        scanf("%49[^\n]", searched);
        int flag = 1;
        int selectedIndex = -1; // Initialize selectedIndex

        for (i = 0; i < addressBook->contactCount; i++)
        {
        if (strcmp(addressBook->contacts[i].email, searched) == 0)
        {
            selectedIndex = i; // Save the index of the found contact
            printf("Contact found - ");
            printf("%-15s\t%-15s\t%-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            
            int editChoice;
            printf("Which field do you want to edit?\n");
            printf("1.Name\n2.Phone\n3.Email\n");
            printf("Enter the number: ");
            scanf(" %d", &editChoice);

            switch (editChoice)
            {
                case 1:
                {
                    printf("Enter new name: ");
                    char newName[50];
                    getchar(); // to consume the newline character
                    scanf("%49[^\n]", newName);
                    int validName = 1;
                    
                    for (int j = 0; newName[j] != '\0'; j++)// Validate new name
                    { // To check if input name contains only aphabets and spaces
                        if (!((newName[j] >= 'A' && newName[j] <= 'Z') || (newName[j] >= 'a' && newName[j] <= 'z') || newName[j] == ' '))
                        {
                            validName = 0;
                            break;
                        }
                    }

                    if (validName)
                    {
                        strcpy(addressBook->contacts[selectedIndex].name, newName);// update if name is valid
                        printf("Name updated successfully!\n");
                    }
                    else
                    {
                        printf("Invalid name! Name must contain only letters and spaces.\n");
                    }
                    break;
                }

                case 2:
                {
                    printf("Enter new phone number: ");
                    char newPhone[20];
                    int isValidPhone = 1;
                    getchar(); //consumes new line character  left by input
                    scanf("%19[^\n]", newPhone);
                    
                    int length = 0;
                    for (int j = 0; newPhone[j] != '\0'; j++)// Validate phone number
                    {
                        if (newPhone[j] < '0' || newPhone[j] > '9')// checks if input contains only digits
                        {
                            isValidPhone = 0;
                            break;
                        }
                        length++;
                    }

                    if (length != 10)// checks if input length is 10 digits
                    {
                        isValidPhone = 0;
                    }
                    
                    for (int j = 0; j < addressBook->contactCount; j++)// Check if phone already exists
                    {
                        if (strcmp(addressBook->contacts[j].phone, newPhone) == 0)
                        {
                            printf("Phone number already exists for contact: %s\n", addressBook->contacts[j].name);
                            isValidPhone = 0;
                            break;
                        }
                    }

                    if (isValidPhone) // new number is updated
                    {
                        strcpy(addressBook->contacts[selectedIndex].phone, newPhone);
                        printf("Phone number updated successfully!\n");
                    }
                    else
                    {
                        printf("Invalid phone number! Must be exactly 10 digits and should not already exist.\n");
                    }
                    break;
                }

                case 3:
                {
                    printf("Enter new email: ");
                    char newEmail[50];
                    int isValidEmail = 1;
                    int atFound = 0, dotFound = 0;
                    getchar();
                    scanf("%49[^\n]", newEmail);
                    
                    for (int j = 0; newEmail[j] != '\0'; j++) // Validate email
                    { // checks if email contains only alphabets,numbers ,@ and .
                        if (!((newEmail[j] >= 'a' && newEmail[j] <= 'z') || (newEmail[j] >= '0' && newEmail[j] <= '9') || newEmail[j] == '@' || newEmail[j] == '.'))
                        {
                            printf("Invalid email. Only lowercase letters, digits, '@', and '.' are allowed.\n");
                            isValidEmail = 0;
                            break;
                        }

                        if (newEmail[j] == ' ') //  checks for spaces
                        {
                            printf("Invalid email. No spaces are allowed.\n");
                            isValidEmail = 0;
                            break;
                        }

                        if (newEmail[j] == '@') //checks for  '@' 
                        {
                            if (atFound)
                            {
                                printf("Invalid email. Only one '@' is allowed.\n");
                                isValidEmail = 0;
                                break;
                            }
                            atFound = 1;
                        }

                        if (newEmail[j] == '.' && atFound)
                        {
                            dotFound = 1;
                        }

                        if (newEmail[j] == '.' && !atFound) // checks if '.' appears before '@'
                        {
                            printf("Invalid email. '.' cannot appear before '@'.\n");
                            isValidEmail = 0;
                            break;
                        }
                    }

                    if (isValidEmail && (!atFound || !dotFound)) // checks for both '@' and '.' is present in new email
                    {
                        printf("Invalid email. It must contain both '@' and '.'.\n");
                        isValidEmail = 0;
                    }

                    if (isValidEmail)
                    {
                        strcpy(addressBook->contacts[selectedIndex].email, newEmail); // valid email is updated
                        printf("Email updated successfully!\n");
                    }
                    else
                    {
                        printf("Email not updated due to invalid input.\n");
                    }
                    break;
                }

                default:
                {
                    printf("Invalid input! No changes made.\n");
                    break;
                }
            }

            flag = 0;
            break;
        }
    }

    if (flag == 1)
    {
        printf("Contact not found.\n");
    }
    break;
    }
    } 
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tENTERED INTO DELETE CONTACT\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    char searched[50];
    int i,sch,flag=1;
    char choice;
    printf("Search by\n1.Name\n2.Ph no:\n3.email\nEnter your choice : ");
    scanf("%d",&sch);
    getchar();//  to consume newline character left by previous input
   switch(sch)
    { 
        case 1:
        {
        printf("Enter the name (or partial name): ");
        // to consume the newline character left by previous input
        scanf("%49[^\n]", searched);

        int matchingIndexes[100], matchCount = 0;
         
         for (i = 0; i < addressBook->contactCount; i++)// Search for contacts that match the entered name
         {
           if (strncmp(addressBook->contacts[i].name, searched, strlen(searched)) == 0)
           {
            matchingIndexes[matchCount++] = i;
            // Display the matching contact with an index
            printf("%d. %-15s\t%-15s\t%-30s\n", matchCount, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
           }
         }
        
        if (matchCount == 0)// If no matching contact was found
        {
        printf("No contacts found with the name \"%s\".\n", searched);
        }
        else
        {
        int deleteIndex;               
        printf("Enter the number of the contact you want to delete : ");// Ask the user which contact they want to delete
        scanf("%d", &deleteIndex);
        
        if (deleteIndex >= 1 && deleteIndex <= matchCount) // Validate the user's selection
        {
            int selectedIndex = matchingIndexes[deleteIndex - 1];  // Get the actual index in the  array

            // Confirm deletion
            printf("Are you sure you want to delete this contact? (y/n): ");
            getchar();
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y')
            {
                // Shift contacts to remove the selected contact
                for (int j = selectedIndex; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }

                addressBook->contactCount--; // Decrease the contact count
                printf("Contact deleted successfully.\n");
            }
            else
            {
                printf("Deletion canceled.\n");
            }
        }
        else
        {
            printf("Invalid selection. No contact deleted.\n");
        }
        }
        break;
        }

        case 2:
        {
         printf("Enter the Phone no: ");
         scanf("%49[^\n]",searched);
         for(i=0;i<addressBook->contactCount;i++)
        {
           if(strcmp(addressBook->contacts[i].phone,searched)==0 )// search for matching contacts
           {
           printf("Contact found - ");
           printf("%-15s\t%-15s\t%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
           printf("Do you want to delete this contact ?(y/n): ");
           scanf(" %c", &choice);
           if (choice == 'y' || choice == 'Y')  // confirm deletion
           {
              for (int j = i; j < addressBook->contactCount - 1; j++) // Shift contacts to remove the selected contact
              {
              addressBook->contacts[j] = addressBook->contacts[j + 1];
              }
              addressBook->contactCount--;  // Decrease the contact count
            printf("Contact deleted.\n");
            }
             else 
            {
             printf("Deletion of contact is cancelled.\n");
            }
           flag=0;
           break;
           }
        }
           if(flag==1)
          { 
          printf("Contact not found.\n");
          }
          break;
        }

        case 3:
        {
         printf("Enter the email : ");
         scanf("%49[^\n]",searched);
         for(i=0;i<addressBook->contactCount;i++)
        {
           if(strcmp(addressBook->contacts[i].email,searched)==0 ) // searches for matching contact
           {
           printf("Contact found - ");
           printf("%-15s\t%-15s\t%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
           printf("Do you want to delete this contact ?(y/n): ");
           scanf(" %c", &choice);
           if (choice == 'y' || choice == 'Y') // confirms deletion
           {
              for (int j = i; j < addressBook->contactCount - 1; j++) // Shift contacts to remove the selected contact
              {
              addressBook->contacts[j] = addressBook->contacts[j + 1];
              }
              addressBook->contactCount--;  // Decrease the contact count
            printf("Contact deleted.\n");
            } else 
            {
             printf("Deletion cancelled.\n");
            }
           flag=0;
           break;
           }
        }
           if(flag==1)
          { 
          printf("Contact not found.\n");
          }
          break;
        }
        default :
        {
            printf("Invalid Input\n");
        }
    }
}

