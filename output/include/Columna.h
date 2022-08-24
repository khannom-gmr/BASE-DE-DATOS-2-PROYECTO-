#pragma once
#include "Registro.h"

// Clase Columna
class Columna
{
	string numeColumna;
	string tipColumna;
	float tam;
	int nrRegistros;
	Registro** registros;
public:
	//constructor fara parametri
	
	Columna()
	{
		this->numeColumna = "Anónimo";
		this->tipColumna = "Desconocido";
		this->tam = 0;
		this->nrRegistros = 0;
		this->registros = NULL;
	}
	Columna(string numeColumna, string tipColumna, float tam)
	{
		this->numeColumna = numeColumna;
		this->tipColumna = tipColumna;
		this->tam = tam;
		this->nrRegistros = 0;
		this->registros = NULL;
	}
	//constructor cu toti parametri
	Columna(string numeColumna, string tipColumna, float tam, int nrRegistros, Registro** registros)
	{
		this->numeColumna = numeColumna;
		this->tipColumna = tipColumna;
		this->tam = tam;
		this->nrRegistros = nrRegistros;
		this->registros = new Registro * [nrRegistros];
		for (int i = 0; i < this->nrRegistros; i++)
		{
			this->registros[i] = registros[i];
		}
	}
	string getNumeColumna()
	{
		return this->numeColumna;
	}
	string getTipColumna()
	{
		return this->tipColumna;
	}

