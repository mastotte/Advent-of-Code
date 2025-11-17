def main():
    line_count = 0
    
    with open("input2.txt", "r") as file:
        for line in file:
            line_count += 1

            expanded = ""
            char_count = 0
            for n in line:
                if char_count % 2 == 0:
                    for i in range(int(n)):
                        expanded += str(char_count // 2)

                else:
                    for i in range(int(n)):
                        expanded += "."

                char_count += 1


    while "." in expanded:
        index = expanded.index(".")
        i = len(expanded) - 1
        for r in reversed(expanded):
            if r != ".":
                expanded = expanded[:i] + expanded[i + 1:]
                expanded = expanded[:index] + r + expanded[index + 1:]
                break
                
            i -= 1
    print(expanded)
    total = 0
    index = 0
    for n in expanded: 
        total += int(n) * index
        index += 1
    
    print(total)

if __name__ == "__main__":
    main()