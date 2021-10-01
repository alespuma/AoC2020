#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <vector>
#include <map>
#include <set>
#include <list>

#include <algorithm>
#include <iterator>
#include <regex>

using namespace std;


int computer1(vector<pair<string, int>> &instructions)
{
    vector<int> visited(instructions.size());
    int acc = 0;
    unsigned int i = 0;

    while (true)
    {
        visited[i] += 1;
        if (visited[i] == 2)
            return acc;

        if (instructions[i].first == "nop"){
            i++;
        }
        else if (instructions[i].first == "acc"){
            acc += instructions[i].second;
            i++;
        }
        else if (instructions[i].first == "jmp"){
            i += instructions[i].second;
        }
    }
    return 0;
}

int computer2(vector<pair<string, int>> &instructions)
{
    vector<int> visited(instructions.size());
    int acc = 0;
    unsigned int i = 0;
    while (true){
        if (i == instructions.size())
            return acc;

        if (i > instructions.size()){
            return -9999;
        }

        visited[i] += 1;
        if (visited[i] > 1){
            return -9999;
        }

        if (instructions[i].first == "nop"){
            i++;
        }
        else if (instructions[i].first == "acc"){
            acc += instructions[i].second;
            i++;
        }
        else if (instructions[i].first == "jmp"){
            i += instructions[i].second;
        }
    }
    return 0;
}

int main ()
{
    int ans1 = 0, ans2 = -9999;

    vector<std::pair<std::string, int>> instructions;
    fstream myfile("C:/Users/alesk/Desktop/AoC_2021/AoC_D8/AoC_D8_p1.txt", std::ios_base::in);
    string line;
    regex pieces_regex("([a-z]{3}) ([+-]\\d*)");
    smatch pieces_match;
    while(getline(myfile, line)){
        regex_search(line, pieces_match, pieces_regex);
        instructions.push_back({pieces_match[1], stoi(pieces_match[2])});
    }
    myfile.close();

    ans1 = computer1(instructions);


    vector<pair<string, int>> instructions2;
    for(unsigned int i=0; i<instructions.size(); i++)
    {
        instructions2 = instructions;

        if (instructions2[i].first == "jmp")
        {
            instructions2[i].first = "nop";
            ans2 = computer2(instructions2);
        }
        else if (instructions2[i].first == "nop")
        {
            instructions2[i].first = "jmp";
            ans2 = computer2(instructions2);
        }
        if (ans2 != -9999)
            break;
    }

    cout << ans1 << endl;
    cout << ans2 << endl;

    return 0;
}
