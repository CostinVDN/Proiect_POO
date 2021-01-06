#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Bilete
{

private:
	const int codBilet;
	char* dataBilet;
	string DataFilm; //Data cand uleaza fimul
	int* OreRulare; // La ce ore ruleaza un film intr-o zi
	int nrSpectacole;
	static int nrBileteEmise;
	float pret;
	int idFilm;
	int rand;
	int loc;

public:

	Bilete() : codBilet{ ++nrBileteEmise }
	{

		dataBilet = nullptr;
		OreRulare = nullptr;
		idFilm = 0;
		pret = 0.0;
		rand = 0;
		loc = 0;
		nrSpectacole = 0;

	}

	Bilete(char* dataBilet, string DataFilm, int* OreRulare, int nrSpectacole, int idFilm, float pret, int rand, int loc)
		: codBilet{ ++nrBileteEmise }
	{

		if (dataBilet != nullptr)
		{

			this->dataBilet = new char[strlen(dataBilet) + 1];
			strcpy_s(this->dataBilet, strlen(dataBilet) + 1, dataBilet);

		}
		else
		{

			dataBilet = nullptr;

		}

		if (OreRulare != nullptr)
		{

			this->OreRulare = new int[nrSpectacole];
			for (int indx = 0; indx < nrSpectacole; indx++)
			{

				this->OreRulare[indx] = OreRulare[indx];

			}

		}
		else
		{

			this->OreRulare = nullptr;

		}

		this->nrSpectacole = nrSpectacole;
		this->DataFilm = DataFilm;
		this->pret = pret;
		this->rand = rand;
		this->loc = loc;
		this->idFilm = idFilm;

	}

	Bilete(const Bilete& b) : codBilet{ b.codBilet }
	{

		if (b.dataBilet != nullptr)
		{

			this->dataBilet = new char[strlen(b.dataBilet) + 1];
			strcpy_s(this->dataBilet, strlen(b.dataBilet) + 1, b.dataBilet);

		}
		else
		{

			this->dataBilet = nullptr;

		}

		if (b.OreRulare != nullptr)
		{

			this->OreRulare = new int[b.nrSpectacole];
			for (int indx = 0; indx < b.nrSpectacole; indx++)
			{

				this->OreRulare[indx] = b.OreRulare[indx];

			}

		}
		else
		{

			this->OreRulare = nullptr;

		}

		this->nrSpectacole = b.nrSpectacole;
		this->DataFilm = b.DataFilm;
		this->pret = b.pret;
		this->rand = b.rand;
		this->loc = b.loc;
		this->idFilm = b.idFilm;

	}

	Bilete& operator=(const Bilete& b)
	{

		delete[] dataBilet;
		delete[] OreRulare;

		if (this != &b)
		{

			if (b.dataBilet != nullptr)
			{

				this->dataBilet = new char[strlen(b.dataBilet) + 1];
				strcpy_s(this->dataBilet, strlen(b.dataBilet) + 1, b.dataBilet);

			}
			else
			{

				this->dataBilet = nullptr;

			}

			if (b.OreRulare != nullptr)
			{

				this->OreRulare = new int[b.nrSpectacole];
				for (int indx = 0; indx < b.nrSpectacole; indx++)
				{

					this->OreRulare[indx] = b.OreRulare[indx];

				}

			}
			else
			{

				this->OreRulare = nullptr;

			}

			this->nrSpectacole = b.nrSpectacole;
			this->DataFilm = b.DataFilm;
			this->pret = b.pret;
			this->rand = b.rand;
			this->loc = b.loc;
			this->idFilm = b.idFilm;
		}

		return*this;

	}

	~Bilete()
	{

		delete[] dataBilet;
		delete[] OreRulare;

	}

	void setDataFilm(int zi, int luna, int an)
	{

		this->DataFilm = to_string(zi) + "." + to_string(luna) + "." + to_string(an);

	}

	//Se afiseaza detalii biletelor emise pentru un anumit film dupa IDfilm
	bool operator[](int indx)
	{

		if (this->idFilm == indx)
			return true;
		else
		{

			return false;
		}

	}

	//Se acorda o reducere clientilor fideli de 10%,20%
	Bilete operator-(float reducere)
	{

		this->pret = this->pret * (1 - reducere / 100);

		return *this;
	}

	//Se schimba data filmului cu 1 zi dupa
	Bilete operator++()
	{

		int zi, luna, an;
		int pozitie_s = 0, pozitie_f = 0;

		Bilete copie_bilet = *this;

		pozitie_s = 0;
		pozitie_f = DataFilm.find(".");
		zi = stoi(copie_bilet.DataFilm.substr(pozitie_s, pozitie_f));

		pozitie_s = pozitie_f + 1;
		pozitie_f = DataFilm.find(".", pozitie_s);
		luna = stoi(copie_bilet.DataFilm.substr(pozitie_s, pozitie_f - pozitie_s));

		pozitie_s = pozitie_f + 1;

		an = stoi(copie_bilet.DataFilm.substr(pozitie_s, 4));

		zi++;

		switch (luna)
		{

		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 9:
		case 11:
		case 12:

			if (zi > 31)
			{
				zi = 1;
				++luna;
			}

			if (luna > 12)
			{
				luna = 1;
				++an;
			}
			break;

		case 2:
			if (zi > 28)
			{
				zi = 1;
				++luna;
			}
			break;

		case 4:
		case 6:
		case 10:

			if (zi > 30)
			{
				zi = 1;
				++luna;
			}

		}

		this->DataFilm = ((zi >= 10) ? to_string(zi) : "0" + to_string(zi)) + "." + ((luna >= 10) ? to_string(luna) : "0" + to_string(luna)) + "." + to_string(an);


		return *this;

	}

	Bilete operator++(int x)
	{

		int zi, luna, an;
		int pozitie_s = 0, pozitie_f = 0;

		Bilete copie_bilet = *this;

		pozitie_s = 0;
		pozitie_f = DataFilm.find(".");
		zi = stoi(copie_bilet.DataFilm.substr(pozitie_s, pozitie_f));

		pozitie_s = pozitie_f + 1;
		pozitie_f = DataFilm.find(".", pozitie_s);
		luna = stoi(copie_bilet.DataFilm.substr(pozitie_s, pozitie_f - pozitie_s));

		pozitie_s = pozitie_f + 1;

		an = stoi(copie_bilet.DataFilm.substr(pozitie_s, 4));

		zi++;

		switch (luna)
		{

		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 9:
		case 11:
		case 12:

			if (zi > 31)
			{
				zi = 1;
				++luna;
			}

			if (luna > 12)
			{
				luna = 1;
				++an;
			}
			break;

		case 2:
			if (zi > 28)
			{
				zi = 1;
				++luna;
			}
			break;

		case 4:
		case 6:
		case 10:

			if (zi > 30)
			{
				zi = 1;
				++luna;
			}

		}

		copie_bilet.DataFilm = ((zi >= 10) ? to_string(zi) : "0" + to_string(zi)) + "." + ((luna >= 10) ? to_string(luna) : "0" + to_string(luna)) + "." + to_string(an);

		return copie_bilet;

	}

	//Returneaza data Biletului
	explicit operator string()
	{


		return dataBilet;

	}

	//Returneaza true/false daca biletul s-a emis in aceeasi zi cu ziua  in care ruleaza filmul
	bool operator!()
	{


		if (DataFilm == dataBilet)
			return false;
		else
			return true;

	}

	//Verifica daca biletele s-au emis pentru filme din aceeasi zi
	string operator==(Bilete& b)
	{

		//Se verifica ca biletele sa nu fie emis pentru acleasi film
		if (this->DataFilm == b.DataFilm)
		{

			return "Biletele sunt emise pentru filme ce ruleaza in aceeasi zi";
		}
		else
		{

			return "Biletele sunt emise pentru filme ce NU ruleaza in aceeasi zi";

		}

	}

	//Verifica care din filme are mai multe proiectii dupa ora 17
	int operator>=(Bilete& b)
	{

		int proiectii_film1 = 0;
		int proiectii_film2 = 0;

		for (int indx = 0; indx < this->nrSpectacole; indx++)
		{

			if (this->OreRulare[indx] > 17)
				++proiectii_film1;

		}

		for (int indx = 0; indx < b.nrSpectacole; indx++)
		{

			if (b.OreRulare[indx] > 17)
				++proiectii_film2;

		}

		if ((proiectii_film1 == 0) && (proiectii_film2 == 0))
			return 0;

		if (proiectii_film1 > proiectii_film2)
			return 1;

		if (proiectii_film1 < proiectii_film2)
			return 2;

		if (proiectii_film1 == proiectii_film2)
			return 3;

	}

	int getnrBilete()
	{

		return Bilete::nrBileteEmise;

	}

	int getIDFilm()
	{

		return this->idFilm;
	}

	friend istream& operator>> (istream&, Bilete&);
	friend ostream& operator<< (ostream&, Bilete);
};

