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

unsigned int cntOccSeats(const std::vector<std::string>& grid, const std::uint32_t startX, const std::uint32_t startY)
{
    std::vector<std::pair<int, int>> dxy = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int newX = 0;
    int newY = 0;
    std::uint32_t occSeats = 0;

    for (auto it : dxy)
    {
        newX = startX + it.first;
        newY = startY + it.second;
        if ((newX >= 0) && (newY >= 0) && (newX < grid.size()) && (newY < grid[0].size()))
            if (grid[newX][newY] == '#')
                occSeats++;
    }
    return occSeats;
}

int cntOccSeats2(const std::vector<std::string>& grid, const std::uint32_t startX, const std::uint32_t startY)
{
    std::vector<std::pair<int, int>> dxy = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int newX = 0;
    int newY = 0;
    std::uint32_t occSeats = 0;

    for (auto it : dxy)
    {
        newX = startX + it.first;
        newY = startY + it.second;
        while ((newX >= 0) && (newY >= 0) && (newX < grid.size()) && (newY < grid[0].size()) && grid[newX][newY] != 'L')
        {
            if (grid[newX][newY] == '#')
            {
                occSeats++;
                break;
            }
            newX += it.first;
            newY += it.second;
        }
    }
    return occSeats;
}


int main()
{
    std::fstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D11/AoC_D11_p1.txt", std::ios_base::in);
    std::string line;
    std::vector<std::string> grid, newGrid;
    //std::uint32_t occSeats = 0;
    std::uint32_t occSeats2 = 0;

    while (std::getline(myFile, line))
            grid.push_back(line);
    myFile.close();
    newGrid = grid;

    //Part 2 předělanej z Part 1 (if podmínka je ze 4 na 5 daní)
    do
    {
        grid = newGrid;
        for (std::uint32_t x = 0; x < grid.size(); x++)
            for (std::uint32_t y = 0; y < grid[0].size(); y++)
            {
                occSeats2 = cntOccSeats2(grid, x, y);
                if ((grid[x][y] == 'L') && (occSeats2 == 0))
                    newGrid[x][y] = '#';
                if ((grid[x][y] == '#') && (occSeats2 >= 5))
                    newGrid[x][y] = 'L';
            }
    } while (grid != newGrid);

    //occSeats = std::accumulate(std::begin(grid), std::end(grid), 0, [](int total, const std::string& row) {
    //    return total + std::count(std::begin(row), std::end(row), '#');
    //    });

    occSeats2 = std::accumulate(std::begin(grid), std::end(grid), 0, [](int total, const std::string& row) {
        return total + std::count(std::begin(row), std::end(row), '#');
        });

    std::cout << occSeats2 << std::endl;
    return 0;
}
