#pragma once
#include "Registro.h"
#include "Columna.h"
#include "Tabla.h"

// Clase Base de Datos o (Esquema)
class BD
{
	string numeBD;
	int Nro_Tabla ;
	Tabla** tabla;

public:
	//constructor fara parametrii
	BD()
	{
		this->numeBD = " ";
		this->Nro_Tabla  = 0;
		this->tabla = NULL;
	}
	//constructor cu toti parametrii
	BD(string numeBD, int Nro_Tabla , Tabla** tabla)
	{
		this->numeBD = numeBD;
		this->Nro_Tabla  = Nro_Tabla ;
		this->tabla = new Tabla * [Nro_Tabla ];
		for (int i = 0; i < this->Nro_Tabla ; i++)
		{
			this->tabla[i] = tabla[i];
		}
	}

	//getters 
	string getNumeBD()
	{
		return this->numeBD;
	}
	Tabla** getTabla()
	{
		return this->tabla;
	}
	int getNrTabla()
	{
		return this->Nro_Tabla ;
	}
	// setters
	void setNumeBD(string numeBD)
	{
		this->numeBD = numeBD;

	}
	void setNrTabla(int Nro_Tabla )
	{
		this->Nro_Tabla  = Nro_Tabla ;
	}
	void setTabla(int Nro_Tabla , Tabla** tabla)
	{
		if (Nro_Tabla  > 0 && tabla != NULL)
		{
			this->Nro_Tabla  = Nro_Tabla ;
			this->tabla = new Tabla * [this->Nro_Tabla ];
			for (int i = 0; i < Nro_Tabla ; i++)
			{
				this->tabla[i] = tabla[i];
			}
		}
	}
	//destructor
	~BD()
	{

		if (this->tabla != NULL)
		{
			delete[]this->tabla;
		}
	}

	//constructorul de copiere
	BD(const BD& b)
	{
		this->numeBD = b.numeBD;

		this->Nro_Tabla  = b.Nro_Tabla ;
		this->tabla = new Tabla * [b.Nro_Tabla ];
		for (int i = 0; i < this->Nro_Tabla ; i++)
		{
			this->tabla[i] = b.tabla[i];
		}

	}

	//operator<<
	friend ostream& operator<<(ostream& out, const BD& b)
	{

		out << "NumeBD: " << b.numeBD << endl;
		out << "Nro de Tabla: " << b.Nro_Tabla  << endl;
		for (int i = 0; i < b.Nro_Tabla ; i++)
		{
			out << *b.tabla[i] << endl;
		}
		return out;

	}
	friend ofstream& operator<<(ofstream& out, const BD& b)
	{

		out << b.numeBD << endl;
		out << b.Nro_Tabla  << endl;
		for (int i = 0; i < b.Nro_Tabla ; i++)
		{
			out << *b.tabla[i] << endl;
		}
		return out;

	}
	//operatorul >>

	friend istream& operator>>(istream& in, BD& b)
	{
		cout << "Introduzca el nombre de la base de datos: ";
		in >> b.numeBD;
		cout << "Introduzca el número de tablas: ";
		delete[]b.tabla;
		in >> b.Nro_Tabla ;
		b.tabla = new Tabla * [b.Nro_Tabla ];
		for (int i = 0; i < b.Nro_Tabla ; i++)
		{
			b.tabla[i] = new Tabla();
			in >> *b.tabla[i];
		}

		return in;
	}
	friend ifstream& operator>>(ifstream& in, BD& b)
	{

		in >> b.numeBD;
		delete[]b.tabla;
		in >> b.Nro_Tabla ;
		b.tabla = new Tabla * [b.Nro_Tabla ];
		for (int i = 0; i < b.Nro_Tabla ; i++)
		{
			b.tabla[i] = new Tabla();
			in >> *b.tabla[i];
		}

		return in;
	}
	//operator =
	BD& operator=(const BD& b)
	{
		if (this != &b)
		{

			if (this->tabla != NULL)
			{
				delete[]this->tabla;
			}
			this->numeBD = b.numeBD;
			this->Nro_Tabla  = b.Nro_Tabla ;
			this->tabla = new Tabla * [b.Nro_Tabla ];
			for (int i = 0; i < this->Nro_Tabla ; i++)
			{
				this->tabla[i] = b.tabla[i];
			}

		}
		return *this;
	}


	BD& operator+=(Tabla& t)
	{
		BD cp = *this;
		delete[]tabla;
		this->Nro_Tabla ++;
		this->tabla = new Tabla * [this->Nro_Tabla ];
		for (int i = 0; i < cp.Nro_Tabla ; i++)
		{
			this->tabla[i] = cp.tabla[i];
		}
		this->tabla[this->Nro_Tabla  - 1] = &t;
		return *this;
	}
	BD& operator -=(Tabla& t)
	{
		int aux = 0;
		BD cp = *this;
		for (int i = 0; i < this->Nro_Tabla ; i++)
		{
			if (this->tabla[i] == &t)
			{
				aux++;
			}
		}
		delete[]this->tabla;
		this->Nro_Tabla  = this->Nro_Tabla  - aux;
		this->tabla = new Tabla * [this->Nro_Tabla ];
		int loc = 0;
		for (int i = 0; i < cp.Nro_Tabla ; i++)
		{
			if (cp.tabla[i] != &t)
			{
				this->tabla[loc] = cp.tabla[i];
				loc++;
			}
		}
		return *this;
	}
	void escribeEnArchivoBinario(fstream& archivo)
	{

		int LgNumeBD = this->numeBD.length();
		archivo.write((char*)&LgNumeBD, sizeof(int));
		archivo.write(this->numeBD.c_str(), LgNumeBD);
		archivo.write((char*)&this->Nro_Tabla , sizeof(int));
		for (int i = 0; i < this->Nro_Tabla ; i++)
		{
			archivo.write((char*)&*this->tabla[i], sizeof(*this->tabla[i]));
		}
	}
	void leeDelArchivoBinario(fstream& archivo)
	{
		if (this->tabla != NULL)
		{
			delete[] this->tabla;
		}
		int LgNumeBD;
		archivo.read((char*)&LgNumeBD, sizeof(int));
		string a;
		a.resize(LgNumeBD);
		archivo.read((char*)a.c_str(), LgNumeBD);
		this->numeBD = a;
		archivo.read((char*)&this->Nro_Tabla , sizeof(int));
		this->tabla = new Tabla * [this->Nro_Tabla ];
		for (int i = 0; i < this->Nro_Tabla ; i++)
		{
			this->tabla[i] = new Tabla();
			archivo.read((char*)&*this->tabla[i], sizeof(*this->tabla[i]));
		}

	}

};