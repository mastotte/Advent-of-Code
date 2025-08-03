def getMiddle(input):
    nums = input.split(",")
    return int(nums[len(nums) // 2])

def isValid(rules, input):

    for rule in rules:
        first, second = rule.split("|")

        first_index = input.find(first)
        second_index = input.find(second)

        if(first_index > second_index):
            return False
        
    return True

# Return all rules relevant to the input
def getRules(rules, input):

    relevant_rules = []
    for rule in rules:
        x, y = rule.split("|")
        if(x in input and y in input):
            relevant_rules.append(rule)

    return relevant_rules

def rearrange(rules, input):
    # break into a list so we can swap
    fixed = []
    fixed_str = input
    nums = input.split(",")
    for num in nums:
        fixed.append(num)

    while(not isValid(rules, fixed_str)):
        for rule in rules:
            first, second = rule.split("|")

            first_index = fixed.index(first)
            second_index = fixed.index(second)

            if first_index > second_index:
                fixed[first_index], fixed[second_index] = fixed[second_index], fixed[first_index]

        separator = ","
        fixed_str = separator.join(fixed)

    return fixed_str


def main():
    
    rules = []
    inputs = []
    reading_rules = True
    with open("input.txt", "r") as file:
        
        for line in file:
            line = line.strip()
            if(len(line) == 0):
                reading_rules = False
                continue

            if(reading_rules):
                rules.append(line)
            else:
                inputs.append(line)

    total = 0 
    for i in inputs:
        relevant_rules = getRules(rules, i)
        if(isValid(relevant_rules, i)):
            total += getMiddle(i)
    
    print("(Part 1) Total: ", total)

    total = 0
    for i in inputs:
        relevant_rules = getRules(rules, i)
        if(not isValid(relevant_rules, i)):
            fixed = rearrange(relevant_rules, i)
            total += getMiddle(fixed)

    print("(Part 2) Total: ", total)
    

    # You can print or use line_count as needed
    # print("Number of lines:", line_count)

if __name__ == "__main__":
    main()
