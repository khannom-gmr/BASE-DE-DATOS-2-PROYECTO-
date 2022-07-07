#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <cstring>

using namespace std;
class fisierCSV
{
public:
	virtual void importCSV(fstream& file) = 0;
};
class Inregistrare: public fisierCSV
{
	string inregistrare;
	int idInregistrare;
public:
	//constructor fara parametri
	void importCSV(fstream &file)
	{
		getline(file, inregistrare, ',');
	}
	Inregistrare()
	{

		this->inregistrare = "Desconocido";
		this->idInregistrare = 0;
	}
	//constructor cu toti parametri
	Inregistrare(string inregistrare, int idInregistrare)
	{
		this->inregistrare = inregistrare;
		this->idInregistrare = idInregistrare;

	}
	//getteri
	string getInregistrare()
	{
		return this->inregistrare;
	}
	int getIdInregistrare()
	{
		return this->idInregistrare;
	}
	//setteri
	void setInregistrare(string inregistrare)
	{
		this->inregistrare = inregistrare;
	}
	void setIdInregistrare(int idInregistrare)
	{
		this->idInregistrare = idInregistrare;
	}
	//constructorul de copiere
	Inregistrare(const Inregistrare& inr)
	{
		this->inregistrare = inr.inregistrare;
		this->idInregistrare = inr.idInregistrare;
	}

	Inregistrare& operator= (const Inregistrare& inr)
	{
		this->inregistrare = inr.inregistrare;
		this->idInregistrare = inr.idInregistrare;
		return*this;
	}
	friend ostream& operator<<(ostream& out, const Inregistrare& inr)
	{

		out << inr.inregistrare << endl;
		/*out << "Id Inregistrare: " << i.idInregistrare << endl;*/
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Inregistrare& inr)
	{
		out << inr.inregistrare << endl;
		out << inr.idInregistrare << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Inregistrare& inr)
	{

		cout << "Introduzca su registro:";
		in >> inr.inregistrare;
		cout << "Introduzca su ID de registro:";
		in >> inr.idInregistrare;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Inregistrare& inr)
	{

		in >> inr.inregistrare;
		in >> inr.idInregistrare;
		return in;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		int LgInregistrare = this->inregistrare.length();
		fisier.write((char*)&LgInregistrare, sizeof(int));
		fisier.write(this->inregistrare.c_str(), LgInregistrare);
		fisier.write((char*)&this->idInregistrare, sizeof(int));
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		int LgInregistrare;
		fisier.read((char*)&LgInregistrare, sizeof(int));
		string a;
		a.resize(LgInregistrare);
		fisier.read((char*)a.c_str(), LgInregistrare);
		this->inregistrare = a;
		fisier.read((char*)&this->idInregistrare, sizeof(int));
	}
};
class Coloana
{
	string numeColoana;
	string tipColoana;
	float dimensiune;
	int nrInregistrari;
	Inregistrare** inregistrari;
public:
	//constructor fara parametri
	
	Coloana()
	{
		this->numeColoana = "Anónimo";
		this->tipColoana = "Desconocido";
		this->dimensiune = 0;
		this->nrInregistrari = 0;
		this->inregistrari = NULL;
	}
	Coloana(string numeColoana, string tipColoana, float dimensiune)
	{
		this->numeColoana = numeColoana;
		this->tipColoana = tipColoana;
		this->dimensiune = dimensiune;
		this->nrInregistrari = 0;
		this->inregistrari = NULL;
	}
	//constructor cu toti parametri
	Coloana(string numeColoana, string tipColoana, float dimensiune, int nrInregistrari, Inregistrare** inregistrari)
	{
		this->numeColoana = numeColoana;
		this->tipColoana = tipColoana;
		this->dimensiune = dimensiune;
		this->nrInregistrari = nrInregistrari;
		this->inregistrari = new Inregistrare * [nrInregistrari];
		for (int i = 0; i < this->nrInregistrari; i++)
		{
			this->inregistrari[i] = inregistrari[i];
		}
	}
	string getNumeColoana()
	{
		return this->numeColoana;
	}
	string getTipColoana()
	{
		return this->tipColoana;
	}

