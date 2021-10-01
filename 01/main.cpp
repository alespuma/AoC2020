#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> numsBig;
    std::vector<int> numsSmall;
    std::ifstream infile("C:/Users/alesk/Desktop/AoC_2021/AoC_D1/AoC_D1_p1.txt");

    int num;
    while (infile >> num)
    {
        if (num > 1010)
            numsBig.push_back(num);
        else
            numsSmall.push_back(num);
    }
    // Part 1
    for (int i : numsBig)
        for (int j : numsSmall)
            if (i + j == 2020)
                std::cout << i*j << std::endl;
    // Part 2
    std::ifstream infile2("C:/Users/alesk/Desktop/AoC_2021/AoC_D1/AoC_D1_p1.txt");
    std::vector<int> nums;
    while (infile2 >> num)
        nums.push_back(num);

    for (int i  = 0; i  < nums.size() - 2;  i++)
        for (int j = i + 1; j < nums.size() - 1; j++)
            for (int k = nums.size() - 1; k > j; k--)
                if (nums[i] + nums[j] + nums[k] == 2020)
                    std::cout << nums[i]*nums[j]*nums[k] << std::endl;

    return 0;
}
