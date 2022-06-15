/* 
 * PARTH BHOIWALA
 * CMPSC 122
 * SPRING 2015
 * PROF. WINSLOW
 * APRIL 3, 2015
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Tree.h"
#include "Tree2.h"
#include <ctype.h>


using namespace std;
void displayInst();


/* IMPORTANT INFORMATION FOR THE CLIENT/USER
 *
  --> If you choose to load your text file, Then Make sure that it does not have a space 
 *    after the comma. If you do have a space after a comma then the getline function 
 *    won't get the data properly and will cause error in search mode.
 * 
  --> The class called "Tree2.cpp" and "Tree2.h" don't do anything. So Ignore Them.
 *    
 * 
  --> There's a lot of useless code that I've commented out. Also Ignore Them.
 *    I call them trash code. I didn't delete them b/c it might be useful someday.
 *  
  --> All comments that describe my code begin with 3 slashes '///'
 * 
 */



int main(int argc, char** argv) {

    
    cout << "      WELCOME TO THE PROGRAM!" << endl;
    displayInst();
    
    
    
   string menuChoice = "0"; 
   Tree2 fcnCaller;
   Tree fcnCallerOld;
   
   fcnCallerOld.loadFile();
   
   
   while (menuChoice != "3" && menuChoice != "quit" && menuChoice != "exit" )
{
    cout << endl << endl; 
    cout << " ******************************" << endl;
    cout << " ~~~~~~~~~~~~ MENU ~~~~~~~~~~~~" << endl;
    cout << " ******************************" << endl;
    cout << endl;
    cout << " What would you like to Do? " << endl;
    cout << " 1 - Add mode (add) " << endl;
    cout << " 2 - Search mode (search) " << endl;
    cout << " 3 - Quit (quit)" << endl;
    cout << " Choice: ";
    cin >> menuChoice;
    menuChoice = fcnCallerOld.lowerCase(menuChoice);
    
    cout << endl;
   
//    Tree2 fcnCaller;
    if (menuChoice == "1" || menuChoice == "add") // ADD A NEW CAR
    {        
        //fcnCaller.functionAdd();
        fcnCallerOld.askInfo();
    }
    else if (menuChoice == "2" || menuChoice == "search") // SEARCH
    {           //fcnCaller.hasFeature();
           fcnCallerOld.preCheck();
    }
    else
    {
        if (menuChoice != "quit" && menuChoice != "exit" && menuChoice != "3")  /// Quit
        {
            cout << " Invalid Entry! Try Again " << endl;
        }
    }
    
   
}
    
    
   
    
    return 0;
}

void displayInst()
{
    cout << "  This program has two features: " << endl;
    cout << "  ADD: Will add info of your car to the file " << endl;
    cout << "  SEARCH: Will search for the best car for you " << endl;
    cout << "   ~ HASFEATURE: Look up a car by its Attribute " << endl;
    cout << "   ~ CHECKAUTO: Look up a car by its Name " << endl;
    cout << "   ~ SHOW: Display cars that match your criteria" << endl;
    cout << "   ~ These functions will only work in SEARCH" << endl;
    cout << "  User Menu will accept 'words' and 'numbers'" << endl;
    cout << "  The program is Not Case Sensitive " << endl;

}