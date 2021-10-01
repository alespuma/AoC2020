#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <stack>

using namespace std;

int parentCnt(const map<string, set<string>> cont, string color)
{
    set<string> contColor;
    string currColor;
    stack<string> queue;
    queue.push(color);

    while (queue.size())
    {
        currColor = queue.top(); queue.pop();
        if (cont.count(currColor) > 0)
            for (auto it : cont.at(currColor))
            {
                contColor.insert(it);
                queue.push(it);
            }
    }
    return contColor.size();
}

int bagCnt(const map<string, map<string, int>> cont2, string color)
{
    int total = 0;
    if (cont2.count(color))
        for (auto rule : cont2.at(color))
             total += rule.second * (bagCnt(cont2, rule.first) + 1);
    return total;
}

int main()
{
    ifstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D7/AoC_D7_p1.txt");
    string line, trash, adj, color, adjIn, colorIn;
    map<string, set<string>> cont;
    map<string, map<string, int>> cont2;
    int cnt;

    while (getline(myFile, line))
    {
        stringstream lineStream(line);
        lineStream >> adj >> color >> trash >> trash;
        while (lineStream)
            if (lineStream >> cnt >> adjIn >> colorIn >> trash)
            {
                cont[adjIn + colorIn].insert(adj + color);
                cont2[adj + color][adjIn + colorIn] = cnt;
            }
    }


    cout << parentCnt(cont, "shinygold") << '\n' << bagCnt(cont2, "shinygold") << endl;
    return 0;
}
