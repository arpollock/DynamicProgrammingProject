//
// Created by Alex Pollock on 2019-03-17.
//

#include "OptData.h"

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

