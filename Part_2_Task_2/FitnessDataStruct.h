
#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Helper function prototypes
// Tokenizes a record string and extracts date, time, and steps
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

// Imports data from a CSV file and populates the FITNESS_DATA array
int importData(const char *filename, FITNESS_DATA *data, int *record_count);

// Returns the total number of records in the FITNESS_DATA array
int getTotalRecords(const FITNESS_DATA *data, int record_count);

// Displays the date and time of the timeslot with the fewest steps
void displayMinStepsTimeSlot(const FITNESS_DATA *data, int record_count);

// Displays the date and time of the timeslot with the largest number of steps
void displayMaxStepsTimeSlot(const FITNESS_DATA *data, int record_count);

// Calculates and returns the mean step count of all records in the array
double calculateMeanSteps(const FITNESS_DATA *data, int record_count);

// Calculates and finds the longest continuous period above 500 steps
void findLongestAbove500Period(const FITNESS_DATA *data, int record_count);

#endif // FITNESS_DATA_STRUCT_H
