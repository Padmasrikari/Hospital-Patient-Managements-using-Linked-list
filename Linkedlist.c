#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure of a patient node
typedef struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    int wardNo;
    struct Patient *next;
} Patient;

Patient *head = NULL;

// Function to create a patient node
Patient* createPatient(int id, char name[], int age, char gender[], char disease[], int wardNo) {
    Patient newNode = (Patient)malloc(sizeof(Patient));

    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->age = age;
    strcpy(newNode->gender, gender);
    strcpy(newNode->disease, disease);
    newNode->wardNo = wardNo;
    newNode->next = NULL;

    return newNode;
}

// 1. Admit new patient (Insert at end)
void admitPatient() {
    int id, age, wardNo;
    char name[50], gender[10], disease[50];

    printf("\nEnter Patient ID: ");
    scanf("%d", &id);
    getchar();

    printf("Enter Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &age);
    getchar();

    printf("Enter Gender: ");
    fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = '\0';

    printf("Enter Disease: ");
    fgets(disease, sizeof(disease), stdin);
    disease[strcspn(disease, "\n")] = '\0';

    printf("Enter Ward Number: ");
    scanf("%d", &wardNo);

    Patient *newNode = createPatient(id, name, age, gender, disease, wardNo);

    if (head == NULL) {
        head = newNode;
    } else {
        Patient *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("\nPatient admitted successfully!\n");
}

// 2. Display all patients
void displayPatients() {
    if (head == NULL) {
        printf("\nNo patients currently admitted.\n");
        return;
    }

    Patient *temp = head;
    printf("\n--- Current Patient List ---\n");
    while (temp != NULL) {
        printf("\nID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Age: %d\n", temp->age);
        printf("Gender: %s\n", temp->gender);
        printf("Disease: %s\n", temp->disease);
        printf("Ward No: %d\n", temp->wardNo);
        temp = temp->next;
    }
}

// 3. Search patient by ID
Patient* searchPatientById(int id) {
    Patient *temp = head;

    while (temp != NULL) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void searchPatient() {
    int id;
    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    Patient *p = searchPatientById(id);
    if (p == NULL) {
        printf("\nPatient not found.\n");
    } else {
        printf("\n--- Patient Found ---\n");
        printf("ID: %d\n", p->id);
        printf("Name: %s\n", p->name);
        printf("Age: %d\n", p->age);
        printf("Gender: %s\n", p->gender);
        printf("Disease: %s\n", p->disease);
        printf("Ward No: %d\n", p->wardNo);
    }
}

// 4. Update patient details
void updatePatient() {
    int id;
    printf("\nEnter Patient ID to update: ");
    scanf("%d", &id);
    getchar();

    Patient *p = searchPatientById(id);
    if (p == NULL) {
        printf("\nPatient not found.\n");
        return;
    }

    printf("\n--- Update Details for %s ---\n", p->name);

    printf("Enter new disease: ");
    fgets(p->disease, sizeof(p->disease), stdin);
    p->disease[strcspn(p->disease, "\n")] = '\0';

    printf("Enter new ward number: ");
    scanf("%d", &p->wardNo);

    printf("\nPatient details updated successfully.\n");
}

// 5. Discharge (Delete) patient
void dischargePatient() {
    int id;
    printf("\nEnter Patient ID to discharge: ");
    scanf("%d", &id);

    if (head == NULL) {
        printf("\nNo patients to delete.\n");
        return;
    }

    Patient *temp = head, *prev = NULL;

    // If head node to delete
    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        printf("\nPatient discharged successfully.\n");
        return;
    }

    // Find the patient to delete
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nPatient not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);

    printf("\nPatient discharged successfully.\n");
}

// 6. Count number of patients
void countPatients() {
    int count = 0;
    Patient *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("\nTotal number of patients: %d\n", count);
}

// Main menu
int main() {
    int choice;

    do {
        printf("\n===== HOSPITAL PATIENT MANAGEMENT SYSTEM =====\n");
        printf("1. Admit New Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Update Patient Details\n");
        printf("5. Discharge Patient\n");
        printf("6. Count Patients\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: admitPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: dischargePatient(); break;
            case 6: countPatients(); break;
            case 7: printf("\nExiting program...\n"); break;
            default: printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}