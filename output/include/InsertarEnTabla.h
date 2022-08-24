#pragma once
#include "Registro.h"
#include "Columna.h"
#include "Tabla.h"
#include "BD.h"

// Clase Insertar en la Tabla
class InsertInTable
{
	int nrTab = 1;
	Tabla** tb;
public:
	InsertInTable()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	InsertInTable(Tabla& tb)
	{
		this->tb = new Tabla * [nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = &tb;
		}
	}
	Tabla** getTb()
	{
		return this->tb;
	}
	int getNrTab()
	{
		return this->nrTab;
	}
	void setTab(Tabla T)
	{
		if (this->tb != NULL)
		{

			this->tb = new Tabla * [this->nrTab];
			for (int i = 0; i < nrTab; i++)
			{
				this->tb[i] = &T;
			}
		}
	}
	~InsertInTable()
	{

		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	InsertInTable(const InsertInTable& t)
	{
		this->tb = new Tabla * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	InsertInTable& operator=(const InsertInTable& t)
	{
		if (this != &t)
		{
			if (this->tb != NULL)
			{
				delete[]this->tb;
			}
			this->tb = new Tabla * [t.nrTab];
			for (int i = 0; i < this->nrTab; i++)
			{
				this->tb[i] = t.tb[i];
			}

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const InsertInTable& t)
	{
		out << "Nro de Tabla: " << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const InsertInTable& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, InsertInTable& t)
	{

		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabla * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabla();
			in >> *t.tb[i];
		}
		return in;
	}
	friend ifstream& operator >>(ifstream& in, InsertInTable& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabla * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabla();
			in >> *t.tb[i];
		}
		return in;
	}
	InsertInTable& operator+=(Columna& c)
	{
		*this->tb[0] += c;
		return *this;
	}
	void escribeEnArchivoBinario(fstream& archivo)
	{
		archivo.write((char*)&nrTab, sizeof(nrTab));

		for (int i = 0; i < this->nrTab; i++)
		{
			archivo.write((char*)&*tb[i], sizeof(*tb[i]));

		}
	}
	void leeDelArchivoBinario(fstream& archivo)
	{
		archivo.read((char*)&nrTab, sizeof(nrTab));
		delete[] tb;
		tb = new Tabla * [this->nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			tb[i] = new Tabla();
			archivo.read((char*)&*tb[i], sizeof(*tb[i]));
		}


	}
};


class ModificaInTabla
{
	int nrTab = 1;
	Tabla** tb;
public:
	ModificaInTabla()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	ModificaInTabla(Tabla& tb)
	{
		this->tb = new Tabla * [nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = &tb;
		}
	}
	Tabla** getTb()
	{
		return this->tb;
	}
	int getNrTab()
	{
		return this->nrTab;
	}
	void setTb(Tabla T)
	{
		if (this->tb != NULL)
		{

			this->tb = new Tabla * [this->nrTab];
			for (int i = 0; i < nrTab; i++)
			{
				this->tb[i] = &T;
			}
		}
	}
	~ModificaInTabla()
	{
		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	ModificaInTabla(const ModificaInTabla& t)
	{
		this->tb = new Tabla * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	ModificaInTabla& operator=(const ModificaInTabla& t)
	{
		if (this != &t)
		{
			if (this->tb != NULL)
			{
				delete[]this->tb;
			}
			this->tb = new Tabla * [t.nrTab];
			for (int i = 0; i < this->nrTab; i++)
			{
				this->tb[i] = t.tb[i];
			}

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ModificaInTabla& t)
	{
		out << "Nro de Tabla: " << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const ModificaInTabla& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, ModificaInTabla& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabla * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabla();
			in >> *t.tb[i];
		}
		return in;
	}
	friend ifstream& operator >>(ifstream& in, ModificaInTabla& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabla * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabla();
			in >> *t.tb[i];
		}
		return in;
	}
	void escribeEnArchivoBinario(fstream& archivo)
	{
		archivo.write((char*)&nrTab, sizeof(nrTab));

		for (int i = 0; i < this->nrTab; i++)
		{
			archivo.write((char*)&*tb[i], sizeof(*tb[i]));

		}
	}
	void leeDelArchivoBinario(fstream& archivo)
	{
		archivo.read((char*)&nrTab, sizeof(nrTab));
		delete[] tb;
		tb = new Tabla * [this->nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			tb[i] = new Tabla();
			archivo.read((char*)&*tb[i], sizeof(*tb[i]));
		}
	}

};