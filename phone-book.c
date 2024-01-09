#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int displayMenu();
void loadingAnimation();
void transition();
int addContact();
char* takeName();
struct Contact searchContact(char*);
int printContact();
int deleteContact();
int displayContacts();
int updateContact();


struct Contact {
    char name[50];
    char phone [15];
    char address[100];
    char group[100];
};

int displayMenu() {
    int option;
    system("cls");
    system("color 02");
    printf("\n\n\t\t\xB2\xB2\xB2 PHONE BOOK \xB2\xB2\xB2\n");
    printf("\n\n\t\t1. Add contacts");
    printf("\n\n\t\t2. Delete contacts");
    printf("\n\n\t\t3. Search contact");
    printf("\n\n\t\t4. Display all contacts");
    printf("\n\n\t\t5. Update contact");
    printf("\n\n\t\t6. Exit the phone book\n\n");
    scanf("%i", &option);
    do{
        switch (option)
        {
        case 1:
            transition();
            addContact();
            break;
        case 2:
            transition();
            deleteContact();
        case 3:
            transition();
            printContact();
        case 4:
            transition();
            displayContacts();
        case 5:
            transition();
            updateContact();
        case 6:
            transition();
            exit(0);
        default:
            printf("\n\n\tInvalid input. Enter a numeric response from 1-6");
            break;
        }
    } while(option < 1 || option > 6);
    return 0;
}
void loadingAnimation() {
    printf("\n\n\t\tLoading");
    fflush(stdout); // the string in printf is first stored in the buffer
    // this prevents it from being stored and render immediately

    for (int i = 0; i < 4; ++i) {
        usleep(500000); // 0.5-second delay
        printf(".");
        fflush(stdout); 
    }

    printf("\n\n");
}
void transition() {
    system("cls");
    printf("\n\n\t\tTransitioning to the next screen...");
    loadingAnimation();
    system("cls");
}

int addContact() {
    struct Contact contact1;

    printf("\n\n\t\tName:\t");
    scanf("%s", contact1.name);

    printf("\n\n\t\tPhone:\t");
    scanf("%s", contact1.phone);

    printf("\n\n\t\tAddress:\t");
    scanf("%s", contact1.address);

    printf("\n\n\t\tGroup:\t");
    scanf("%s", contact1.group);

    FILE* file = fopen("contacts.csv", "a+");
    if (file == NULL) {
        perror("\n\n\t\tError opening file");
        return 1;
    }

    char contact[256];
    // sprintf is used to concatenate strings.
    sprintf(contact, "%s,%s,%s,%s\n", contact1.name, contact1.phone, contact1.address, contact1.group);
    fputs(contact, file);
    fclose(file);
    return 0;
}

char* takeName() {
    char name[50];
    printf("\n\n\t\tEnter the name of the contact to delete:\t");
    scanf("%49s", name);
}

struct Contact searchContact(char* name) {
    

    struct Contact contact1;
    FILE* file = fopen("contacts.csv", "r");

    if(file == NULL) {
        perror("\n\n\t\tError opening file.");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while(fgets(line,1024, file) != NULL) {
        char* token = strtok(line, ",");

        if(strcmp(token, name) == 0) {
            strcpy(contact1.name, token);
            strcpy(contact1.phone, strtok(NULL, ","));
            strcpy(contact1.address, strtok(NULL, ","));
            strcpy(contact1.group, strtok(NULL, ","));
            break;
        }   
    }
    return contact1;
}

int printContact() {
    char* name = takeName();
    struct Contact contact1 = searchContact(name);
    printf("\n\n\t\tNAME : %s\n", contact1.name);
    printf("\t\tPHONE: %s\n", contact1.phone);
    printf("\t\tCITY : %s\n", contact1.address);
    printf("\t\tGROUP: %s\n\n", contact1.group);
}

int deleteContact() {
    char* name = takeName();

    char* file_path = "contacts.csv";
    FILE* file = fopen(file_path, "r");
    FILE* temp = fopen("temp.csv", "w");

    if (file == NULL || temp == NULL) {
        fprintf(stderr, "\n\n\t\tError opening files.");
        exit(EXIT_FAILURE);

    }
    char line[1024];
    while (fgets(line, 1024, file) != NULL) {
        char* token = strtok(line, ",");
        if(token != NULL && strcmp(token, name) !=0) {
            fputs(line, temp);
        }
    }
    fclose(file);
    fclose(temp);

    if (remove(file_path) != 0 || rename("temp.csv", file_path) != 0) {
        fprintf(stderr, "\n\n\tError updating the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("\n\n\tContact deleted successfully.\n");
    
    return 0;
    
}
int displayContacts() {
    FILE* file = fopen("contacts.csv", "r");

    if(file == NULL) {
        fprintf(stderr, "\n\n\t\tError opening file.");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    printf("NAME\t\t\tNUMBER\t\t\tCITY\t\t\tGROUP\n\n");

    while(fgets(line, 1024, file) != NULL) {
        int index = 0;
        char* token = strtok(line, ",");

        while(token!=NULL) {
            printf("%s\t\t\t", token);
            token = strtok(NULL, ",");
            index++;
            if(index % 4 == 0) {
                printf("\n\n");
            }
        }
    }
    fclose(file);
    return 0;
}
int updateContact() {
    char* name = takeName();

    int option;

    struct Contact contact1 = searchContact(name);
    printf("\n\n\tWhat do you want to change?");
    printf("\n\n\t\t1. Name");
    printf("\n\n\t\t2. Number");
    printf("\n\n\t\t3. Address");
    printf("\n\n\t\t4. Group");
    printf("\n\n\tI want to change:\t");
    if(scanf("%i", &option) != 1) {
        printf("Invalid input");
    }

    switch (option)
    {
    char new[50];
    case 1:
        printf("\n\n\tEnter new Name:\t");

        if(scanf("%s", new) != 1) {
            printf("\n\n\t\tInvalid input");
        }
        deleteContact(contact1.name);
        if(addContact(new, contact1.phone, contact1.address, contact1.group) == 0) {
            printf("\n\n\t\tContacts successfully updated.");
        }
        break;
    case 2:
        printf("\n\n\tEnter new number:\t");
        if(scanf("%s", new) != 1) {
            printf("\n\n\t\tInvalid input");
        }
        deleteContact(contact1.name);
        if( addContact(contact1.name, new, contact1.address, contact1.group) == 0) {
            printf("\n\n\t\tContacts successfully updated.");
        };
        break;
    case 3:
        printf("\n\n\tEnter new address:\t");
        if(scanf("%s", new) != 1) {
            printf("\n\n\t\tInvalid input");
        }
        deleteContact(contact1.name);
        if(addContact(contact1.name, contact1.phone, new, contact1.group) == 0) {
            printf("\n\n\t\tContacts successfully updated.");
        }
        break;
    case 4:
        printf("\n\n\tEnter new group:\t");
        if(scanf("%s", new) != 1) {
            printf("\n\n\t\tInvalid input");
        }

        deleteContact(contact1.name);
        if(addContact(contact1.name, contact1.phone,contact1.address , new) == 0) {
            printf("\n\n\t\tContacts successfully updated.");
        }
        break;
    default:
        break;
    }
}

int main() {
    //displayMenu();
    //addContact("ishola", "0201733020", "kumasi", "friends");
    //deleteContact("ishola");
    //displayContacts();
    //printContact("ishola");
    displayMenu();
    return 0;
    // loop to ensure that the user can run multiple operations without restarting the program

}