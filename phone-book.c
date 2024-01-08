#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone [15];
    char address[100];
    char group[100];
};

int displayMenu() {
    system("cls");
    system("color 02");
    printf("\n\n\t\t\xB2\xB2\xB2 PHONE BOOK \xB2\xB2\xB2");
    printf("\n\n\n\t\t1. Add contacts");
    printf("\n\n\t\t2. Delete contacts");
    printf("\n\n\t\t3. Search contact");
    printf("\n\n\t\t4. Display all contacts");
    printf("\n\n\t\t5. Update contact");
    printf("\n\n\t\t6. Exit the phone book\n\n");
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

int addContact(char* name, char* phone, char* address, char* group) {
    FILE* file = fopen("contacts.csv", "a+");
    if (file == NULL) {
        perror("\n\n\t\tError opening file");
        return 1;
    }
    char contact[256];
    // sprintf is used to concatenate strings.
    sprintf(contact, "%s,%s,%s,%s\n", name, phone, address, group);
    fputs(contact, file);
    fclose(file);
    return 0;
}
int main() {
    displayMenu();
    return 0;
}