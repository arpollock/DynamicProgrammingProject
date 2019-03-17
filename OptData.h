//
// Created by Alex Pollock on 2019-03-17.
//

#ifndef DYNAMICPROGRAMMINGPROJECT_OPTDATA_H
#define DYNAMICPROGRAMMINGPROJECT_OPTDATA_H

#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

class OptData{
public:
    OptData(int days, vector<int> dayData, vector<int> sinceReboot);
    void printDataProcessed();
    void outputOptimalSolution();
private:
    void fillTable();
    int days;
    vector< vector<int> > dataProcessed;
    vector<int> dayData;
    vector<int> sinceReboot;

    vector<int> optimalSolution;

};

#endif //DYNAMICPROGRAMMINGPROJECT_OPTDATA_H
