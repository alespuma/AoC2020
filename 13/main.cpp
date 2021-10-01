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
#include <numeric>

std::int64_t modInverse(const std::uint64_t a, const std::uint64_t m)
{
    std::uint64_t m0 = m;
    std::uint64_t a0 = a;
    std::uint64_t y = 0;
    std::int64_t x = 1;

    if (m == 1)
        return 0;

    while (a0 > 1) {
        std::uint64_t q = a0 / m0;
        std::uint64_t t = m0;

        m0 = a0 % m0;
        a0 = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m;

    return x;
}

int main()
{
    std::fstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D13/AoC_D13_p1.txt", std::ios_base::in);
    std::uint32_t time;
    std::string line;

    myFile >> time;
    myFile.ignore();

    // Part 1
    std::getline(myFile, line);
    std::istringstream ss(line);
    std::string busIdStr;
    std::uint32_t bestBusId;
    std::uint32_t minWait = std::numeric_limits<uint32_t>::max();

    while (getline(ss, busIdStr, ','))
        if (busIdStr != "x")
        {
            std::uint32_t busId;
            busId = static_cast<std::uint32_t>(std::stoi(busIdStr));

            std::uint32_t waitTime = ((time / busId) + 1 ) * busId - time;
            if (waitTime < minWait)
            {
                        minWait = waitTime;
                        bestBusId = busId;
            }
        }
    std::cout << bestBusId * minWait << std::endl;
    myFile.close();

    //Part 2
    std::istringstream ss2(line);
    std::uint32_t idx = 0;
    std::string busIdStr2;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> busIds;

    while (getline(ss2, busIdStr2, ','))
    {
        if (busIdStr2 != "x")
        {
            std::uint32_t busId2;
            busId2 = static_cast<std::uint32_t>(std::stoi(busIdStr2));

            busIds.emplace_back(idx, busId2);
        }
        idx += 1;
    }

    std::uint64_t M = accumulate(
            busIds.begin(),
            busIds.end(),
            static_cast<std::uint64_t>(1),
            [](const std::uint64_t& p, const std::pair<std::uint32_t, std::uint32_t>& e)
            {
                return p * e.second;
            });

    std::uint64_t time2 = 0;
    for (const auto& it : busIds)
    {
        const uint64_t m = it.second;
        const uint64_t a = (m - it.first % m) % m;
        const uint64_t b = M / m;
        const uint64_t bPrime = modInverse(b, m);

            time2 += a * b * bPrime;
        }

        time2 = time2 % M;

    std::cout << time2 << std::endl;
    return 0;
}