class Film
{

private:
	const int idFilm;
	char* nume;
	int* program;
	static int nrFilme;
	string gen;
	int durata;
	int pozitie_top;

	//Bilet Bilete;

public:
	Film() : idFilm(++nrFilme)
	{

		nume = nullptr;
		program = nullptr;
		gen = "";
		durata = 0;
		pozitie_top = 0;
	}

	Film(char* nume, int* program, string gen, int durata, int pozitie_top = 20) :idFilm(++nrFilme)
	{
		if (strlen(nume) != 0)
		{

			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
		{

			this->nume = nullptr;
		}

		if (program != nullptr)
		{

			this->program = new int[7];

			for (int indx{ 0 }; indx < 7; indx++)
			{

				this->program[indx] = program[indx];
			}
		}
		else
		{

			this->program = nullptr;
		}


		this->gen = gen;
		this->durata = durata;
		if (pozitie_top > 0)
		{

			this->pozitie_top = pozitie_top;
		}

	}

	Film(const Film& f) :idFilm(f.idFilm)
	{

		if (strlen(f.nume) != 0)
		{

			this->nume = new char[strlen(f.nume) + 1];
			strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
		}
		else
		{

			this->nume = nullptr;
		}

		if (f.program != nullptr)
		{

			this->program = new int[7];

			for (int indx = 0; indx < 7; indx++)
			{

				this->program[indx] = f.program[indx];
			}
		}
		else
		{

			this->program = nullptr;
		}


		this->gen = f.gen;
		this->durata = f.durata;
		this->pozitie_top = f.pozitie_top;

	}


	Film& operator=(const Film& f)
	{

		delete[] nume;
		delete[] program;

		if (this != &f)
		{
			if (strlen(f.nume) != 0)
			{

				this->nume = new char[strlen(f.nume) + 1];
				strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
			}
			else
			{

				this->nume = nullptr;
			}

			if (f.program != nullptr)
			{

				this->program = new int[7];

				for (int indx = 0; indx < 7; indx++)
				{

					this->program[indx] = f.program[indx];
				}
			}
			else
			{

				this->program = nullptr;
			}


			this->gen = f.gen;
			this->durata = f.durata;
			this->pozitie_top = f.pozitie_top;

		}

		return *this;

	}

	//Verifica daca un film ruleaza intr-o anumita  zi
	bool operator[](int zi)
	{
		bool ruleaza = false;

		for (int indx = 0; indx < 7; indx++)
		{

			if (this->program[zi] == 1)
				ruleaza = true;
		}

		return ruleaza;

	}


	~Film()
	{

		delete[] nume;
		delete[] program;

	}

	void setnume(char* nume)
	{

		delete[] nume;
		if (strlen(nume) != 0)
		{

			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}

	}

	char* getnume()
	{

		return this->nume;

	}

	void setprogram(char* program)
	{

		delete[] program;
		this->program = new int[7];

		for (int indx = 0; indx < 7; indx++)
		{
			this->program[indx] = program[indx];

		}

	}

	//operatorul ++ creste program rularii filmului cu 1 zi
	Film operator++()
	{

		bool alocare_zi = false;
		int indx = 6;

		do
		{

			if (this->program[indx] == 0)
			{

				this->program[indx] = 1;
				alocare_zi = true;
			}

			indx--;

		} while ((indx < 0) || (!alocare_zi));


		return *this;
	}

	Film operator++(int i)
	{
		Film copie = *this;
		bool alocare_zi = false;
		int indx = 6;

		do
		{

			if (copie.program[indx] == 0)
			{

				copie.program[indx] = 1;
				alocare_zi = true;
			}

			indx--;

		} while ((indx < 0) || (!alocare_zi));

		return copie;
	}

	Film operator+(int poz)
	{

		this->pozitie_top -= poz;

		return *this;

	}

	//Returneaza Numele filmului
	explicit operator string()
	{

		return this->nume;

	}

	//Returneaza durata filmului 
	operator int()
	{

		return durata;

	}

	//Returneaza daca filmul este in top 10
	bool operator!()
	{

		if (this->pozitie_top > 10)
			return true;
		else
			return false;

	}

	//Care din filmele comparate ruleaza mai multe zile intr-o saptamana
	Film operator>=(const Film& f)
	{

		int nr_zile_film1 = 0, nr_zile_film2 = 0;

		for (int indx = 0; indx < 7; indx++)
		{

			if (this->program[indx] == 1)
				nr_zile_film1++;

			if (f.program[indx] == 1)
				nr_zile_film2++;

		}

		if (nr_zile_film1 >= nr_zile_film2)
			return *this;

		if (nr_zile_film1 < nr_zile_film2)
			return f;

	}

	//Verifica daca doua filme ruleaza in aceleasi zile
	bool operator==(Film& f)
	{

		for (int indx = 0; indx < 7; indx++)
		{

			if (this->program[indx] != f.program[indx])
				return false;
		}

		return true;

	}

	friend ostream& operator<< (ostream&, Film);
	friend istream& operator>> (istream&, Film&);
};

int Film::nrFilme = 0;
int Bilete::nrBileteEmise = 0;

ostream& operator<< (ostream& out, Film f)
{

	string zile_sapt[] = { "Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica" };

	//out << "Detalii Film :" << endl;
	out << "=============================" << endl;

	if (f.nume != nullptr)
	{
		out << "Nume: " << f.nume << endl;
	}

	if (f.program != nullptr)
	{
		out << "Frecventa: ";
		for (int indx = 0; indx < 7; indx++)
		{

			if (f.program[indx] == 1)
			{

				out << zile_sapt[indx] << " ";

			}
		}

		out << endl;
	}

	out << "Genul: " << f.gen << endl;
	out << "Durata: " << f.durata << " min. " << endl;
	out << "Pozitie top 10: " << f.pozitie_top << endl;

	return out;
}

istream& operator>> (istream& in, Film& f)
{

	string buffer;

	delete[] f.nume;
	cout << "Nume film: ";
	in >> ws;

	getline(in, buffer);
	f.nume = new char[buffer.length() + 1];
	strcpy_s(f.nume, buffer.length() + 1, buffer.c_str());

	cout << endl;

	delete[] f.program;
	f.program = new int[7];
	for (int indx = 0; indx < 7; indx++)
	{

		f.program[indx] = 0;
	}

	int nr_frecventa;
	int zi_rulare;

	cout << "De cate ori va rula filmul intr-o sapatamana : ";
	in >> nr_frecventa;

	cout << "In ce zile va rula filmul [Se va introduce numarul zilei saptamanii (ex: 3 pt Miercur)]: " << endl;
	for (int indx = 1; indx <= nr_frecventa; indx++)
	{
		cout << "Ziua " << indx << ": ";
		in >> zi_rulare;
		f.program[zi_rulare - 1] = 1;

	}

	cout << endl;

	cout << "Genul filmului: ";
	in >> f.gen;
	cout << endl;

	cout << "Durata filmului: ";
	in >> f.durata;
	cout << endl;

	return in;
}

class Client
{
private:
	const int idClient;
	static int nrClienti;
	char* nume;
	int nrCarduri;
	int* nrAsociatCard;
	string email;

public:
	Client() : idClient(++nrClienti)
	{
		nume = nullptr;
		nrCarduri = 0;
		nrAsociatCard = nullptr;
		email = "";
	}

