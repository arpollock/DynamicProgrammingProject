#include <iostream>
#include <vector>
#include "OptData.h"

using namespace std;

int main() {

    int days = 4;

    vector<int> x;
    x.push_back(10);
    x.push_back(1);
    x.push_back(7);
    x.push_back(7);

    vector<int> s;
    s.push_back(8);
    s.push_back(4);
    s.push_back(2);
    s.push_back(1);

    OptData test(days, x, s);
    test.printDataProcessed();


    return 0;
}