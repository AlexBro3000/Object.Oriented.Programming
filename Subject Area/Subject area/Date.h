#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

string getDate()
{
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    return asctime(timeinfo);
}

string strDate()
{
    string str = getDate();
    stringstream ss(str);
    string s1, s2, s3;

    getline(ss, s1, ':');
    getline(ss, s2, ':');
    getline(ss, s3, '\n');

    return s1 + "." + s2 + "." + s3;
}
