//
// Created by Alex Pollock on 2019-03-31.
//

#include "DPSolution.h"

DPSolution::DPSolution(vector<int> dayData,vector<int> rebootData){
    this->dayData = dayData;
    this->rebootData = rebootData;
    vector<int> tempData(dayData.size()+1, -1);
    optValTable = tempData;
    vector<int> tempReboot(optValTable.size(), 0);
    rebootDays = tempReboot;
}

void DPSolution::findOptimalRebootSchedule(){
    int maxDataProc = recursiveFindMax(dayData.size());
    cout << maxDataProc << endl;traceback();

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

    rebootDays.at(days) = rebootOn;

    //cout << "Days: " << days << " DataProc: " << maxData << " Reboot on: " << rebootOn << endl;
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
    int days = dayData.size();
    int currRebootPosition = days;
    int j = days-rebootDays.at(currRebootPosition)-1;
    stack<int> toPrint;
    for( int i = days-1; i>=0; i--){
        // PRINT DEBUG:
        //cout << "CurrRebootPos: " << currRebootPosition << " i: " << i << " j: "<< j << endl;
        int dataProc = 0;
        if( rebootDays.at(currRebootPosition) == (i+1) ){ // a reboot day
            int newPos = rebootDays.at(currRebootPosition)-1;
            currRebootPosition = newPos;
            j = i-rebootDays.at(currRebootPosition)-1;
        }else{ // not a reboot day
            dataProc = min( dayData.at(i), rebootData.at(j) );
            j--;
        }
        toPrint.push(dataProc);
    }

    while(!toPrint.empty()){
        int ele = toPrint.top();
        toPrint.pop();
        cout << ele << " ";
    }
}