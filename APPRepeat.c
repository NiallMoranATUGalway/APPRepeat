#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>

//passenger struct 
typedef struct Passenger {
    int pps;                        // unique identifier
    char firstName[40];
    char lastName[40];
    int yearBorn;
    char emailAddress[75];
    char travelledFrom[40];
    char travelClass[40];
    char railTripsPerYear[20];
    struct Passenger* next;
} Passenger;


void AddPassenger(Passenger** head);
bool PasswordEntry();



int main() {
    Passenger* head = NULL;  // start of linked list


    int option;

    printf("--- Rail Ireland Passenger Database ---\n");

    if (PasswordEntry() == true)
    {
        printf("\n---Main Menu---");
        printf("\n1. Add passenger\n");
        printf("Enter number : ");
        (void)scanf("%d", &option);

        switch (option)
        {
        case 1:
            AddPassenger(&head);
            break;
        default:
            break;
        }

    }
	return 0;
}


//reads file from login.txt and compares that to the user input
bool PasswordEntry()
{
    FILE* fptr;
    int openStatus; //local variable that determines if file is open
    char filePassword[25];
    char userInputtedPassword[25];

    //opening password file
    fptr = fopen("login.txt", "r");

    if (fptr == NULL)
    {
        printf("Password File could not be opened\n");
        openStatus = 0;
    }
    else {
        openStatus = 1;
    }

    if (openStatus == 1)
    {
        //reading in variable using fscanf
        fscanf(fptr, "%s", &filePassword);

        printf("Please enter password : ");
        scanf("%s", userInputtedPassword);

        //if the user inputted password and file password are the same, then grant access
        if (strcmp(userInputtedPassword, filePassword) == 0)
        {
            printf("Admin logged in \n");
            return true;
        }
        else
        {
        printf("Invalid Password\n");
        }

    //closing password file
    fclose(fptr);

    return false;
    }
}

void AddPassenger(Passenger** head) {

    //local declarations
    int option;


    Passenger* newP = (Passenger*)malloc(sizeof(Passenger));
    if (!newP) {
        printf("Memory allocation failed\n");
        return;
    }

    //allocate memory for new passenger
    printf("\n---Add Passenger---\n");
    printf("Enter PPS number (integer) :  ");
    (void)scanf("%d", &newP->pps);

    printf("Please enter first name : ");
    (void)scanf("%s", newP->firstName);

    printf("Please enter last name : ");
    (void)scanf("%s", newP->lastName);

    printf("Please enter year born : ");
    (void)scanf("%d", &newP->yearBorn);

    printf("Please enter email address : ");
    (void)scanf("%s", newP->emailAddress);

    //area selection
    printf("Which of the following areas did you travel from?");
    printf("\n1. Dublin");
    printf("\n2. Leinster");
    printf("\n3. Connacht");
    printf("\n4. Ulster");
    printf("\n5. Munster\n");
    printf("Enter number : ");
    (void)scanf("%d", &option);

    switch (option) {
        case 1: 
            strcpy(newP->travelledFrom, "Dublin");
            break;
        case 2: 
            strcpy(newP->travelledFrom, "Leinster"); 
            break;
        case 3: 
            strcpy(newP->travelledFrom, "Connacht"); 
            break;
        case 4: 
            strcpy(newP->travelledFrom, "Ulster"); 
            break;
        case 5: 
            strcpy(newP->travelledFrom, "Munster"); 
            break;
        default: 
            strcpy(newP->travelledFrom, "Invalid"); 
            break;
    }

    // travel class
    printf("What travel class did you use to travel by?");
    printf("\n1. Economy");
    printf("\n2. First Class\n");
    printf("Enter number : ");
    (void)scanf("%d", &option);

    if (option == 1) {
        strcpy(newP->travelClass, "Economy");
    }
    else if (option == 2)
    {
        strcpy(newP->travelClass, "First Class");
    }
    else {
        strcpy(newP->travelClass, "Invalid");
    }

    // trips per year
    printf("How many rail trips in Ireland do you make per year?");
    printf("\n1. Less than three ");
    printf("\n2. Less than five ");
    printf("\n3. More than five\n");
    printf("Enter number : ");
    (void)scanf("%d", &option);

    if (option == 1) {
        strcpy(newP->railTripsPerYear, "<3");
    }
    else if (option == 2) {
        strcpy(newP->railTripsPerYear, "<5");
    }
    else if (option == 3) {
        strcpy(newP->railTripsPerYear, "5+");
    }
    else {
        strcpy(newP->railTripsPerYear, "Invalid");
    }

    // Insert at head of linked list
    newP->next = *head;
    *head = newP;

    printf("\nPassenger added successfully\n");
}