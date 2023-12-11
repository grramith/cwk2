#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
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

// Complete the main function
int main() {

    // Read in csv file FitnessData_2023.csv
    // Declaring a pointer for the csv file
    FILE *FitnessDataPointer; 

    //Opening the csv file for Read-Only
    char filename[] = "FitnessData_2023.csv";
    FitnessDataPointer = fopen(filename,"r");

    // Lets the customer know if the csv file is empty
    if (FitnessDataPointer == NULL) {
            printf("File is empty!");
        }

    // Store it in a suitably sized and structured array and typedef data structure
    // Creating a suitably sized array of the typedef data structure FITNESS_DATA
    FITNESS_DATA FitnessData[1000];

    // New variable acts as a record counter
    int record_count = 0;

    // Read and parse the CSV data
    while (fscanf(FitnessDataPointer, "%10[^,],%5[^,],%d\n", FitnessData[record_count].date, FitnessData[record_count].time, &FitnessData[record_count].steps) == 3) {
        // Increment the record counter
        record_count++;
    }
    // Close the file
    fclose(FitnessDataPointer);

    // Write the number of records in the file to the screen
    printf("Number of records in file: %d\n", record_count);

    // Print the first three rows of the csv file
    for (int row = 0; row < 3; row++) {
        printf("%s/%s/%d\n", FitnessData[row].date, FitnessData[row].time, FitnessData[row].steps);
    }

return 0;
}