	float getDimensiune()
	{
		return this->dimensiune;
	}
	Inregistrare** getInregistrare()
	{
		return this->inregistrari;
	}
	int getNrInregistrari()
	{
		return this->nrInregistrari;
	}
	//setteri
	void setNumeColoana(string numeColoana)
	{
		this->numeColoana = numeColoana;
	}
	void setTipColoana(string tipColoana)
	{
		this->tipColoana = tipColoana;
	}
	void setDimensiune(float dimensiune)
	{
		this->dimensiune = dimensiune;
	}
	void setNrInregistrari(int nrInregistrari)
	{
		this->nrInregistrari = nrInregistrari;
	}
	void setInregistrari(int nrInregistrari, Inregistrare** inregistrari)
	{
		if (nrInregistrari > 0 && inregistrari != NULL)
		{
			this->nrInregistrari = nrInregistrari;
			this->inregistrari = new Inregistrare * [this->nrInregistrari];
			for (int i = 0; i < nrInregistrari; i++)
			{
				this->inregistrari[i] = inregistrari[i];
			}
		}
	}
	//destructor
	~Coloana()
	{
		if (this->inregistrari != NULL)
		{
			delete[]this->inregistrari;
		}
	}
	//constructor de copiere
	Coloana(const Coloana& c)
	{
		this->numeColoana = c.numeColoana;
		this->tipColoana = c.tipColoana;
		this->dimensiune = c.dimensiune;
		this->nrInregistrari = c.nrInregistrari;
		this->inregistrari = new Inregistrare * [c.nrInregistrari];
		for (int i = 0; i < this->nrInregistrari; i++)
		{
			this->inregistrari[i] = c.inregistrari[i];
		}
	}
	Coloana& operator=(const Coloana& c)
	{
		if (this->inregistrari != NULL)
		{
			delete[]this->inregistrari;
		}
		this->numeColoana = c.numeColoana;
		this->tipColoana = c.tipColoana;
		this->dimensiune = c.dimensiune;
		this->nrInregistrari = c.nrInregistrari;
		this->inregistrari = new Inregistrare * [c.nrInregistrari];
		for (int i = 0; i < this->nrInregistrari; i++)
		{
			this->inregistrari[i] = c.inregistrari[i];
		}
		return*this;
	}
	friend ostream& operator<<(ostream& out, const Coloana& c)
	{

		out << c.numeColoana << endl;
		//out << "Numar Inregistrari: " << c.nrInregistrari << endl;

		for (int i = 0; i < c.nrInregistrari; i++)
		{
			out << *c.inregistrari[i];
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Coloana& c)
	{

		out << c.numeColoana << endl;
		out << c.tipColoana << endl;
		out << c.dimensiune << endl;
		out << c.nrInregistrari << endl;
		for (int i = 0; i < c.nrInregistrari; i++)
		{
			out << *c.inregistrari[i];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Coloana& c)
	{

		cout << "Introduzca el nombre de la columna:";
		in >> c.numeColoana;
		cout << "Introduzca el tipo de columna: ";
		in >> c.tipColoana;
		cout << "Introduzca el tamaño de la columna: ";
		in >> c.dimensiune;
		cout << "Introduzca su número de registro: ";
		delete[]c.inregistrari;
		in >> c.nrInregistrari;
		c.inregistrari = new Inregistrare * [c.nrInregistrari];
		for (int i = 0; i < c.nrInregistrari; i++)
		{
			c.inregistrari[i] = new Inregistrare();
			in >> *c.inregistrari[i];
		}


		return in;
	}
	friend ifstream& operator>>(ifstream& in, Coloana& c)
	{

		in >> c.numeColoana;
		in >> c.tipColoana;
		in >> c.dimensiune;
		delete[]c.inregistrari;
		in >> c.nrInregistrari;
		c.inregistrari = new Inregistrare * [c.nrInregistrari];
		for (int i = 0; i < c.nrInregistrari; i++)
		{
			c.inregistrari[i] = new Inregistrare();
			in >> *c.inregistrari[i];
		}


		return in;
	}
	//operator cast
	explicit operator string()
	{
		return this->numeColoana;
	}
	Coloana& operator+=(Inregistrare& in)
	{
		Coloana cp = *this;
		delete[]inregistrari;
		this->nrInregistrari++;
		this->inregistrari = new Inregistrare * [this->nrInregistrari];
		for (int i = 0; i < cp.nrInregistrari; i++)
		{
			this->inregistrari[i] = cp.inregistrari[i];
		}
		this->inregistrari[this->nrInregistrari - 1] = &in;
		return *this;
	}
	Coloana& operator -=(Inregistrare& in)
	{
		int aux = 0;
		Coloana cp = *this;
		for (int i = 0; i < this->nrInregistrari; i++)
		{
			if (this->inregistrari[i] == &in)
			{
				aux++;
			}
		}
		delete[]this->inregistrari;
		this->nrInregistrari = this->nrInregistrari - aux;
		this->inregistrari = new Inregistrare * [this->nrInregistrari];
		int loc = 0;
		for (int i = 0; i < cp.nrInregistrari; i++)
		{
			if (cp.inregistrari[i] != &in)
			{
				this->inregistrari[loc] = cp.inregistrari[i];
				loc++;
			}
		}
		return *this;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		int LgNumeColoana = this->numeColoana.length();
		fisier.write((char*)&LgNumeColoana, sizeof(int));
		fisier.write(this->numeColoana.c_str(), LgNumeColoana);
		int LgTipColoana = this->tipColoana.length();
		fisier.write((char*)&LgTipColoana, sizeof(int));
		fisier.write(this->tipColoana.c_str(), LgTipColoana);
		fisier.write((char*)&this->dimensiune, sizeof(float));
		fisier.write((char*)&this->nrInregistrari, sizeof(int));
		for (int i = 0; i < this->nrInregistrari; i++)
		{
			fisier.write((char*)&*this->inregistrari[i], sizeof(*this->inregistrari[i]));
		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		if (this->inregistrari != NULL)
		{
			delete[] this->inregistrari;
		}
		int LgNumeColoana;
		fisier.read((char*)&LgNumeColoana, sizeof(int));
		string a;
		a.resize(LgNumeColoana);
		fisier.read((char*)a.c_str(), LgNumeColoana);
		this->numeColoana = a;
		int LgTipColoana;
		fisier.read((char*)&LgTipColoana, sizeof(int));
		string b;
		b.resize(LgTipColoana);
		fisier.read((char*)b.c_str(), LgTipColoana);
		this->tipColoana = a;
		fisier.read((char*)&this->dimensiune, sizeof(float));
		fisier.read((char*)&this->nrInregistrari, sizeof(int));
		this->inregistrari = new Inregistrare * [this->nrInregistrari];
		for (int i = 0; i < this->nrInregistrari; i++)
		{
			this->inregistrari[i] = new Inregistrare();
			fisier.read((char*)&*this->inregistrari[i], sizeof(*inregistrari[i]));
		}

	}
};
class Tabela
{
	string cheiePrimara="ch";
	string denumireTabela;
	int nrColoane;
	Coloana** coloane;


public:
	//constructor fara parametri
	Tabela()
	{
		this->denumireTabela = "Desconocido";
		this->nrColoane = 0;
		this->coloane = NULL;
	}
	Tabela( string denumireTabela)
	{
		this->denumireTabela = denumireTabela;
		this->nrColoane = 0;
		this->coloane = NULL;
	}
	//constructor cu toti parametri
	Tabela( string denumireTabela, int nrColoane, Coloana** coloane)
	{
	
		this->denumireTabela = denumireTabela;
		this->nrColoane = nrColoane;
		this->coloane = new Coloana * [nrColoane];
		for (int i = 0; i < this->nrColoane; i++)
		{
			this->coloane[i] = coloane[i];
		}
	}
	string getCheiePrimara()
	{
		return this->cheiePrimara;
	}
	string getDenumireTabela()
	{
		return this->denumireTabela;
	}
	Coloana** getColoana()
	{
		return this->coloane;
	}
	int getNrColoane()
	{
		return this->nrColoane;
	}

	void setCheiePrimara(string cheiePrimara)
	{
		this->cheiePrimara = cheiePrimara;
	}
	void setDenumireTabela(string denumireTabela)
	{
		this->denumireTabela = denumireTabela;
	}

	void setNrColoane(int nrColoane)
	{
		this->nrColoane = nrColoane;
	}
	void setColoana(int nrColoane, Coloana** coloane)
	{
		if (nrColoane > 0 && coloane != NULL)
		{
			this->nrColoane = nrColoane;
			this->coloane = new Coloana * [this->nrColoane];
			for (int i = 0; i < nrColoane; i++)
			{
				this->coloane[i] = coloane[i];
			}
		}
	}
	//destructor
	~Tabela()
	{
		if (this->coloane != NULL)
		{
			delete[]this->coloane;
		}

	}
	//constructor de copiere
	Tabela(const Tabela& t)
	{

		this->cheiePrimara = t.cheiePrimara;
		this->denumireTabela = t.denumireTabela;
		this->nrColoane = t.nrColoane;
		this->coloane = new Coloana * [t.nrColoane];
		for (int i = 0; i < this->nrColoane; i++)
		{
			this->coloane[i] = t.coloane[i];
		}

	}
	Tabela& operator=(const Tabela& t)
	{
		if (this->coloane != NULL)
		{
			delete[]this->coloane;
		}

		this->cheiePrimara = t.cheiePrimara;
		this->denumireTabela = t.denumireTabela;
		this->nrColoane = t.nrColoane;
		this->coloane = new Coloana * [t.nrColoane];
		for (int i = 0; i < this->nrColoane; i++)
		{
			this->coloane[i] = t.coloane[i];
		}
		return*this;
	}
	friend ostream& operator<<(ostream& out, const Tabela& t)
	{

		out << t.denumireTabela << endl;
		out << "Sin columnas:" << t.nrColoane << endl << endl;
		for (int i = 0; i < t.nrColoane; i++)
		{
			out << *t.coloane[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Tabela& t)
	{
		out << t.denumireTabela << endl;
		out << t.nrColoane << endl;
		for (int i = 0; i < t.nrColoane; i++)
		{
			out << *t.coloane[i] << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Tabela& t)
	{
		cout << "Introducir nombreTabla: ";

		in >> t.denumireTabela;
		cout << "Introduzca el número de columnas: ";
		delete[]t.coloane;
		in >> t.nrColoane;
		t.coloane = new Coloana * [t.nrColoane];
		for (int i = 0; i < t.nrColoane; i++)
		{
			t.coloane[i] = new Coloana();
			in >> *t.coloane[i];
		}

		return in;
	}
	friend ifstream& operator>>(ifstream& in, Tabela& t)
	{


		in >> t.denumireTabela;
		delete[]t.coloane;
		in >> t.nrColoane;
		t.coloane = new Coloana * [t.nrColoane];
		for (int i = 0; i < t.nrColoane; i++)
		{
			t.coloane[i] = new Coloana();
			in >> *t.coloane[i];
		}

		return in;
	}
	bool operator ==(const Tabela& t)
	{
		return this->denumireTabela == t.denumireTabela;
	}
	Tabela& operator+=(Coloana& c)
	{
		Tabela cp = *this;
		delete[]coloane;
		this->nrColoane++;
		this->coloane = new Coloana * [this->nrColoane];
		for (int i = 0; i < cp.nrColoane; i++)
		{
			this->coloane[i] = cp.coloane[i];
		}
		this->coloane[this->nrColoane - 1] = &c;
		return *this;
	}
	Tabela& operator -=(Coloana& c)
	{
		int aux = 0;
		Tabela cp = *this;
		for (int i = 0; i < this->nrColoane; i++)
		{
			if (this->coloane[i] == &c)
			{
				aux++;
			}
		}
		delete[]this->coloane;
		this->nrColoane = this->nrColoane - aux;
		this->coloane = new Coloana * [this->nrColoane];
		int loc = 0;
		for (int i = 0; i < cp.nrColoane; i++)
		{
			if (cp.coloane[i] != &c)
			{
				this->coloane[loc] = cp.coloane[i];
				loc++;
			}
		}
		return *this;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		int LgCheiePrimara = this->cheiePrimara.length();
		fisier.write((char*)&LgCheiePrimara, sizeof(int));
		fisier.write(this->cheiePrimara.c_str(), LgCheiePrimara);
		int LgDenumireTabela = this->denumireTabela.length();
		fisier.write((char*)&LgDenumireTabela, sizeof(int));
		fisier.write(this->denumireTabela.c_str(), LgDenumireTabela);
		fisier.write((char*)&this->nrColoane, sizeof(int));
		for (int i = 0; i < this->nrColoane; i++)
		{
			fisier.write((char*)&*this->coloane[i], sizeof(*coloane[i]));
		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		if (this->coloane != NULL)
		{
			delete[] this->coloane;
		}
		int LgCheiePrimara;
		fisier.read((char*)&LgCheiePrimara, sizeof(int));
		string a;
		a.resize(LgCheiePrimara);
		fisier.read((char*)a.c_str(), LgCheiePrimara);
		this->cheiePrimara = a;
		int LgDenumireTabela;
		fisier.read((char*)&LgDenumireTabela, sizeof(int));
		string b;
		b.resize(LgDenumireTabela);
		fisier.read((char*)b.c_str(), LgDenumireTabela);
		this->denumireTabela = a;
		fisier.read((char*)&this->nrColoane, sizeof(int));
		this->coloane = new Coloana * [this->nrColoane];
		for (int i = 0; i < this->nrColoane; i++)
		{
			this->coloane[i] = new Coloana();
			fisier.read((char*)&*this->coloane[i], sizeof(*coloane[i]));
		}

	}

};
class BD
{
	string numeBD;
	int nrTabele;
	Tabela** tabele;

public:
	//constructor fara parametrii
	BD()
	{
		this->numeBD = " ";
		this->nrTabele = 0;
		this->tabele = NULL;
	}
	//constructor cu toti parametrii
	BD(string numeBD, int nrTabele, Tabela** tabele)
	{
		this->numeBD = numeBD;
		this->nrTabele = nrTabele;
		this->tabele = new Tabela * [nrTabele];
		for (int i = 0; i < this->nrTabele; i++)
		{
			this->tabele[i] = tabele[i];
		}
	}

	//getteri
	string getNumeBD()
	{
		return this->numeBD;
	}
	Tabela** getTabel()
	{
		return this->tabele;
	}
	int getNrTabele()
	{
		return this->nrTabele;
	}
	//setteri
	void setNumeBD(string numeBD)
	{
		this->numeBD = numeBD;

	}
	void setNrTabele(int nrTabele)
	{
		this->nrTabele = nrTabele;
	}
	void setTabele(int nrTabele, Tabela** tabele)
	{
		if (nrTabele > 0 && tabele != NULL)
		{
			this->nrTabele = nrTabele;
			this->tabele = new Tabela * [this->nrTabele];
			for (int i = 0; i < nrTabele; i++)
			{
				this->tabele[i] = tabele[i];
			}
		}
	}
	//destructor
	~BD()
	{

		if (this->tabele != NULL)
		{
			delete[]this->tabele;
		}
	}

	//constructorul de copiere
	BD(const BD& b)
	{
		this->numeBD = b.numeBD;

		this->nrTabele = b.nrTabele;
		this->tabele = new Tabela * [b.nrTabele];
		for (int i = 0; i < this->nrTabele; i++)
		{
			this->tabele[i] = b.tabele[i];
		}

	}

	//operator<<
	friend ostream& operator<<(ostream& out, const BD& b)
	{

		out << "NumeBD: " << b.numeBD << endl;
		out << "Nr Tabele :" << b.nrTabele << endl;
		for (int i = 0; i < b.nrTabele; i++)
		{
			out << *b.tabele[i] << endl;
		}
		return out;

	}
	friend ofstream& operator<<(ofstream& out, const BD& b)
	{

		out << b.numeBD << endl;
		out << b.nrTabele << endl;
		for (int i = 0; i < b.nrTabele; i++)
		{
			out << *b.tabele[i] << endl;
		}
		return out;

	}
	//operatorul >>

	friend istream& operator>>(istream& in, BD& b)
	{
		cout << "Introduzca el nombre de la base de datos: ";
		in >> b.numeBD;
		cout << "Introduzca el número de tablas: ";
		delete[]b.tabele;
		in >> b.nrTabele;
		b.tabele = new Tabela * [b.nrTabele];
		for (int i = 0; i < b.nrTabele; i++)
		{
			b.tabele[i] = new Tabela();
			in >> *b.tabele[i];
		}

		return in;
	}
	friend ifstream& operator>>(ifstream& in, BD& b)
	{

		in >> b.numeBD;
		delete[]b.tabele;
		in >> b.nrTabele;
		b.tabele = new Tabela * [b.nrTabele];
		for (int i = 0; i < b.nrTabele; i++)
		{
			b.tabele[i] = new Tabela();
			in >> *b.tabele[i];
		}

		return in;
	}
	//operator =
	BD& operator=(const BD& b)
	{
		if (this != &b)
		{

			if (this->tabele != NULL)
			{
				delete[]this->tabele;
			}
			this->numeBD = b.numeBD;
			this->nrTabele = b.nrTabele;
			this->tabele = new Tabela * [b.nrTabele];
			for (int i = 0; i < this->nrTabele; i++)
			{
				this->tabele[i] = b.tabele[i];
			}

		}
		return *this;
	}


	BD& operator+=(Tabela& t)
	{
		BD cp = *this;
		delete[]tabele;
		this->nrTabele++;
		this->tabele = new Tabela * [this->nrTabele];
		for (int i = 0; i < cp.nrTabele; i++)
		{
			this->tabele[i] = cp.tabele[i];
		}
		this->tabele[this->nrTabele - 1] = &t;
		return *this;
	}
	BD& operator -=(Tabela& t)
	{
		int aux = 0;
		BD cp = *this;
		for (int i = 0; i < this->nrTabele; i++)
		{
			if (this->tabele[i] == &t)
			{
				aux++;
			}
		}
		delete[]this->tabele;
		this->nrTabele = this->nrTabele - aux;
		this->tabele = new Tabela * [this->nrTabele];
		int loc = 0;
		for (int i = 0; i < cp.nrTabele; i++)
		{
			if (cp.tabele[i] != &t)
			{
				this->tabele[loc] = cp.tabele[i];
				loc++;
			}
		}
		return *this;
	}
	void scriereInFisierBinar(fstream& fisier)
	{

		int LgNumeBD = this->numeBD.length();
		fisier.write((char*)&LgNumeBD, sizeof(int));
		fisier.write(this->numeBD.c_str(), LgNumeBD);
		fisier.write((char*)&this->nrTabele, sizeof(int));
		for (int i = 0; i < this->nrTabele; i++)
		{
			fisier.write((char*)&*this->tabele[i], sizeof(*this->tabele[i]));
		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		if (this->tabele != NULL)
		{
			delete[] this->tabele;
		}
		int LgNumeBD;
		fisier.read((char*)&LgNumeBD, sizeof(int));
		string a;
		a.resize(LgNumeBD);
		fisier.read((char*)a.c_str(), LgNumeBD);
		this->numeBD = a;
		fisier.read((char*)&this->nrTabele, sizeof(int));
		this->tabele = new Tabela * [this->nrTabele];
		for (int i = 0; i < this->nrTabele; i++)
		{
			this->tabele[i] = new Tabela();
			fisier.read((char*)&*this->tabele[i], sizeof(*this->tabele[i]));
		}

	}

};

class Legatura
{
	string denumireLegatura;
public:
	//constructor fara parametri
	Legatura()
	{
		this->denumireLegatura = "Anonim";
	}
	//constructor cu toti parametri
	Legatura(string denumireLegatura)
	{
		this->denumireLegatura = denumireLegatura;
	}
	//getteri
	string getDenumireLegatura()
	{
		return this->denumireLegatura;
	}
	//setteri
	void setDenumireLegatura(string denumireLegatura)
	{
		this->denumireLegatura = denumireLegatura;
	}

	//constructorul de copiere
	Legatura(const Legatura& l)
	{
		this->denumireLegatura = l.denumireLegatura;
	}
	Legatura& operator=(const Legatura& l)
	{
		this->denumireLegatura = l.denumireLegatura;
		return*this;
	}


	friend ostream& operator<<(ostream& out, const Legatura& l)
	{

		out << "Nombre del enlace: " << l.denumireLegatura << endl;


		return out;
	}
	friend istream& operator>>(istream& in, Legatura& l)
	{

		cout << "Introduzca el nombre del enlace:";
		in >> l.denumireLegatura;

		return in;
	}
};
class CreeazaTabela
{

	int nrBD = 1;
	BD** baze;

public:
	//constructor fara parametrii
	CreeazaTabela()
	{

		this->nrBD = 0;
		this->baze = NULL;
	}
	//constructor cu toti parametrii
	CreeazaTabela(BD& baze)
	{

		this->baze = new BD * [nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			this->baze[i] = &baze;
		}
	}

	//getteri

	BD** getBD()
	{
		return this->baze;
	}
	int getNrBD()
	{
		return this->nrBD;
	}
	//setteri

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
	//destructor
	~CreeazaTabela()
	{

		if (this->baze != NULL)
		{
			delete[]this->baze;
		}
	}

	//constructorul de copiere
	CreeazaTabela(const CreeazaTabela& b)
	{

		this->baze = new BD * [b.nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			this->baze[i] = b.baze[i];
		}

	}

	//operator<<
	friend ostream& operator<<(ostream& out, const CreeazaTabela& b)
	{

		out << "Nr baze :" << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;

	}
	friend ofstream& operator<<(ofstream& out, const CreeazaTabela& b)
	{

		out << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;

	}
	//operatorul >>

	friend istream& operator>>(istream& in, CreeazaTabela& b)
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
	friend ifstream& operator>>(ifstream& in, CreeazaTabela& b)
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
	CreeazaTabela& operator+=(Tabela& t)
	{
		*this->baze[0] += t;
		return *this;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		fisier.write((char*)&nrBD, sizeof(nrBD));

		for (int i = 0; i < this->nrBD; i++)
		{
			fisier.write((char*)&*baze[i], sizeof(*baze[i]));

		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		fisier.read((char*)&nrBD, sizeof(nrBD));
		delete[] baze;
		baze = new BD * [this->nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			baze[i] = new BD();
			fisier.read((char*)&*baze[i], sizeof(*baze[i]));
		}


	}

};
class EliminaTabela
{
	int nrBD = 1;
	BD** baze;
public:
	EliminaTabela()
	{
		this->nrBD = 0;
		this->baze = NULL;
	}
	EliminaTabela(BD& baze)
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
	~EliminaTabela()
	{
		if (this->baze != NULL)
		{
			delete[]this->baze;
		}
	}

	EliminaTabela(const EliminaTabela& b)
	{

		this->baze = new BD * [b.nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			this->baze[i] = b.baze[i];
		}

	}

	EliminaTabela& operator=(const EliminaTabela& b)
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
	friend ostream& operator<<(ostream& out, const EliminaTabela& b)
	{
		out << "Nr baze :" << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const EliminaTabela& b)
	{

		out << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, EliminaTabela& b)
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
	friend ifstream& operator >>(ifstream& in, EliminaTabela& b)
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

	EliminaTabela& operator-=(Tabela& t)
	{
		*this->baze[0] += t;
		return *this;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		fisier.write((char*)&nrBD, sizeof(nrBD));

		for (int i = 0; i < this->nrBD; i++)
		{
			fisier.write((char*)&*baze[i], sizeof(*baze[i]));

		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		fisier.read((char*)&nrBD, sizeof(nrBD));
		delete[] baze;
		baze = new BD * [this->nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			baze[i] = new BD();
			fisier.read((char*)&*baze[i], sizeof(*baze[i]));
		}


	}
};
class InsereazaInTabela
{
	int nrTab = 1;
	Tabela** tb;
public:
	InsereazaInTabela()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	InsereazaInTabela(Tabela& tb)
	{
		this->tb = new Tabela * [nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = &tb;
		}
	}
	Tabela** getTb()
	{
		return this->tb;
	}
	int getNrTab()
	{
		return this->nrTab;
	}
	void setTab(Tabela T)
	{
		if (this->tb != NULL)
		{

			this->tb = new Tabela * [this->nrTab];
			for (int i = 0; i < nrTab; i++)
			{
				this->tb[i] = &T;
			}
		}
	}
	~InsereazaInTabela()
	{

		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	InsereazaInTabela(const InsereazaInTabela& t)
	{
		this->tb = new Tabela * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	InsereazaInTabela& operator=(const InsereazaInTabela& t)
	{
		if (this != &t)
		{
			if (this->tb != NULL)
			{
				delete[]this->tb;
			}
			this->tb = new Tabela * [t.nrTab];
			for (int i = 0; i < this->nrTab; i++)
			{
				this->tb[i] = t.tb[i];
			}

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const InsereazaInTabela& t)
	{
		out << "Nr Tabele :" << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const InsereazaInTabela& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, InsereazaInTabela& t)
	{

		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	friend ifstream& operator >>(ifstream& in, InsereazaInTabela& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	InsereazaInTabela& operator+=(Coloana& c)
	{
		*this->tb[0] += c;
		return *this;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		fisier.write((char*)&nrTab, sizeof(nrTab));

		for (int i = 0; i < this->nrTab; i++)
		{
			fisier.write((char*)&*tb[i], sizeof(*tb[i]));

		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		fisier.read((char*)&nrTab, sizeof(nrTab));
		delete[] tb;
		tb = new Tabela * [this->nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			tb[i] = new Tabela();
			fisier.read((char*)&*tb[i], sizeof(*tb[i]));
		}


	}
};
class ModificaInTabela
{
	int nrTab = 1;
	Tabela** tb;
public:
	ModificaInTabela()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	ModificaInTabela(Tabela& tb)
	{
		this->tb = new Tabela * [nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = &tb;
		}
	}
	Tabela** getTb()
	{
		return this->tb;
	}
	int getNrTab()
	{
		return this->nrTab;
	}
	void setTb(Tabela T)
	{
		if (this->tb != NULL)
		{

			this->tb = new Tabela * [this->nrTab];
			for (int i = 0; i < nrTab; i++)
			{
				this->tb[i] = &T;
			}
		}
	}
	~ModificaInTabela()
	{
		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	ModificaInTabela(const ModificaInTabela& t)
	{
		this->tb = new Tabela * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	ModificaInTabela& operator=(const ModificaInTabela& t)
	{
		if (this != &t)
		{
			if (this->tb != NULL)
			{
				delete[]this->tb;
			}
			this->tb = new Tabela * [t.nrTab];
			for (int i = 0; i < this->nrTab; i++)
			{
				this->tb[i] = t.tb[i];
			}

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ModificaInTabela& t)
	{
		out << "Nr Tabele :" << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const ModificaInTabela& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, ModificaInTabela& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	friend ifstream& operator >>(ifstream& in, ModificaInTabela& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		fisier.write((char*)&nrTab, sizeof(nrTab));

		for (int i = 0; i < this->nrTab; i++)
		{
			fisier.write((char*)&*tb[i], sizeof(*tb[i]));

		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		fisier.read((char*)&nrTab, sizeof(nrTab));
		delete[] tb;
		tb = new Tabela * [this->nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			tb[i] = new Tabela();
			fisier.read((char*)&*tb[i], sizeof(*tb[i]));
		}
	}

};
class StergeDinTabela
{
	int nrTab = 1;
	Tabela** tb;
public:
	StergeDinTabela()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	StergeDinTabela(Tabela& tb)
	{
		this->tb = new Tabela * [nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = &tb;
		}
	}
	Tabela** getTb()
	{
		return this->tb;
	}
	int getNrTab()
	{
		return this->nrTab;
	}
	void setTab(Tabela T)
	{
		if (this->tb != NULL)
		{

			this->tb = new Tabela * [this->nrTab];
			for (int i = 0; i < nrTab; i++)
			{
				this->tb[i] = &T;
			}
		}
	}
	~StergeDinTabela()
	{
		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	StergeDinTabela(const StergeDinTabela& t)
	{
		this->tb = new Tabela * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	StergeDinTabela& operator=(const StergeDinTabela& t)
	{
		if (this != &t)
		{
			if (this->tb != NULL)
			{
				delete[]this->tb;
			}
			this->tb = new Tabela * [t.nrTab];
			for (int i = 0; i < this->nrTab; i++)
			{
				this->tb[i] = t.tb[i];
			}


		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const StergeDinTabela& t)
	{
		out << "Nr Tabele :" << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const StergeDinTabela& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, StergeDinTabela& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	friend ifstream& operator >>(ifstream& in, StergeDinTabela& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	StergeDinTabela& operator-=(Coloana& c)
	{
		*this->tb[0] -= c;
		return *this;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		fisier.write((char*)&nrTab, sizeof(nrTab));

		for (int i = 0; i < this->nrTab; i++)
		{
			fisier.write((char*)&*tb[i], sizeof(*tb[i]));

		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		fisier.read((char*)&nrTab, sizeof(nrTab));
		delete[] tb;
		tb = new Tabela * [this->nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			tb[i] = new Tabela();
			fisier.read((char*)&*tb[i], sizeof(*tb[i]));
		}
	}
};

class ImportaTabela
{
	int nrTab = 1;
	Tabela** tb;
public:
	
	ImportaTabela()
	{
		this->nrTab = 0;
		this->tb = NULL;
	}
	ImportaTabela(Tabela& tb)
	{
		this->tb = new Tabela * [nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = &tb;
		};
	}
	Tabela** geTbl()
	{
		return this->tb;
	}
	int getNrTbl()
	{
		return this->nrTab;
	}
	void setTbl(Tabela T)
	{
		if (this->tb != NULL)
		{

			this->tb = new Tabela * [this->nrTab];
			for (int i = 0; i < nrTab; i++)
			{
				this->tb[i] = &T;
			}
		}
	}
	~ImportaTabela()
	{
		if (this->tb != NULL)
		{
			delete[]this->tb;
		}
	}

	ImportaTabela(const ImportaTabela& t)
	{
		this->tb = new Tabela * [t.nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			this->tb[i] = t.tb[i];
		}
	}

	ImportaTabela& operator=(const ImportaTabela& t)
	{
		if (this != &t)
		{
			if (this->tb != NULL)
			{
				delete[]this->tb;
			}
			this->tb = new Tabela * [t.nrTab];
			for (int i = 0; i < this->nrTab; i++)
			{
				this->tb[i] = t.tb[i];
			}

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ImportaTabela& t)
	{
		out << "Nr Tabele :" << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const ImportaTabela& t)
	{
		out << t.nrTab << endl;
		for (int i = 0; i < t.nrTab; i++)
		{
			out << *t.tb[i] << endl;
		}
		return out;
	}
	friend istream& operator >>(istream& in, ImportaTabela& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	friend ifstream& operator >>(ifstream& in, ImportaTabela& t)
	{
		delete[]t.tb;
		in >> t.nrTab;
		t.tb = new Tabela * [t.nrTab];
		for (int i = 0; i < t.nrTab; i++)
		{
			t.tb[i] = new Tabela();
			in >> *t.tb[i];
		}
		return in;
	}
	void scriereInFisierBinar(fstream& fisier)
	{
		fisier.write((char*)&nrTab, sizeof(nrTab));

		for (int i = 0; i < this->nrTab; i++)
		{
			fisier.write((char*)&*tb[i], sizeof(*tb[i]));

		}
	}
	void citireDinFisierBinar(fstream& fisier)
	{
		fisier.read((char*)&nrTab, sizeof(nrTab));
		delete[] tb;
		tb = new Tabela * [this->nrTab];
		for (int i = 0; i < this->nrTab; i++)
		{
			tb[i] = new Tabela();
			fisier.read((char*)&*tb[i], sizeof(*tb[i]));
		}
	}

};


string introducereComanda()
{
	string temp;
	cout << "Introduzca el comando: ";
	while (!getline(cin, temp) || temp.empty()) {
		cin.clear();
		cin.ignore('\n');
	}
	return temp;
}
string creareComanda(string comanda)
{

	char delimitator = ' ';
	char* comandaValabila = new char[comanda.size() + 1];
	strcpy(comandaValabila, comanda.c_str());
	int nrCuvinte = 1;
	for (int i = 0; i < strlen(comandaValabila); i++)
	{
		if (comandaValabila[i] == delimitator || comandaValabila[i] == '\n')
		{
			nrCuvinte++;
		}
	}

	string* comandaF = new string[nrCuvinte];
	int nr = 0;
	for (int i = 0; i < strlen(comandaValabila); i++)
	{
		if (comandaValabila[i] != delimitator)
		{
			comandaF[nr] = comandaF[nr] + comandaValabila[i];
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
		return "Comanda introdusa este gresita";
	}
}
int main()
{
	//string com = introducereComanda();
	//string comandaTestat = creareComanda(com);
	//identificareComanda(comandaTestat);
	cout << "Registro de clases" << endl;
	Inregistrare in("Tudor", 102);
	Inregistrare in1("Mircea", 103);
	Inregistrare in2("David", 104);
	Inregistrare in3("Catalin", 105);
	Inregistrare in4("23", 102);
	Inregistrare in5("24", 103);
	Inregistrare in6("33", 104);
	Inregistrare in7("42", 105);
	Inregistrare in8("2300", 102);
	Inregistrare in9("2400", 103);
	Inregistrare in10("3000", 104);
	Inregistrare in11("3100", 105);
	Inregistrare in12("Ciocolata", 21);
	Inregistrare in13("Lapte", 22);
	Inregistrare in14("Faina", 23);
	Inregistrare in15("Zahar", 24);
	Inregistrare in16("100", 21);
	Inregistrare in17("1", 22);
	Inregistrare in18("12", 23);
	Inregistrare in19("11", 24);
	Inregistrare in20("8", 21);
	Inregistrare in21("6", 22);
	Inregistrare in22("3.5", 23);
	Inregistrare in23("4", 24);

	cout << in << endl;
	cout << in1 << endl;
	cout << in2 << endl;
	cout << in3 << endl;
	cout << in4 << endl;
	cout << in5 << endl;
	cout << in6 << endl;
	cout << in7 << endl;
	cout << in8 << endl;
	cout << in9 << endl;
	cout << in10 << endl;
	cout << in11 << endl;
	cout << in12 << endl;
	cout << in13 << endl;
	cout << in14 << endl;
	cout << in15 << endl;
	cout << in16 << endl;
	cout << in17 << endl;
	cout << in18 << endl;
	cout << in19 << endl;
	cout << in20 << endl;
	cout << in21 << endl;
	cout << in22 << endl;
	cout << in23 << endl;

	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream fh("inregistrari.txt", ios::out);
	fh << in;
	fh << in1;
	fh.close();
	cout << "Los objetos se han escrito con exito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream fsh("inregistrari.txt", ios::in);
	Inregistrare inr1, inr2;
	if (fsh.is_open())
	{
		fsh >> inr1;
		fsh >> inr2;
		fsh.close();
		cout << "Los objetos fueron leedos con exito desde el archivo" << endl << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << inr1 << endl << endl;
	cout << inr2 << endl << endl;

	cout << endl;

	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binario=======" << endl;
	fstream fbI("fisierBInr.bin", ios::out | ios::binary);
	if (fbI.is_open())
	{
		inr1.scriereInFisierBinar(fbI);
		cout << "Se ha escrito con exito en binario" << endl << endl;
		fbI.close();
	}
	Inregistrare inrBin;
	cout << "=======Lectura de un archivo binario=======" << endl;
	fstream fbIcit("fisierBInr.bin", ios::in | ios::binary);
	if (fbIcit.is_open())
	{
		inrBin.citireDinFisierBinar(fbIcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbIcit.close();
	}
	cout << inrBin << endl;
	cout << "----------------------------------------" << endl;
	cout << endl << endl << endl << endl;
	cout << "Clase de columna" << endl;
	Inregistrare** inregistrari = new Inregistrare * [4];
	inregistrari[0] = &in;
	inregistrari[1] = &in1;
	inregistrari[2] = &in2;
	inregistrari[3] = &in3;
	Coloana c;
	Inregistrare** inregistrari1 = new Inregistrare * [4];
	inregistrari1[0] = &in4;
	inregistrari1[1] = &in5;
	inregistrari1[2] = &in6;
	inregistrari1[3] = &in7;
	Inregistrare** inregistrari2 = new Inregistrare * [4];
	inregistrari2[0] = &in8;
	inregistrari2[1] = &in9;
	inregistrari2[2] = &in10;
	inregistrari2[3] = &in11;


	Coloana c1("Nombre", "char", 25, 4, inregistrari);
	Coloana c2("Edad", "char", 22, 4, inregistrari1);
	Coloana c3("Salario", "char", 31, 4, inregistrari2);
	cout << c1 << endl << endl;
	cout << c2 << endl << endl;
	cout << c3 << endl << endl;


	Inregistrare** inregistrari3 = new Inregistrare * [4];
	inregistrari3[0] = &in12;
	inregistrari3[1] = &in13;
	inregistrari3[2] = &in14;
	inregistrari3[3] = &in15;
	Inregistrare** inregistrari4 = new Inregistrare * [4];
	inregistrari4[0] = &in16;
	inregistrari4[1] = &in17;
	inregistrari4[2] = &in18;
	inregistrari4[3] = &in19;
	Inregistrare** inregistrari5 = new Inregistrare * [4];
	inregistrari5[0] = &in20;
	inregistrari5[1] = &in21;
	inregistrari5[2] = &in22;
	inregistrari5[3] = &in23;

	Coloana c4("Denumire_produs", "char", 14, 4, inregistrari3);
	Coloana c5("Gramaj", "char", 21, 4, inregistrari4);
	Coloana c6("Pret", "char", 25, 4, inregistrari5);
	cout << c4 << endl << endl;
	cout << c5 << endl << endl;
	cout << c6 << endl << endl;

	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream fis("coloane.txt", ios::out);
	fis << c1;
	fis << c2;
	fis.close();
	cout << "Los objetos se han escrito con exito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream fsr("coloane.txt", ios::in);
	Coloana cn1, cn2;
	if (fsr.is_open())
	{
		fsr >> cn1;
		fsr >> cn2;
		fsr.close();
		cout << "Los objetos fueron leedos con exito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << cn1 << endl << endl;
	cout << cn2 << endl << endl;

	cout << endl;

	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binario=======" << endl;
	fstream fbC("fisierBCol.bin", ios::out | ios::binary);
	if (fbC.is_open())
	{
		cn1.scriereInFisierBinar(fbC);
		cn2.scriereInFisierBinar(fbC);
		cout << "Escribir con exito en binario" << endl << endl;
		fbC.close();
	}
	Coloana colBin;
	Coloana colBin2;
	cout << "=======Lectura de un archivo binario=======" << endl;
	fstream fbCcit("fisierBCol.bin", ios::in | ios::binary);
	if (fbCcit.is_open())
	{
		colBin.citireDinFisierBinar(fbCcit);
		colBin2.citireDinFisierBinar(fbCcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbCcit.close();
	}
	cout << colBin << endl;
	cout << colBin2 << endl;
	cout << "----------------------------------------" << endl;
	cout << endl << endl << endl << endl;
	cout << " Clase de tabla" << endl;
	Tabela t;

	Coloana** coloane = new Coloana * [3];
	coloane[0] = &c1;
	coloane[1] = &c2;
	coloane[2] = &c3;
	Tabela t1("Empleados", 3, coloane);
	Coloana** coloane1 = new Coloana * [3];
	coloane1[0] = &c4;
	coloane1[1] = &c5;
	coloane1[2] = &c6;
	Tabela t2("Productos", 3, coloane1);

	cout << t1 << endl;
	cout << t2 << endl;

	cout << "=======Archivos de texto=======" << endl << endl;
	cout << "=======Escribir en un archivo=======" << endl << endl;
	ofstream g("tabele.txt", ios::out);
	g << t1;
	g << t2;
	g.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl << endl;
	cout << "=======Lectura del archivo=======" << endl << endl;
	ifstream gh("tabele.txt", ios::in);
	Tabela tb1, tb2;
	if (gh.is_open())
	{
		gh >> tb1;
		gh >> tb2;
		gh.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo";
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << tb1 << endl << endl;
	cout << tb2 << endl << endl;
	cout << endl;

	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fbT("fisierBTab.bin", ios::out | ios::binary);
	if (fbT.is_open())
	{
		tb1.scriereInFisierBinar(fbT);
		cout << "Escribir con éxito en binario" << endl << endl;
		fbT.close();
	}
	Tabela tabBin;
	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fbTcit("fisierBTab.bin", ios::in | ios::binary);
	if (fbTcit.is_open())
	{
		tabBin.citireDinFisierBinar(fbTcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbTcit.close();
	}
	cout << tabBin << endl;

	cout << "Clasa BD" << endl;

	Tabela** tabele1 = new Tabela * [2];
	tabele1[0] = &t1;
	tabele1[1] = &t2;
	BD b1("Supermercado", 2, tabele1);
	cout << b1 << endl;

	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream h("BazaDeDate.txt", ios::out);
	h << b1;
	h.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream hf("BazaDeDate.txt", ios::in);
	BD bd1, bd2;
	if (hf.is_open())
	{
		hf >> bd1;
		hf >> bd2;
		hf.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << bd1 << endl << endl;
	cout << bd2 << endl << endl;

	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fbBD("fisierBinBD.bin", ios::out | ios::binary);
	if (fbBD.is_open())
	{
		bd1.scriereInFisierBinar(fbBD);
		cout << "Escribir con éxito en binario" << endl << endl;
		fbBD.close();
	}
	BD bdBin;
	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fbBDcit("fisierBinBD.bin", ios::in | ios::binary);
	if (fbBDcit.is_open())
	{
		bdBin.citireDinFisierBinar(fbBDcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbBDcit.close();
	}
	cout << bdBin << endl;

	cout << "|||||||||||||||||||||" << endl << endl << endl << endl;
	cout << "=====Clasa Creeaza Tabela=====" << endl;

	CreeazaTabela ctb(bd1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream hj("Creare.txt", ios::out);
	hj << ctb;
	hj << ctb;
	hj.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream hk("Creare.txt", ios::in);
	CreeazaTabela ct1, ct2, ctBin;
	if (hk.is_open())
	{
		hk >> ct1;
		hk >> ct2;
		hk.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << ct1 << endl << endl;
	cout << ct2 << endl << endl;

	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fcr("fisBinareCreare.bin", ios::out | ios::binary);
	if (fcr.is_open())
	{
		ct1.scriereInFisierBinar(fcr);
		cout << "Escribir con éxito en binario" << endl << endl;
		fcr.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fcrCit("fisBinareCreare.bin", ios::in | ios::binary);
	if (fcrCit.is_open())
	{
		ctBin.citireDinFisierBinar(fcrCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fcrCit.close();
	}
	cout << ctBin << endl;

	cout << "=====Clasa Elimina Tabela=====" << endl;
	EliminaTabela etb(bd1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream j("Eliminari.txt", ios::out);
	j << etb;
	j << etb;
	j.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream jf("Eliminari.txt", ios::in);
	EliminaTabela el1, el2, elBin;
	if (jf.is_open())
	{
		jf >> el1;
		jf >> el2;
		jf.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << el1 << endl << endl;
	cout << el2 << endl << endl;

	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fer("fisBinarElimina.bin", ios::out | ios::binary);
	if (fer.is_open())
	{
		el1.scriereInFisierBinar(fer);
		cout << "Escribir con éxito en binario" << endl << endl;
		fer.close();
	}
	cout << "=======Lectura del archivo binar=======" << endl;
	fstream felCit("fisBinarElimina.bin", ios::in | ios::binary);
	if (felCit.is_open())
	{
		elBin.citireDinFisierBinar(felCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		felCit.close();
	}
	cout << elBin << endl;

	cout << "=====Clasa Insereaza in Tabela=====" << endl;

	InsereazaInTabela instb(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream k("inserari.txt", ios::out);
	k << instb;
	k << instb;
	k.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream kj("inserari.txt", ios::in);
	InsereazaInTabela inser1, inser2, inserBin;
	if (kj.is_open())
	{
		kj >> inser1;
		kj >> inser2;
		kj.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << inser1 << endl << endl;
	cout << inser2 << endl << endl;

	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fin("fisBinareInserare.bin", ios::out | ios::binary);
	if (fin.is_open())
	{
		inser1.scriereInFisierBinar(fin);
		cout << "Escribir con éxito en binario" << endl << endl;
		fin.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream finCit("fisBinareInserare.bin", ios::in | ios::binary);
	if (finCit.is_open())
	{
		inserBin.citireDinFisierBinar(finCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		finCit.close();
	}
	cout << inserBin << endl;

	cout << "=====Clasa Modifica in Tabela=====" << endl;

	ModificaInTabela mod(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream m("modificari.txt", ios::out);
	m << mod;
	m << mod;
	m.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream md("modificari.txt", ios::in);
	ModificaInTabela mod1, mod2, modBin;
	if (md.is_open())
	{
		md >> mod1;
		md >> mod2;
		md.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << mod1 << endl << endl;
	cout << mod2 << endl << endl;


	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fmod("fisBinareModificare.bin", ios::out | ios::binary);
	if (fmod.is_open())
	{
		mod1.scriereInFisierBinar(fmod);
		cout << "Escribir con éxito en binario" << endl << endl;
		fmod.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fmodCit("fisBinareModificare.bin", ios::in | ios::binary);
	if (fmodCit.is_open())
	{
		modBin.citireDinFisierBinar(fmodCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fmodCit.close();
	}
	cout << modBin << endl;

	cout << "=====Clasa Sterge din Tabela=====" << endl;
	StergeDinTabela st(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream s("stergeri.txt", ios::out);
	s << st;
	s << st;
	s.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream sf("stergeri.txt", ios::in);
	StergeDinTabela str1, str2, strBin;
	if (sf.is_open())
	{
		sf >> str1;
		sf >> str2;
		sf.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << str1 << endl << endl;
	cout << str2 << endl << endl;
	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fst("fisBinareStergere.bin", ios::out | ios::binary);
	if (fst.is_open())
	{
		str1.scriereInFisierBinar(fst);
		cout << "Escribir con éxito en binario" << endl << endl;
		fst.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fstCit("fisBinareStergere.bin", ios::in | ios::binary);
	if (fstCit.is_open())
	{
		strBin.citireDinFisierBinar(fstCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fstCit.close();
	}
	cout << strBin << endl;

	cout << "=====Clasa Importa Tabela=====" << endl;
	ImportaTabela imp(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream y("importuri.txt", ios::out);
	y << imp;
	y << imp;
	y.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream yf("importuri.txt", ios::in);
	ImportaTabela impt1, impt2, imptBin;
	if (yf.is_open())
	{
		yf >> impt1;
		yf >> impt2;
		yf.close();
		cout << "Los objetos fueron leídos con éxito desde el archivo" << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	cout << impt1 << endl << endl;
	cout << impt2 << endl << endl;
	cout << "=======Archivos binarios=======" << endl;
	cout << "=======Escribir en un archivo binar=======" << endl;
	fstream fimp("fisBinareImport.bin", ios::out | ios::binary);
	if (fimp.is_open())
	{
		impt1.scriereInFisierBinar(fimp);
		cout << "Escribir con éxito en binario" << endl << endl;
		fimp.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fimpCit("fisBinareInserare.bin", ios::in | ios::binary);
	if (fimpCit.is_open())
	{
		imptBin.citireDinFisierBinar(fimpCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fimpCit.close();
	}
	cout << imptBin << endl;
	cout << endl << endl << "Executie comenzi" << endl << endl;
	Tabela creataPtTeste;
	BD bazaDeDatePTTeste = b1;
	StergeDinTabela sdtTest;
	string com;
	int nrFisiereCreateCuSelect=0;
	CreeazaTabela ctPtTeste1(bazaDeDatePTTeste);
	do
	{
		com = introducereComanda();
		string comandaTestat = creareComanda(com);
		identificareComanda(comandaTestat);
		string Comanda11 = identificareComanda(comandaTestat);

		if (Comanda11 == "create table")
		{
			cout << "Am reusit!" << endl;
			string eliminaCom = com.substr(0, 12);
			cout << eliminaCom << endl;
			string restulComenzii = com.substr(13, -1);
			cout << restulComenzii << endl;
			int nr = 1;
			int nrspatii = 0;
			string numeTabela;
			for (int i = 0; i < restulComenzii.size(); i++)
			{
				if (restulComenzii[i] == ' ' && nrspatii < 1)
				{
					if (restulComenzii[i] != ',')
					{
						nr++;
						nrspatii++;
					}
				}
				if (restulComenzii[i] != ' ')
				{
					nrspatii = 0;
				}
			}
			cout << "La orden es  " << nr << " palabras!" << endl;

			if ((nr - 1) % 3 == 0)
			{
				int pozitie = 0;
				string* cuvinteComanda = new string[nr];
				for (int i = 0; i < restulComenzii.size(); i++)
				{
					if (restulComenzii[i] != ' ')
					{
						if (restulComenzii[i] != ',')
						{
							cuvinteComanda[pozitie] += restulComenzii[i];
						}
					}
					else
					{
						pozitie++;
					}
				}
				string numeTabela = cuvinteComanda[0];
				string numeFisier = numeTabela + ".txt";
				ifstream citNumeTab(numeFisier, ios::in);
				if (citNumeTab.is_open())
				{
					cout << "Din pacate tabela deja exista!" << endl;

				}
				else
				{

					ofstream fTab(numeFisier, ios::out);
					for (int i = 0; i < nr; i++)
					{
						if (i == 1)
						{
							fTab << (nr - 1) / 3 << " " << cuvinteComanda[i] << " ";
						}
						else if (i % 3 == 0 && i > 0)
						{
							fTab << cuvinteComanda[i] << " " << 0 << " ";
						}
						else
						{
							fTab << cuvinteComanda[i] << " ";

						}

					}
					fTab.close();
					ifstream citiTestTab(numeFisier, ios::in);
					Tabela* aux = new Tabela();
					citiTestTab >> *aux;
					ctPtTeste1 += *aux;
				}
			}

			else
			{
				cout << "El comando no tiene todos los detalles para crear columnas!" << endl;
			}
		}
		else if (Comanda11 == "drop table")
		{
			string eliminaCom = com.substr(0, 10);
			string restulComenzii = com.substr(11, -1);
			string numeFisierElim = restulComenzii + ".txt";
			char* eliminator = new char[numeFisierElim.size() + 1];
			strcpy(eliminator, numeFisierElim.c_str());
			if (remove(eliminator) == 0)
				cout << ("La tabla ha sido eliminada!\n");
			else
				cout << ("Tabla inválida. La operación no se realizó!\n");
		}
		else if (Comanda11 == "insert into")
		{
			cout << "Comanda este insert into: " << endl << endl;
			string eliminaCom = com.substr(0, 11);
			cout << eliminaCom << endl;
			string restulComenzii = com.substr(12, -1);
			cout << restulComenzii << endl;
			int nr = 1;
			int nrspatii = 0;
			string numeTabela;
			for (int i = 0; i < restulComenzii.size(); i++)
			{
				if (restulComenzii[i] == ' ' && nrspatii < 1)
				{
					if (restulComenzii[i] != ',')
					{
						nr++;
						nrspatii++;
					}
				}
				if (restulComenzii[i] != ' ')
				{
					nrspatii = 0;
				}
			}
			cout << "La orden es  " << nr << " palabras!" << endl;
			int pozitie = 0;
			string* cuvinteComanda = new string[nr];
			for (int i = 0; i < restulComenzii.size(); i++)
			{
				if (restulComenzii[i] != ' ')
				{
					if (restulComenzii[i] != ',' && restulComenzii[i]!='(' && restulComenzii[i] != ')')
					{
						cuvinteComanda[pozitie] += restulComenzii[i];
					}
				}
				else
				{
					pozitie++;
				}
			}
			int nrcuvDupaValues = 0;
			int nrcuvInainteValues = -1;
			int pozValues = 0;
			for (int i = 0; i < nr; i++)
			{
				if (cuvinteComanda[i] == "VALUES" || cuvinteComanda[i] == "values")
				{
					pozValues = i;
				}
			}
			for (int i = 0; i < nr; i++)
			{
				if (i<pozValues)
				{
					nrcuvInainteValues++;
				}
				else if (i > pozValues)
				{
					nrcuvDupaValues++;
				}
			}
			if (nrcuvDupaValues != nrcuvInainteValues)
			{
				cout << "No ha introducido los datos correctamente!" << endl;
			}
			else
			{
				int nrTabGasite = 0;
				for (int i = 0; i < bazaDeDatePTTeste.getNrTabele(); i++)
				{
					
					string numeTabCautata = bazaDeDatePTTeste.getTabel()[i]->getDenumireTabela();
					if (cuvinteComanda[0] == numeTabCautata)
					{
						nrTabGasite++;
						for (int j = 1; j < pozValues; j++)
						{
							string numeColoanaCautata = cuvinteComanda[j];
							for (int z = 0; z < bazaDeDatePTTeste.getTabel()[i]->getNrColoane(); z++)
							{
								if (cuvinteComanda[j] == bazaDeDatePTTeste.getTabel()[i]->getColoana()[z]->getNumeColoana())
								{
									Inregistrare* ptrInregistrareTest = new Inregistrare();
									ptrInregistrareTest->setInregistrare(cuvinteComanda[j + pozValues]);
									*bazaDeDatePTTeste.getTabel()[i]->getColoana()[z] += *ptrInregistrareTest;
								}
								else
								{
									cout << endl << "Nu exista acea Coloana" << endl;
								}
							}
						}
					}
					if (nrTabGasite == 0)
					{
						cout << "Nu am gasit nicio tabela!" << endl;
					}
				}
			}
		}
		else if (Comanda11 == "delete from")
		{
			string eliminaCom = com.substr(0, 11);
			string restulComenzii = com.substr(12, -1);
			int nrTab=0;
			for (int i = 0; i < bazaDeDatePTTeste.getNrTabele(); i++)
			{
				if (restulComenzii == bazaDeDatePTTeste.getTabel()[i]->getDenumireTabela())
				{
					nrTab++;
					bazaDeDatePTTeste.getTabel()[i]->setNrColoane(0);

				
				}
			}
			if (nrTab == 0)
			{
				cout << " No he encontrado la tabla que buscaba!" << endl;
			}
			else
				cout << "Los datos de la tabla han sido borrados" << endl << endl;
		}
		else if (Comanda11 == "select")
		{
			cout << "Comanda este SELECT!!" << endl;
			string eliminaCom = com.substr(0, 6);
			string restulComenzii = com.substr(7, -1);
			cout << restulComenzii << endl;
			int nr = 1;
			int nrspatii = 0;
			string numeTabela;
			for (int i = 0; i < restulComenzii.size(); i++)
			{
				if (restulComenzii[i] == ' ' && nrspatii < 1)
				{
					if (restulComenzii[i] != ',')
					{
						nr++;
						nrspatii++;
					}
				}
				if (restulComenzii[i] != ' ')
				{
					nrspatii = 0;
				}
			}
			cout << "La orden es  " << nr << " palabras!" << endl;
			int pozitie = 0;
			string* cuvinteComanda = new string[nr];
			for (int i = 0; i < restulComenzii.size(); i++)
			{
				if (restulComenzii[i] != ' ')
				{
					if (restulComenzii[i] != ',')
					{
						cuvinteComanda[pozitie] += restulComenzii[i];
					}
				}
				else
				{
					pozitie++;
				}
			}
			int pozFrom = 0;

			for (int i = 0; i < nr; i++)
			{
				if (cuvinteComanda[i] == "from")
					pozFrom = i;
				cout << cuvinteComanda[i] << " / ";
			}
			if (cuvinteComanda[0] == "*")
			{
				string numeFisierSelect = "SELECT_" + to_string(nrFisiereCreateCuSelect);
				numeFisierSelect += ".txt";
				ofstream afisareSelect(numeFisierSelect);
				for (int i = 0; i < bazaDeDatePTTeste.getNrTabele(); i++)
				{
					if (cuvinteComanda[2] == bazaDeDatePTTeste.getTabel()[i]->getDenumireTabela())
					{
						afisareSelect << *bazaDeDatePTTeste.getTabel()[i];
						cout << *bazaDeDatePTTeste.getTabel()[i] << endl << endl;
					}
				}
				nrFisiereCreateCuSelect++;
				
			}
			else
			{
				string numeFisierSelect = "SELECT_" + to_string(nrFisiereCreateCuSelect);
				numeFisierSelect += ".txt";
				ofstream afisareSelect(numeFisierSelect);
				for (int i = 0; i < bazaDeDatePTTeste.getNrTabele(); i++)
				{
					if (cuvinteComanda[nr-1] == bazaDeDatePTTeste.getTabel()[i]->getDenumireTabela())
					{
						for (int j = 0; j < bazaDeDatePTTeste.getTabel()[i]->getNrColoane(); j++)
						{
							for (int z = 0; z < pozFrom; z++)
							{
								if (cuvinteComanda[z] == bazaDeDatePTTeste.getTabel()[i]->getColoana()[j]->getNumeColoana())
								{
									afisareSelect << *bazaDeDatePTTeste.getTabel()[i]->getColoana()[j];
									cout << *bazaDeDatePTTeste.getTabel()[i]->getColoana()[j] << endl << endl;
								}
							}
						}
					}
				
				}
				nrFisiereCreateCuSelect++;
			}
		}
		else
		{
			cout << "Ha fallado" << endl;
		}



	} while (com.size() >= 3);
	cout << "Las tablas de la base de datos son: ";
	cout << bazaDeDatePTTeste<<endl;
	cout << "-----------------------------------|||---------------------------" << endl;
	cout << ctPtTeste1 << endl; 

}