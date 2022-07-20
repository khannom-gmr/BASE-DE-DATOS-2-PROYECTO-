#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Tree.h"
#include <ctype.h>

using namespace std;

void displayInst()
{
    cout << "  Este programa tiene dos caracteristicas: " << endl;
    cout << "  ADD: Agregara informacion de su tabla al archivo " << endl;
    cout << "  SEARCH: Buscara la tabla " << endl;
    cout << "   ~ HASFEATURE: Buscar una tabla por su atributo " << endl;
    cout << "   ~ CHECKTAB: Buscar una tabla por su nombre " << endl;
    cout << "   ~ SHOW: Mostrar las tablas que coinciden con sus criterios" << endl;
    cout << "   ~ Estas funciones solo funcionaran en BUSCAR" << endl;
    cout << "  El menu de usuario aceptara 'palabras' y 'numeros'"  << endl;
    cout << "  El programa no distingue entre mayusculas y minusculas " << endl;
}

int main(int argc, char** argv) {

    cout << "       BIENVENIDO AL PROGRAMA!" << endl;
    displayInst();
        
    string menuChoice = "0"; 
    Tree fcnCallerOld; //<- Esta es la clase que llama a las funciones
    
    fcnCallerOld.loadFile();
      
    while (menuChoice != "5" && menuChoice != "quit" && menuChoice != "exit" )
    {
        cout << endl << endl;
        cout << " ******************************" << endl;
        cout << " ~~~~~~~~~~~~ MENU ~~~~~~~~~~~~" << endl;
        cout << " ******************************" << endl;
        cout << endl;

        cout << " Que le gustaria hacer? " << endl;
        cout << " 1 - Modo Agregar (add) " << endl;
        cout << " 2 - Modo Buscar (search) " << endl;
        cout << " 3 - Modo Eliminar (delete) " << endl;
        cout << " 4 - Modo Actualizar (update) " << endl;
        cout << " 5 - Quit (quit)" << endl;
        cout << " Eleccion: ";
        cin >> menuChoice;
        menuChoice = fcnCallerOld.lowerCase(menuChoice);
        
        cout << endl;

        if (menuChoice == "1" || menuChoice == "add") // ADD A NEW TAB
        {        
            //fcnCaller.functionAdd();
            fcnCallerOld.askInfo();
        }
        else if (menuChoice == "2" || menuChoice == "search") // SEARCH
        {           //fcnCaller.hasFeature();
            fcnCallerOld.preCheck();
        }
        else if (menuChoice == "3" || menuChoice == "delete") // DELETE
        {
            string tableName;
            cout << " Ingrese en nombre de la tabla: ";
            cin >> tableName;
            fcnCallerOld.borrar(tableName);
        }
        else if (menuChoice == "4" || menuChoice == "update") // UPDATE
        {
            string tableName;
            cout << " Ingrese en nombre de la tabla: ";
            cin >> tableName;
            fcnCallerOld.actualizar(tableName);
        }
        else
        {
            if (menuChoice != "quit" && menuChoice != "exit" && menuChoice != "5")  /// Quit
            {
                cout << " ¡Entrada invalida! Intentelo de nuevo " << endl;
            }
        }
    }
    
    return 0;
}