	Client(char* nume, int* nrAsociatCard, int nrCarduri, string tipClient, bool abonat) : idClient(++nrClienti)
	{
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
		{
			this->nume = nullptr;
		}

		if (nrAsociatCard != nullptr && nrCarduri > 0)
		{
			this->nrAsociatCard = new int[nrCarduri];
			for (int i = 0; i < nrCarduri; i++)
			{
				this->nrAsociatCard[i] = nrAsociatCard[i];
			}
			this->nrCarduri = nrCarduri;
		}
		else
		{
			this->nrAsociatCard = nullptr;
			this->nrCarduri = 0;
		}

		this->email = email;
	}

	Client(const Client& c) : idClient(c.idClient)
	{
		if (c.nume != nullptr)
		{
			nume = new char[strlen(c.nume) + 1];
			strcpy_s(nume, strlen(c.nume) + 1, c.nume);
		}
		else
		{
			nume = nullptr;
		}

		if (c.nrAsociatCard != nullptr && c.nrCarduri > 0)
		{
			nrAsociatCard = new int[c.nrCarduri];
			for (int i = 0; i < c.nrCarduri; i++)
			{
				nrAsociatCard[i] = c.nrAsociatCard[i];
			}
			nrCarduri = c.nrCarduri;
		}
		else
		{
			nrAsociatCard = nullptr;
			nrCarduri = 0;
		}

		email = c.email;
	}

