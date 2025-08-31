#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>

//passenger struct 
typedef struct Passenger {
    int pps;  
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
void DisplayAllPassengers(Passenger* head);
void DisplayPassengerInfo(Passenger* head);
void UpdatePassenger(Passenger* head);
int DeletePassenger(Passenger** head);
void GenerateStatistics(Passenger* head);
void WriteReport(Passenger* head, const char* filename);


int main() {
    Passenger* head = NULL;  // start of linked list

    //local declarations
    int option = 0;

    printf("--- Rail Ireland Passenger Database ---\n");

    if (PasswordEntry() == true)
    {
        while(option != 10)
        {
            printf("\n---Main Menu---");
            printf("\n1. Add passenger\n");
            printf("2. Display all passengers\n");
            printf("3. Display passenger info\n");
            printf("4. Update passenger statistic\n");
            printf("5. Delete passenger\n");
            printf("6. Generate Statistics\n");
            printf("7. Print all passenger details into a report file\n");
            printf("10. Exit\n");
            printf("Enter number : ");
            (void)scanf("%d", &option);

            switch (option)
            {
            case 1:
                AddPassenger(&head);
                break;
            case 2:
                DisplayAllPassengers(head);
                break;
            case 3:
                DisplayPassengerInfo(head);
                break;
            case 4:
                UpdatePassenger(head);
                break;
            case 5:
                DeletePassenger(&head);
                break;
            case 6:
                GenerateStatistics(head);
                break;
            case 7:
                WriteReport(head, "report.txt");
                break;
            case 10:
                break;
            default:
                break;
            }
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
            printf("Log-in successful \n");
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

void DisplayAllPassengers(Passenger* head) {
    if (head == NULL) {
        printf("\nNo passengers in the list.\n");
        return;
    }

    printf("\n---Passenger List---\n");
    Passenger* cur = head;
    while (cur != NULL) {
        printf("PPS: %d | %s %s\n", cur->pps, cur->firstName, cur->lastName);
        cur = cur->next; // move to next passenger
    }
}

void DisplayPassengerInfo(Passenger* head) {
    int userInputtedPassengerPPS;
    bool found = false;

    printf("\n---Display Passenger Info---\n");
    printf("Please enter PPS number of passenger : ");
    (void)scanf("%d", &userInputtedPassengerPPS);

    // Traverse the linked list
    Passenger* cur = head;
    while (cur != NULL) {
        if (cur->pps == userInputtedPassengerPPS) {
            // Match found, print details
            printf("\nPPS : %d\n", cur->pps);
            printf("Name : %s %s\n", cur->firstName, cur->lastName);
            printf("Year Born : %d\n", cur->yearBorn);
            printf("Email : %s\n", cur->emailAddress);
            printf("Travelled From : %s\n", cur->travelledFrom);
            printf("Travel Class : %s\n", cur->travelClass);
            printf("Trips Per Year : %s\n", cur->railTripsPerYear);
            found = true;
            break;
        }
        //move to next passenger in the list 
        cur = cur->next;
    }

    if (found == false) {
        printf("\nNo passenger found with PPS %d.\n", userInputtedPassengerPPS);
    }
}

void UpdatePassenger(Passenger* head) {

    //local declartions
    int searchPps;
    int choice;
    int option;

    printf("\n--- Update Passenger ---\n");
    printf("Enter PPS number of passenger to update: ");
    scanf("%d", &searchPps);

    Passenger* cur = head;
    while (cur != NULL) {
        // if cur->pps matches the passenger is found
        if (cur->pps == searchPps) {
            printf("\nPassenger found: %s %s (PPS %d)\n",
                cur->firstName, cur->lastName, cur->pps);

            printf("\nWhat would you like to update?\n");
            printf("1. Email\n");
            printf("2. Travelled From\n");
            printf("3. Travel Class\n");
            printf("4. Trips per Year\n");
            printf("5. Year Born\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            //nested switch statements for overwriting
            switch (choice) {
            case 1:
                printf("Enter new email: ");
                scanf("%s", cur->emailAddress);
                break;
            case 2: {
                printf("Areas: 1.Dublin 2.Leinster 3.Connacht 4.Ulster 5.Munster\n");
                scanf("%d", &option);
                switch (option) {
                case 1:
                    strcpy(cur->travelledFrom, "Dublin");
                    break;
                case 2:
                    strcpy(cur->travelledFrom, "Leinster");
                    break;
                case 3:
                    strcpy(cur->travelledFrom, "Connacht");
                    break;
                case 4:
                    strcpy(cur->travelledFrom, "Ulster");
                    break;
                case 5: strcpy(cur->travelledFrom, "Munster");
                    break;
                }
                break;
            }
            case 3: {
                int option;
                printf("1. Economy  2. First Class\n");
                scanf("%d", &option);
                if (option == 1) {
                    strcpy(cur->travelClass, "Economy");
                }
                else if (option == 2) {
                    strcpy(cur->travelClass, "First Class");
                }
                break;
            }
            case 4: {
                int option;
                printf("1. <3  2. <5  3. 5+\n");
                scanf("%d", &option);
                if (option == 1) {
                    strcpy(cur->railTripsPerYear, "<3");
                }
                else if (option == 2) {
                    strcpy(cur->railTripsPerYear, "<5");
                }
                else if (option == 3) {
                    strcpy(cur->railTripsPerYear, "5+");
                }
                break;
            }
            case 5:
                printf("Enter new year born: ");
                (void)scanf("%d", &cur->yearBorn);
                break;
            default:
                printf("Invalid choice.\n");
            }

            printf("Passenger update successful\n");
            return;
        }
        cur = cur->next; // keep searching
    }

    printf("No passenger found with PPS %d.\n", searchPps);
}

int DeletePassenger(Passenger** head)
{
    //local declarations 
    int pps;

    //if the linked list is empty
    if (head == NULL || *head == NULL) {
        printf("\nNo passengers in the list.\n");
        return -1;
    }

    printf("\n--- Delete Passenger ---\n");
    printf("Enter PPS number to delete: ");

    //input validation to make sure user entered a number
    if (scanf("%d", &pps) != 1) {
        printf("Invalid input.\n");
        return 0;
    }

    Passenger* cur = *head;
    Passenger* prev = NULL;

    // case 1: node to delete is the head
    if (cur != NULL && cur->pps == pps) {
        *head = cur->next;   // move head
        printf("Deleted: %s %s (PPS %d)\n", cur->firstName, cur->lastName, cur->pps);
        free(cur);
        return 1;
    }

    // case 2: search the rest of the list
    while (cur != NULL && cur->pps != pps) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) { // not found
        printf("No passenger found with PPS %d.\n", pps);
        return 0;
    }

    // unlink and free the found node
    prev->next = cur->next;
    printf("Deleted: %s %s (PPS %d)\n", cur->firstName, cur->lastName, cur->pps);
    free(cur);
    return 1;
}

void GenerateStatistics(Passenger* head) {
    //local variables
    //counters
    int total = 0;
    int dublin = 0;
    int leinster = 0;
    int connacht = 0;
    int ulster = 0;
    int munster = 0;

    int classChoice;

    if (head == NULL) {
        printf("\nNo passengers in the list.\n");
        return;
    }


    printf("\n---Generate Statistics---\n");
    printf("Choose travel class:\n");
    printf("1. Economy\n");
    printf("2. First Class\n");
    printf("Enter choice: ");
    (void)scanf("%d", &classChoice);

    //nested if statements in a while loop to count 
    //each chosen province by looping through the linked list

    Passenger* cur = head;
    while (cur != NULL) {

        //economy case
        //count only if user chooses economy and only those in economy
        if (classChoice == 1 && strcmp(cur->travelClass, "Economy") == 0) {
            total++;

            if (strcmp(cur->travelledFrom, "Dublin") == 0) {
                dublin++;
            }
            else if (strcmp(cur->travelledFrom, "Leinster") == 0) {
                leinster++;
            }
            else if (strcmp(cur->travelledFrom, "Connacht") == 0) {
                connacht++;
            }
            else if (strcmp(cur->travelledFrom, "Ulster") == 0) {
                ulster++;
            }
            else if (strcmp(cur->travelledFrom, "Munster") == 0) {
                munster++;
            }
        }

        //first class case
        else if (classChoice == 2 && strcmp(cur->travelClass, "First Class") == 0) {
            total++;

            if (strcmp(cur->travelledFrom, "Dublin") == 0) {
                dublin++;
            }
            else if (strcmp(cur->travelledFrom, "Leinster") == 0) {
                leinster++;
            }
            else if (strcmp(cur->travelledFrom, "Connacht") == 0) {
                connacht++;
            }
            else if (strcmp(cur->travelledFrom, "Ulster") == 0) {
                ulster++;
            }
            else if (strcmp(cur->travelledFrom, "Munster") == 0) {
                munster++;
            }
        }

        cur = cur->next; //move to next passenger
    }

    if (total == 0) {
        printf("\nNo passengers found for that class.\n");
        return;
    }

    printf("\n---Statistics for %s---\n",
        (classChoice == 1 ? "Economy" : "First Class"));

    //multiplying province by a hundred then dividing by the total
    //to get its percentage
    printf("Dublin   : %.2f%%\n", (dublin * 100.0) / total);
    printf("Leinster : %.2f%%\n", (leinster * 100.0) / total);
    printf("Connacht : %.2f%%\n", (connacht * 100.0) / total);
    printf("Ulster   : %.2f%%\n", (ulster * 100.0) / total);
    printf("Munster  : %.2f%%\n", (munster * 100.0) / total);
}

void WriteReport(Passenger* head, const char* filename) {
    //opening file in write mode
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Could not open %s for writing.\n", filename);
        return;
    }

    //pointer to the start of the file
    fprintf(f, "=== Rail Ireland Passenger Report ===\n\n");

    //if there are no elements in the linked list
    if (head == NULL) {
        fprintf(f, "No passengers in the list.\n");
        fclose(f);
        printf("Report written to %s (empty).\n", filename);
        return;
    }

    //contents to file
    Passenger* cur = head;
    while (cur != NULL) {
        fprintf(f, "PPS: %d\n", cur->pps);
        fprintf(f, "Name: %s %s\n", cur->firstName, cur->lastName);
        fprintf(f, "Year Born: %d\n", cur->yearBorn);
        fprintf(f, "Email: %s\n", cur->emailAddress);
        fprintf(f, "Travelled From: %s\n", cur->travelledFrom);
        fprintf(f, "Travel Class: %s\n", cur->travelClass);
        fprintf(f, "Trips Per Year: %s\n", cur->railTripsPerYear);
        fprintf(f, "-----------------------------\n");
        cur = cur->next;
    }

    //closing file
    fclose(f);
    printf("Report written to %s\n", filename);
}