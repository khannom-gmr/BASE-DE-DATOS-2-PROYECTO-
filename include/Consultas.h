#pragma once
#include "Registro.h"

string introducirComando()
{
	string temp;
	cout << "Introduzca el comando: ";
	while (!getline(cin, temp) || temp.empty()) {
		cin.clear();
		cin.ignore('\n');
	}
	return temp;
}

string crearComando(string comando)
{

	char delimitator = ' ';
	char* ComandoValido = new char[comando.size() + 1];
	strcpy(ComandoValido, comando.c_str());
	int nrCuvinte = 1;
	for (int i = 0; i < strlen(ComandoValido); i++)
	{
		if (ComandoValido[i] == delimitator || ComandoValido[i] == '\n')
		{
			nrCuvinte++;
		}
	}

	string* comandaF = new string[nrCuvinte];
	int nr = 0;
	for (int i = 0; i < strlen(ComandoValido); i++)
	{
		if (ComandoValido[i] != delimitator)
		{
			comandaF[nr] = comandaF[nr] + ComandoValido[i];
		}
		else
		{
			nr++;
		}
	}
	string textVerificat;
	if (nr == 0)
	{
		textVerificat = comandaF[0];
	}
	else
	{
		 textVerificat = comandaF[0] + " " + comandaF[1];
	
	}

	return textVerificat;
}

string identificareComanda(string textVerificat)
{
	string subText = textVerificat.substr(0, 6);
	if (textVerificat == "CREATE TABLE" || textVerificat == "create table")
	{
		return "create table";
	}
	else if (textVerificat == "DROP TABLE" || textVerificat == "drop table")
	{
		return "drop table";
	}
	else if (textVerificat == "DISPLAY TABLE" || textVerificat == "display table")
	{
		return "display table";
	}
	else if (subText == "update" || subText == "UPDATE")
	{
		return "update";

	}
	else if (subText == "select" || subText == "SELECT")
	{
		return "select";

	}
	else if (textVerificat == "insert into" || textVerificat == "INSERT INTO")
	{
		return "insert into";
	}
	else if (textVerificat == "delete from" || textVerificat == "DELETE FROM")
	{
		return "delete from";

	}
	else
	{
		return "El comando introducido es incorrecto";
	}
}