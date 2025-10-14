

def xmasCount(grid, x, y):
    found = 0
    up_con = (y >= 3)
    down_con = (y + 4 <= len(grid))
    left_con = (x >= 3)
    right_con = (x + 4 <= len(grid[0]))
    word = ""
    # search down
    if(down_con):
        for i in range(4):
            word += grid[y + i][x]
    
    if word == "XMAS":
        found += 1

    word = ""
    # search up
    if(up_con):
        for i in range(4):
            word += grid[y - i][x]
    
    if word == "XMAS":
        found += 1

    word = ""
    # search left
    if(left_con):
        for i in range(4):
            word += grid[y][x - i]
    
    if word == "XMAS":
        found += 1

    word = ""
    # search right
    if(right_con):
        for i in range(4):
            word += grid[y][x + i]
    
    if word == "XMAS":
        found += 1

    # -- Diagonals
    word = ""
    # search up left
    if(up_con and left_con):
        for i in range(4):
            word += grid[y - i][x - i]
    
    if word == "XMAS":
        found += 1

    word = ""
    # search up right
    if(up_con and right_con):
        for i in range(4):
            word += grid[y - i][x + i]
    
    if word == "XMAS":
        found += 1

    word = ""
    # search down left
    if(down_con and left_con):
        for i in range(4):
            word += grid[y + i][x - i]
    
    if word == "XMAS":
        found += 1

    word = ""
    # search down right
    if(down_con and right_con):
        for i in range(4):
            word += grid[y + i][x + i]
    
    if word == "XMAS":
        found += 1

    
    return found

def is_x_MAS(grid, x, y):
    if(x == 0 or y == 0 or y == len(grid) - 1 or x == len(grid[0]) - 1):
       return False
    
    # a1 and a2 check up-left to down-right MAS
    a1 = grid[y-1][x-1] == 'M' and grid[y+1][x+1] == 'S'
    a2 = grid[y-1][x-1] == 'S' and grid[y+1][x+1] == 'M'

    # b1 and b2 check down-left to up-right MAS
    b1 = grid[y+1][x-1] == 'M' and grid[y-1][x+1] == 'S'
    b2 = grid[y+1][x-1] == 'S' and grid[y-1][x+1] == 'M'

    if((a1 or a2) and (b1 or b2)):
        return True
    else:
        return False

def main():
    line_count = 0
    
    grid = []
    with open("input.txt", "r") as file:
        for line in file:
            row = []
            for letter in line:
                if letter != '\n':
                    row.append(letter)

            grid.append(row)
            line_count += 1

    found = 0
    col_len = len(grid)
    row_len = len(grid[0])
    for x in range(row_len):
        for y in range(col_len):
            if(grid[y][x] == 'X'):
                found += xmasCount(grid, x, y)

    print("(Part 1) XMAS found: ", found)

    found = 0
    for x in range(row_len):
        for y in range(col_len):
            if(grid[y][x] == 'A'):
                if(is_x_MAS(grid, x, y)):
                    found += 1

    print("(Part 2) X-MAS found: ", found)

    # You can print or use line_count as needed
    # print("Number of lines:", line_count)

if __name__ == "__main__":
    main()
