//
// Created by Alex Pollock on 2019-03-31.
//

#include "DPSolution.h"

DPSolution::DPSolution(vector<int> dayData,vector<int> rebootData){
    this->dayData = dayData;
    this->rebootData = rebootData;
    vector<int> tempData(dayData.size()+1, -1);
    optValTable = tempData;
}

void DPSolution::findOptimalRebootSchedule(){
    int maxDataProc = recursiveFindMax(dayData.size());
    cout << maxDataProc << endl;
    traceback();
}

int DPSolution::recursiveFindMax(int days){
    if( days <= 0 ){ // cannot process data on the 0th day
        return 0;
    }

    int maxData = 0;
    int rebootOn = 0;
    for(int i = 0; i <= days; i++){
        int currVal = sumDaysLeft(i, days);

        if( optValTable.at(i) == -1 ){ // value has NOT been calculated before
            int calcVal = recursiveFindMax(i-1);
            optValTable.at(i) = calcVal;
        }
        currVal += optValTable.at(i);

        if(currVal > maxData){ // keep track of running max to return
            maxData = currVal;
            rebootOn = i;
        }
    } // end for loop

    if( rebootOn != 0 ){
        // rebootDays.clear(); // UNCOMMENT THIS LINE TO GET CORRECT SOLUTION
        // no clear gets right solution for two reboot case, clear gets right solution for implementation case
        // overall solution will come from identifying when a reboot is needed and when it isnt AFTER it is inserted (?)
        // clearing gets the right answer but I don't think it's right
        // will fail when opt solution is more than one reboot
        rebootDays.insert(rebootOn);
    }

    cout << "Days: " << days << " DataProc: " << maxData << " Reboot on: " << rebootOn << endl;
    return maxData;
}

int DPSolution::sumDaysLeft(int lastRebootDayNum, int totDays){
    int totDataProc = 0;
    for(int j = lastRebootDayNum+1; j<=totDays; j++){
        totDataProc += min( dayData.at(j-1), rebootData.at(j-lastRebootDayNum-1) );
    }
    return totDataProc;
}

void DPSolution::traceback(){
//    cout << "Reboot days: ";
//    for(int ele: rebootDays){
//        cout << ele << " " ;
//    }
//    cout << endl;

    int j = 0;
    for( int i = 0; i<dayData.size(); i++){
        int dataProc = 0;
        if( rebootDays.count(i+1) == 0 ){ // not a reboot day
            dataProc = min( dayData.at(i), rebootData.at(j) );
            j++;
        }else{
            j = 0;
        }
        cout << dataProc << " ";
    }
    cout << endl;
}