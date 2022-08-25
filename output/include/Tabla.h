#pragma once
#include "Registro.h"
#include "Columna.h"
// Clase Tabla
class Tabla
{
	string cheiePrimara="ch";
	string nombreTabla;
	int nrColumnas;
	Columna** columnas;


public:
	//constructor fara parametri
	Tabla()
	{
		this->nombreTabla = "Desconocido";
		this->nrColumnas = 0;
		this->columnas = NULL;
	}
	Tabla( string nombreTabla)
	{
		this->nombreTabla = nombreTabla;
		this->nrColumnas = 0;
		this->columnas = NULL;
	}
	//constructor cu toti parametri
	Tabla( string nombreTabla, int nrColumnas, Columna** columnas)
	{
	
		this->nombreTabla = nombreTabla;
		this->nrColumnas = nrColumnas;
		this->columnas = new Columna * [nrColumnas];
		for (int i = 0; i < this->nrColumnas; i++)
		{
			this->columnas[i] = columnas[i];
		}
	}
	string getCheiePrimara()
	{
		return this->cheiePrimara;
	}
	string getNombreTabla()
	{
		return this->nombreTabla;
	}
	Columna** getColumna()
	{
		return this->columnas;
	}
	int getNrColumnas()
	{
		return this->nrColumnas;
	}

	void setCheiePrimara(string cheiePrimara)
	{
		this->cheiePrimara = cheiePrimara;
	}
	void setNombreTabla(string nombreTabla)
	{
		this->nombreTabla = nombreTabla;
	}

	void setNrColumnas(int nrColumnas)
	{
		this->nrColumnas = nrColumnas;
	}
	void setColumna(int nrColumnas, Columna** columnas)
	{
		if (nrColumnas > 0 && columnas != NULL)
		{
			this->nrColumnas = nrColumnas;
			this->columnas = new Columna * [this->nrColumnas];
			for (int i = 0; i < nrColumnas; i++)
			{
				this->columnas[i] = columnas[i];
			}
		}
	}
	//destructor
	~Tabla()
	{
		if (this->columnas != NULL)
		{
			delete[]this->columnas;
		}

	}
	//constructor de copiere
	Tabla(const Tabla& t)
	{

		this->cheiePrimara = t.cheiePrimara;
		this->nombreTabla = t.nombreTabla;
		this->nrColumnas = t.nrColumnas;
		this->columnas = new Columna * [t.nrColumnas];
		for (int i = 0; i < this->nrColumnas; i++)
		{
			this->columnas[i] = t.columnas[i];
		}

	}
	Tabla& operator=(const Tabla& t)
	{
		if (this->columnas != NULL)
		{
			delete[]this->columnas;
		}

		this->cheiePrimara = t.cheiePrimara;
		this->nombreTabla = t.nombreTabla;
		this->nrColumnas = t.nrColumnas;
		this->columnas = new Columna * [t.nrColumnas];
		for (int i = 0; i < this->nrColumnas; i++)
		{
			this->columnas[i] = t.columnas[i];
		}
		return*this;
	}
	friend ostream& operator<<(ostream& out, const Tabla& t)
	{

		out << t.nombreTabla << endl;
		out << "Sin columnas:" << t.nrColumnas << endl << endl;
		for (int i = 0; i < t.nrColumnas; i++)
		{
			out << *t.columnas[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Tabla& t)
	{
		out << t.nombreTabla << endl;
		out << t.nrColumnas << endl;
		for (int i = 0; i < t.nrColumnas; i++)
		{
			out << *t.columnas[i] << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Tabla& t)
	{
		cout << "Introducir nombreTabla: ";

		in >> t.nombreTabla;
		cout << "Introduzca el número de columnas: ";
		delete[]t.columnas;
		in >> t.nrColumnas;
		t.columnas = new Columna * [t.nrColumnas];
		for (int i = 0; i < t.nrColumnas; i++)
		{
			t.columnas[i] = new Columna();
			in >> *t.columnas[i];
		}

		return in;
	}
	friend ifstream& operator>>(ifstream& in, Tabla& t)
	{


		in >> t.nombreTabla;
		delete[]t.columnas;
		in >> t.nrColumnas;
		t.columnas = new Columna * [t.nrColumnas];
		for (int i = 0; i < t.nrColumnas; i++)
		{
			t.columnas[i] = new Columna();
			in >> *t.columnas[i];
		}

		return in;
	}
	bool operator ==(const Tabla& t)
	{
		return this->nombreTabla == t.nombreTabla;
	}
	Tabla& operator+=(Columna& c)
	{
		Tabla cp = *this;
		delete[]columnas;
		this->nrColumnas++;
		this->columnas = new Columna * [this->nrColumnas];
		for (int i = 0; i < cp.nrColumnas; i++)
		{
			this->columnas[i] = cp.columnas[i];
		}
		this->columnas[this->nrColumnas - 1] = &c;
		return *this;
	}
	Tabla& operator -=(Columna& c)
	{
		int aux = 0;
		Tabla cp = *this;
		for (int i = 0; i < this->nrColumnas; i++)
		{
			if (this->columnas[i] == &c)
			{
				aux++;
			}
		}
		delete[]this->columnas;
		this->nrColumnas = this->nrColumnas - aux;
		this->columnas = new Columna * [this->nrColumnas];
		int loc = 0;
		for (int i = 0; i < cp.nrColumnas; i++)
		{
			if (cp.columnas[i] != &c)
			{
				this->columnas[loc] = cp.columnas[i];
				loc++;
			}
		}
		return *this;
	}
	void escribeEnArchivoBinario(fstream& archivo)
	{
		int LgCheiePrimara = this->cheiePrimara.length();
		archivo.write((char*)&LgCheiePrimara, sizeof(int));
		archivo.write(this->cheiePrimara.c_str(), LgCheiePrimara);
		int LgNombreTabla = this->nombreTabla.length();
		archivo.write((char*)&LgNombreTabla, sizeof(int));
		archivo.write(this->nombreTabla.c_str(), LgNombreTabla);
		archivo.write((char*)&this->nrColumnas, sizeof(int));
		for (int i = 0; i < this->nrColumnas; i++)
		{
			archivo.write((char*)&*this->columnas[i], sizeof(*columnas[i]));
		}
	}
	void leeDelArchivoBinario(fstream& archivo)
	{
		if (this->columnas != NULL)
		{
			delete[] this->columnas;
		}
		int LgCheiePrimara;
		archivo.read((char*)&LgCheiePrimara, sizeof(int));
		string a;
		a.resize(LgCheiePrimara);
		archivo.read((char*)a.c_str(), LgCheiePrimara);
		this->cheiePrimara = a;
		int LgNombreTabla;
		archivo.read((char*)&LgNombreTabla, sizeof(int));
		string b;
		b.resize(LgNombreTabla);
		archivo.read((char*)b.c_str(), LgNombreTabla);
		this->nombreTabla = a;
		archivo.read((char*)&this->nrColumnas, sizeof(int));
		this->columnas = new Columna * [this->nrColumnas];
		for (int i = 0; i < this->nrColumnas; i++)
		{
			this->columnas[i] = new Columna();
			archivo.read((char*)&*this->columnas[i], sizeof(*columnas[i]));
		}

	}

};