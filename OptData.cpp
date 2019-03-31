//
// Created by Alex Pollock on 2019-03-17.
//

#include "OptData.h"

void findOptimalRebootSchedule(int days, vector<int> dayData, vector<int> rebootData){
    int dataProcessed = recursiveFindMax(days, dayData, rebootData);
    cout << "*-*-*-*-*-*-*-*-*" <<endl;
    cout << dataProcessed << endl;
    cout << "*-*-*-*-*-*-*-*-*" <<endl;
    return;
}

int recursiveFindMax(int days, vector<int> dayData, vector<int> rebootData){
    if( days == 0 ){ // cannot process data on the 0th days
        return 0;
    }

    int maxData = 0;
    for(int i = 0; i <= days; i++){

        int currVal = recursiveFindMax(i-1, dayData, rebootData) + sumDaysLeft(i, days, dayData, rebootData);
        if(currVal > maxData){
            maxData = currVal;
        }

    }
    return maxData;
}

int sumDaysLeft(int lastRebootDayNum, int totDays, vector<int> dayData, vector<int> rebootData){
    int totDataProc = 0;
    for(int j = lastRebootDayNum+1; j<=totDays; j++){
        totDataProc += min( dayData.at(j-1), rebootData.at(j-lastRebootDayNum-1) );
    }
    return totDataProc;
}

void printDataProcessed(int days, vector<int> inputDayData, vector<int> inputSinceReboot){

    vector<int> dayData;
    vector<int> sinceReboot;
    sinceReboot.push_back(0);
    dayData.push_back(0);

    for(int i=1; i<=days;i++){
        dayData.push_back( inputDayData.at(i-1));

        sinceReboot.push_back( inputSinceReboot.at(i-1));
        cout<<" i: "<<i<<"   "<<dayData[i]<<"  "<<sinceReboot[i]<<endl;
    }

    //For the base case
    vector<int> optRow(days+1,0);
    vector<vector<int>> optSolution(days+1,optRow);

    // Opt Solution for a day is the previous day + data processed that day
    for (int i = 1; i <= days; i++){
        for (int j = 1; j <= days; j++){
            optSolution[i][j] = optSolution[j - 1][i - 1] + min(dayData[i],sinceReboot[j]); // Recurrence relation (O(n^2))
        }
    }



    for(int i=1; i<=days; i++){
        int value;
        int compare;
        vector<int> values;


        for(int k =1; k<=i-1;k++){
            values = optSolution[i-1];

            if(compare < values[k]){
                compare = values[k];
                optSolution[i][0] = compare;
                //       cout<< "value k is :"<<values[k]<<"    ";
            }
            //      cout<<endl;
            //        cout<<"value compare: "<<compare<<endl;
        }
        //        cout<<"test value size "<< values.size()<<endl;
        vector<int> col;

        for(int j=1;j<=i;j++){
            value = optSolution[i-1][j-1];

            // cout<<"   this is i-1,j-1:  " <<optSolution[i-1][j-1] <<endl;
            // col.push_back(max(compare,min(dayData[i],sinceReboot[j])+value));

            optSolution[i][j] =  max(optSolution[i][0],min(dayData[i],sinceReboot[j])+value);
            cout<< "This is the function optSolution: "<<optSolution[i][j] <<endl;//max(compare,min(dayData[i],sinceReboot[j])+value))<<endl;

        }


    }

    int maxx;
    int rebootday;
    for(int i =0; i<=days; i++)
    {

        if(maxx<optSolution[days][i])
        {
            maxx = optSolution[days][i];
            rebootday = i;
        }

    }

    cout<<endl;
    cout<<"OptSolution is : " << maxx<<"  in the day: "<< rebootday<<endl;

    vector<int> processdata(11);
    //processdata.push_back(0);

    for(int i=0;i<=10;i++)
    {
        if(i< rebootday){
            processdata[i]=(min(dayData[i],sinceReboot[i]));
        }
        if(i==rebootday){
            processdata[i]=0;
        }
        if(i> rebootday){
            processdata[i] = min(dayData[i],sinceReboot[i-rebootday]);
        }

    }


    for(int i=0;i<=days;i++){
        cout<<processdata[i]<<endl;
    }
}

