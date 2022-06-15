#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;

template <typename K, typename V>
class Tree {
	struct Node {
		K key;
		V value;
		int height;
		Node* left;
		Node* right;
		Node(const K& k, const V& val, Node* lft, Node* rgt, int h = 0)
			:key(k), value(val), left(lft), right(rgt), height(h) {}
	};

public:
	Tree();
	~Tree(){
		clear(root);
	};

	void insert(const K& key, const V& value);
	void remove(const K& key);
	bool contains(const K& key) const;
	void preorder() {
		preorder(root);
	}
	void inorder() {
		inorder(root);
	}
	void postorder() {
		postorder(root);
	}
	//10 grafica el arbol con graphviz
	void print() {
		ofstream salida;
		salida.open("graph.gv",ios::out);
		salida<<"graph {"<<endl;

		printPri(root,salida);

		salida<<"}"<<endl;
		salida.close();

	}

private:
	//Metodos privados
	void insert(const K& key, const V& value, Node*& spot);
	void remove(const K& key, Node*& spot);
	bool contains(const K& key, Node* root) const;
	Node* findMin(Node*& root) const;
	void rotateWithLeftChild(Node*& spot);
	void rotateWithRightChild(Node*& spot);
	void doubleWithLeftChild(Node*& spot);
	void doubleWithRightChild(Node*& spot);
	void balance(Node*& spot);
	int height(Node* spot) const;
	void preorder(Node* root);
	void inorder(Node* root);
	void postorder(Node* root);

	void printPri(Node* root,ofstream& salida);
	static const int ALOWED_IMBALANCE = 1;
	//variables privadas
	Node* root;
	int n;

	//10 limpia el arbol
	void clear(Node*& spot){
		if(spot->left==NULL && spot->right==NULL){
			cout<<"Nodo "<<spot->key<<endl;
			delete spot;
		}else{
			if(spot->left!=NULL){
				clear(spot->left);
			}
			if(spot->right!=NULL){
				clear(spot->right);
			}
			cout<<"Nodo "<<spot->key<<endl;
			delete spot;
		}
	};

};

//1 crea arbol vacio
template <typename K, typename V>
Tree<K, V>::Tree()
	:root(NULL), n(0) {}

//2 inserta el nodo con llave key
template <typename K, typename V>
void Tree<K, V>::insert(const K& key, const V& value) {
	insert(key, value, root);
}

//3 elimina el nodo de llave key
template <typename K, typename V>
void Tree<K, V>::remove(const K& key) {
	remove(key, root);
}

//4 busca el elemento por su llave
template <typename K, typename V>
bool Tree<K, V>::contains(const K& key) const {
	return contains(key, root);
}

template <typename K, typename V>
void Tree<K, V>::insert(const K& key, const V& value, Node*& spot) {
	if (spot == NULL) {
		++n;
		spot = new Node(key, value, NULL, NULL);
	}
	else {
		if (key > spot->key){
			insert(key, value, spot->right);
		}
		else {
			if (key < spot->key){
				insert(key, value, spot->left);
			}
		}
	}
	balance(spot);
}

template <typename K, typename V>
bool Tree<K, V>::contains(const K& key, Node* root) const {
	if (root != NULL) {
		if (key > root->key)
			return contains(key, root->right);
		else if (key < root->key)
			return contains(key, root->left);
		else
			return true;
	}
	return false;
}

template <typename K, typename V>
void Tree<K, V>::remove(const K& key, Node*& spot) {
	if (spot == NULL){
		return;
	}

	if (key < spot->key ){
		remove(key, spot->left);
	} else {
		if (spot->key < key){
			remove(key, spot->right);
		}
		else {
			if (spot->left != NULL && spot->right != NULL) {
				spot->key = findMin(spot->right)->key;
				remove(spot->key, spot->right);
			} else {
				Node* oldNode = spot;
				spot = (spot->left != NULL) ? spot->left : spot->right;
				delete oldNode;
			}
		}
	}

	balance(spot);
}

template <typename K, typename V>
typename Tree<K, V>::Node* Tree<K, V>::findMin(Node*& spot) const {
	if (spot->left == NULL){
		return spot;
	}

	return findMin(spot->left);
}

