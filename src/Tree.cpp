/* 
 * PARTH BHOIWALA
 * CMPSC 122
 * SPRING 2015
 * PROF. WINSLOW
 * APRIL 3, 2015
 */


#include "Tree.h"
#include "Tree2.h"      // <-- Useless
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <basetsd.h>
#include <ctype.h>

//#define DEBUG   /// This Displays The Debugging Code. You can turn it OFF by commenting it out


using namespace std;

Tree::Tree() {    
    root = NULL;                /// set root to NULL
    if(!dataFile.is_open()){ dataFile.open(fileLocation, fstream::app); }  /// Open the text files
    if (!resultFile.is_open()) { resultFile.open(resultLocation, fstream::app);}
    if (!dataFileRead.is_open()) {dataFileRead.open(fileLocation, fstream::app);}
}


void Tree::loadFile() {
    
    string trash;
#ifdef DEBUG
    cout << " entered loadFile " << endl;
#endif
    //    carInfo myOldCar;    
    if(dataFileRead.fail()) {
   // cerr << " ERROR: Unable to Open File '" << fileLocation << "' " << endl; }  /// Error if can't open file
        }
    else{
        
    while (!dataFileRead.eof())
    {   
       carInfo myOldCar; 
#ifdef DEBUG
       cout << " in while " << endl;
#endif
       getline(dataFileRead, myOldCar.nameCar, ',');        /// Reads Car's Name from file
//        getline(dataFileRead, trash, ' ');
        myOldCar.nameCar = lowerCase(myOldCar.nameCar);     
#ifdef DEBUG
       cout << " got the name " << myOldCar.nameCar << endl;
#endif  
        getline(dataFileRead, myOldCar.attribute, '\n');
        myOldCar.attribute = lowerCase(myOldCar.attribute);     /// Reads All Attributes from line
#ifdef DEBUG
       cout << " all attrs are :" << myOldCar.attribute << endl;
#endif  
        string attrOne;
      
        do{ 
            attrOne = myOldCar.attribute.substr(0, myOldCar.attribute.find(","));       /// Separates each attribute
#ifdef DEBUG
            cout << " piece: " << attrOne << endl;    
#endif 
            myOldCar.VecAttribute.push_back(attrOne); 
            myOldCar.attribute.erase(0, attrOne.length()+1);
#ifdef DEBUG
            cout << " after erasing, what's left is " << myOldCar.attribute << endl;
#endif          
        }while(attrOne.length() != 0);
        
        myVec.push_back(myOldCar);          /// Inserts it into myVec
        insertCar(root, myOldCar);          /// Inserts it into BST
    }   
#ifdef DEBUG
    for (int i=0; i<myVec.size(); i++)
    {
        cout << endl << " Car is " << myVec[i].nameCar << endl;
        cout << endl << " myVec[i].VecAttribue[j] has: " << endl;
        //cout << endl << " int i = " << i << endl;
        for (int j=0; j<myVec[i].VecAttribute.size(); j++)
        {
        cout << myVec[i].VecAttribute[j] << ", "; 
        }
    
    } 
#endif
    }
}


