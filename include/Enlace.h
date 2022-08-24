#pragma once
#include "Registro.h"
#include "Columna.h"
#include "Tabla.h"
#include "BD.h"

// Clase Enlace
class Enlace
{
	string nombreEnlace;
public:
	//constructor sin parámetros
	Enlace()
	{
		this->nombreEnlace = "Anonimo";
	}
	//constructor con todos los parámetros
	Enlace(string nombreEnlace)
	{
		this->nombreEnlace = nombreEnlace;
	}
	//getters
	string getNombreEnlace()
	{
		return this->nombreEnlace;
	}
	//setters
	void setNombreEnlace(string nombreEnlace)
	{
		this->nombreEnlace = nombreEnlace;
	}

	//constructor de copia
	Enlace(const Enlace& l)
	{
		this->nombreEnlace = l.nombreEnlace;
	}
	Enlace& operator=(const Enlace& l)
	{
		this->nombreEnlace = l.nombreEnlace;
		return*this;
	}


	friend ostream& operator<<(ostream& out, const Enlace& l)
	{

		out << "Nombre del enlace: " << l.nombreEnlace << endl;


		return out;
	}
	friend istream& operator>>(istream& in, Enlace& l)
	{

		cout << "Introduzca el nombre del enlace:";
		in >> l.nombreEnlace;

		return in;
	}
};


class CrearTabla
{

	int nrBD = 1;
	BD** baze;

public:
	//constructor sin parámetros
	CrearTabla()
	{

		this->nrBD = 0;
		this->baze = NULL;
	}
	//constructor con todos los parámetros
	CrearTabla(BD& baze)
	{

		this->baze = new BD * [nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			this->baze[i] = &baze;
		}
	}

	//getters

	BD** getBD()
	{
		return this->baze;
	}
	int getNrBD()
	{
		return this->nrBD;
	}
	//setters

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
	~CrearTabla()
	{

		if (this->baze != NULL)
		{
			delete[]this->baze;
		}
	}

	//constructor de copia
	CrearTabla(const CrearTabla& b)
	{

		this->baze = new BD * [b.nrBD];
		for (int i = 0; i < this->nrBD; i++)
		{
			this->baze[i] = b.baze[i];
		}

	}

	// sobrecarga del operator<<
	friend ostream& operator<<(ostream& out, const CrearTabla& b)
	{

		out << "Nr baze :" << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;

	}
	friend ofstream& operator<<(ofstream& out, const CrearTabla& b)
	{

		out << b.nrBD << endl;
		for (int i = 0; i < b.nrBD; i++)
		{
			out << *b.baze[i] << endl;
		}
		return out;

	}
	//operador >>

	friend istream& operator>>(istream& in, CrearTabla& b)
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
	friend ifstream& operator>>(ifstream& in, CrearTabla& b)
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
	CrearTabla& operator+=(Tabla& t)
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