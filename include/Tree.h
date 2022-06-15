/* 
 * PARTH BHOIWALA
 * CMPSC 122
 * SPRING 2015
 * PROF. WINSLOW
 * APRIL 3, 2015
 */


#ifndef TREE_H
#define	TREE_H

#include <string>
#include <fstream>
#include <vector>
#define fileLocation "autodata.txt"
//#define fileLocation "D:\\CSc\\SPRING SEMESTER\\MID-TERM PROJECT\\CarDealerProgram\\autodata.txt"
#define resultLocation "results.txt"
using namespace std;

struct TreeNode         /// Makes the Binary Search Tree
    {
    string info;            /// Holds Name of Car
    TreeNode* left;         /// Left pointer
    TreeNode* right;        /// Right pointer
    };

class Tree {    
public:
    Tree();             /// Constructor
    
    struct carInfo{       /// store Car's info in struct
        string nameCar;
        string attribute;
       vector <string> VecAttribute;    /// All the attributes (size is unknown)
        //string attribute;        
    };
     vector <carInfo> myVec;
     
 //    vector <string> VecAttribute;
    // carInfo myNewCar;
     carInfo searchCars;                /// struct of carInfo type
     vector <carInfo> matchingCars;  /// <- Useless
    
    //string newCar;
    //string attribute;
    ifstream dataFileRead;                  /// File that stores info of cars "autodata.txt"
    ofstream dataFile;
    ofstream resultFile;                /// File for user "result.txt"
  
    void insertCar(TreeNode*& tree, carInfo myNewCar2);    
    /// Function: Inserts car's info into BST
    /// Pre: Tree is Empty
    /// Post: Tree holds car info in a form of BST
    
    void askInfo();
    /// Function: Ask User for Name of Car and its Attributes
    /// Pre: nothing
    /// Post: User enters Car's Info
    
    void loadFile();
    /// Function: Load the file if it exits
    /// Pre: Check if file exits
    /// Post: If so, then load data into data structure
    
    void checkAuto(TreeNode*& tree, string lookFor) ;
    /// Function: Uses BST to look for car's name
    /// Pre: BST is there, ask for car's name
    /// Post: Looks up the car and displays its attributes if found
    
    bool hasFeature();
    /// Function: Uses vectors to look for car's attributes (traverses entire structure)
    /// Pre: vector has data
    /// Post: eliminates cars that don't have that attribute
    
    void preCheck();
    /// Function: Enters search mode
    /// Pre: Ask user to call either of those functions
    /// Post: Call appropriate function
    
    void show();
    /// Function: Shows name of cars
    /// Pre: nothing
    /// Post: displays names of cars that match the criteria
    
    void reset();
    /// Function: Resets the structure before exiting search mode
    /// Pre: structure has been initialized
    /// Post: structure is reset & updated
    
   string lowerCase(string lowerCase);
   /// Function: Convert string to lowercase
   /// Pre: get the string
   /// Post: return converted lowercased string
    
   /// SOME TRASH CODE BELOW
   //void insertAttribute(TreeNode* tree, string something2);      
   //void Print(ofstream& dataFile, TreeNode* tree);     
   //void insertCar(TreeNode* tree, TreeNode* newnode);
   //void insertCar(TreeNode* tree, string something);
    
    TreeNode* ptrToSearch;      /// <- Useless
    TreeNode* root;             /// root node
    string lookFor;             /// look for car
    string hFeature;            /// feature to look for
    string nameOfSearch;        /// title of search
    string searchChoice;        /// search mode choice
    

 
    
    
    
    ~Tree();
private:
 
    //TreeNode* root;
    TreeNode* passTree; /// <- Useless
};

#endif	/* TREE_H */