void Tree::askInfo()
{
    carInfo myNewCar;
    cout << endl;
    cout << " ******************************" << endl;
    cout << "        *** ADD MODE ***       " << endl;
    cout << endl; 
    dataFile << endl;
     cout << " Enter the name of the Car: ";    /// Get the name of the car
    cin.ignore();
    //cin >> newCar;
    getline(cin, myNewCar.nameCar);//, '\n');  
    dataFile << myNewCar.nameCar << ",";   /// Output it to the file
    //myNewCar.border = "*";
    myNewCar.nameCar = lowerCase(myNewCar.nameCar); /// Store it in struct
    
    //insertCar(root, myNewCar.nameCar);
    //Print(dataFile, root);
    
    cout << " Enter it's attributes: " << endl;  /// Get its attributes
    //TreeNode* ptrToName;
    //ptrToName = myNewCar.nameCar;
    do{
        //cin.ignore(); 
    cout << "                        ";
        getline(cin, myNewCar.attribute);
        dataFile << myNewCar.attribute << ",";               
        myNewCar.attribute = lowerCase(myNewCar.attribute); 
                   //insertAttribute(root, myNewCar.attribute);          
                   //insertCar(root, myNewCar.attribute); 
        myNewCar.VecAttribute.push_back(myNewCar.attribute); /// Store it into the vector of attributes
         
    }while(!myNewCar.attribute.empty()); /// Loop Until until hits 'endline'
     myVec.push_back(myNewCar);     /// vector push_back
    
    insertCar(root, myNewCar);  /// Call the Function that can insert the struct into a Binary Search Tree

    
 #ifdef DEBUG   
    cout << " myVec[i].VecAttribue[j] has: " << endl;
    
    for (int i=0; i<myVec.size(); i++)
    {
        cout << endl << " int i = " << i << endl;
        for (int j=0; j<myVec[i].VecAttribute.size(); j++)
        {
        cout << myVec[i].VecAttribute[j] << ", "; 
        }
    } 
#endif
    cout << "    Car Successfully Added!    " << endl;
    cout << " ******************************" << endl;
   // cout << endl;
    cout << endl;
}



void Tree::insertCar(TreeNode*& tree, carInfo myNewCar2)    /// Enters the struct in to BST, takes in root ptr as ROOT
{
#ifdef DEBUG
    cout << " insertCar is called" << endl;  
#endif
  if (tree == NULL)
  {                                     /// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;                /// Set left & right pointer to NULL
    tree->left = NULL;
  //tree->info = newnode->info;
    tree->info = myNewCar2.nameCar;   /// Set the node as the Name of Car (CheckAutoFunction)
    
 //   dataFile << tree->info << ", " ;
#ifdef DEBUG
    cout << " just inserted " << tree->info << " into the BST " << endl;
#endif
  }
  else if (myNewCar2.nameCar < tree->info)      /// If Car's Name is Smaller than node
  { 
      insertCar(tree->left, myNewCar2);    /// Insert in left subtree
  }
  else                                          /// If Car's Name is Greater than node
  {
      insertCar(tree->right, myNewCar2);   /// Insert in right subtree
  }
  
}

void Tree::preCheck()                    /// SEARCH MODE
{
    string lookFor;                 /// Car to look for in checkAuto
    bool terminate;                 /// Terminate Search Mode if hasfeature has only one car left
    cout << endl;
    cout << " ******************************" << endl;
    cout << "      *** SEARCH MODE ***      " << endl;
   
    cout << " Name of the Search: ";        /// Title of Search
    cin.ignore();
    getline(cin, nameOfSearch);
    resultFile << endl << " TITLE: " << nameOfSearch << endl << endl;
    // cin >> nameOfSearch;
    
    while (true)                    /// Remain in Search Mode until it is terminated or user choses to quit
    {
    cout << endl;
    cout << " How do you want to search? " << endl;
    cout << " 'CheckAuto' or 'HasFeatures' or 'Show' or 'Exit') : ";
    //cin.ignore();
    getline(cin, searchChoice);
    //cin >> searchChoice;
    searchChoice = lowerCase(searchChoice);
    
    if (searchChoice == "exit" || searchChoice == "quit")   /// Exit Search Mode if user wants to
    {
        reset();
        break;
    }    
    
    else if (searchChoice == "checkauto")           /// Call CheckAuto
    {        
     cout << " Car's Name:  ";                  /// Ask for Car to look for
    //cin.ignore();
    getline(cin, lookFor);
    lookFor = lowerCase(lookFor);           
        
    checkAuto(root, lookFor);           
    //checkAuto(ptrToSearch, lookFor);          /// <- Useless
    }
    else if (searchChoice == "hasfeatures" || searchChoice == "hasfeature")         /// Call hasFeature
    {
     terminate = hasFeature();                          /// Terminate 'Search mode' if hasFeature return False
     if (terminate == false) { 
         reset();
     break; }     
    }
    else if (searchChoice == "show" || searchChoice == "Show")          /// Show Cars that currently match criteria
    {
        show();
    }
    
    else
    {
        cout << " Invalid Entry " << endl;          /// Display this if User's entry is invalid
    }
    
    } // Exit While    
    
    
     cout << " ******************************" << endl;
}



