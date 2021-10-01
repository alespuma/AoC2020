#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

using namespace std;

struct Strategy {
    int right;
    int down;
    int trees;
};

int main()
{
    // part 1
    ifstream myfile("C:/Users/alesk/Desktop/AoC_2021/AoC_D3/AoC_D3_p1.txt");
    string line;
    int cnt = 3;
    int trees = 0;

    myfile >> line;
    while (myfile >> line)
    {
        if (cnt >= line.length())
            cnt = cnt - line.length();
        if (line.at(cnt) == '#')
            trees++;
        cnt =  cnt + 3;
    }
    cout << trees << endl;

    // part 2
    ifstream myfile2("C:/Users/alesk/Desktop/AoC_2021/AoC_D3/AoC_D3_p1.txt");
    string line2;
    Strategy slopes[] = { {1, 1, 0}, {3, 1, 0}, {5, 1, 0}, {7, 1, 0}, {1, 2, 0} };
    int cntRow = 1;

    myfile2 >> line2;
    while (myfile2 >> line2)
    {
        for (auto& it : slopes)
            if (it.down == 1 || cntRow % it.down == 0)
                if (line2[(cntRow / it.down * it.right) % line2.size()] == '#')
                    it.trees++;
        cntRow++;
    }

    int treesProduct = 1;
    for (auto& it : slopes)
        treesProduct = treesProduct * it.trees;

    cout << treesProduct << endl;

    return 0;
}
