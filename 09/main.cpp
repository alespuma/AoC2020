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

uintmax_t findValid(vector<uintmax_t>& nums, unsigned int first)
{
    for(unsigned int i = first; i < nums.size(); i++)
        {
            bool valid = false;
            for(unsigned int j = i - first; j < i && !valid; j++)
                for(unsigned int k = i - first; k < i && !valid; k++)
                {
                    if(j == k)
                        continue;
                    if(nums[j] + nums[k] == nums[i])
                        valid = true;
                }
            if(!valid)
                return nums[i];
        }
    return 0;
}

uintmax_t findWeak(vector<uintmax_t>& nums, uintmax_t target)
{
    vector<uintmax_t> sumTable(nums.size());
    partial_sum(nums.cbegin(), nums.cend(), sumTable.begin());
    for(unsigned int i = 1; i <= sumTable.size(); i++)
    {
        for(unsigned int j = 0; j < i; j++)
        {
            if(sumTable[i] - sumTable[j] == target )
            {
                const auto MinMax = minmax_element(nums.cbegin() + j, nums.cbegin() + i);
                return *MinMax.second + *MinMax.first;
            }
        }
    }
    return 0;
}

int main()
{
    fstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D9/AoC_D9_p1.txt");
    uintmax_t currNumber;
    vector<uintmax_t> nums;
    int result, result2;

    while (myFile >> currNumber)
        nums.push_back(currNumber);

    result = findValid(nums, 25);
    result2 = findWeak(nums, result);

    cout << result << endl;
    cout << result2 << endl;
    return 0;
}