bool Tree::hasFeature()
{
    cout << " Feature: ";               /// Ask for feature to look for
    //cin.ignore();
    getline(cin, hFeature);
    hFeature = lowerCase(hFeature);
#ifdef DEBUG
     cout << " hFeature i have is " << hFeature << endl;
     cout << " size of myVec is " << myVec.size() << endl;
#endif
    
  
  for (int i=0; i <myVec.size();/*i++*/)    /// Loop vector to check for feature
  {
#ifdef DEBUG
  cout << " I am in first for loop" << endl; 
#endif
      bool found = false;
       for ( int j=0; j< myVec[i].VecAttribute.size(); j++)   /// check every attribute
        {
#ifdef DEBUG  
   cout << " Now I am in second for loop looking at - " << myVec[i].VecAttribute[j] << endl; 
#endif
           if (hFeature == myVec[i].VecAttribute[j] && !found) /// set found to true if feature is found
            {
                found = true;                
#ifdef DEBUG
        cout << " hFeature " << hFeature << " == myVec[i].VecAttribute[j] " << myVec[i].VecAttribute[j] << endl; 
#endif
                //break;
                //  myVec[i].VecAttribute.erase(myVec[i].VecAttribute.begin(), myVec[i].VecAttribute.begin()+j);
               // myVec[i].VecAttribute.erase(myVec[i].VecAttribute.begin()+j);
                //break;
            } 
            
        }
        if (found == false)         /// Erase the element (car) if it doesn't have the feature
        {
            myVec.erase(myVec.begin()+i);
            // myVec[i].VecAttribute.erase(myVec[i].VecAttribute.begin()+i);
#ifdef DEBUG
            cout <<  "myVec's size is " << myVec.size() << endl;
#endif
        }
        else
        { i++;}     /// increment the loop
    }
   
  if (myVec.size() == 1)        /// If only 1 car has the feature, display it and return False
  {
      cout << endl;
      cout << " CONGRATULATIONS !!! Car Found !!! " << endl;
      resultFile << " CONGRATULATIONS !!! Car Found !!! " << endl;
      cout << " Car Name: " << myVec[0].nameCar << " Is Your Car " << endl;
      resultFile << " Car Name: " << myVec[0].nameCar << " Is Your Car " << endl;
      cout << " Attributes: " << endl;
      resultFile << " Attributes: " << endl;
      for (int i=0; i<myVec[0].VecAttribute.size(); i++)
      {
          cout << " " << myVec[0].VecAttribute[i] << endl;
          resultFile << " " << myVec[0].VecAttribute[i] << endl;
      }
      return false; // False means there is no more cars to search = TERMINATE
  }
  else 
  {
      return true; // True means there is MORE cars to search = DON'T TERMINATE
  }
    
  
  
  
  // BELOW IS SOME TRASH CODE -- PLEASE IGNOTE THIS 
     
    /*for (int i=0; i<myVec.size(); i++) // go through the vector 
    {
        for (int j=0; j< myVec[i].VecAttribute.size(); j++)
        {
           if (hFeature == myVec[i].VecAttribute[j])
           {
               searchCars.nameCar = myVec[i].nameCar;
               for (int k=0; k <myVec[i].VecAttribute.size(); k++)
               {
                   searchCars.attribute = myVec[i].VecAttribute[k];
                   matchingCars.push_back(searchCars);
               }
               // break;
           }
        }
       
    }*/

    
    
   /* for (int i = 0; i<myVec.size(); i++)
   {
    if (hFeature != myVec[i].attribute)
    {
        myVec.erase(myVec.begin()+i);
        i--;
    }
   }*/
    
    
    /*for (int i=0; i<myVec.size(); i++) // go through the vector 
    {
       if (hFeature == myVec[i].attribute)
       {
           iF = find(myVec.begin(), i, "*" );
           iB = find(i, myVec.end(), "*");
           ITf = distance(myVec.begin(), iF);
           ITb = distance(myVec.begin(), iB);
           for (int j=ITf; j<ITb; j++)
           {
               searchCars.attribute = myVec[j].attribute;
               matchingCars.push_back(searchCars);
           }
           
       }
       
   }*/
}