	~Client()
	{
		delete[] nume;
		delete[] nrAsociatCard;

	}

	Client& operator=(Client& c)
	{
		delete[] nume;
		delete[] nrAsociatCard;

		if (c.nume != nullptr)
		{
			nume = new char[strlen(c.nume) + 1];
			strcpy_s(nume, strlen(c.nume) + 1, c.nume);
		}
		else
		{
			nume = nullptr;
		}

		if (c.nrAsociatCard != nullptr && c.nrCarduri > 0)
		{
			nrAsociatCard = new int[c.nrCarduri];
			for (int i = 0; i < c.nrCarduri; i++)
			{
				nrAsociatCard[i] = c.nrAsociatCard[i];
			}
			nrCarduri = c.nrCarduri;
		}
		else
		{
			nrAsociatCard = nullptr;
			nrCarduri = 0;
		}

		email = c.email;

		return *this;
	}

	int operator[](int index)
	{
		if (index >= 0 && index > nrCarduri)
		{
			return nrAsociatCard[index];
		}
		return -1;
	}

	friend Client operator+(int, Client);

	//Creste numarul de zile selectate
	//forma 1: functie metoda
	Client operator++()
	{
		nrCarduri++;
		return *this;
	}

	//forma 2:functie globala
	friend Client operator++(Client);

	explicit operator string()
	{
		return this->nume;
	}

	//Verifica daca clientul a selectat un numar de zile
	bool operator!()
	{
		if (nrCarduri == 0)
			return true;
		return false;
	}

	//Compara numarul de zile selectate de doi clienti
	Client operator>=(const Client& c)
	{
		if (nrCarduri >= c.nrCarduri)
			return *this;
		return c;
	}

	//Verifica daca doi clienti au selectat acelasi numar de zile
	bool operator==(Client& c)
	{
		if (nrCarduri == c.nrClienti)
			return true;
		return false;
	}

	friend ostream& operator<<(ostream&, Client);
	friend istream& operator>>(istream&, Client&);
};

int Client::nrClienti = 0;

ostream& operator<<(ostream& out, Client c)
{
	if (c.nume != nullptr)
	{
		out << endl << "Nume: " << c.nume << endl;
	}
	out << "Email: " << c.email << endl;

	if (c.nrCarduri > 0)
	{
		out << "Numar carduri " << c.nrCarduri << endl;
	}
	else if (c.nrCarduri == 0)
	{
		cout << "Nu sunt carduri inregistrate" << endl;
	}

	if (c.nrAsociatCard != nullptr)
	{
		for (int i = 0; i < c.nrCarduri; i++)
		{
			out << "Card " << i + 1 << ": " << c.nrAsociatCard[i] << endl;
		}
	}
	cout << endl;
	return out;
}

istream& operator>>(istream& in, Client& c)
{
	cout << "Nume: ";
	delete[] c.nume;
	char buffer[50];
	//in >> ws;
	in.getline(buffer, 49);
	c.nume = new char[strlen(buffer) + 1];
	strcpy_s(c.nume, strlen(buffer) + 1, buffer);

	cout << endl << "Email: ";
	//in >> ws;
	getline(in, c.email);
	cout << endl;

	if (c.nrAsociatCard != nullptr)
	{
		delete[] c.nrAsociatCard;
	}

	cout << "Doresti sa salvezi datele cardurilor pentru plati ulterioare? [apasa 1 pentru da, 0 pentru nu] ";
	int optiune = 0;
	in >> optiune;
	if (optiune == 1)
	{
		cout << endl << "Introdu numarul de carduri pe care doresti sa le salvezi: ";
		in >> c.nrCarduri;
		if (c.nrCarduri > 0)
		{
			
			c.nrAsociatCard = new int[c.nrCarduri];
			for (int i = 0; i < c.nrCarduri; i++)
			{
				cout << "Intordu numarul asociat pentru ";
				cout << "Cardul " << i + 1 << ": ";
				in >> c.nrAsociatCard[i];
			}
		}
		else
		{
			c.nrCarduri = 0;
			c.nrAsociatCard = nullptr;
		}
		cout << endl;
	}


	return in;
}

//Creste numarul de carduri selectate
Client operator+(int x, Client c)
{
	c.nrClienti += x;
	return c;
}

Client operator++(Client c)
{
	c.nrCarduri++;
	return c;
}

class Rezervare
{
private:
	const int idRezervare;
	static int nrRezervari;
	char* dataRezervare;
	int* nrBileteRezervate;
	int nrBilete;
	bool achitat;
	//Client idClient;
	//Bilet idBilet;

public:
	Rezervare() :idRezervare(++nrRezervari)
	{
		dataRezervare = nullptr;
		nrBileteRezervate = nullptr;
		nrBilete = 0;
		achitat = false;
		//idClient=0;
		//idBilet=0;
	}

