#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;
class archivoCSV
{
public:
	virtual void importCSV(fstream& file) = 0;
};

// Clase Registro
class Registro: public archivoCSV
{
	string registro;
	int idRegistro;
public:
	
	void importCSV(fstream &file)
	{
		getline(file, registro, ',');
	}
	Registro()
	{

		this->registro = "Desconocido";
		this->idRegistro = 0;
	}
	
	Registro(string registro, int idRegistro)
	{
		this->registro = registro;
		this->idRegistro = idRegistro;

	}
	//getteri
	string getRegistro()
	{
		return this->registro;
	}
	int getIdRegistro()
	{
		return this->idRegistro;
	}
	//setteri
	void setRegistro(string registro)
	{
		this->registro = registro;
	}
	void setIdRegistro(int idRegistro)
	{
		this->idRegistro = idRegistro;
	}
	//constructor de copia
	Registro(const Registro& inr)
	{
		this->registro = inr.registro;
		this->idRegistro = inr.idRegistro;
	}

	Registro& operator= (const Registro& inr)
	{
		this->registro = inr.registro;
		this->idRegistro = inr.idRegistro;
		return*this;
	}
	friend ostream& operator<<(ostream& out, const Registro& inr)
	{

		out << inr.registro << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Registro& inr)
	{
		out << inr.registro << endl;
		out << inr.idRegistro << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Registro& inr)
	{

		cout << "Introduzca su registro:";
		in >> inr.registro;
		cout << "Introduzca su ID de registro:";
		in >> inr.idRegistro;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Registro& inr)
	{

		in >> inr.registro;
		in >> inr.idRegistro;
		return in;
	}
	void escribeEnArchivoBinario(fstream& archivo)
	{
		int LgRegistro = this->registro.length();
		archivo.write((char*)&LgRegistro, sizeof(int));
		archivo.write(this->registro.c_str(), LgRegistro);
		archivo.write((char*)&this->idRegistro, sizeof(int));
	}
	void leeDelArchivoBinario(fstream& archivo)
	{
		int LgRegistro;
		archivo.read((char*)&LgRegistro, sizeof(int));
		string a;
		a.resize(LgRegistro);
		archivo.read((char*)a.c_str(), LgRegistro);
		this->registro = a;
		archivo.read((char*)&this->idRegistro, sizeof(int));
	}
};
