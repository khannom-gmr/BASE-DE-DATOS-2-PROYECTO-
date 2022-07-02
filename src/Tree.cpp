#include "Tree.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <basetsd.h>
#include <ctype.h>

using namespace std;

Tree::Tree() {    
    root = NULL;
    if(!dataFile.is_open()){ dataFile.open(fileLocation, fstream::app); }
    if (!resultFile.is_open()) { resultFile.open(resultLocation, fstream::app);}
    if (!dataFileRead.is_open()) {dataFileRead.open(fileLocation, fstream::app);}
}

void Tree::loadFile() {
    
    string trash;
}

void Tree::askInfo()
{
    tabInfo myNewTab;
    cout << endl;
    cout << " ******************************" << endl;
    cout << "        *** MODO AGREGAR ***       " << endl;
    cout << endl; 
    dataFile << endl;
    cout << " Introduzca el nombre del tabla: ";
    cin.ignore();

    getline(cin, myNewTab.nameTab);
    dataFile << myNewTab.nameTab << ",";

    myNewTab.nameTab = lowerCase(myNewTab.nameTab);
    
    cout << " Introduzca sus atributos: " << endl;
    do{
    cout << "                        ";
        getline(cin, myNewTab.attribute);
        dataFile << myNewTab.attribute << ",";               
        myNewTab.attribute = lowerCase(myNewTab.attribute); 

        myNewTab.VecAttribute.push_back(myNewTab.attribute); 
         
    }while(!myNewTab.attribute.empty());
     myVec.push_back(myNewTab);
    
    insertTab(root, myNewTab);

    cout << "    Tabla agregada con exito!    " << endl;
    cout << " ******************************" << endl;
    cout << endl;
}

void Tree::insertTab(TreeNode*& tree, tabInfo myNewTab2)
{
    if (tree == NULL)
    {   
        tree = new TreeNode;
        tree->right = NULL; 
        tree->left = NULL;

        tree->info = myNewTab2.nameTab;
    }
    else if (myNewTab2.nameTab < tree->info)
    { 
        insertTab(tree->left, myNewTab2);
    }
    else  
    {
        insertTab(tree->right, myNewTab2);
    }
}

void Tree::preCheck()
{
    string lookFor;
    bool terminate;
    cout << endl;
    cout << " ******************************" << endl;
    cout << "      *** MODO DE BUSQUEDA ***      " << endl;
   
    cout << " Nombre de la busqueda: ";
    cin.ignore();
    getline(cin, nameOfSearch);
    resultFile << endl << " TITULO: " << nameOfSearch << endl << endl;
    
    while (true)
    {
        cout << endl;
        cout << " ¿Como quiere buscar? " << endl;
        cout << " 'checkTab' o 'HasFeatures' o 'Show' o 'Exit') : ";
        getline(cin, searchChoice);

        searchChoice = lowerCase(searchChoice);
        
        if (searchChoice == "exit" || searchChoice == "quit")
        {
            reset();
            break;
        }    
        
        else if (searchChoice == "checkTab")
        {        
        cout << " Nombre de la tabla:  "; 
        getline(cin, lookFor);
        lookFor = lowerCase(lookFor);           
            
        checkTab(root, lookFor);           
        }
        else if (searchChoice == "hasfeatures" || searchChoice == "hasfeature") 
        {
            terminate = hasFeature();  
            if (terminate == false) { 
                reset();
                break; 
            }     
        }
        else if (searchChoice == "show" || searchChoice == "Show") 
        {
            show();
        }
        
        else
        {
            cout << " Entrada invalida " << endl;
        }
    
    } 
    cout << " ******************************" << endl;
}

bool Tree::hasFeature()
{
        cout << " Caracteristica: ";
        getline(cin, hFeature);
        hFeature = lowerCase(hFeature);
    
    
    for (int i=0; i <myVec.size();) 
    {
        bool found = false;
        for ( int j=0; j< myVec[i].VecAttribute.size(); j++)
        {
            if (hFeature == myVec[i].VecAttribute[j] && !found)
                {
                    found = true;                
                } 
            
        }
        if (found == false)
        {
            myVec.erase(myVec.begin()+i);
        }
        else{
            i++;
        }  
    }  
    
    if (myVec.size() == 1)
    {
        cout << endl;
        cout << " ¡¡¡FELICIDADES!!! ¡¡¡tabla encontrada!!! " << endl;
        resultFile << " ¡¡¡FELICIDADES!!! ¡¡¡tabla encontrada!!! " << endl;
        cout << " Nombre del tabla: " << myVec[0].nameTab << " Es su tabla " << endl;
        resultFile << " Nombre del tabla: " << myVec[0].nameTab << " Es su tabla " << endl;
        cout << " Attributes: " << endl;
        resultFile << " Attributes: " << endl;
        for (int i=0; i<myVec[0].VecAttribute.size(); i++)
        {
            cout << " " << myVec[0].VecAttribute[i] << endl;
            resultFile << " " << myVec[0].VecAttribute[i] << endl;
        }
        return false;
    }
    else 
    {
        return true;
    }
}

void Tree::checkTab(TreeNode*& tree, string lookFor) 
{
    if (tree != NULL)
    {
        if (tree->info == lookFor) 
        {
            bool displayedIt = false;
            for (int i=0; i<myVec.size(); i++) 
            {
                if (lookFor == myVec[i].nameTab)
                {
                    resultFile << endl << " checkTab: " << endl << lookFor << endl;
                    cout << " Attributes: " << endl;
                    
                    for (int j=0; j< myVec[i].VecAttribute.size(); j++)
                    {
                        cout << "             ";
                        cout << myVec[i].VecAttribute[j] << endl;
                        resultFile << myVec[i].VecAttribute[j] << endl;
                    }
                    displayedIt = true;
                    break;
                }
            }
            
            if (!displayedIt) 
            {
                cout << " Tabla no encontrada " << endl;
            }
        }
        else if (lookFor < tree->info)
        {
            checkTab(tree->left, lookFor);
        }
        else if (lookFor > tree->info) 
        {
            checkTab(tree->right, lookFor);
        }
    }
    else  
    {
        cout << " tabla no encontrada en el Sistema " << endl;
    }
    
}


void Tree::show()
{
    if (myVec.empty())
    {
        cout << " ¡Lo sentimos! No hay tablas que coincidan con sus criterios de busqueda " << endl;
    }
    else{ 
        
    cout << " Los tablas que coinciden con sus criterios de busqueda son: " << endl;
    resultFile << endl << " Show: " << endl << " Los tablas que coinciden con sus criterios de busqueda son: " << endl;
    for (int i = 0; i < myVec.size(); i++)
    {
        cout << " " << i+1 << ".  " << myVec[i].nameTab << endl;
        resultFile << " " << i+1 << ".  " << myVec[i].nameTab << endl;
    }
    cout << endl;
    resultFile << endl;
    }
}


void Tree::reset()
{
    root = NULL;
    myVec.clear();
    loadFile();
}

string Tree::lowerCase(string lowerCase) 
{    
    for (int i=0; i<lowerCase.length(); i++)
    {
        lowerCase[i] = tolower(lowerCase[i]);
    }
    return lowerCase;
}

Tree::~Tree(){
    dataFile.close();
    delete root;
}
