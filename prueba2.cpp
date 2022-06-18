#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>


using namespace std;

struct Nodo {
    string dato;
    Nodo* der;
    Nodo* izq;
    Nodo* padre;
};

void menu();
Nodo *crearNodo(string,Nodo*);
void insertarNodo(Nodo*&, string,Nodo*);
bool busqueda(Nodo*, string);
void preOrden(Nodo*);
void inOrden(Nodo*);
void postOrden(Nodo*);
void eliminar(Nodo*, string);
void eliminarNodo(Nodo*);
Nodo* minimo(Nodo*);
void reemplazar(Nodo*, Nodo*);
void destruirNodo(Nodo*);
Nodo* arbol = NULL;

int main()
{
    menu();
}
//Función del menu
void menu() {
    int opcion;
    string dato;

    do {
        cout << "\t.:MENU:." << endl;
        cout << "1.Insertar un nuevo nodo" << endl;
        cout << "2.Buscar un elemento en el arbol" << endl;
        cout << "3.Recorrer el arbol en PreOrden" << endl;
        cout << "4.Recorrer el arbol en InOrden" << endl;
        cout << "5.Recorrer el arbol en PostOrden" << endl;
        cout << "6.Eliminar un nodo del arbol" << endl;
        cout << "7.Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese el dato: ";
            cin >> dato;
            insertarNodo(arbol, dato,NULL);
            cout << "\n";
            break;
        case 2:
            cout <<"\n" <<"Introduce el dato que estas buscando ";
            cin >> dato;
            if (busqueda(arbol, dato) == true) {
                cout << "\n" << "El elemento " << dato << " si se encuentra en el arbol" << endl;
            }
            else {
                cout << "\n" << "El elemento " << dato << " no se encuentra en el arbol" << endl;
            }
           
            break;
        case 3:
            cout << "\nRecorrido en PreOrden: " << endl;
            preOrden(arbol);
            cout << "\n\n";
            break;
        case 4:
            cout << "\nRecorrido en InOrden: " << endl;
            inOrden(arbol);
            cout << "\n\n";
            break;
        case 5:
            cout << "\nRecorrido en PostOrden: " << endl;
            postOrden(arbol);
            cout << "\n\n";
            break;
        case 6:
            cout << "\nDigite el numero que desea eliminar:";
            cin >> dato;
            eliminar(arbol, dato);
            cout << "\n";
            break;
        }
    }while (opcion != 7);
    
}
//Función para crear un nuevo nodo
Nodo* crearNodo(string n,Nodo* padre) {
    Nodo* nuevo_nodo = new Nodo();

    nuevo_nodo->dato = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->padre = padre;

    return nuevo_nodo;
}
//Función para insertar nodos en el árbol
void insertarNodo(Nodo *&arbol, string n,Nodo*padre) {
    if (arbol == NULL) { //Si el arbol está vacío
        Nodo *nuevo_nodo = crearNodo(n,padre);
        arbol = nuevo_nodo;
    }
    else { // Si el arbol tiene un nodo o más
        string valorRaiz = arbol->dato; // Obtener valor de la raíz
        if (n < valorRaiz) {
            insertarNodo(arbol->izq, n,arbol);
        }
        else {
            insertarNodo(arbol->der, n,arbol);
        }
    }
}
// Función para buscar un dato en el arbol
bool busqueda(Nodo* arbol, string n) {
    if (arbol == NULL) {
        return false;
    }
    else if (arbol->dato == n){
        return true;
    }
    else if (n <arbol->dato) {
        return busqueda(arbol->izq, n);
    }
    else {
        return busqueda(arbol->der, n);
    }
}
// Funcion para recorrido en profundidad - PreOrden
void preOrden(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    }
    else {
        cout << arbol->dato << " - ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}
// Funcion para recorrido en profundidad - InOrden
void inOrden(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    }
    else {
        inOrden(arbol->izq);
        cout << arbol->dato << " - ";
        inOrden(arbol->der);
    }
}
// Funcion para recorrido en profundidad - PostOrden
void postOrden(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    }
    else {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << arbol->dato << " - ";
    }
}
// Funcion para eliminar un nodo del arbol
void eliminar(Nodo* arbol, string n) {
    if (arbol == NULL) {
        return;
    }
    else if (n < arbol->dato) { //Si el valor es menor
        eliminar(arbol->izq, n); // Busca por la izquierda
    }
    else if (n > arbol->dato) { // Si el valor es mayor
        eliminar(arbol->der, n); //Busca por la derecha
    }
    else {
        eliminarNodo(arbol);
    }
}
// Funcion para eliminar el nodo encontrado
void eliminarNodo(Nodo* nodoEliminar) {
    if (nodoEliminar->izq && nodoEliminar->der) {
        Nodo* menor = minimo(nodoEliminar->der); // Primero te vas hacia la derecha
        nodoEliminar->dato = menor->dato;
        eliminarNodo(menor);
    }
    else if (nodoEliminar->izq) {
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }
    else if (nodoEliminar->der) {
        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }
    else { // No tiene hijos
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);
    }
}
// Función para determinar el nodo más izquierdo posible
Nodo* minimo(Nodo* arbol) {
    if (arbol == NULL) {
        return NULL;
    }
    if (arbol->izq) { // Si tiene hijo izquierdo
        return minimo(arbol->izq); // retorna el hijo izquierdo
    }
    else { // Si no tiene hijo izquierdo (significa que él es el más izquierdo)
        return arbol; // se retorna a sí mismo
    }
}
// Función para reemplazar dos nodos
void reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
    if (arbol->padre) {
        //arbol->padre hay que asignarle su nuevo hijo
        if (arbol->dato == arbol->padre->izq->dato) {
            arbol->padre->izq = nuevoNodo;
        }
        else if (arbol->dato == arbol->padre->der->dato) {
            arbol->padre->der = nuevoNodo;
        }
    }
    if (nuevoNodo) {
        // Procedemos a asignarle su nuevo padre
        nuevoNodo->padre = arbol->padre;
    }
}
// Función para destruir un nodo
void destruirNodo(Nodo* nodo) {
    nodo->izq = NULL;
    nodo->der = NULL;
    delete nodo;
}