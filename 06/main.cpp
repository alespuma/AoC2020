#include <fstream>
#include <iostream>

#include <array>
#include <string>

int main()
{
    int ans1 = 0, ans2 = 0;

    std::fstream myfile("C:/Users/alesk/Desktop/AoC_2021/AoC_D6/AoC_D6_p1.txt");
    std::string line;

    std::array<char, 26> present;
    present.fill(0);
    int num_people = 0;
    while (std::getline(myfile, line))
    {
        if (line == "")
        {
            for (unsigned int i = 0; i < 26; i++)
                if (present[i] > 0)
                    ans1++;

            for (unsigned int i = 0; i < 26; i++)
                if (present[i] == num_people)
                    ans2++;

            present.fill(0);
            num_people = 0;
        } else
        {
            num_people++;
            for (unsigned int i = 0; i < line.size(); i++)
                present[int(line[i]) - 97]++;
        }
    }
    myfile.close();

    for (unsigned int i = 0; i < 26; i++)
        if (present[i] > 0)
            ans1++;

    for (unsigned int i = 0; i < 26; i++)
        if (present[i] == num_people)
            ans2++;

    std::cout << ans1 << std::endl;
    std::cout << ans2 << std::endl;

    return 0;
}
