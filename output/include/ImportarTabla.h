#pragma once
#include "Tabla.h"

// 
class ImportarTabla
{
	int nrTab = 1;
	Tabla** tb;
public:
	
	ImportarTabla()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	ImportarTabla(Tabla& tb)
	{
		this->tb = new Tabla * [nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = &tb;
		};
	}
	Tabla** geTbl()
	{
		return this->tb;
	}
	int getNrTbl()
	{
		return this->nrTab;
	}
	void setTbl(Tabla T)
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
	~ImportarTabla()
	{
		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	ImportarTabla(const ImportarTabla& t)
	{
		this->tb = new Tabla * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	ImportarTabla& operator=(const ImportarTabla& t)
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
	friend ostream& operator<<(ostream& out, const ImportarTabla& t)
	{
		out << "Nro de Tabla: " << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const ImportarTabla& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, ImportarTabla& t)
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
	friend ifstream& operator >>(ifstream& in, ImportarTabla& t)
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