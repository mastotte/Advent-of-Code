#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
bool is_carat(char c){
    return (c == '^' || c == 'v' || c == '<' || c == '>');
}
void fill_path(int* start_x, int* start_y, int line_count, int line_length, char grid[line_count][line_length]){
    bool found = false;
    int x = 0;
    int y = 0;
    char cursor = '^';
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < line_length; j++)
        {
            if (is_carat(grid[i][j])){
                x = i;
                y = j;
                *start_x = i;
                *start_y = j;
                cursor = grid[i][j];
                found = true;
                break;
            }
        }
        if (found){
            break;
        }
    }
    grid[x][y] = 'X'; // mark starting point
    while (true){
        if (cursor == '^'){ // up
            if (x == 0) break;
            if (grid[x-1][y] == '#'){
                cursor = '>';
            }else{
                x--;
                grid[x][y] = 'X';
            }
        }else if (cursor == 'v'){ // down
            if (x == line_count - 1) break;
            if (grid[x+1][y] == '#'){
                cursor = '<';
            }else{
                x++;
                grid[x][y] = 'X';
            }
        }else if (cursor == '>'){ // right
            if (y == line_length - 1) break;
            if (grid[x][y+1] == '#'){
                cursor = 'v';
            }else{
                y++;
                grid[x][y] = 'X';
            }
        }else if (cursor == '<'){ // left
            if (y == 0) break;
            if (grid[x][y-1] == '#'){
                cursor = '^';
            }else{
                y--;
                grid[x][y] = 'X';
            }
        }
    }
}
int part2(int start_x, int start_y, int line_count, int line_length, char grid[line_count][line_length]){
    // loop through all X's, testing if putting an obstacle there causes infinite steps.
    // brute force method
     // hardcoding is not recommended, but I am doing it here for convenience.
    int inf_count = 0;
    for (int i = 0; i < line_count; i++){
        for (int j = 0; j < line_length; j++){
            if (grid[i][j] == 'X'){
                char cursor = '^';
                int x = start_x;
                int y = start_y;
                grid[i][j] = '#'; // revert this to X at end
                int steps = 0; // if steps > (line_length * line_count), we are in an infinite loop
                while (steps < line_count * line_length){
                    if (cursor == '^'){ // up
                        if (x == 0) break;
                        if (grid[x-1][y] == '#'){
                            cursor = '>';
                        }else{
                            x--;
                        }
                    }else if (cursor == 'v'){ // down
                        if (x == line_count - 1) break;
                        if (grid[x+1][y] == '#'){
                            cursor = '<';
                        }else{
                            x++;
                        }
                    }else if (cursor == '>'){ // right
                        if (y == line_length - 1) break;
                        if (grid[x][y+1] == '#'){
                            cursor = 'v';
                        }else{
                            y++;
                        }
                    }else if (cursor == '<'){ // left
                        if (y == 0) break;
                        if (grid[x][y-1] == '#'){
                            cursor = '^';
                        }else{
                            y--;
                        }
                    }
                    steps++;
                }
                grid[i][j] = 'X'; // reverting to X at end to not mess up grid

                // check if infinite
                if (steps >= line_count * line_length){
                    //printf("Infinite spot found at (%d, %d)\n", i, j);
                    inf_count++;
                }
            }
        }
    }
    return inf_count;


}
int get_line_length(char* file_name){
    int line_length = 0;
    char c;
    FILE *file;
    file = fopen(file_name, "r");
    do
    {
        c = fgetc(file);
        line_length++;
    } while (c != '\n');
    fclose(file);
    return line_length - 2;
}
int get_line_count(char* file_name, int line_length){
    int line_count = 0;
    line_length += 3;
    FILE *file;
    file = fopen(file_name, "r");
    char buffer[line_length];

    while (fgets(buffer, line_length, file))
    {
        line_count++;
    }
    fclose(file);
    return line_count;
}
int main()
{
    FILE *file;
    char file_name[20] = "input.txt";

    int line_length = get_line_length(file_name);
    int line_count = get_line_count(file_name, line_length);
    int bufsize = 256;

    //printf("Line Length: %d\n", line_length);
    //printf("Line Count: %d\n", line_count);

    char grid[line_count][line_length];

    char buffer[bufsize];
    int i = 0;
    int j = 0;
    file = fopen(file_name, "r");

    for(int i = 0; i < line_count; i++){
        fgets(buffer, bufsize, file);
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        strncpy(grid[i], buffer, line_length);
    }
    int start_x, start_y;
    fill_path(&start_x, &start_y, line_count, line_length, grid);
    int inf_count = part2(start_x, start_y, line_count, line_length, grid);
    printf("Spots for infinite guard loops: %d\n", inf_count);

    int x_count = 0;
    for(int i = 0; i < line_count; i++){
        for(int j = 0; j < line_length; j++){
            //printf("%c", grid[i][j]);
            if (grid[i][j] == 'X') x_count++;
        }
        //printf("\n");
    }
    
    printf("X count: %d\n", x_count);
    return 0;
}