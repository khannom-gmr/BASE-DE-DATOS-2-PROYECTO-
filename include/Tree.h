#ifndef TREE_H
#define	TREE_H

#include <string>
#include <fstream>
#include <vector>
#define fileLocation "tabdata.txt"
#define resultLocation "results.txt"

using namespace std;

struct TreeNode
    {
        string info;
        TreeNode* left;
        TreeNode* right;
    };

class Tree {    
public:
    Tree(); 
    
    struct tabInfo{
        string nameTab;
        string attribute;
        vector <string> VecAttribute;
    };
    vector <tabInfo> myVec;

    tabInfo searchTabs;  
    vector <tabInfo> matchingTabs; 

    ifstream dataFileRead;   
    ofstream dataFile;
    ofstream resultFile;  
  
    void insertTab(TreeNode*& tree, tabInfo myNewTab2);    
    
    void askInfo();
    
    void loadFile();
    
    void checkTab(TreeNode*& tree, string lookFor) ;
    
    bool hasFeature();

    void preCheck();
    
    void show();

    void reset();
    
   string lowerCase(string lowerCase);
   
    TreeNode* ptrToSearch;   
    TreeNode* root;          
    string lookFor;         
    string hFeature;       
    string nameOfSearch;     
    string searchChoice;   
       
    ~Tree();
private:
    TreeNode* passTree;
};

#endif
