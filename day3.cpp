#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
int evaluate(string content){
    regex pattern(R"(mul\(\d+,\d+\))");
    int total = 0;
    for (sregex_iterator it(content.begin(), content.end(), pattern), end; it != end; ++it)
    {
        smatch match = *it;
        string s = match.str();
        string sub = s.substr(4, s.length() - 5);
        int num1 = stoi(sub.substr(0, sub.find(',')));
        int num2 = stoi(sub.substr(sub.find(',') + 1));

        total += num1 * num2;
    }
    return total;
}
int main()
{
    ifstream file("input.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    
    regex do_pattern(R"(do\(\))");
    regex dont_pattern(R"(don't\(\))");
    smatch match;
    int total = 0;

    regex current_pattern = dont_pattern;
    int prev_position = 0;
    int end_position = 0;
    int loop_lim = 0;
    bool do_next = false;
    for (sregex_iterator it(content.begin(), content.end(), current_pattern), end; it != end; ++it)
    {
        smatch match = *it;
        loop_lim++;
        end_position = match.position();

        if(!do_next){
            string sub_content = content.substr(prev_position, end_position - prev_position);

            total += evaluate(sub_content);
        }

        if(do_next){
            current_pattern = dont_pattern;
            do_next = false;
        } else {
            current_pattern = do_pattern;
            do_next = true;
        }

        prev_position = end_position;
    }

    if(!do_next){
        string end_of_content = content.substr(end_position, content.length() - end_position);
        total += evaluate(end_of_content);
    }

    cout << "Total: " << total << endl;
    return 0;
}