void Tree::checkAuto(TreeNode*& tree, string lookFor)      /// CheckAuto - Uses Binary Search Tree to look up the Car
{
    if (tree != NULL)
    {
    if (tree->info == lookFor)      /// if car's name matches
    {
        
#ifdef DEBUG
        cout << " This is working" << endl;
#endif
        // SOME OTHER TRASH CODE BELOW
        /* for (int i=0; i<matchingCars.size(); i++)
        {
            cout << VecAttribute[i] << endl;
        }*/
        
        bool displayedIt = false;
        for (int i=0; i<myVec.size(); i++)          /// display its attributes
        {
            if (lookFor == myVec[i].nameCar)
            {
                resultFile << endl << " CheckAuto: " << endl << lookFor << endl;
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
            cout << " Car Not Found " << endl;
        }
    }
    else if (lookFor < tree->info)          /// else look at another node (smaller)
    {
        checkAuto(tree->left, lookFor);
    }
    else if (lookFor > tree->info)          /// else look at another node (greater)
    {
        checkAuto(tree->right, lookFor);
    }
    /*else if (tree == NULL)              /// <- Useless
    {
        cout << " ERROR 404: Tree Not Found " << endl;
      //  return;
    }*/
}
    else                                /// if car is not in system
    {
        cout << " Car not found in the System " << endl;
        //return;
    }
    
}


void Tree::show()           /// Displays the the Cars that match the search criteria
{
    
    if (myVec.empty())
    {
        cout << " Sorry! No Cars Match Your Search Criteria " << endl;
    }
    else{ 
        
    cout << " Cars that match your search criteria are: " << endl;
    resultFile << endl << " Show: " << endl << " Cars that match your search criteria are: " << endl;
    for (int i = 0; i < myVec.size(); i++)
    {
        cout << " " << i+1 << ".  " << myVec[i].nameCar << endl;
        resultFile << " " << i+1 << ".  " << myVec[i].nameCar << endl;
    }
    cout << endl;
    resultFile << endl;
    }
}


void Tree::reset()
{
    /// Before exiting Search Mode
    root = NULL;        /// Delete entire Tree (root is Now NULL)
    myVec.clear();      /// Delete entire vector (To Reset)
    loadFile();         /// Refill the attributes by reading everything from File
    /// So now everything is back to normal and updated.
}




string Tree::lowerCase(string lowerCase)            /// function that converts the string into lowercase
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
































// UNNECESSARY CODE
/*
void Tree::insertAttribute(TreeNode* tree, string something2)
{
    cout << " just went into insert attribute" << endl;
    if (tree == NULL)
  {                     // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = something2;
    dataFile << tree->info << ", ";
    cout << " just inserted " << something2 << endl;
  }
    else if (something2 < tree->info)
    insertAttribute(tree->left, something2);    // Insert in left subtree.
  else
    insertAttribute(tree->right, something2);   // Insert in right subtree.
}
*/

/*
void PrintTree(TreeNode* tree, std::ofstream& dataFile) 
// Prints info member of iems in tree in sorted order on outFile.
{
    
   if(!dataFile.is_open()){ dataFile.open(fileLocation, fstream::app); }
    if (tree != NULL)
  {
        cout << " now printing" << endl;
    PrintTree(tree->left, dataFile);   // Print left subtree.
    dataFile << tree->info << ", ";
    PrintTree(tree->right, dataFile);  // Print right subtree.
  }
}
void Tree::Print(ofstream& dataFile, TreeNode* tree)
// Calls recursive function Print to print iems in the tree.
{
  PrintTree(tree, dataFile);
}
*/

/* UNNECESSARY CODE
 
/*void Tree::readData(){
    
    inputFile.open(fileLocation);
    
    if(inputFile.fail()) {
       cout << " Cannot open file" << endl; }
    
    while (!inputFile.eof())
    {        
        getline(inputFile, nameOfCar, ',');
        getline(inputFile, attribute, '\n');
      //cout << " Name of Car: " << nameOfCar << endl;
      //cout << " Attributes: " << attribute << endl;
      cout << endl;
    }
    inputFile.close();
}*/