	Rezervare(char* dataRezervare, int* nrBileteRezervate, int nrBilete, bool achitat) :idRezervare(++nrRezervari)
	{
		if (dataRezervare != nullptr)
		{
			this->dataRezervare = new char[strlen(dataRezervare) + 1];
			strcpy_s(this->dataRezervare, strlen(dataRezervare) + 1, dataRezervare);
		}
		else
		{
			this->dataRezervare = nullptr;
		}

		if (nrBileteRezervate != nullptr)
		{
			this->nrBilete = nrBilete;
			this->nrBileteRezervate = new int[nrBilete];
			for (int i = 0; i < nrBilete; i++)
			{
				this->nrBileteRezervate[i] = nrBileteRezervate[i];
			}
		}
		else
		{
			this->nrBileteRezervate = nullptr;
			this->nrBilete = 0;
		}
		this->achitat = achitat;
		//this->idClient=idClient;
		//this->idBilet=idBilet;
	}

	Rezervare(const Rezervare& r) :idRezervare(r.idRezervare)
	{
		if (r.dataRezervare != nullptr)
		{
			dataRezervare = new char[strlen(r.dataRezervare) + 1];
			strcpy_s(dataRezervare, strlen(r.dataRezervare) + 1, r.dataRezervare);
		}
		else
		{
			dataRezervare = nullptr;
		}

		if (r.nrBileteRezervate != nullptr)
		{
			nrBilete = r.nrBilete;
			nrBileteRezervate = new int[r.nrBilete];
			for (int i = 0; i < r.nrBilete; i++)
			{
				nrBileteRezervate[i] = r.nrBileteRezervate[i];
			}
		}
		else
		{
			nrBileteRezervate = nullptr;
			nrBilete = 0;
		}
		achitat = r.achitat;
		//idClient=r.idClient;
		//idBilet=r.idBilet;
	}

	~Rezervare()
	{
		delete[]dataRezervare;
		delete[]nrBileteRezervate;
	}

	Rezervare& operator=(const Rezervare& r)
	{
		delete[]dataRezervare;
		delete[]nrBileteRezervate;
		if (r.dataRezervare != nullptr)
		{
			dataRezervare = new char[strlen(r.dataRezervare) + 1];
			strcpy_s(dataRezervare, strlen(r.dataRezervare) + 1, r.dataRezervare);
		}
		else
		{
			dataRezervare = nullptr;
		}

		if (r.nrBileteRezervate != nullptr)
		{
			nrBilete = r.nrBilete;
			nrBileteRezervate = new int[r.nrBilete];
			for (int i = 0; i < r.nrBilete; i++)
			{
				nrBileteRezervate[i] = r.nrBileteRezervate[i];
			}
		}
		else
		{
			nrBileteRezervate = nullptr;
			nrBilete = 0;
		}
		achitat = r.achitat;
		//idClient=r.idClient;
		//idBilet=r.idBilet;

		return *this;
	}

	int& operator[](int index) throw (exception)
	{
		if (index >= 0 && index < nrBilete / sizeof(int) && nrBileteRezervate != nullptr)
		{
			return nrBileteRezervate[index];
		}
		else
		{
			throw exception("Nu exista rezervare cu numarul de bilete introdus");
		}
	}

	friend Rezervare operator+(int, Rezervare);

	//Modifica rezervarea prin anularea unor bilete 
	//forma 1: functie metoda
	Rezervare operator--()
	{
		nrBilete--;
		return *this;
	}

	//forma 2: functie globala
	friend Rezervare operator--(Rezervare);

	explicit operator string()
	{
		return dataRezervare;
	}

	bool operator!()
	{
		return achitat != false;
	}

	//Verifica care dintre cele doua rezervari are mai multe bilete
	Rezervare operator > (Rezervare& r)
	{
		if (nrBilete > r.nrBilete)
			return *this;
		return r;
	}

