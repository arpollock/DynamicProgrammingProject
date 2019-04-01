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
    vector<int> rebootDays;
};


#endif //DYNAMICPROGRAMMINGPROJECT_DPSOLUTION_H
