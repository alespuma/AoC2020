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


int main()
{
    std::fstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D12/AoC_D12_p1.txt", std::ios_base::in);
    std::vector<std::pair<char, std::uint32_t>> dir;
    std::string line;

    while (std::getline(myFile, line))
    {
        std::pair<char, std::uint32_t> temp;
        temp.first = line.at(0);
        temp.second = stoi(line.substr(1, 3));
        dir.push_back(temp);
    }
    //Part 1                        // E  S  W  N
    std::array<std::int32_t, 4> ship {0, 0, 0, 0};
    std::uint8_t rot = 0;

    for (auto it : dir)
    {
        if (it.first == 'N')
            ship[3] += it.second;
        if (it.first == 'S')
            ship[1] += it.second;
        if (it.first == 'E')
            ship[0] += it.second;
        if (it.first == 'W')
            ship[2] += it.second;
        if (it.first == 'L')
            rot = (rot + (360 - it.second) / 90) % 4;
        if (it.first == 'R')
            rot = (rot + it.second / 90) % 4;
        if (it.first == 'F')
            ship[rot] += it.second;
    }
    std::cout << std::abs(ship[1] - ship[3]) + std::abs(ship[0] - ship[2]) << std::endl;

    //Part 2                             // E  S  W  N
    std::array<std::int32_t, 4> waypoint {10, 0, 0, 1};
    ship = { 0, 0, 0, 0 };
    rot = 0;
    for (auto it : dir)
    {
        if (it.first == 'N')
            waypoint[3] += it.second;
        if (it.first == 'S')
            waypoint[1] += it.second;
        if (it.first == 'E')
            waypoint[0] += it.second;
        if (it.first == 'W')
            waypoint[2] += it.second;
        if (it.first == 'L')
            std::rotate(waypoint.begin(), waypoint.begin() + it.second / 90, waypoint.end());
        if (it.first == 'R')
            std::rotate(waypoint.rbegin(), waypoint.rbegin() + it.second / 90, waypoint.rend());
        if (it.first == 'F')
            for (int j = 0; j < 4; ++j)
                ship[j] += it.second * waypoint[j];
    }
    std::cout << std::abs(ship[1] - ship[3]) + std::abs(ship[0] - ship[2]) << std::endl;

    return 0;
}
