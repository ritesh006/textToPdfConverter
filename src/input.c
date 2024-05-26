#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include the unistd.h header for access() and F_OK
#include "header.h"

char filePath[120];

void inputFunc()
{
    FILE *inputFile;

    printf("Enter Your File Path: ");
    scanf("%119s", filePath); // Limit input to 119 characters

    printf("%s\n", filePath);

    // Check if the file exists and if the user has the necessary permissions
    if (access(filePath, F_OK) != -1) 
    {
        // File exists, now try to open it
        inputFile = fopen(filePath, "r");
        if (inputFile == NULL) 
        {
            printf("Error: Could not open file. Permission denied.\n");
        } 
        else 
        {
            printf("File Opened Successfully\n");
            fclose(inputFile); // Close the file only if it was successfully opened
        }
    } 
    else 
    {
        printf("Error: File does not exist or cannot be opened.\n");
    }
}