OptData::OptData(int days, vector<int> dayData, vector<int> sinceReboot){
    this->days = days;
    // populate day 0 with 0 processing
    this->dayData.push_back(0);
    this->sinceReboot.push_back(0);
    for(int i=0; i<days;i++){
        this->dayData.push_back( dayData.at(i));
        this->sinceReboot.push_back( sinceReboot.at(i));
    }
    fillTable();
}

void OptData::fillTable(){
    // fill row i=0 with all 0s
    // represents reboot everyday case
    vector<int> rowZero;
    for(int j=0; j<= days; j++){
        rowZero.push_back(0);
    }
    dataProcessed.push_back(rowZero);
    // for all cells i>j-> -1 (black out)
    // fill all other cells with min(dayData_j, sinceReboot_i)
    for(int i=1; i<=days ; i++){
        vector<int> row;
        for(int j=0; j<= days; j++) {
            if(j<i){
                row.push_back(-1);
            }else{
                int minVal = min( dayData[j], sinceReboot[i] );
                row.push_back(minVal);
            }
        }
        dataProcessed.push_back(row);
    }

}

void OptData::printDataProcessed(){
    for(int i=0; i<dataProcessed.size() ; i++){
        for(int j=0; j< dataProcessed.at(i).size(); j++) {
            cout << setw(3) << dataProcessed[i][j] << "|";
        }
        cout << endl;
    }
}

void OptData::outputOptimalSolution(){
    int sum = 0;
    for(int ele: optimalSolution){
        sum += ele;
    }

    cout <<"Name outputfile (do not include .txt): ";
    string fromUser = "no_user_input";
    cin >> fromUser;

    string fileName = "dp_" + fromUser + ".txt";

    ofstream outfile(fileName);
    if(!outfile.is_open()){
        cerr << "Error opening output file" <<endl;
    }
    outfile << sum << endl;
    for(int ele: optimalSolution){
        outfile << ele << " " ;
    }
    outfile.close();
    return;

}

int OptData::amountProcessed(int i, int j, string r){

    if(traverseValues.count(r)>0) return traverseValues[r]; // already calculated case

    if(r==""){
        traverseValues.emplace(r,dataProcessed[i][j]);
    }else{
        string copyR = r;
        copyR.pop_back();
        traverseValues.emplace(r, dataProcessed[i][j]+traverseValues.at(copyR));
    }

    if(r.length()<dataProcessed.size()-1){
        //emplace for reset case
        traverseValues.emplace(r+'r', amountProcessed(0, j + 1, r + 'r')+dataProcessed[i][j]);
        //emplace for continue case
        traverseValues.emplace(r+'-', amountProcessed(i + 1, j + 1, r + '-')+dataProcessed[i][j]);
    }

    return traverseValues.at(r);
}

void OptData::findPossibleSolutions(){
    amountProcessed(0,0,"");
    traceback();
    outputOptimalSolution();

    // PRINT DEBUG
//    for(auto kv: traverseValues){
//        cout << kv.first << ": " << kv.second << endl;
//    }
//    cout <<endl;
//    for(auto kv: traverseValues){
//        if( kv.first.length() == days ){
//            cout << kv.first << ": " << kv.second << endl;
//        }
//    }
}


void OptData::traceback(){
    int maxV=-1;
    string maxKey="None Found";

    // find sequence with max result
    for(auto kv: traverseValues){
        if( kv.first.length() == days && kv.second>maxV ){ // only get full solution
            maxKey = kv.first;
            maxV = kv.second;
        }
    }

    // PRINT DEBUG
//    cout << "***** OPTIMAL SOLUTION *****" <<endl;
//    cout << maxKey<< ':'<<maxV<< endl;

    // convert string into data sequence
    int i = 0;
    for( int j = 0; j<maxKey.size();j++ ){
        if( maxKey.at(j)=='r' ){ // reset -> i=0
            i=0;
        }else{
            i++;
        }
        optimalSolution.push_back( dataProcessed[i][j+1] );
    }

    // PRINT DEBUG
//    for(int ele: optimalSolution){
//        cout << ele << " ";
//    }
}

