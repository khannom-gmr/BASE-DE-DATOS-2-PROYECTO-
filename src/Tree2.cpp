#include "Tree2.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

Tree2::Tree2() {
    vector<carInfo>myVec;
   
}

void Tree2::functionAdd()
{
    if(!dataFile.is_open()){ dataFile.open(fileLocation, fstream::app); }

    cout << endl << " *** AGREGAR ***" << endl;
    dataFile << endl;
    
    
    myVec.push_back(mycar1);
   /* cout << " Enter the Name of Car:  ";
                            cin.ignore();
                    //        counter = counter + 1;
    getline(cin, mycar1.nameOfCar);
   //carInfo[counter] = carName;
    dataFile << mycar1.nameOfCar << ", ";
    
    
    cout << " Enter its attributes:  " << endl;*/
    
    bool firstTime = true;
    do{
        if (firstTime){
        cout << " Introduzca el nombre del coche:  ";
        cin.ignore();
        getline(cin, mycar1.nameOfCar);
        dataFile << mycar1.nameOfCar << ", ";
        cout << " Introduzca sus atributos:  " << endl; }
        
        getline(cin, mycar1.attribute);        
        dataFile << mycar1.attribute << ", ";
        myVec.push_back(mycar1);
        firstTime = false;
    }while(!mycar1.attribute.empty());
   
    cout << " Coche agregado con exito al sistema " << endl;
    cout << " myVec's size is " << myVec.size() << endl;
    
}

void Tree2::hasFeature()
{
     cout << " myVec's size is " << myVec.size() << endl;
     cout << " Tiene la característica: ";
     cin >> hFeature;
    for (int i=0; i<myVec.size(); i++)
    {
   
    if (myVec[i].attribute == hFeature)
    {
       foundCar = myVec[i].nameOfCar;
    
    cout << " " << foundCar << " tiene esta caracteristica" << endl;
    
    }
    }
    
}