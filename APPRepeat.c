#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>

void AddPassenger();
bool PasswordEntry();


int main() {
    int option;
    //bool passwordCorrect;

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
            AddPassenger();
            break;
        default:
            break;
        }

    }
	return 0;
}
//declarations
void AddPassenger() {

    printf("\n---Add Passenger---\n");
    char name[40];
    char lastName[40];
    int yearBorn;
    char emailAddress[75];
    int option;
    char travelledFrom[40];
    char travelClass[40];
    char railTripsPerYear[150];

    //asking user for passenger details
    printf("Please enter first name : ");
    (void)scanf("%s", name);
    
    printf("Please enter last name : ");
    (void)scanf("%s", lastName);

    printf("Please enter year born : ");
    (void)scanf("%d", &yearBorn);

    printf("Please enter email address : ");
    (void)scanf("%s", emailAddress);
    

    printf("Which of the following areas did you travel from?");
    printf("\n1. Dublin");
    printf("\n2. Leinster");
    printf("\n3. Cannacht");
    printf("\n4. Ulster");
    printf("\n5. Munster\n");
    printf("Enter number : ");
    (void)scanf("%d", &option);

    switch (option)
    {
    case 1: 
        strcpy(travelledFrom, "Dublin");
        break;
    case 2:
        strcpy(travelledFrom, "Leinster");
        break;
    case 3:
        strcpy(travelledFrom, "Cannacht");
        break;
    case 4:
        strcpy(travelledFrom, "Ulster");
        break;
    case 5:
        strcpy(travelledFrom, "Munster");
        break;
    default:
        strcpy(travelledFrom, "Invalid");
        break;
    }
    

    printf("What travel class did you use to travel by?");
    printf("\n1. Economy");
    printf("\n2. First Class\n");
    printf("Enter number : ");
    (void)scanf("%d", &option);

    switch (option)
    {
    case 1:
        strcpy(travelClass, "Economy");
        break;
    case 2:
        strcpy(travelClass, "First Class");
        break;
    default:
        strcpy(travelClass, "Invalid");
        break;
    }



    printf("How many rail trips in Ireland do you make per year?");
    printf("\n1. Less than three ");
    printf("\n2. Less than five ");
    printf("\n3. More than five\n");
    printf("Enter number : ");
    (void)scanf("%d", &option);

    switch (option)
    {
    case 1:
        strcpy(railTripsPerYear, "<3");
        break;
    case 2:
        strcpy(railTripsPerYear, "<5");
        break;
    case 3:
        strcpy(railTripsPerYear, "5+");
        break;
    default:
        strcpy(railTripsPerYear, "Invalid");
        break;
    }

    printf("\n%s %s %d %s ", name, lastName, yearBorn, emailAddress);
    printf("%s %s %s", travelledFrom, travelClass, railTripsPerYear);
}

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