#include "include.h"


int main()
{
	Registro in("Kiro", 102);										//Hacemos unos registros previos para provar la escritura
	Registro in1("Cesar", 103);
	Registro in2("David", 104);
	Registro in3("Gabriel", 105);
	Registro in4("23", 102);
	Registro in5("24", 103);
	Registro in6("33", 104);
	Registro in7("42", 105);
	Registro in8("2300", 102);
	Registro in9("2400", 103);
	Registro in10("3000", 104);
	Registro in11("3100", 105);
	Registro in12("Chocolate", 21);
	Registro in13("Leche", 22);
	Registro in14("Vainilla", 23);
	Registro in15("Azúcar", 24);
	Registro in16("100", 21);
	Registro in17("1", 22);
	Registro in18("12", 23);
	Registro in19("11", 24);
	Registro in20("8", 21);
	Registro in21("6", 22);
	Registro in22("3.5", 23);
	Registro in23("4", 24);
	////////////////////////////////////////////////////////////////
	cout << "=======Escribir en un archivo=======" << endl;					//Se genera un archivo donde guardamos nuestros registros
	ofstream fh("registros.txt", ios::out);
	fh << in;
	fh << in1;
	fh.close();
	cout << "Los objetos se han escrito con exito en el archivo" << endl;
	///////////////////////////////////////////////////////////////
	cout << "=======Lectura del archivo=======" << endl;								//Se hace la lectura de los archivos
	ifstream fsh("registros.txt", ios::in);
	Registro inr1, inr2;
	if (fsh.is_open())
	{
		fsh >> inr1;
		fsh >> inr2;
		fsh.close();
		cout << "Los objetos fueron leidos con exito desde el archivo" << endl << endl;
	}
	else
	{
		cout << "Archivo inexistente" << endl;
	}
	/////////////////////////////////////////////////////////////
	cout << "=======Archivos binarios=======" << endl;						//Lectura y escritura de archivos binarios (.bin)
	cout << "=======Escribir en un archivo binario=======" << endl;
	fstream fbI("registroBInr.bin", ios::out | ios::binary);
	if (fbI.is_open())
	{
		inr1.escribeEnArchivoBinario(fbI);
		cout << "Se ha escrito con exito en binario" << endl << endl;
		fbI.close();
	}
	Registro inrBin;
	cout << "=======Lectura de un archivo binario=======" << endl;
	fstream fbIcit("registroBInr.bin", ios::in | ios::binary);
	if (fbIcit.is_open())
	{
		inrBin.leeDelArchivoBinario(fbIcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbIcit.close();
	}
	cout << inrBin << endl;
	/////////////////////////////////////////////////////////////
	cout << endl;												//Insercion de los registros en columnas
	cout << "Clase de columna" << endl;
	Registro** registros = new Registro * [4];
	registros[0] = &in;
	registros[1] = &in1;
	registros[2] = &in2;
	registros[3] = &in3;
	Columna c;
	Registro** registros1 = new Registro * [4];
	registros1[0] = &in4;
	registros1[1] = &in5;
	registros1[2] = &in6;
	registros1[3] = &in7;
	Registro** registros2 = new Registro * [4];
	registros2[0] = &in8;
	registros2[1] = &in9;
	registros2[2] = &in10;
	registros2[3] = &in11;


	Columna c1("Nombre", "char", 25, 4, registros);
	Columna c2("Edad", "char", 22, 4, registros1);
	Columna c3("Salario", "char", 31, 4, registros2);
	cout << c1 << endl << endl;
	cout << c2 << endl << endl;
	cout << c3 << endl << endl;


	Registro** registros3 = new Registro * [4];
	registros3[0] = &in12;
	registros3[1] = &in13;
	registros3[2] = &in14;
	registros3[3] = &in15;
	Registro** registros4 = new Registro * [4];
	registros4[0] = &in16;
	registros4[1] = &in17;
	registros4[2] = &in18;
	registros4[3] = &in19;
	Registro** registros5 = new Registro * [4];
	registros5[0] = &in20;
	registros5[1] = &in21;
	registros5[2] = &in22;
	registros5[3] = &in23;

	Columna c4("Nombre_producto", "char", 14, 4, registros3);
	Columna c5("Gramaj", "char", 21, 4, registros4);
	Columna c6("Pret", "char", 25, 4, registros5);

	///////////////////////////////////////////////////////
	cout << "=======Archivos de texto=======" << endl;							//Escritura y lectura de las culumnas
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream fis("columnas.txt", ios::out);
	fis << c1;
	fis << c2;
	fis.close();
	cout << "Los objetos se han escrito con exito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream fsr("columnas.txt", ios::in);
	Columna cn1, cn2;
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
	cout << cn1 << endl;
	cout << cn2 << endl;

	cout << "=======Archivos binarios=======" << endl;						//Escritura y lectura de columnas en binario(.bin)
	cout << "=======Escribir en un archivo binario=======" << endl;
	fstream fbC("registroBCol.bin", ios::out | ios::binary);
	if (fbC.is_open())
	{
		cn1.escribeEnArchivoBinario(fbC);
		cn2.escribeEnArchivoBinario(fbC);
		cout << "Escribir con exito en binario" << endl << endl;
		fbC.close();
	}
	Columna colBin;
	Columna colBin2;
	cout << "=======Lectura de un archivo binario=======" << endl;
	fstream fbCcit("registroBCol.bin", ios::in | ios::binary);
	if (fbCcit.is_open())
	{
		colBin.leeDelArchivoBinario(fbCcit);
		colBin2.leeDelArchivoBinario(fbCcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbCcit.close();
	}
	cout << colBin << endl;
	cout << colBin2 << endl;
	//////////////////////////////////////////////////
	cout << "tabla" << endl;
	Tabla t;												//Una tabla será una culumna de columnas

	Columna** columnas = new Columna * [3];
	columnas[0] = &c1;
	columnas[1] = &c2;
	columnas[2] = &c3;
	Tabla t1("Empleados", 3, columnas);
	Columna** columnas1 = new Columna * [3];
	columnas1[0] = &c4;
	columnas1[1] = &c5;
	columnas1[2] = &c6;
	Tabla t2("Productos", 3, columnas1);

	cout << t1 << endl;
	cout << t2 << endl;

	cout << "=======Archivos de texto=======" << endl << endl;
	cout << "=======Escribir en un archivo=======" << endl << endl;
	ofstream g("tabla.txt", ios::out);
	g << t1;
	g << t2;
	g.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl << endl;
	cout << "=======Lectura del archivo=======" << endl << endl;
	ifstream gh("tabla.txt", ios::in);
	Tabla tb1, tb2;
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
	fstream fbT("registroBTab.bin", ios::out | ios::binary);
	if (fbT.is_open())
	{
		tb1.escribeEnArchivoBinario(fbT);
		cout << "Escribir con éxito en binario" << endl << endl;
		fbT.close();
	}
	Tabla tabBin;
	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fbTcit("registroBTab.bin", ios::in | ios::binary);
	if (fbTcit.is_open())
	{
		tabBin.leeDelArchivoBinario(fbTcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbTcit.close();
	}
	cout << tabBin << endl;

	cout << "Clasa BD" << endl;

	Tabla** tabele1 = new Tabla * [2];
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
	fstream fbBD("registroBinBD.bin", ios::out | ios::binary);
	if (fbBD.is_open())
	{
		bd1.escribeEnArchivoBinario(fbBD);
		cout << "Escribir con éxito en binario" << endl << endl;
		fbBD.close();
	}
	BD bdBin;
	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fbBDcit("registroBinBD.bin", ios::in | ios::binary);
	if (fbBDcit.is_open())
	{
		bdBin.leeDelArchivoBinario(fbBDcit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fbBDcit.close();
	}
	cout << bdBin << endl;

	cout << "|||||||||||||||||||||" << endl << endl << endl << endl;
	cout << "=====Clasa Creeaza Tabla=====" << endl;

	CrearTabla ctb(bd1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream hj("Creare.txt", ios::out);
	hj << ctb;
	hj << ctb;
	hj.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream hk("Creare.txt", ios::in);
	CrearTabla ct1, ct2, ctBin;
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
	fstream fcr("Crear_Archivo_Binario.bin", ios::out | ios::binary);
	if (fcr.is_open())
	{
		ct1.escribeEnArchivoBinario(fcr);
		cout << "Escribir con éxito en binario" << endl << endl;
		fcr.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fcrCit("Crear_Archivo_Binario.bin", ios::in | ios::binary);
	if (fcrCit.is_open())
	{
		ctBin.leeDelArchivoBinario(fcrCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fcrCit.close();
	}
	cout << ctBin << endl;

	cout << "=====Clasa Elimina Tabla=====" << endl;
	EliminaTabla etb(bd1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream j("Eliminari.txt", ios::out);
	j << etb;
	j << etb;
	j.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream jf("Eliminari.txt", ios::in);
	EliminaTabla el1, el2, elBin;
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
		el1.escribeEnArchivoBinario(fer);
		cout << "Escribir con éxito en binario" << endl << endl;
		fer.close();
	}
	cout << "=======Lectura del archivo binar=======" << endl;
	fstream felCit("fisBinarElimina.bin", ios::in | ios::binary);
	if (felCit.is_open())
	{
		elBin.leeDelArchivoBinario(felCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		felCit.close();
	}
	cout << elBin << endl;

	cout << "=====Inserciones de clase en la tabla=====" << endl;

	InsertInTable instb(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream k("inserciones.txt", ios::out);
	k << instb;
	k << instb;
	k.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream kj("inserciones.txt", ios::in);
	InsertInTable inser1, inser2, inserBin;
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
	fstream fin("Insertar_en_Binario.bin", ios::out | ios::binary);
	if (fin.is_open())
	{
		inser1.escribeEnArchivoBinario(fin);
		cout << "Escribir con éxito en binario" << endl << endl;
		fin.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream finCit("Insertar_en_Binario.bin", ios::in | ios::binary);
	if (finCit.is_open())
	{
		inserBin.leeDelArchivoBinario(finCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		finCit.close();
	}
	cout << inserBin << endl;

	cout << "=====Clasa Modifica in Tabla=====" << endl;

	ModificaInTabla mod(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream m("modificaciones.txt", ios::out);
	m << mod;
	m << mod;
	m.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream md("modificaciones.txt", ios::in);
	ModificaInTabla mod1, mod2, modBin;
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
	fstream fmod("Modificar_Binario.bin", ios::out | ios::binary);
	if (fmod.is_open())
	{
		mod1.escribeEnArchivoBinario(fmod);
		cout << "Escribir con éxito en binario" << endl << endl;
		fmod.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fmodCit("Modificar_Binario.bin", ios::in | ios::binary);
	if (fmodCit.is_open())
	{
		modBin.leeDelArchivoBinario(fmodCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fmodCit.close();
	}
	cout << modBin << endl;

	cout << "=====Clasa Sterge din Tabla=====" << endl;
	DeleteInTabla st(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream s("eliminaciones.txt", ios::out);
	s << st;
	s << st;
	s.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream sf("eliminaciones.txt", ios::in);
	DeleteInTabla str1, str2, strBin;
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
	fstream fst("Borrar_del_Binario.bin", ios::out | ios::binary);
	if (fst.is_open())
	{
		str1.escribeEnArchivoBinario(fst);
		cout << "Escribir con éxito en binario" << endl << endl;
		fst.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fstCit("Borrar_del_Binario.bin", ios::in | ios::binary);
	if (fstCit.is_open())
	{
		strBin.leeDelArchivoBinario(fstCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fstCit.close();
	}
	cout << strBin << endl;

	cout << "=====Clasa Importa Tabla=====" << endl;
	ImportarTabla imp(t1);
	cout << "=======Archivos de texto=======" << endl;
	cout << "=======Escribir en un archivo=======" << endl;
	ofstream y("importaciones.txt", ios::out);
	y << imp;
	y << imp;
	y.close();
	cout << "Los objetos se han escrito con éxito en el archivo" << endl;
	cout << "=======Lectura del archivo=======" << endl;
	ifstream yf("importaciones.txt", ios::in);
	ImportarTabla impt1, impt2, imptBin;
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
	fstream fimp("Importar_del_Binario.bin", ios::out | ios::binary);
	if (fimp.is_open())
	{
		impt1.escribeEnArchivoBinario(fimp);
		cout << "Escribir con éxito en binario" << endl << endl;
		fimp.close();
	}

	cout << "=======Lectura del archivo binar=======" << endl;
	fstream fimpCit("Insertar_en_Binario.bin", ios::in | ios::binary);
	if (fimpCit.is_open())
	{
		imptBin.leeDelArchivoBinario(fimpCit);
		cout << "Lectura exitosa del binario" << endl << endl;
		fimpCit.close();
	}
	cout << imptBin << endl;
	cout << endl << endl << "Ejecucion de la orden" << endl << endl;
	Tabla creataPtTeste;
	BD Prueba_BD = b1;
	DeleteInTabla sdtTest;
	string com;
	int nrArchivoeCreateCuSelect=0;
	CrearTabla ctPtTeste1(Prueba_BD);
	do
	{
		com = introducirComando();
		string comandaTestat = crearComando(com);
		identificareComanda(comandaTestat);
		string Comanda11 = identificareComanda(comandaTestat);

		if (Comanda11 == "create table")
		{
			cout << "Lo hemos conseguido." << endl;
			string eliminaCom = com.substr(0, 12);
			cout << eliminaCom << endl;
			string restulComenzii = com.substr(13, -1);
			cout << restulComenzii << endl;
			int nr = 1;
			int nrspatii = 0;
			string numeTabla;
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
				string numeTabla = cuvinteComanda[0];
				string numeArchivo = numeTabla + ".txt";
				ifstream citNumeTab(numeArchivo, ios::in);
				if (citNumeTab.is_open())
				{
					cout << "Lamentablemente la tabla ya existe!" << endl;

				}
				else
				{

					ofstream fTab(numeArchivo, ios::out);
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
					ifstream citiTestTab(numeArchivo, ios::in);
					Tabla* aux = new Tabla();
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
			string numeArchivoElim = restulComenzii + ".txt";
			char* eliminator = new char[numeArchivoElim.size() + 1];
			strcpy(eliminator, numeArchivoElim.c_str());
			if (remove(eliminator) == 0)
				cout << ("La tabla ha sido eliminada!\n");
			else
				cout << ("Tabla inválida. La operación no se realizó!\n");
		}
		else if (Comanda11 == "insert into")
		{
			cout << "El comando es insert into: " << endl << endl;
			string eliminaCom = com.substr(0, 11);
			cout << eliminaCom << endl;
			string restulComenzii = com.substr(12, -1);
			cout << restulComenzii << endl;
			int nr = 1;
			int nrspatii = 0;
			string numeTabla;
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
				for (int i = 0; i < Prueba_BD.getNrTabla(); i++)
				{
					
					string numeTabCautata = Prueba_BD.getTabla()[i]->getNombreTabla();
					if (cuvinteComanda[0] == numeTabCautata)
					{
						nrTabGasite++;
						for (int j = 1; j < pozValues; j++)
						{
							string numeColumnaCautata = cuvinteComanda[j];
							for (int z = 0; z < Prueba_BD.getTabla()[i]->getNrColumnas(); z++)
							{
								if (cuvinteComanda[j] == Prueba_BD.getTabla()[i]->getColumna()[z]->getNumeColumna())
								{
									Registro* ptrRegistroTest = new Registro();
									ptrRegistroTest->setRegistro(cuvinteComanda[j + pozValues]);
									*Prueba_BD.getTabla()[i]->getColumna()[z] += *ptrRegistroTest;
								}
								else
								{
									cout << endl << "No existe tal Columna" << endl;
								}
							}
						}
					}
					if (nrTabGasite == 0)
					{
						cout << "No se ha encontrado ninguna tabla!" << endl;
					}
				}
			}
		}
		else if (Comanda11 == "delete from")
		{
			string eliminaCom = com.substr(0, 11);
			string restulComenzii = com.substr(12, -1);
			int nrTab=0;
			for (int i = 0; i < Prueba_BD.getNrTabla(); i++)
			{
				if (restulComenzii == Prueba_BD.getTabla()[i]->getNombreTabla())
				{
					nrTab++;
					Prueba_BD.getTabla()[i]->setNrColumnas(0);

				
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
			cout << "El comando es SELECT!!" << endl;
			string eliminaCom = com.substr(0, 6);
			string restulComenzii = com.substr(7, -1);
			cout << restulComenzii << endl;
			int nr = 1;
			int nrspatii = 0;
			string numeTabla;
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
				string numeArchivoSelect = "SELECT_" + to_string(nrArchivoeCreateCuSelect);
				numeArchivoSelect += ".txt";
				ofstream afisareSelect(numeArchivoSelect);
				for (int i = 0; i < Prueba_BD.getNrTabla(); i++)
				{
					if (cuvinteComanda[2] == Prueba_BD.getTabla()[i]->getNombreTabla())
					{
						afisareSelect << *Prueba_BD.getTabla()[i];
						cout << *Prueba_BD.getTabla()[i] << endl << endl;
					}
				}
				nrArchivoeCreateCuSelect++;
				
			}
			else
			{
				string numeArchivoSelect = "SELECT_" + to_string(nrArchivoeCreateCuSelect);
				numeArchivoSelect += ".txt";
				ofstream afisareSelect(numeArchivoSelect);
				for (int i = 0; i < Prueba_BD.getNrTabla(); i++)
				{
					if (cuvinteComanda[nr-1] == Prueba_BD.getTabla()[i]->getNombreTabla())
					{
						for (int j = 0; j < Prueba_BD.getTabla()[i]->getNrColumnas(); j++)
						{
							for (int z = 0; z < pozFrom; z++)
							{
								if (cuvinteComanda[z] == Prueba_BD.getTabla()[i]->getColumna()[j]->getNumeColumna())
								{
									afisareSelect << *Prueba_BD.getTabla()[i]->getColumna()[j];
									cout << *Prueba_BD.getTabla()[i]->getColumna()[j] << endl << endl;
								}
							}
						}
					}
				
				}
				nrArchivoeCreateCuSelect++;
			}
		}
		else
		{
			cout << "Ha fallado" << endl;
		}

	} while (com.size() >= 3);
	cout << "Las tablas de la base de datos son: ";
	cout << Prueba_BD<<endl;
	cout << "-----------------------------------|||---------------------------" << endl;
	cout << ctPtTeste1 << endl; 

}