	//Verifica daca cele doua rezervari comparate au acelasi numar de bilete
	bool operator == (Rezervare& r)
	{
		if (nrBilete == r.nrBilete)
			return true;
		return false;
	}
	friend ostream& operator<<(ostream&, Rezervare);
	friend istream& operator>>(istream&, Rezervare&);
};

int Rezervare::nrRezervari = 0;

ostream& operator<<(ostream& out, Rezervare r)
{
	out << "Detalii legate de rezervare: " << endl;
	if (r.dataRezervare != nullptr)
	{
		out << "Data rezervarii: " << r.dataRezervare << endl;
	}
	out << "Numarul de bilete rezervate: " << r.nrBilete << endl;
	if (r.nrBileteRezervate != nullptr)
	{
		for (int i = 0; i < r.nrBilete; i++)
		{
			out << "Id-ul biletului " << i << ":" << r.nrBileteRezervate[i] << endl;
		}
	}

	if (r.achitat != 1)
		out << "Neachitat";
	else
		out << "Achitat";
	out << endl;

	return out;
}

istream& operator>>(istream& in, Rezervare& r)
{
	delete[]r.dataRezervare;
	string buffer;
	cout << "Data rezervarii: ";
	in >> ws;
	getline(in, buffer);
	r.dataRezervare = new char[buffer.length() + 1];
	strcpy_s(r.dataRezervare, buffer.length() + 1, buffer.c_str());

	delete[]r.nrBileteRezervate;
	cout << "Introdu numarul de bilete pe care doresti sa le rezervi: " ;
	in >> r.nrBilete;
	r.nrBileteRezervate = new int[r.nrBilete];
	//for (int i = 0; i < r.nrBilete; i++)
	//{
	//	cout << "Id-ul biletului " << i << " :";
	//	in >> r.nrBileteRezervate[i];
	//}

	//cout << "Introduceti 0 daca nu ati achitat sau 1 daca ati achitat ";
	//in >> r.achitat;

	return in;
}

//Modifica ziua rezervarii. Rezervarea se va putea modifica doar daca a fost facuta in prima parte a lunii (pana in ziua 15 a lunii).
//Rezervarea poate fi modificata doar cu 7 zile mai tarziu, nu mai mult
Rezervare operator+(int x, Rezervare rez)
{
	int zi = atoi(rez.dataRezervare);
	if (zi <= 15 && x <= 7)
	{
		zi += x;
		string zi_noua = zi_noua + to_string(zi);
		rez.dataRezervare[0] = zi_noua[0];
		rez.dataRezervare[1] = zi_noua[1];
	}

	return rez;
}

Rezervare operator--(Rezervare r)
{
	r.nrBilete--;
	return r;
}



class Sala
{
private:
	const int nrSala;
	char* numeSala;
	int** locuriSala;
	static int nrTotalSali;
	string tipSala;
	int nrLocuriPeRand;
	int nrRanduri;

public:
	Sala() : nrSala(++nrTotalSali)
	{
		numeSala = nullptr;
		locuriSala = nullptr;
		nrTotalSali = 0;
		tipSala = "2D";
		nrLocuriPeRand = 0;
		nrRanduri = 0;
	}

	Sala(char* numeSala,int** locuriSala, int nrRanduri, int nrLocuriPeRand, string tipSala) :nrSala(++nrTotalSali)
	{
		if (strlen(numeSala) != 0)
		{
			this->numeSala = new char[strlen(numeSala) + 1];
			strcpy_s(this->numeSala, strlen(numeSala) + 1, numeSala);
		}
		else
		{
			this->numeSala = nullptr;
		}

		if (nrRanduri > 0 && nrLocuriPeRand > 0)
		{
			this->locuriSala = new int* [nrRanduri];
			for (int i = 0; i < nrRanduri; i++)
			{
				this->locuriSala[i] = new int[nrLocuriPeRand];
			}
			for (int i = 0; i < nrRanduri; i++)
			{
				for (int j = 0; j < nrLocuriPeRand; j++)
				{
					this->locuriSala[i][j] = locuriSala[i][j];
				}
			}

		}
		else
		{
			this->locuriSala = nullptr;
		}
		this->nrRanduri = nrRanduri;
		this->nrLocuriPeRand = nrLocuriPeRand;
		this->tipSala = tipSala;
	}

	Sala(const Sala& s) :nrSala(s.nrSala)
	{
		if (strlen(s.numeSala) != 0)
		{
			this->numeSala = new char[strlen(s.numeSala) + 1];
			strcpy_s(this->numeSala, strlen(s.numeSala) + 1, s.numeSala);
		}
		else
		{
			this->numeSala = nullptr;
		}

		if (s.nrRanduri > 0 && s.nrLocuriPeRand > 0)
		{
			this->locuriSala = new int* [s.nrRanduri];
			for (int i = 0; i < s.nrRanduri; i++)
			{
				this->locuriSala[i] = new int[s.nrLocuriPeRand];
			}
			for (int i = 0; i < s.nrRanduri; i++)
			{
				for (int j = 0; j < s.nrLocuriPeRand; j++)
				{
					this->locuriSala[i][j] = s.locuriSala[i][j];
				}
			}

		}
		else
		{
			this->locuriSala = nullptr;
		}
		this->nrRanduri = s.nrRanduri;
		this->nrLocuriPeRand = s.nrLocuriPeRand;
		this->tipSala = s.tipSala;
	}


	Sala& operator=(const Sala& s)
	{
		delete[] numeSala;
		delete[] locuriSala;

		if (this != &s)
		{
			if (strlen(s.numeSala) != 0)
			{
				this->numeSala = new char[strlen(s.numeSala) + 1];
				strcpy_s(this->numeSala, strlen(s.numeSala) + 1, s.numeSala);
			}
			else
			{
				this->numeSala = nullptr;
			}

			if (s.nrRanduri > 0 && s.nrLocuriPeRand > 0)
			{
				this->locuriSala = new int* [s.nrRanduri];
				for (int i = 0; i < s.nrRanduri; i++)
				{
					this->locuriSala[i] = new int[s.nrLocuriPeRand];
				}
				for (int i = 0; i < s.nrRanduri; i++)
				{
					for (int j = 0; j < s.nrLocuriPeRand; j++)
					{
						this->locuriSala[i][j] = s.locuriSala[i][j];
					}
				}

			}
			else
			{
				this->locuriSala = nullptr;
			}
			this->nrRanduri = s.nrRanduri;
			this->nrLocuriPeRand = s.nrLocuriPeRand;
			this->tipSala = s.tipSala;
		}
		return *this;
	}

	~Sala()
	{
		delete[] numeSala;
		delete[] locuriSala;
	}

