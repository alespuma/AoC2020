#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct passport {
    string byr; string iyr; string eyr; string hgt;
    string hcl; string ecl; string pid; string cid;
};

passport resetPass(passport pass)
{
    pass.byr.clear();
    pass.cid.clear();
    pass.ecl.clear();
    pass.eyr.clear();
    pass.hcl.clear();
    pass.hgt.clear();
    pass.iyr.clear();
    pass.pid.clear();
    return pass;
}

passport setField(passport pass, string field, string val)
{
    if (field == "byr")
        pass.byr = val;
    if (field == "iyr")
        pass.iyr = val;
    if (field == "eyr")
        pass.eyr = val;
    if (field == "hgt")
        pass.hgt = val;
    if (field == "hcl")
        pass.hcl = val;
    if (field == "ecl")
        pass.ecl = val;
    if (field == "pid")
        pass.pid = val;
    if (field == "cid")
        pass.cid = val;
    return pass;
}

bool isValid(passport pass)
{
    return !(pass.byr.empty() || pass.iyr.empty() || pass.eyr.empty() || pass.hgt.empty() || pass.hcl.empty() || pass.ecl.empty() || pass.pid.empty());
}

bool isValidStrict(passport pass){
        if (!isValid(pass))
            return false;

        int temp = stoi(pass.byr);
        if (pass.byr.empty() || temp < 1920 || temp > 2002)
            return false;

        temp = stoi(pass.iyr);
        if (pass.iyr.empty() || temp < 2010 || temp> 2020)
            return false;

        temp = stoi(pass.eyr);
        if (pass.eyr.empty() || temp < 2020 || temp > 2030)
            return false;

        string jednotky = pass.hgt.substr(pass.hgt.size() - 2);
        int heightVal = stoi(pass.hgt);
        if (jednotky == "cm" && (heightVal < 150 || heightVal > 193))
            return false;
        if (jednotky == "in" && (heightVal < 59 || heightVal > 76))
            return false;
        if (jednotky != "cm" && jednotky != "in")
            return false;

        if (pass.hcl[0] != '#' || pass.hcl.size() != 7)
            return false;
        for (int i = 1; i < pass.hcl.size(); i++)
        {
            if (!((pass.hcl[i] >= 48 && pass.hcl[i] <= 57) || (pass.hcl[i] >= 97 && pass.hcl[i] <= 102)))
                return false;
        }

        if (pass.ecl != "amb" && pass.ecl != "blu" && pass.ecl != "brn" && pass.ecl != "gry" && pass.ecl != "grn" && pass.ecl != "hzl" && pass.ecl != "oth")
            return false;

        int digits = 0;
        for (int i = 0; i < pass.pid.size(); i++)
        {
            if (pass.pid[i] < 48 ^ pass.pid[i] > 57)
                return false;
            digits++;
        }
        if (digits != 9)
            return false;

        return true;
    }

int main()
{
    vector<passport> passports;
    passport currPassport;
    ifstream myfile("C:/Users/alesk/Desktop/AoC_2021/AoC_D4/AoC_D4_p1.txt");
    string line, fieldName, fieldVal;
    int index = 0;

    while(getline(myfile, line))
    {
        index = 0;
        if (line == "")
        {
            passports.push_back(currPassport);
            currPassport = resetPass(currPassport);
        }
        while (index < line.size())
        {
            fieldName = line.substr(index, 3);
            index += 4;
            fieldVal = "";
            while (line[index] != ' ' && index < line.size())
            {
                fieldVal += line[index];
                index++;
            }
            index++;
            currPassport = setField(currPassport, fieldName, fieldVal);
        }
    }
    passports.push_back(currPassport);
    myfile.close();

    //Part 1
    int validPass = 0;
    for (int i = 0; i < passports.size(); i++)
            if (isValid(passports[i]))
                validPass++;

    cout << validPass << endl;

    //Part 2
    int validPass2 = 0;
    for (int i = 0; i < passports.size(); i++)
            if (isValidStrict(passports[i]))
                validPass2++;
    cout << validPass2 << endl;
    return 0;
}
