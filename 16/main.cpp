#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <regex>

const std::regex CONSTRAINTS_RX("(.*)\\: ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)");

struct Rule
{
    std::uintmax_t MinA, MinB, MaxA, MaxB;
    bool Test(std::uintmax_t Number) const
    {
        return
            (MinA <= Number && Number <= MaxA) ||
            (MinB <= Number && Number <= MaxB);
    }
};

int main()
{
    std::fstream myFile("C:/Users/alesk/Desktop/AoC_2021/AoC_D16/AoC_D16_p1.txt");
    std::map<std::uintmax_t, Rule> Rules;
    std::map<std::uintmax_t, Rule*> RuleSpans;
    std::set<std::uintmax_t> ValidFields, DepartureField;

    std::string CurLine;
    std::uintmax_t RuleIdx = 0;
    while( std::getline(myFile, CurLine) && CurLine.size() )
    {
        std::smatch match;
        if (regex_match(CurLine, match, CONSTRAINTS_RX))
        {
            auto field = match[1].str();
            Rule CurRule;
            uint32_t low1, low2, high1, high2;
            std::istringstream ss(match[2].str());
            ss >> low1; CurRule.MinA = low1;
            ss.clear();

            ss.str(match[3].str());
            ss >> high1; CurRule.MaxA = high1;
            ss.clear();

            ss.str(match[4].str());
            ss >> low2; CurRule.MinB = low2;
            ss.clear();

            ss.str(match[5].str());
            ss >> high2; CurRule.MaxB = high2;
            ss.clear();

            Rules[RuleIdx] = CurRule;
            RuleSpans[low1] = &Rules[RuleIdx]; RuleSpans[low2] = &Rules[RuleIdx];
            ++RuleIdx;
        }
    }

    // Your Ticket
    std::vector<std::uintmax_t> YourTicket;
    std::getline(myFile, CurLine); // "your ticket:"
    if(std::getline(myFile, CurLine))
    {
        std::stringstream TicketStream(CurLine); std::string CurNum;
        while(std::getline(TicketStream, CurNum, ','))
            YourTicket.push_back(std::stoull(CurNum));
    }

    // Nearby tickets
    std::vector<std::vector<std::uintmax_t>> NearbyTickets;
    std::getline(myFile, CurLine); // ""
    std::getline(myFile, CurLine); // "nearby tickets:"
    while(std::getline(myFile, CurLine) && CurLine.size())
    {
        NearbyTickets.push_back({});
        auto& CurTicket = NearbyTickets.back();
        std::stringstream TicketStream(CurLine); std::string CurNum;
        while(std::getline(TicketStream, CurNum, ',')) CurTicket.push_back(std::stoull(CurNum));
    }

    std::uintmax_t Part1{};
    std::vector<std::vector<std::uintmax_t>> ValidTickets;
    for(const auto& CurTicket : NearbyTickets)
    {
        bool ValidTicket = true;
        for(auto& Num : CurTicket)
        {
            const auto Match = --RuleSpans.lower_bound(Num);
            if(!Match->second->Test(Num))
            {
                // Not matched
                Part1 += Num;
                ValidTicket = false;
            }
        }
        if( ValidTicket )
        {
            ValidTickets.push_back(CurTicket);
        }
    }

    std::cout << Part1 << std::endl;

    std::vector<std::vector<std::uintmax_t>> Columns(ValidTickets[0].size());
    for( std::size_t Row = 0; Row < ValidTickets.size(); ++Row )
        for( std::size_t Column = 0; Column < ValidTickets[Row].size(); ++Column )
            Columns[Column].push_back(ValidTickets[Row][Column]);

    std::map<std::uintmax_t, std::set<std::uintmax_t>> Possibilities;

    for( std::size_t i = 0; i < Columns.size(); ++i )
    {
        for(const auto Span : Rules)
        {
            bool ValidCol = true;
            for(const auto Val : Columns[i])
                ValidCol &= Span.second.Test(Val);
            if(ValidCol)
                Possibilities[i].insert(Span.first);
        }
    }

    std::vector<std::uintmax_t> OrderIndex(Possibilities.size());\
    // Gaussian elimination
    while(Possibilities.size())
    {
        // Find the column with the least amount of possibilities
        std::uintmax_t RuleIndex = ~0ull;
        std::uintmax_t MinColumnSize = ~0ull;
        for( auto Possibility : Possibilities )
        {
            if(Possibility.second.size() < MinColumnSize)
            {
                RuleIndex = Possibility.first;
                MinColumnSize = Possibility.second.size();
            }
        }

        assert(Possibilities[RuleIndex].size() == 1);

        const std::uintmax_t CurBasis = *Possibilities[RuleIndex].begin();
        Possibilities.erase(RuleIndex);
        OrderIndex[CurBasis] = RuleIndex;
        for( auto& Possibility : Possibilities )
            Possibility.second.erase(CurBasis);
    }
    std::uintmax_t Part2 = 1;
    for( std::size_t i = 0; i < 6; ++i )
    {
        Part2 *= YourTicket[OrderIndex[i]];
    }
    std::cout << Part2 << std::endl;

    return 0;
}
