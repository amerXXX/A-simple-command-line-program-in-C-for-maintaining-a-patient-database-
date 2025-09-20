#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 10
#define MAX_NAME_LENGTH 50
#define DATA_FILE "patientData.txt"

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float age;
} Patient;

// Function to read patients from file
int readPatientRecords(Patient patients[], int *count) {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        // File does not exist yet, treat as empty
        *count = 0;
        return 0;
    }

    int id;
    char name[MAX_NAME_LENGTH];
    float age;
    int index = 0;

    while (fscanf(file, "%d %s %f", &id, name, &age) != EOF) {
        if (index >= MAX_PATIENTS) {
            fprintf(stderr, "Error: Maximum patient capacity reached!\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        // Check if all values are read correctly
        if (feof(file) || ferror(file)) {
            fprintf(stderr, "Error: The patientData.txt file is corrupted!\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        patients[index].id = id;
        strncpy(patients[index].name, name, MAX_NAME_LENGTH);
        patients[index].age = age;
        index++;
    }

    fclose(file);
    *count = index;
    return 0;
}

// Function to display all patients
void displayPatientRecords(Patient patients[], int count) {
    printf("\nPatient Records:\n");
    printf("-------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Age: %.2f\n", patients[i].id, patients[i].name, patients[i].age);
    }
}

// Function to check if a string is a positive integer
int isPositiveInteger(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    Patient patients[MAX_PATIENTS];
    int patientCount = 0;

    // Validate command-line arguments
    if (argc != 4) {
        fprintf(stderr, "Error: Expected 3 arguments (ID Name Age).\n");
        return EXIT_FAILURE;
    }

    // Convert and validate patient ID
    if (!isPositiveInteger(argv[1])) {
        fprintf(stderr, "Error: Patient ID must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    int newId = atoi(argv[1]);
    if (newId <= 0) {
        fprintf(stderr, "Error: Invalid Patient ID.\n");
        return EXIT_FAILURE;
    }

    // Copy name
    char newName[MAX_NAME_LENGTH];
    strncpy(newName, argv[2], MAX_NAME_LENGTH);

    // Convert and validate Age
    float newAge = atof(argv[3]);
    if (newAge < 0.0 || newAge > 30.0) {
        fprintf(stderr, "Error: Age must be between 0.0 and 30.0.\n");
        return EXIT_FAILURE;
    }

    // Read existing patients
    readPatientRecords(patients, &patientCount);

    // Check for duplicate ID
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == newId) {
            fprintf(stderr, "Error: Patient ID already exists!\n");
            return EXIT_FAILURE;
        }
    }

    // Check capacity
    if (patientCount >= MAX_PATIENTS) {
        fprintf(stderr, "Error: Maximum patient capacity reached!\n");
        return EXIT_FAILURE;
    }

    // Add new patient
    patients[patientCount].id = newId;
    strncpy(patients[patientCount].name, newName, MAX_NAME_LENGTH);
    patients[patientCount].age = newAge;
    patientCount++;

    // Display all patients
    displayPatientRecords(patients, patientCount);

    // Bonus: Append new patient to file
    FILE *file = fopen(DATA_FILE, "a");
    if (!file) {
        fprintf(stderr, "Error: Failed to open file for writing.\n");
        return EXIT_FAILURE;
    }
    fprintf(file, "%d %s %.2f\n", newId, newName, newAge);
    fclose(file);

    return EXIT_SUCCESS;
}
