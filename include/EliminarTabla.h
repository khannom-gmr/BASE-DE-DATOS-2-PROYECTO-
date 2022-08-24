#pragma once
#include "Registro.h"
#include "Columna.h"
#include "Tabla.h"
#include "BD.h"

// Clase Eliminar Tabla
class EliminaTabla
{
	int nrBD = 1;
	BD** baze;
public:
	EliminaTabla()
	{
		this->nrBD = 0;
		this->baze = NULL;
	}
	EliminaTabla(BD& baze)
	{
		this->baze = new BD * [nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			this->baze[i] = &baze;
		}
	}
	BD** getBd()
	{
		return this->baze;
	}
	int getNrBD()
	{
		return this->nrBD;
	}
	void setBD(BD B)
	{
		if (this->baze != NULL)
		{

			this->baze = new BD * [this->nrBD];
			for (int i = 0; i < nrBD; i++)
			{
				this->baze[i] = &B;
			}
		}
	}
	~EliminaTabla()
	{
		if (this->baze != NULL)
		{
			delete[]this->baze;
		}
	}

	EliminaTabla(const EliminaTabla& b)
	{

		this->baze = new BD * [b.nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			this->baze[i] = b.baze[i];
		}

	}

	EliminaTabla& operator=(const EliminaTabla& b)
	{
		if (this != &b)
		{
			if (this->baze != NULL)
			{
				delete[]this->baze;
			}
			this->baze = new BD * [b.nrBD];
			for (int i = 0; i < this->nrBD; i++)
			{
				this->baze[i] = b.baze[i];
			}

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const EliminaTabla& b)
	{
		out << "Nr Bases :" << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const EliminaTabla& b)
	{

		out << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, EliminaTabla& b)
	{

		delete[]b.baze;
		in >> b.nrBD;
		b.baze = new BD * [b.nrBD];
		for (int i = 0; i < b.nrBD; i++)
		{
			b.baze[i] = new BD();
			in >> *b.baze[i];
		}
		return in;
	}
	friend ifstream& operator >>(ifstream& in, EliminaTabla& b)
	{

		delete[]b.baze;
		in >> b.nrBD;
		b.baze = new BD * [b.nrBD];
		for (int i = 0; i < b.nrBD; i++)
		{
			b.baze[i] = new BD();
			in >> *b.baze[i];
		}
		return in;
	}

	EliminaTabla& operator-=(Tabla& t)
	{
		*this->baze[0] += t;
		return *this;
	}
	void escribeEnArchivoBinario(fstream& archivo)
	{
		archivo.write((char*)&nrBD, sizeof(nrBD));

		for (int i = 0; i < this->nrBD; i++)
		{
			archivo.write((char*)&*baze[i], sizeof(*baze[i]));

		}
	}
	void leeDelArchivoBinario(fstream& archivo)
	{
		archivo.read((char*)&nrBD, sizeof(nrBD));
		delete[] baze;
		baze = new BD * [this->nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			baze[i] = new BD();
			archivo.read((char*)&*baze[i], sizeof(*baze[i]));
		}


	}
};