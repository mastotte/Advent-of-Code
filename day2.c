#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
bool isSafe(int *line, int length, int ignore)
{
    
    int direction = 999; // -1 for down, +1 for up, 999 for start
    int next = 0;
    for (int i = 0; i < length - 1; i++)
    {
        bool skip = false;
        next++;

        if (i == ignore){
            continue;
        }
        if (i + 1 == ignore){
            next++;
            if (i == length - 2){
                continue;
            }
            skip = true;
        }


        
        if (direction == 999){
            if (line[i] < line[next])
            {
                direction = 1;
            }
            else if (line[i] > line[next])
            {
                direction = -1;
            }else
            {
                return false;
            }
        }

        if (direction == -1){
            if (line[i] - line[next] < 1 || line[i] - line[next] > 3)
            {
                return false;
            }
        }
        else
        {
            if (line[next] - line[i] < 1 || line[next] - line[i] > 3)
            {
                return false;
            }
        }


        if (skip)
        {
            i++;
        }
    }

    return true;
    
}

bool isLineSafe(int *line, int length){
    for (int i = 0; i < length; i++){
        
        if (isSafe(line, length, i)){
            return true;
        }
    }

    return false;
}
int main()
{
    FILE *file;
    file = fopen("input.txt", "r");

    char buffer[256];
    
    int safe = 0;
    int line_count = 0;
    while (fgets(buffer, 256, file) && line_count < 10000)
    {

        line_count++;
        int buffer_length = (int) strlen(buffer) - 2; //eliminate surrounding characters
        int line[buffer_length];
        char *number = strtok(buffer, " ");

        int index = 0;
        do
        {
            line[index] = atoi(number);
            index++;
        } while (number = strtok(NULL, " "));

        int length = index;

        if (isLineSafe(line, length))
        {
            safe++;
        }else{
        }
    }

    printf("Safe: %d\n", safe);
    return 0;
}