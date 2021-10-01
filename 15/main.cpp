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

std::vector<std::uint32_t> nums{11, 0, 1, 10, 5, 19};

std::uint32_t memoryGame(std::uint32_t finalTurn)
{
    std::unordered_map<std::uint32_t, std::uint32_t> lastSeen; //<Cislo, posledni videna pozice>
    for (std::size_t i = 0; i < nums.size(); i++)
        lastSeen[nums[i]] = i;

    std::uint32_t currNum;
    std::uint32_t prev = nums[nums.size() - 1];
    for (std::size_t i = nums.size(); i < finalTurn; i++)
    {
        if (lastSeen.find(prev) == lastSeen.end())
            currNum = 0;
        else
            currNum = i - 1 - lastSeen[prev];

        lastSeen[prev] = i - 1;
        prev = currNum;
    }
    return prev;
}

int main()
{
    std::cout << "Part 1: " << memoryGame(2020) << std::endl;
    std::cout << "Part 2: " << memoryGame(30000000) << std::endl;
    return 0;
}
