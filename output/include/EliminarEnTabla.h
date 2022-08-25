#pragma once
#include "Tabla.h"

class DeleteInTabla
{
	int nrTab = 1;
	Tabla** tb;
public:
	DeleteInTabla()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	DeleteInTabla(Tabla& tb)
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
	~DeleteInTabla()
	{
		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	DeleteInTabla(const DeleteInTabla& t)
	{
		this->tb = new Tabla * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	DeleteInTabla& operator=(const DeleteInTabla& t)
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
	friend ostream& operator<<(ostream& out, const DeleteInTabla& t)
	{
		out << "Nr Tabla :" << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const DeleteInTabla& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, DeleteInTabla& t)
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
	friend ifstream& operator >>(ifstream& in, DeleteInTabla& t)
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
	DeleteInTabla& operator-=(Columna& c)
	{
		*this->tb[0] -= c;
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