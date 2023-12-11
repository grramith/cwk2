#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

// Function to check if a file is valid
int isValidFile(FILE *file) {
    return file != NULL;
}

// Function to read data from a file into an array
int readData(FILE *file, FitnessData *data, int *record_count) {
    *record_count = 0;

    while (fscanf(file, "%10[^,],%5[^,],%d\n", data[*record_count].date, data[*record_count].time, &data[*record_count].steps) == 3) {
        (*record_count)++;
    }

    // Check if any errors occurred during reading
    if (ferror(file)) {
        fprintf(stderr, "Error reading data from the file.\n");
        clearerr(file);  // Clear the error flag
        return 0;        // Return 0 to indicate an error
    }

    return 1;
}

// Function to swap two FitnessData records
void swap(FitnessData *a, FitnessData *b) {
    FitnessData temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform bubble sort on the FitnessData array in descending order of steps
void bubbleSort(FitnessData *data, int record_count) {
    for (int i = 0; i < record_count - 1; i++) {
        for (int j = 0; j < record_count - i - 1; j++) {
            if (data[j].steps < data[j + 1].steps) {
                swap(&data[j], &data[j + 1]);
            }
        }
    }
}

// Function to write sorted data to a file with a .tsv extension
int writeSortedData(const char *filename, FitnessData *data, int record_count) {
    char outputFilename[255];
    snprintf(outputFilename, sizeof(outputFilename), "%s.tsv", filename);

    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Error opening output file %s\n", outputFilename);
        return 0;
    }

    for (int i = 0; i < record_count; i++) {
        fprintf(outputFile, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose(outputFile);
    return 1;
}

int main() {
    char filename[255];

    // Ask the user for a filename
    printf("Enter filename: ");
    scanf("%s", filename);

    // Open the file for reading
    FILE *inputFile = fopen(filename, "r");

    // Check if the file is valid
    if (!isValidFile(inputFile)) {
        printf("Error: invalid file\n");
        return 1;
    }

    FitnessData data[1000];
    int record_count;

// Read data from the file
if (!readData(inputFile, data, &record_count)) {
    printf("Error reading data from the file.\n");
    fclose(inputFile);
    return 1;
}

    fclose(inputFile);

    // Sort the data in descending order of steps
    bubbleSort(data, record_count);

    // Write the sorted data to a new file with a .tsv extension
    if (!writeSortedData(filename, data, record_count)) {
        printf("Error writing sorted data to the file.\n");
        return 1;
    }

    printf("Data sorted and written to %s.tsv\n", filename);

    return 0;
}

