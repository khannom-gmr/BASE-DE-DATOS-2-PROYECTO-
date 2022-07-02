#ifndef TREE_H
#define	TREE_H

#include <string>
#include <fstream>
#include <vector>
#define fileLocation "tabdata.txt"
#define resultLocation "results.txt"

using namespace std;

struct TreeNode         /// Hace el árbol de búsqueda binaria
    {
        string info;            /// Contiene el nombre de la tabla
        TreeNode* left;         /// Puntero izquierdo
        TreeNode* right;        /// Puntero derecho
    };

class Tree {    
public:
    Tree();             /// Constructor
    
    struct tabInfo{       /// almacenar la información de la tabla en la estructura
        string nameTab;
        string attribute;
        vector <string> VecAttribute;    /// Todos los atributos (el tamaño es desconocido)
        //string attribute;        
    };
     vector <tabInfo> myVec;
     
    // vector <string> VecAttribute;
    // tabInfo myNewCar;
     tabInfo searchTabs;                /// struct de tipo tabInfo
     vector <tabInfo> matchingTabs;  /// <- Useless
    
    //string newCar;
    //string attribute;
    ifstream dataFileRead;                  /// Archivo que almacena la información de las tablas "tabdata.txt"
    ofstream dataFile;
    ofstream resultFile;                /// Archivo para el usuario "result.txt"
  
    void insertTab(TreeNode*& tree, tabInfo myNewTab2);    
    /// Función: Inserta la información de la tabla en el BST
    /// Pre: El árbol está vacío
    /// Post: El árbol contiene la información de la tabla en forma de BST
    
    void askInfo();
    /// Función: Preguntar al usuario el nombre de la tabla y sus atributos
    /// Pre: nada
    /// Post: El usuario introduce la información de la tabla
    
    void loadFile();
    /// Función: Cargar el archivo si sale
    /// Pre: Comprobar si el archivo sale
    /// Post: Si es así, entonces carga los datos en la estructura de datos
    
    void checkTab(TreeNode*& tree, string lookFor) ;
    /// Función: Utiliza el BST para buscar el nombre de la tabla
    /// Pre: El BST está ahí, pregunta por el nombre de la tabla
    /// Post: Busca la tabla y muestra sus atributos si lo encuentra
    
    bool hasFeature();
    /// Función: Utiliza los vectores para buscar los atributos de la tabla (recorre toda la estructura)
    /// Pre: el vector tiene datos
    /// Post: elimina las tablas que no tienen ese atributo
    
    void preCheck();
    /// Función: Entra en el modo de búsqueda
    /// Pre: Pide al usuario que llame a cualquiera de esas funciones
    /// Post: Llama a la función apropiada
    
    void show();
    /// Función: Muestra el nombre de las tablas
    /// Pre: nada
    /// Post: muestra los nombres de las tablas que coinciden con los criterios
    
    void reset();
    /// Función: Restablece la estructura antes de salir del modo de búsqueda
    /// Pre: la estructura ha sido inicializada
    /// Post: la estructura se restablece y se actualiza
    
   string lowerCase(string lowerCase);
   /// Función: Convertir la cadena a minúsculas
   /// Pre: obtener la cadena
   /// Post: devuelve la cadena convertida a minúsculas
   
    TreeNode* ptrToSearch;      /// <- Useless
    TreeNode* root;             /// root node
    string lookFor;             /// buscar tabla
    string hFeature;            /// característica a buscar
    string nameOfSearch;        /// título de la búsqueda
    string searchChoice;        /// elección del modo de búsqueda
       
    ~Tree();
private:
    //TreeNode* root;
    TreeNode* passTree; /// <- Useless
};

#endif
