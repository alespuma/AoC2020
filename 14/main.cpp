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

std::uint64_t applyMask(std::uint64_t number, std::string mask)
{
    std::uint64_t zerosMask = (1ULL << 37) - 1;
    std::uint64_t onesMask = 0;

    for (std::size_t i = 0; i < mask.size(); i++)
        if (mask[mask.size() - i - 1] == '1')
            onesMask += 1ULL << i;
        else if  (mask[mask.size() - i - 1] == '0')
            zerosMask ^= 1ULL << i;

  return (number | onesMask) & zerosMask;
}

std::vector<std::uint64_t> applyMask2(std::uint64_t address, std::string mask)
{
    std::uint64_t zeros_mask = (1ULL << 37) - 1;
    std::uint64_t ones_mask = 0;

    for (std::size_t i = 0; i < mask.size(); i++)
        if (mask[mask.size() - i - 1] == '1')
            ones_mask += 1ULL << i;
        else if (mask[mask.size() - i - 1] == 'X')
            zeros_mask ^= 1ULL << i;

    std::vector<std::uint64_t> addresses {(address | ones_mask) & zeros_mask};
    for (std::size_t i = 0; i < mask.size(); ++i)
        if (mask[mask.size() - i - 1] == 'X')
            for (std::size_t j = 0, size{addresses.size()}; j < size; ++j)
                addresses.push_back(addresses[j] | (1ULL << i));

  return addresses;
}

int main()
{
    std::fstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D14/AoC_D14_p1.txt", std::ios_base::in);
    std::map<std::uint64_t, std::uint64_t> memory, memory2;
    std::string command, trash, value, mask;

    while (myFile >> command >> trash >> value)
        if (command == "mask")
            mask = value;
        else
        {
            const std::uint64_t address {std::atoi(command.substr(4, command.size() - 5).c_str())};
            memory[address] = applyMask(std::atoi(value.c_str()), mask);

            const std::vector<std::uint64_t>& addresses = applyMask2(address, mask);
            for (const auto & ad : addresses)
                memory2[ad] = std::atoi(value.c_str());
        }

    std::uint64_t sum = 0;
    std::uint64_t sum2 = 0;

    for (const auto & mem : memory)
        sum += mem.second;
    for (const auto & mem : memory2)
        sum2 += mem.second;

    std::cout << "Part one: " << sum  << std::endl;
    std::cout << "Part two: " << sum2 << std::endl;
    return 0;
}
