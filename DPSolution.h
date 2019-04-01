//
// Created by Alex Pollock on 2019-03-31.
//

#ifndef DYNAMICPROGRAMMINGPROJECT_DPSOLUTION_H
#define DYNAMICPROGRAMMINGPROJECT_DPSOLUTION_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <stack>

using namespace std;

void findOptimalRebootSchedule(int days, vector<int> dayData, vector<int> rebootData);
int recursiveFindMax(int days, vector<int> dayData, vector<int> rebootData);
int sumDaysLeft(int lastRebootDayNum, int totDays, vector<int> dayData, vector<int> rebootData);

class DPSolution {
public:
    DPSolution(vector<int> dayData,vector<int> rebootData);
    void findOptimalRebootSchedule();
private:
    int recursiveFindMax(int days);
    int sumDaysLeft(int lastRebootDayNum, int totDays);
    void traceback();
    vector<int> dayData;
    vector<int> rebootData;
    vector<int> optValTable;
    vector<int> rebootDays; // TODO: fix tracking & traceback logic
};


#endif //DYNAMICPROGRAMMINGPROJECT_DPSOLUTION_H
