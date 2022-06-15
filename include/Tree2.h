/* 
 * PARTH BHOIWALA
 * CMPSC 122
 * SPRING 2015
 * PROF. WINSLOW
 * APRIL 3, 2015
 */


#ifndef TREE2_H
#define	TREE2_H

#include <string>
#include <fstream>
#include <vector>
#define fileLocation "autodata.txt"
//#define fileLocation "D:\\CSc\\SPRING SEMESTER\\MID-TERM PROJECT\\CarDealerProgram\\autodata.txt"
#define resultLocation "results.txt"
//#define arraySize 200

using namespace std;

struct carInfo{
    string nameOfCar;
    string attribute;    
};



class Tree2 {
public:
    Tree2();
   
    void functionAdd();
  //  string carInfo[arraySize];
    string carName;
    string attribute;
   // int counter = 1;
    ofstream dataFile;
    void hasFeature();
    string hFeature;
    carInfo mycar1; 
    vector <carInfo> myVec;
    string foundCar;
    
    
    //~Tree();
private:
  

};

#endif	/* TREE2_H */