	float getDimensiune()
	{
		return this->tam;
	}
	Registro** getRegistro()
	{
		return this->registros;
	}
	int getNrInregistrari()
	{
		return this->nrRegistros;
	}
	//setteri
	void setNumeColumna(string numeColumna)
	{
		this->numeColumna = numeColumna;
	}
	void setTipColumna(string tipColumna)
	{
		this->tipColumna = tipColumna;
	}
	void setDimensiune(float tam)
	{
		this->tam = tam;
	}
	void setNrInregistrari(int nrRegistros)
	{
		this->nrRegistros = nrRegistros;
	}
	void setInregistrari(int nrRegistros, Registro** registros)
	{
		if (nrRegistros > 0 && registros != NULL)
		{
			this->nrRegistros = nrRegistros;
			this->registros = new Registro * [this->nrRegistros];
			for (int i = 0; i < nrRegistros; i++)
			{
				this->registros[i] = registros[i];
			}
		}
	}
	//destructor
	~Columna()
	{
		if (this->registros != NULL)
		{
			delete[]this->registros;
		}
	}
	//constructor de copiere
	Columna(const Columna& c)
	{
		this->numeColumna = c.numeColumna;
		this->tipColumna = c.tipColumna;
		this->tam = c.tam;
		this->nrRegistros = c.nrRegistros;
		this->registros = new Registro * [c.nrRegistros];
		for (int i = 0; i < this->nrRegistros; i++)
		{
			this->registros[i] = c.registros[i];
		}
	}
	Columna& operator=(const Columna& c)
	{
		if (this->registros != NULL)
		{
			delete[]this->registros;
		}
		this->numeColumna = c.numeColumna;
		this->tipColumna = c.tipColumna;
		this->tam = c.tam;
		this->nrRegistros = c.nrRegistros;
		this->registros = new Registro * [c.nrRegistros];
		for (int i = 0; i < this->nrRegistros; i++)
		{
			this->registros[i] = c.registros[i];
		}
		return*this;
	}
	friend ostream& operator<<(ostream& out, const Columna& c)
	{

		out << c.numeColumna << endl;
		//out << "Numar Inregistrari: " << c.nrRegistros << endl;

		for (int i = 0; i < c.nrRegistros; i++)
		{
			out << *c.registros[i];
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Columna& c)
	{

		out << c.numeColumna << endl;
		out << c.tipColumna << endl;
		out << c.tam << endl;
		out << c.nrRegistros << endl;
		for (int i = 0; i < c.nrRegistros; i++)
		{
			out << *c.registros[i];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Columna& c)
	{

		cout << "Introduzca el nombre de la columna:";
		in >> c.numeColumna;
		cout << "Introduzca el tipo de columna: ";
		in >> c.tipColumna;
		cout << "Introduzca el tamaño de la columna: ";
		in >> c.tam;
		cout << "Introduzca su número de registro: ";
		delete[]c.registros;
		in >> c.nrRegistros;
		c.registros = new Registro * [c.nrRegistros];
		for (int i = 0; i < c.nrRegistros; i++)
		{
			c.registros[i] = new Registro();
			in >> *c.registros[i];
		}


		return in;
	}
	friend ifstream& operator>>(ifstream& in, Columna& c)
	{

		in >> c.numeColumna;
		in >> c.tipColumna;
		in >> c.tam;
		delete[]c.registros;
		in >> c.nrRegistros;
		c.registros = new Registro * [c.nrRegistros];
		for (int i = 0; i < c.nrRegistros; i++)
		{
			c.registros[i] = new Registro();
			in >> *c.registros[i];
		}


		return in;
	}
	//operator cast
	explicit operator string()
	{
		return this->numeColumna;
	}
	Columna& operator+=(Registro& in)
	{
		Columna cp = *this;
		delete[]registros;
		this->nrRegistros++;
		this->registros = new Registro * [this->nrRegistros];
		for (int i = 0; i < cp.nrRegistros; i++)
		{
			this->registros[i] = cp.registros[i];
		}
		this->registros[this->nrRegistros - 1] = &in;
		return *this;
	}
	Columna& operator -=(Registro& in)
	{
		int aux = 0;
		Columna cp = *this;
		for (int i = 0; i < this->nrRegistros; i++)
		{
			if (this->registros[i] == &in)
			{
				aux++;
			}
		}
		delete[]this->registros;
		this->nrRegistros = this->nrRegistros - aux;
		this->registros = new Registro * [this->nrRegistros];
		int loc = 0;
		for (int i = 0; i < cp.nrRegistros; i++)
		{
			if (cp.registros[i] != &in)
			{
				this->registros[loc] = cp.registros[i];
				loc++;
			}
		}
		return *this;
	}
	void escribeEnArchivoBinario(fstream& archivo)
	{
		int LgNumeColumna = this->numeColumna.length();
		archivo.write((char*)&LgNumeColumna, sizeof(int));
		archivo.write(this->numeColumna.c_str(), LgNumeColumna);
		int LgTipColumna = this->tipColumna.length();
		archivo.write((char*)&LgTipColumna, sizeof(int));
		archivo.write(this->tipColumna.c_str(), LgTipColumna);
		archivo.write((char*)&this->tam, sizeof(float));
		archivo.write((char*)&this->nrRegistros, sizeof(int));
		for (int i = 0; i < this->nrRegistros; i++)
		{
			archivo.write((char*)&*this->registros[i], sizeof(*this->registros[i]));
		}
	}
	void leeDelArchivoBinario(fstream& archivo)
	{
		if (this->registros != NULL)
		{
			delete[] this->registros;
		}
		int LgNumeColumna;
		archivo.read((char*)&LgNumeColumna, sizeof(int));
		string a;
		a.resize(LgNumeColumna);
		archivo.read((char*)a.c_str(), LgNumeColumna);
		this->numeColumna = a;
		int LgTipColumna;
		archivo.read((char*)&LgTipColumna, sizeof(int));
		string b;
		b.resize(LgTipColumna);
		archivo.read((char*)b.c_str(), LgTipColumna);
		this->tipColumna = a;
		archivo.read((char*)&this->tam, sizeof(float));
		archivo.read((char*)&this->nrRegistros, sizeof(int));
		this->registros = new Registro * [this->nrRegistros];
		for (int i = 0; i < this->nrRegistros; i++)
		{
			this->registros[i] = new Registro();
			archivo.read((char*)&*this->registros[i], sizeof(*registros[i]));
		}

	}
};