	void setLocuriSala(int** locuriNoiSala)

	{
		for (int i = 0; i < nrRanduri; i++)
		{
			for (int j = 0; j < nrLocuriPeRand; j++)
			{
				this->locuriSala[i][j] = locuriNoiSala[i][j];
			}
		}
	}

	void setnrRanduri(int nr)
	{
		this->nrRanduri = this->nrRanduri + nr;
	}

	//Operator indexare [] - Verifica cate locurile disponibile sunt pe un anumit rand
	int operator[](int indexRand)
	{
		int locuriDisponibile = 0;
		for (int index = 0; index < this->nrLocuriPeRand; index++)
		{
			if (this->locuriSala[indexRand][index] == 0)
				locuriDisponibile++;
		}
		return locuriDisponibile;
	}

	//operator +  adaugare locuri pe un rand
	Sala operator+(int nrLocuriNoi)
	{
		this->nrLocuriPeRand += nrLocuriNoi;
		return *this;
	}

	//operatorul ++ adauga un rand intr-o sala
	Sala operator++(int i)
	{
		Sala copie = *this;
		nrRanduri++;
		return copie;
	}

	//operatorul cast (catre orice tip) explicit --cout string Sala 5
	//Returneaza tipul salii
	explicit operator string()
	{
		return this->tipSala;
	}

	//operatorul cast implicit 
	operator char* ()
	{
		return numeSala;
	}

	//operatorul ! pentru negatie => Returneaza daca sala are mai mult de 5 randuri
	bool operator!()
	{
		if (this->nrRanduri > 5)

			return true;
		else
			return false;
	}
	//Operator conditional (<,>,=<,>=)  -- comparare nrLocuri intre 2 sali
	bool operator>=(Sala& s)
	{
		int locuriSala1 = s.nrRanduri * s.nrLocuriPeRand;
		int locuriSala2 = this->nrRanduri * this->nrLocuriPeRand;

		if (locuriSala1 >= locuriSala2)
			return true;
		else
			return false;
	}

	//operatorul pentru testarea egalitatii dintre 2 obiecte ==  verificare nrLocuri ocupate  intre 2 sali
	bool operator == (Sala& s)
	{
		int locuriOcupateSala1 = 0;
		int locuriOcupateSala2 = 0;

		for (int i = 0; i < this->nrRanduri; i++)
		{
			for (int j = 0; j < this->nrLocuriPeRand; j++)
			{
				if (this->locuriSala[i][j] == 1)
					locuriOcupateSala1++;
			}
		}

		for (int i = 0; i < s.nrRanduri; i++)
		{
			for (int j = 0; j < s.nrLocuriPeRand; j++)
			{
				if (s.locuriSala[i][j] == 1)
					locuriOcupateSala2++;
			}
		}

		if (locuriOcupateSala1 == locuriOcupateSala2)
			return true;
		else
			return false;
	}

	friend ostream& operator<< (ostream&, Sala);
	friend istream& operator>> (istream&, Sala&);
};

int Sala::nrTotalSali = 0;

/*Sala &operator++ (Sala s)
{
	s.nrRanduri ++;
	return s;
}*/

ostream& operator<< (ostream& out, Sala s)
{
	out << "Detalii Sala:" << endl;
	out << "=========================" << endl;
	out << "Nr Sala: " << s.nrSala << endl;
	if (s.numeSala != nullptr)
	{
		out << "Nume sala: " << s.numeSala << endl;
	}
	out << "Tip sala: " << s.tipSala << endl;
	out << "Nr locuri in sala: " << s.nrRanduri * s.nrLocuriPeRand << endl << endl;
	out << "Locuri disponibile: " << endl;
	out << "-------------------------" << endl;
	for (int i = 0; i < s.nrRanduri; i++)
	{
		out << "Rand " << i + 1 << ": ";
		for (int j = 0; j < s.nrLocuriPeRand; j++)
		{
			out << " " << s.locuriSala[i][j];
		}
		out << endl;
	}
	//out << "Au fost adaugate " << adaugareLocuripeRand << "locuri pe randul:" << rand <<endl;
	return out;
}

istream& operator>> (istream& in, Sala& s)
{
	string buffer;

	delete[] s.numeSala;
	cout << "Nume sala: ";
	in >> ws;

	getline(in, buffer);
	s.numeSala = new char[buffer.length() + 1];
	strcpy_s(s.numeSala, buffer.length() + 1, buffer.c_str());

	cout << endl;

	delete[] s.locuriSala;
	cout << "Cate randuri sunt in sala? ";
	in >> s.nrRanduri;
	cout << endl;

	cout << "Cate locuri sunt pe fiecare rand? ";
	in >> s.nrLocuriPeRand;
	cout << endl;

	if (s.nrRanduri > 0 && s.nrLocuriPeRand > 0)
	{
		s.locuriSala = new int* [s.nrRanduri];
		for (int i = 0; i < s.nrRanduri; i++)
		{
			s.locuriSala[i] = new int[s.nrLocuriPeRand];
		}
		for (int i = 0; i < s.nrRanduri; i++)
		{
			for (int j = 0; j < s.nrLocuriPeRand; j++)
			{
				s.locuriSala[i][j] = 0;
			}
		}

	}

	cout << "Tip sala: ";
	in >> s.tipSala;
	cout << endl;

	return in;
}



int main()
{
	Client c;
	cin >> c;
	cout << c;
	int** matrice2 = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		matrice2[i] = new int[4];
	}

