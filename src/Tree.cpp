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
    root = NULL;                /// establecer la raíz como NULL
    if(!dataFile.is_open()){ dataFile.open(fileLocation, fstream::app); }  /// Abrir los archivos de texto
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
     cout << " Introduzca el nombre del tabla: ";    /// Obtener el nombre del tabla
    cin.ignore();
    //cin >> newCar;
    getline(cin, myNewTab.nameTab);//, '\n');  
    dataFile << myNewTab.nameTab << ",";   /// Envíalo al archivo
    //myNewTab.border = "*";
    myNewTab.nameTab = lowerCase(myNewTab.nameTab); /// Guárdelo en la estructura
    
    //insertTab(root, myNewTab.nameTab);
    //Print(dataFile, root);
    
    cout << " Introduzca sus atributos: " << endl;  /// Obtener sus atributos
    //TreeNode* ptrToName;
    //ptrToName = myNewTab.nameTab;
    do{
        //cin.ignore(); 
    cout << "                        ";
        getline(cin, myNewTab.attribute);
        dataFile << myNewTab.attribute << ",";               
        myNewTab.attribute = lowerCase(myNewTab.attribute); 
                   //insertAttribute(root, myNewTab.attribute);          
                   //insertTab(root, myNewTab.attribute); 
        myNewTab.VecAttribute.push_back(myNewTab.attribute); /// Almacenarla en el vector de atributos
         
    }while(!myNewTab.attribute.empty()); /// Bucle hasta que llegue a 'endline'
     myVec.push_back(myNewTab);     /// vector push_back
    
    insertTab(root, myNewTab);  /// Llamar a la función que puede insertar la estructura en un árbol de búsqueda binario

    cout << "    Tabla agregada con exito!    " << endl;
    cout << " ******************************" << endl;
   // cout << endl;
    cout << endl;
}

void Tree::insertTab(TreeNode*& tree, tabInfo myNewTab2)    /// Introduce la estructura en el BST, toma el ptr raíz como ROOT
{
    if (tree == NULL)
    {                                     /// Lugar de inserción encontrada.
        tree = new TreeNode;
        tree->right = NULL;                /// Poner el puntero izquierdo y derecho en NULL
        tree->left = NULL;
        //tree->info = newnode->info;
        tree->info = myNewTab2.nameTab;   /// Establecer el nodo como el nombre del tabla (checkTabFunction)
        
        //   dataFile << tree->info << ", " ;
    }
    else if (myNewTab2.nameTab < tree->info)      /// Si el nombre del tabla es más pequeño que el nodo
    { 
        insertTab(tree->left, myNewTab2);    /// Insertar en el subárbol izquierdo
    }
    else                                          /// Si el nombre del tabla es mayor que el nodo
    {
        insertTab(tree->right, myNewTab2);   /// Insertar en el subárbol derecho
    }
}

void Tree::preCheck()                    /// SEARCH MODE
{
    string lookFor;                 /// tabla para buscar en checkTab
    bool terminate;                 /// Terminar el modo de búsqueda si a hasfeature sólo le queda un tabla
    cout << endl;
    cout << " ******************************" << endl;
    cout << "      *** MODO DE BUSQUEDA ***      " << endl;
   
    cout << " Nombre de la busqueda: ";        /// Título de la búsqueda
    cin.ignore();
    getline(cin, nameOfSearch);
    resultFile << endl << " TITULO: " << nameOfSearch << endl << endl;
    // cin >> nameOfSearch;
    
    while (true)                    /// Permanecer en el modo de búsqueda hasta que se termine o el usuario decida salir.
    {
        cout << endl;
        cout << " ¿Como quiere buscar? " << endl;
        cout << " 'showtab' o 'HasFeatures' o 'Show' o 'Exit') : ";
        //cin.ignore();
        getline(cin, searchChoice);
        //cin >> searchChoice;
        searchChoice = lowerCase(searchChoice);
        
        if (searchChoice == "exit" || searchChoice == "quit")   /// Salir del modo de búsqueda si el usuario quiere
        {
            reset();
            break;
        }    
        
        else if (searchChoice == "showtab")           /// Llamar a checkTab
        {        
        cout << " Nombre de la tabla:  ";                  /// Pregunte por el tabla para buscar
        //cin.ignore();
        getline(cin, lookFor);
        lookFor = lowerCase(lookFor);           
            
        checkTab(root, lookFor);           
        //checkTab(ptrToSearch, lookFor);          /// <- Useless
        }
        else if (searchChoice == "hasfeatures" || searchChoice == "hasfeature")         /// Llamar a hasFeature
        {
            terminate = hasFeature();                          /// Termina el 'Modo de búsqueda' si hasFeature devuelve False
            if (terminate == false) { 
                reset();
                break; 
            }     
        }
        else if (searchChoice == "show" || searchChoice == "Show")          /// Mostrar los tablas que actualmente coinciden con los criterios
        {
            show();
        }
        
        else
        {
            cout << " Entrada invalida " << endl;          /// Muestra esto si la entrada del usuario es inválida
        }
    
    } // Exit While    
    cout << " ******************************" << endl;
}

