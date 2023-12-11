#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Outputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);
}

int importData(const char *filename, FITNESS_DATA *data, int *record_count) {
    FILE *FitnessDataPointer;
    FitnessDataPointer = fopen(filename, "r");

    if (FitnessDataPointer == NULL) {

        printf("Error: Could not find or open the file.\n");
        return 1;  // Return 1 to indicate an error
    }
    printf("File successfully loaded.\n");
    *record_count = 0;

    // Read and parse the CSV data
    while (fscanf(FitnessDataPointer, "%10[^,],%5[^,],%d\n", 
                  data[*record_count].date, 
                  data[*record_count].time, 
                  &data[*record_count].steps) == 3) {
        // Increment the record counter
        (*record_count)++;
    }

    // Closing the file
    fclose(FitnessDataPointer);

    // Return 0 to indicate success
    return 0;
}

int getTotalRecords(const FITNESS_DATA *data, int record_count) {
    // Function to get the total number of records
    return record_count;
}

void displayMinStepsTimeSlot(const FITNESS_DATA *data, int record_count) {
    // Function to display the time slot with the fewest steps
    if (record_count == 0) {
        printf("No records available.\n");
        return;
    }

    int min_steps = data[0].steps;
    int min_index = 0;

    for (int i = 1; i < record_count; i++) {
        if (data[i].steps < min_steps) {
            min_steps = data[i].steps;
            min_index = i;
        }
    }

    printf("Fewest steps: %s %s\n", 
           data[min_index].date, data[min_index].time);
}

void displayMaxStepsTimeSlot(const FITNESS_DATA *data, int record_count) {
    // Function to display the time slot with the most steps
    if (record_count == 0) {
        printf("No records available.\n");
        return;
    }

    int max_steps = data[0].steps;
    int max_index = 0;

    for (int i = 1; i < record_count; i++) {
        if (data[i].steps > max_steps) {
            max_steps = data[i].steps;
            max_index = i;
        }
    }

    printf("Largest steps: %s %s\n", 
           data[max_index].date, data[max_index].time);
}

double calculateMeanSteps(const FITNESS_DATA *data, int record_count) {
    // Function to calculate the mean step count of all records
    if (record_count == 0) {
        return 0.0;
    }

    int total_steps = 0;
    for (int i = 0; i < record_count; i++) {
        total_steps += data[i].steps;
    }

    int mean_steps = (double)total_steps / record_count;
    int rounded_steps = (int)(mean_steps+0.5);
    printf("Mean step count: %d\n", rounded_steps);
    return 0;
    }

void findLongestAbove500Period(const FITNESS_DATA *data, int record_count) {
    // Function to find the longest continuous period where the step count is above 500
    if (record_count == 0) {
        printf("No records available.\n");
        return;
    }

    int currentStartIndex = 0;
    int currentLength = 0;

    int longestStartIndex = 0;
    int longestEndIndex = 0;  // New variable to store the end index
    int longestLength = 0;

    for (int i = 0; i < record_count; i++) {
        if (data[i].steps > 500) {
            // If the current sequence is continuous, increment the length
            currentLength++;

            // Updating the longest sequence if the present one is longer
            if (currentLength > longestLength) {
                longestLength = currentLength;
                longestStartIndex = currentStartIndex;
                longestEndIndex = i;  // Update the end index
            }
        } else {
            // If the present sequence is interrupted, reset the start index and length
            currentStartIndex = i + 1;
            currentLength = 0;
        }
    }

    if (longestLength == 0) {
        printf("No continuous period above 500 steps found.\n");
    } else {
        printf("Longest period start: %s %s\n",
               data[longestStartIndex].date, data[longestStartIndex].time);
        printf("Longest period end: %s %s\n",
               data[longestEndIndex].date, data[longestEndIndex].time);
    }
}

// Main function
int main() {
    // Declare variables
    FITNESS_DATA FitnessData[1000];
    int record_count = 0;
    char filename[100];

    // Main menu loop
    char choice;
    do {
        // Display menu options
        printf("\nMenu:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the data and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Exit\n");

        // Get user input
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        // Perform actions based on user choice
        switch (choice) {
                case 'A':
                printf("Enter the filename: ");
                scanf("%s", filename);
                if (importData(filename, FitnessData, &record_count) == 1) {
                    return 1;  // Exit the program due to an error
                }
                break;

            case 'B':
                printf("Total records: %d\n", getTotalRecords(FitnessData, record_count));
                break;

            case 'C':
                displayMinStepsTimeSlot(FitnessData, record_count);
                break;

            case 'D':
                displayMaxStepsTimeSlot(FitnessData, record_count);
                break;

            case 'E':
                calculateMeanSteps(FitnessData, record_count);
                break;

            case 'F':
                findLongestAbove500Period(FitnessData, record_count);
                break;

            case 'Q':
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 'Q');

    return 0;
}
