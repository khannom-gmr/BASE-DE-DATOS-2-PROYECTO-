#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Tree.h"
#include <ctype.h>


using namespace std;
void displayInst();


/* INFORMACIÓN IMPORTANTE PARA EL CLIENTE/USUARIO
 *
  --> Si elige cargar su archivo de texto, entonces asegúrese de que no tenga un espacio 
 * después de la coma. Si tiene un espacio después de la coma entonces la función getline 
 * no obtendrá los datos correctamente y causará un error en el modo de búsqueda.
 * 
  --> La clase llamada "Tree2.cpp" y "Tree2.h" no hacen nada. Así que ignóralos.
 *    
 * 
  --> Hay un montón de código inútil que he comentado. También ignóralos.
 * Los llamo código basura. No los he borrado porque podrían ser útiles algún día.
 *  
  --> Todos los comentarios que describen mi código comienzan con 3 barras '///'
 * 
 */



int main(int argc, char** argv) {

    
    cout << "       BIENVENIDO AL PROGRAMA!" << endl;
    displayInst();
    
    
    
   string menuChoice = "0"; 
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