bool Tree::hasFeature()
{
        cout << " Caracteristica: ";               /// Pregunte por la característica a buscar
        //cin.ignore();
        getline(cin, hFeature);
        hFeature = lowerCase(hFeature);
    
    
    for (int i=0; i <myVec.size();/*i++*/)    /// Vector de bucle para comprobar la característica
    {
        bool found = false;
        for ( int j=0; j< myVec[i].VecAttribute.size(); j++)   /// comprobar cada atributo
        {
            if (hFeature == myVec[i].VecAttribute[j] && !found) /// establecer encontrada como verdadero si se encuentra la característica
                {
                    found = true;                
                    //break;
                    //  myVec[i].VecAttribute.erase(myVec[i].VecAttribute.begin(), myVec[i].VecAttribute.begin()+j);
                // myVec[i].VecAttribute.erase(myVec[i].VecAttribute.begin()+j);
                    //break;
                } 
            
        }
        if (found == false)         /// Borrar el elemento (tabla) si no tiene la característica
        {
            myVec.erase(myVec.begin()+i);
            // myVec[i].VecAttribute.erase(myVec[i].VecAttribute.begin()+i);
        }
        else{
            i++;   /// incrementar el bucle
        }  
    }  
    
    if (myVec.size() == 1)        /// Si sólo 1 tabla tiene la característica, la muestra y devuelve False
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
        return false; // Falso significa que no hay más tablas que buscar = TERMINAR
    }
    else 
    {
        return true; // Verdadero significa que hay MÁS tablas para buscar = NO TERMINAR
    }
}


void Tree::checkTab(TreeNode*& tree, string lookFor)      /// checkTab - Utiliza el árbol de búsqueda binario para buscar el tabla
{
    if (tree != NULL)
    {
        if (tree->info == lookFor)      /// si el nombre del tabla coincide con
        {
            bool displayedIt = false;
            for (int i=0; i<myVec.size(); i++)          /// mostrar sus atributos
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
        else if (lookFor < tree->info)          /// si no, mira otro nodo (más pequeño)
        {
            checkTab(tree->left, lookFor);
        }
        else if (lookFor > tree->info)          /// si no, mira otro nodo (mayor)
        {
            checkTab(tree->right, lookFor);
        }
    }
    else                                /// si el tabla no está en el sistema
    {
        cout << " tabla no encontrada en el Sistema " << endl;
        //return;
    }
    
}


void Tree::show()           /// Muestra los tablas que coinciden con los criterios de búsqueda
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
    /// Antes de salir del modo de búsqueda
    root = NULL;        /// Borrar todo el árbol (la raíz es ahora NULL)
    myVec.clear();      /// Borrar todo el vector (Para reiniciar)
    loadFile();         /// Rellenar los atributos leyendo todo desde el Archivo
    /// Así que ahora todo vuelve a la normalidad y se actualiza.
}

string Tree::lowerCase(string lowerCase)            /// que convierte la cadena en minúsculas
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
