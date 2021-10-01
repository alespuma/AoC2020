#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>

#include <algorithm>
#include <iterator>
#include <regex>

using namespace std;

int main()
{
    fstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D10/AoC_D10_p1.txt", ios_base::in);
    vector<int> jolts;
    int num;

    jolts.push_back(0);
    while (myFile >> num)
        jolts.push_back(num);
    sort(jolts.begin(), jolts.end());
    jolts.push_back(jolts.back() + 3);
    myFile.close();

    // Part 1
    vector<int> diff(jolts.size());
    adjacent_difference(jolts.cbegin(), jolts.cend(), diff.begin());

    cout << count(diff.cbegin(), diff.cend(), 1) * count(diff.cbegin(), diff.cend(), 3) << endl;

    //Part2
    unordered_map<uintmax_t, uintmax_t> cnts{{0,1}};
    for(auto jolt : jolts)
        cnts[jolt] += cnts[jolt - 1] + cnts[jolt - 2] + cnts[jolt - 3];


    cout << cnts[jolts.back()] << endl;
    return 0;
}
