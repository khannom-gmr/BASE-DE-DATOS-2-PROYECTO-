#ifndef TREE_H
#define	TREE_H

#include <string>
#include <fstream>
#include <vector>
#define fileLocation "autodata.txt"
#define resultLocation "results.txt"

using namespace std;

struct TreeNode         /// Hace el árbol de búsqueda binaria
    {
        string info;            /// Contiene el nombre del coche
        TreeNode* left;         /// Puntero izquierdo
        TreeNode* right;        /// Puntero derecho
    };

class Tree {    
public:
    Tree();             /// Constructor
    
    struct carInfo{       /// almacenar la información del coche en la estructura
        string nameCar;
        string attribute;
        vector <string> VecAttribute;    /// Todos los atributos (el tamaño es desconocido)
        //string attribute;        
    };
     vector <carInfo> myVec;
     
    // vector <string> VecAttribute;
    // carInfo myNewCar;
     carInfo searchCars;                /// struct de tipo carInfo
     vector <carInfo> matchingCars;  /// <- Useless
    
    //string newCar;
    //string attribute;
    ifstream dataFileRead;                  /// Archivo que almacena la información de los coches "autodata.txt"
    ofstream dataFile;
    ofstream resultFile;                /// Archivo para el usuario "result.txt"
  
    void insertCar(TreeNode*& tree, carInfo myNewCar2);    
    /// Función: Inserta la información del coche en el BST
    /// Pre: El árbol está vacío
    /// Post: El árbol contiene la información del coche en forma de BST
    
    void askInfo();
    /// Función: Preguntar al usuario el nombre del coche y sus atributos
    /// Pre: nada
    /// Post: El usuario introduce la información del coche
    
    void loadFile();
    /// Función: Cargar el archivo si sale
    /// Pre: Comprobar si el archivo sale
    /// Post: Si es así, entonces carga los datos en la estructura de datos
    
    void checkAuto(TreeNode*& tree, string lookFor) ;
    /// Función: Utiliza el BST para buscar el nombre del coche
    /// Pre: El BST está ahí, pregunta por el nombre del coche
    /// Post: Busca el coche y muestra sus atributos si lo encuentra
    
    bool hasFeature();
    /// Función: Utiliza los vectores para buscar los atributos del coche (recorre toda la estructura)
    /// Pre: el vector tiene datos
    /// Post: elimina los coches que no tienen ese atributo
    
    void preCheck();
    /// Función: Entra en el modo de búsqueda
    /// Pre: Pide al usuario que llame a cualquiera de esas funciones
    /// Post: Llama a la función apropiada
    
    void show();
    /// Función: Muestra el nombre de los coches
    /// Pre: nada
    /// Post: muestra los nombres de los coches que coinciden con los criterios
    
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
    string lookFor;             /// buscar coche
    string hFeature;            /// característica a buscar
    string nameOfSearch;        /// título de la búsqueda
    string searchChoice;        /// elección del modo de búsqueda
       
    ~Tree();
private:
    //TreeNode* root;
    TreeNode* passTree; /// <- Useless
};

#endif
