#include <iostream>
#include <fstream>
#include <stdio.h>
#include <regex>

using namespace std;

bool validPass(int min, int max, char character, string password)
{
    int count = std::count(password.begin(), password.end(), character);
    return count >= min && count <= max;
}

bool validPass2(int pos1, int pos2, char character, string password)
{
    return ((password.at(pos1 - 1) == character)?1:0)+(password.at(pos2 -  1) == character?1:0) == 1;
}

int main()
{
    int result1 = 0;
    int result2  = 0;
    ifstream myfile("C:/Users/alesk/Desktop/AoC_2021/AoC_D2/AoC_D2_p1.txt");
    regex pieces_regex("(\\d+)-(\\d+) ([a-z]): ([a-z]+)");
    smatch pieces_match;
    string line;

    while (getline(myfile, line))
        if(regex_search(line, pieces_match, pieces_regex))
        {
            int pos1 = stoi(pieces_match[1]);
            int pos2 =stoi(pieces_match[2]);
            char character = string(pieces_match[3]).at(0);
            string  password= pieces_match[4];

            result1 +=  validPass(pos1, pos2, character, password)?1:0;
            result2 += validPass2(pos1, pos2, character, password)?1:0;
        }
    cout << result1 << endl;
    cout << result2 << endl;
    return 0;
}