template <typename K, typename V>
void Tree<K, V>::balance(Node*& spot) {
	if (spot != NULL) {
		if (height(spot->left) - height(spot->right) > ALOWED_IMBALANCE) {
			//Realiza rotacion izquierda, compara si la falta esta en left left o left right intercalado
			if (height(spot->left->left) >= height(spot->left->right))
				rotateWithLeftChild(spot);
			else
				doubleWithLeftChild(spot);
		}
		else {
			if (height(spot->right) - height(spot->left) > ALOWED_IMBALANCE) {
				//Realiza Rotacion derecha, compara si la falta esta en left left o left right intercalado
				if (height(spot->right->right) >= height(spot->right->left))
					rotateWithRightChild(spot);
				else
					doubleWithRightChild(spot);
			}
		}
		spot->height = std::max(height(spot->left), height(spot->right)) + 1;
	}
}

template <typename K, typename V>
int Tree<K, V>::height(Node* spot) const {
	return (spot == NULL) ? -1 : spot->height;
}

//7 rotacion left
template <typename K, typename V>
void Tree<K, V>::rotateWithLeftChild(Node*& spot) {
	Node* temp = spot->left;
	spot->left = temp->right;
	temp->right = spot;
	spot->height = std::max(height(spot->left), height(spot->right)) + 1;
	temp->height = std::max(height(temp->left), height(spot)) + 1;
	spot = temp;
}

//8 rotacion right
template <typename K, typename V>
void Tree<K, V>::rotateWithRightChild(Node*& spot) {
	Node* temp = spot->right;
	spot->right = temp->left;
	temp->left = spot;
	spot->height = std::max(height(spot->right), height(spot->left)) + 1;
	temp->height = std::max(height(temp->right), height(spot)) + 1;
	spot = temp;
}

//5 doble left rotate
template <typename K, typename V>
void Tree<K, V>::doubleWithLeftChild(Node*& spot) {
	rotateWithRightChild(spot->left);
	rotateWithLeftChild(spot);
}

//6 doble rigth rotate
template <typename K, typename V>
void Tree<K, V>::doubleWithRightChild(Node*& spot) {
	rotateWithLeftChild(spot->right);
	rotateWithRightChild(spot);
}

//7 imprime pre order
template <typename K, typename V>
void Tree<K, V>::preorder(Node* p) {
	if (p == NULL)
		return;
	std::cout << p->key << " -- " ;
	preorder(p->left);
	preorder(p->right);
}

//8 imprime in order
template <typename K, typename V>
void Tree<K, V>::inorder(Node* p) {
	if (p == NULL)
		return;
	preorder(p->left);
	std::cout << p->key << " -- " ;
	preorder(p->right);
}

//9 imprime post order
template <typename K, typename V>
void Tree<K, V>::postorder(Node* p) {
	if (p == NULL)
		return;
	preorder(p->left);
	preorder(p->right);
	std::cout << p->key << " -- " ;
}

template <typename K, typename V>
void Tree<K, V>::printPri(Node* p,ofstream& salida) {
	if (p == NULL)
		return;
	if(p->left!=NULL){
		salida << p->key << " -- " << p->left->key << ";\n";
	}
	if(p->right!=NULL){
		salida << p->key << " -- " << p->right->key << ";\n";
	}
	printPri(p->right,salida);
	printPri(p->left,salida);
}

int main()
{
	int opcion=1;
	Tree<int, int> arbol;
	int valor=0;

	while(opcion!=3){
		cout<<"1) Insertar: "<<endl;
		cout<<"2) Eliminar: "<<endl;
		cout<<"3) Salir: "<<endl;
		cout<<endl;
		cout<<"Ingresa tu opcion: ";
		cin>>opcion;
		switch(opcion){
			case 1:{
				cout<<"Ingrese el valor a agregar: "<<endl;
				cin>>valor;
				cout<<endl;
				arbol.insert(valor,100);

				system("dot -Tps graph.gv -o graph.ps");
				break;
			}
			case 2:{
				cout<<"Ingrese el valor a eliminar: "<<endl;
				cin>>valor;
				cout<<endl;
				arbol.remove(valor);

				system("dot -Tps graph.gv -o graph.ps");
				break;
			}
			case 3:{
			    cout<<"buscamos un elemento"<<endl;
			    cout<<arbol.contains(80)<<endl;

			    cout<<"preorder"<<endl;
			    arbol.preorder();
			    cout<<endl;
			    cout<<"inorder"<<endl;
			    arbol.inorder();
			    cout<<endl;
			    cout<<"postorder"<<endl;
			    arbol.postorder();
			    cout<<endl;
			    cout<<"imprimiendo arbol"<<endl;
                arbol.print();

				break;
			}
			default:{
				cout<<"Opcion no valida"<<endl;
				break;
			}

		}
	}
    cout<<endl;
    cout<<"arbol con clear"<<endl;
	arbol.~Tree();
	return 0;
}
