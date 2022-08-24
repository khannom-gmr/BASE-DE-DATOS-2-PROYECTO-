#include "include.h"
#include <iostream>
using namespace std;

void registrotest()
{
	Registro in("Tudor", 102);
	Registro in1("Mircea", 103);
	Registro in2("David", 104);
	Registro in3("Catalin", 105);
	Registro in4("23", 102);
	Registro in5("24", 103);
	Registro in6("33", 104);
	Registro in7("42", 105);
	Registro in8("2300", 102);
	Registro in9("2400", 103);
	Registro in10("3000", 104);
	Registro in11("3100", 105);
	Registro in12("Ciocolata", 21);
	Registro in13("Lapte", 22);
	Registro in14("Faina", 23);
	Registro in15("Zahar", 24);
	Registro in16("100", 21);
	Registro in17("1", 22);
	Registro in18("12", 23);
	Registro in19("11", 24);
	Registro in20("8", 21);
	Registro in21("6", 22);
	Registro in22("3.5", 23);
	Registro in23("4", 24);

	cout << "=======Escribir en un archivo=======" << endl;
	ofstream fh("registros.txt", ios::out);
	fh << in;
	fh << in1;
	fh.close();
	cout << "Los objetos se han escrito con exito en el archivo" << endl;
}