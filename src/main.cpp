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

    
    cout << "       BIENVENIDO AL PROGRAMA!" << endl;
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
    cout << " ¿Que le gustaria hacer? " << endl;
    cout << " 1 - Modo Agregar (add) " << endl;
    cout << " 2 - Modo Buscar (search) " << endl;
    cout << " 3 - Quit (quit)" << endl;
    cout << " Eleccion: ";
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
            cout << " ¡Entrada invalida! Intentelo de nuevo " << endl;
        }
    }
    
   
}
    
    
   
    
    return 0;
}

void displayInst()
{
    cout << "  Este programa tiene dos caracteristicas: " << endl;
    cout << "  ADD: Agregara informacion de su coche al archivo " << endl;
    cout << "  SEARCH: Buscara el mejor coche para usted " << endl;
    cout << "   ~ HASFEATURE: Buscar un coche por su atributo " << endl;
    cout << "   ~ CHECKAUTO: Buscar un coche por su nombre " << endl;
    cout << "   ~ SHOW: Mostrar los coches que coinciden con sus criterios" << endl;
    cout << "   ~ Estas funciones solo funcionaran en BUSCAR" << endl;
    cout << "  El menú de usuario aceptará 'palabras' y 'numeros'"  << endl;
    cout << "  El programa no distingue entre mayusculas y minusculas " << endl;

}