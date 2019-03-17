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
#include <string>
#include <map>

using namespace std;

class OptData{
public:
    OptData(int days, vector<int> dayData, vector<int> sinceReboot);
    void printDataProcessed();

    void findPossibleSolutions();
    int amountProcessed(int i, int j, string r);
    void traceback();

    void outputOptimalSolution();

private:
    void fillTable();
    int days;

    vector< vector<int> > dataProcessed;
    vector<int> dayData;
    vector<int> sinceReboot;

    map<string,int> traverseValues;

    vector<int> optimalSolution;

};

#endif //DYNAMICPROGRAMMINGPROJECT_OPTDATA_H
