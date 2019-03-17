#include <iostream>
#include <vector>
#include "OptData.h"

using namespace std;

int main() {

    // EASY TEST CASE
    int easyDays = 4;
    vector<int> easyX;
    easyX.push_back(10);
    easyX.push_back(1);
    easyX.push_back(7);
    easyX.push_back(7);
    vector<int> easyS;
    easyS.push_back(8);
    easyS.push_back(4);
    easyS.push_back(2);
    easyS.push_back(1);
    OptData easyTest(easyDays, easyX, easyS);
    //easyTest.printDataProcessed();
    easyTest.findPossibleSolutions();

    // IMPLEMENTATION TEST CASE
    int impDays = 10;
    vector<int> impX;
    impX.push_back(20); // day 1
    impX.push_back(80); // day 2
    impX.push_back(20); // day 3
    impX.push_back(60); // day 4
    impX.push_back(20); // day 5
    impX.push_back(60); // day 6
    impX.push_back(80); // day 7
    impX.push_back(10); // day 8
    impX.push_back(40); // day 9
    impX.push_back(10); // day 10
    vector<int> impS;
    impS.push_back(100); // day 1
    impS.push_back(90); // day 2
    impS.push_back(50); // day 3
    impS.push_back(45); // day 4
    impS.push_back(40); // day 5
    impS.push_back(35); // day 6
    impS.push_back(20); // day 7
    impS.push_back(15); // day 8
    impS.push_back(10); // day 9
    impS.push_back(5); // day 10
    OptData impTest(impDays, impX, impS);
    //impTest.printDataProcessed();
    impTest.findPossibleSolutions();

    return 0;
}