#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int findRow(int first, int last, string sRow)
{
    if (sRow.size() == 1)
        if (sRow.at(0) == 'B')
            return last;
        else
            return first;

    if (sRow.at(0) == 'B')
        return findRow(first + (last - first + 1) / 2, last, sRow.substr(1, sRow.size() - 1));
    else
        return findRow(first, last - (last - first + 1) / 2, sRow.substr(1, sRow.size() - 1));
}

int findCol(int first, int last, string sCol)
{
    {
        if (sCol.size() == 1)
            if (sCol.at(0) == 'R')
                return last;
            else
                return first;

        if (sCol.at(0) == 'R')
            return findCol(first + (last - first + 1) / 2, last, sCol.substr(1, sCol.size() - 1));
        else
            return findCol(first, last - (last - first + 1) / 2, sCol.substr(1, sCol.size() - 1));
    }
}

int main()
{
    ifstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D5/AoC_D5_p1.txt");
    string line, sRow, sCol;
    vector<int> ids;

    // Part 1
    while (getline(myFile, line))
    {
        sRow = line.substr(0, 7);
        sCol = line.substr(7, 3);
        ids.push_back(findRow(0,  127, sRow) * 8 + findCol(0, 7, sCol));
    }
    sort(ids.begin(), ids.end());
    cout << ids.back() << endl;

    // Part 2
    for(auto it = ++ids.begin(); it != ids.end(); it++)
    {
        auto prev = it; --prev;
        if(*prev + 2 == *it)
            cout << *it - 1 << endl;
    }

    return 0;
}