	matrice2[0][0] = 1;
	matrice2[0][1] = 0;
	matrice2[0][2] = 0;
	matrice2[0][3] = 0;
	matrice2[1][0] = 1;
	matrice2[1][1] = 0;
	matrice2[1][2] = 1;
	matrice2[1][3] = 0;


	Sala s1((char*)"Venus", matrice2, 2, 4, "3D");

	int ff1[] = { 0, 1, 1, 0, 0, 1, 0 };
	Film f1((char*)"Film 1", ff1, "Comedie", 90, 4);
	Film f2((char*)"Film 2", ff1, "Drama", 90, 2);
	Film f3((char*)"Film 3", ff1, "Drama", 90, 1);

	Rezervare r;
	Sala s;

	vector<Film> vectorFilm;

		vectorFilm.push_back(f1);
		vectorFilm.push_back(f2);
		vectorFilm.push_back(f3);


	int optiune = 0;
	int optiuneFilm = 0;
	int rand = 0;
	int loc = 0;
	do
	{
		cout << " Meniu:" << endl;
		cout << "1. Filme" << endl;
		cout << "2. Rezervare bilet" << endl;
		cout << endl << "Selecteaza optiunea: ";
		cin >> optiune;
		cout << endl;

		switch (optiune)
		{
		case 1:

			for (int i = 0; i < 3; i++)
			{
				cout << vectorFilm[i];
			}
			break;
		case 2:

			cin >> r;
			
			for (int i = 0; i < 3; i++)
			{
				cout << endl << "Apasa " << i + 1 << " pentru filmul: " << endl;
				cout << vectorFilm[i];
			}

			cout << endl << "Selecteaza filmul: ";
			cin >> optiuneFilm;

			cout << endl << "Selecteaza randul si locul: " << endl;
			cout << s1 << endl;

			
			cout << "Rand: ";
			cin >> rand;
			cout << "Loc: ";
			cin >> loc;

			cout << endl << "Ati selectat filmul: " << endl << vectorFilm[optiuneFilm] << endl;
			cout << "Locul " << loc << " randul " << rand << endl;
			cout << "Rezervarea a fost facuta cu succes!" << endl << endl;

			break;
		default:
			cout << "Optiunea este invalida, incerca din nou!" << endl << endl;
		}

	} while (optiune == 0);


	//string zile_sapt[] = { "Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica" };

	///*Film film_nou;
	//cin >> film_nou;
	//cout << film_nou;*/

	//int zile[] = { 0, 1, 1, 0, 0, 1, 0 };
	//Film film_nou_1((char*)"Film 1", zile, "Comedie", 90, 15);

	//int zile1[] = { 1, 1, 1, 0, 0, 1, 1 };
	//Film film_nou_2((char*)"Film 2", zile1, "Comedie", 85, 11);

	//int zile2[] = { 1, 0, 1, 0, 0, 1, 1 };
	//Film film_nou_3((char*)"Film 3", zile2, "Actiune", 120, 12);

	//Film filme[] = { film_nou_1, film_nou_2, film_nou_3 };

	//cout << filme[1] << endl;
	//cout << filme[2] << endl << endl;

	//if (filme[1] == filme[2])
	//{

	//	cout << "Filmele ruleaza concomitent!";
	//}
	//else
	//{

	//	cout << "Filmele nu ruleaza in aceleasi zile";

	//}

	//cout << filme[2] + 1 << endl;
	//cout << filme[2] + 3 << endl;
	//cout << string(filme[2]) <<endl;
	//cout << int(filme[2]) << endl;

	//cout << "Filmul care ruleaza de mai multe ori  este: " << string(filme[2] >= filme[1]) << endl;

	//if (!filme[2])
	//{

	//	cout << "Filmul nu este in top 10 !";

	//}
	//else
	//{

	//	cout << "Filmul este in top 10!";
	//}

	/*cout << ++filme[2];

	cout << filme[2]++;*/

	//Sala sala_noua;
	//cin >> sala_noua;
	//cout << sala_noua;

	/*int** matrice1 = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		matrice1[i] = new int[2];
	}

	int** matrice2 = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		matrice2[i] = new int[4];
	}

	matrice1[0][0] = 1;
	matrice1[0][1] = 0;
	matrice1[1][0] = 0;
	matrice1[1][1] = 1;

	//Sala sala_1((char*)"Venus", matrice1, 2, 2, "3D");
	//cout << "Nr de locuri libere in sala:";
	//cin >> sala_1;
	cout << sala_1 << endl;


	matrice2[0][0] = 1;
	matrice2[0][1] = 0;
	matrice2[0][2] = 0;
	matrice2[0][3] = 0;
	matrice2[1][0] = 1;
	matrice2[1][1] = 0;
	matrice2[1][2] = 1;
	matrice2[1][3] = 0;

	Sala sala_2((char*)"Terra", matrice2, 2, 4, "2D");
	cout << "Nr de locuri libere in sala:";
	//cin >> sala_2;
	cout << sala_2[1] << endl;

	if (sala_1 == sala_2)
		cout << "Salile au acelasi numar de locuri ocupate.";
	else
		cout << "Salile NU au acelasi numar de locuri ocupate.";
		*/

		/*int nrBileteRezervate1[] = { 1,2,3,4,5 };
	int nrBileteRezervate2[] = { 6,7,8,9,10 };
	Rezervare r1((char*)"12/02/2020", nrBileteRezervate1, 5, true);
	Rezervare r2((char*)"02/02/2020", nrBileteRezervate2, 5, true);
	r1.operator--();
	cout << r1.getNrBilete();*/

}
