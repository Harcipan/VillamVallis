#include "gameManagement.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
int loadGame(int *kertSor,int *kertOszlop,int *penz, player* p1, char* save_file)
{
    //Load-Game

    // Declare a FILE pointer to handle the file
    FILE *file;

    // Open the file for reading
    file = fopen(save_file, "r");

    // Check if the file was opened successfully
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return false;
    }

    // Read and print the contents of the file line by line
    char line[100]; // You can adjust the size of the buffer based on your needs

    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
        if (strstr(line, "kertSor:") != NULL)
        {
            // Find the line containing "kertSor:"
            char* numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // Parse the number after the colon
                *kertSor = atoi(numberStr + 1);
                //break; // Stop searching after finding the first occurrence
            }
        }
        if (strstr(line, "kertOszlop:") != NULL)
        {
            // Find the line containing "kertSor:"
            char* numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // Parse the number after the colon
                *kertOszlop = atoi(numberStr + 1);
                //break; // Stop searching after finding the first occurrence
            }
        }
        if (strstr(line, "penz:") != NULL)
        {
            // Find the line containing "penz:"
            char* numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // Parse the number after the colon
                *penz = atoi(numberStr + 1);
                //break; // Stop searching after finding the first occurrence
            }
        }
                if (strstr(line, "playerPosX:") != NULL)
        {
            // Find the line containing "penz:"
            char* numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // Parse the number after the colon
                p1->playerX = atoi(numberStr + 1);
                //break; // Stop searching after finding the first occurrence
            }
        }
                if (strstr(line, "playerPosY:") != NULL)
        {
            // Find the line containing "penz:"
            char* numberStr = strchr(line, ':');
            if (numberStr != NULL)
            {
                // Parse the number after the colon
                p1->playerY = atoi(numberStr + 1);
                printf("%d",p1->playerY);
                //break; // Stop searching after finding the first occurrence
            }
        }
    }

    // Close the file when you're done with it
    fclose(file);
    return true;
}

bool readTo2DArray(int *arr[], int rows, int cols) {
    FILE* file = fopen("save_file.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return false;
    }

    char line[1024]; // Assuming a maximum line length of 1024 characters
    int row = 0;
    int dataStarted = false;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the line contains "kertAdat"
        if (strstr(line, "kertAdat") != NULL) {
            dataStarted = true;
            continue; // Skip this line and start processing the next one
        }

        // If dataStarted is 1, then process the line
        if (dataStarted) {
            char* token = strtok(line, ",");
            int col = 0;
            while (token != NULL && col < cols&& row<rows) {
                arr[row][col] = atoi(token);
                token = strtok(NULL, ",");
                col++;
            }
            row++;
        }
    }

    fclose(file);
    return true;
}

//SaveGame
bool saveGame(int kertSor,int kertOszlop, int **kertAdat,int penz, int playerX, int playerY)
{
    FILE *file;

    // Open the file for writing
    file = fopen("save_file.txt", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return false;
    }

    // Write kertSor and kertOszlop to the file
    fprintf(file, "kertSor: %d\n", kertSor);
    fprintf(file, "kertOszlop: %d\n", kertOszlop);
    fprintf(file, "penz: %d\n", penz);
    fprintf(file, "playerPosX: %d\n", playerX);
    fprintf(file, "playerPosY: %d\n", playerY);
    // Write "kertAdat:" to the file
    fprintf(file, "kertAdat:");
    fprintf(file, "\n");
    // Write the elements of kertAdat one after the other
    for (int i = 0; i < kertSor; i++) {
        for (int j = 0; j < kertOszlop; j++) {
            fprintf(file, "%d,", kertAdat[i][j]);
        }
        fprintf(file, "\n");
    }

    // Write a newline at the end of the kertAdat elements
    fprintf(file, "\n");

    // Close the file
    fclose(file);

    printf("\nSave successful.\n");

    return true;
}

void changeScene(int select, int *currentScene)
{
    if(select==1)
    {
        *currentScene=2;
    }

    else
    {
        *currentScene=1;
    }
}
