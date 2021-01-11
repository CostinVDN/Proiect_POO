#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

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

	Sala(char* numeSala, int nrRanduri, int nrLocuriPeRand, string tipSala) :nrSala(++nrTotalSali)
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
					this->locuriSala[i][j] = 0;	//modificat aici
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
					this->locuriSala[i][j] = 0;	//modificat aici
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
						this->locuriSala[i][j] = 0;	//modificat aici
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

	//setter adaugat
	void setDenumireSala(char* denumireSala)
	{
		//if (denumireSala != nullptr)
		//{
			if (numeSala != nullptr)
			{
				delete[] numeSala;
			}
			numeSala = new char[strlen(denumireSala) + 1];
			strcpy_s(numeSala, strlen(denumireSala) + 1, denumireSala);
		//}
		//else
		//{
		//	throw null_exception("Ne pare rau! Sala introdusa nu exista! Va rugam introduceti o valoare corecta.");
		//}
	}

	void setAdaugareRanduri(int nr)
	{
		this->nrRanduri = this->nrRanduri + nr;
	}

	//setter adaugat
	void setnrRanduri(int nrRanduri)
	{
		if (nrRanduri > 0)
		{
			this->nrRanduri = nrRanduri;
		}
	}


	void setLocuriSala(int rand, int loc)
	{
		locuriSala[rand - 1][loc - 1] = 1;
	}

	//getter nume sala
	char* getDenumireSala()
	{
		return numeSala;
	}

	int** getLocuriSala()
	{
		int locuriLibere = 0;
		if (locuriSala != nullptr)
		{
			int** matrice = new int* [nrRanduri];
			for (int i = 0; i < nrRanduri; i++)
			{
				matrice[i] = new int[nrLocuriPeRand];
			}

			for (int i = 0; i < nrRanduri; i++)
			{
				cout << "Rand " << i + 1 << ": ";
				for (int j = 0; j < nrLocuriPeRand; j++)
				{
					cout << " " << locuriSala[i][j];
					if (locuriSala[i][j] == 0)
					{
						locuriLibere++;
					}

				}
				cout << endl;
			}
			cout << "Nr de locuri libere in sala: " << locuriLibere << endl;
			return matrice;
		}
		else {
			return nullptr;
		}
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


	//serializare adaugata
	void serializare()
	{
		ofstream f("sala.bin", ios::binary);

		int length = tipSala.length() + 1;

		f.write((char*)&nrSala, sizeof(nrSala));
		f.write(numeSala, (long long)strlen(numeSala) + 1);
		f.write((char*)&locuriSala, sizeof(locuriSala));
		f.write((char*)&nrTotalSali, sizeof(nrTotalSali));
		f.write((char*)&nrLocuriPeRand, sizeof(nrLocuriPeRand));
		f.write((char*)&nrRanduri, sizeof(nrRanduri));

		f.write((char*)&length, sizeof(length));
		f.write(tipSala.c_str(), length + 1);

		f.write((char*)&nrLocuriPeRand, sizeof(nrLocuriPeRand));

		f.close();
	}


	void deserializare()
	{
		ifstream f("sala.bin", ios::binary);
		int length = 0;
		f.read((char*)&length, sizeof(length));
		char* aux = new char[length];
		f.read(aux, length);
		tipSala = aux;

		f.read((char*)&nrSala, sizeof(nrSala));
		f.read(numeSala, (long long)strlen(numeSala) + 1);
		f.read((char*)&nrTotalSali, sizeof(nrTotalSali));
		f.read((char*)&locuriSala, sizeof(locuriSala));
		f.read((char*)&nrLocuriPeRand, sizeof(nrLocuriPeRand));
		f.read((char*)&nrRanduri, sizeof(nrRanduri));
		f.read((char*)&tipSala, sizeof(tipSala));

		string buffer = "";
		char c = 0;
		while ((c = f.get()) != 0)
		{
			buffer += c;
		}
		delete[] numeSala;
		numeSala = new char[buffer.length() + 1];
		strcpy_s(numeSala, buffer.length() + 1, buffer.c_str());

		f.read((char*)&nrSala, sizeof(nrSala));
		f.close();
	}

	friend ostream& operator<< (ostream&, Sala);
	friend istream& operator>> (istream&, Sala&);
	friend ofstream& operator<<(ofstream&, Sala);
	friend ifstream& operator>>(ifstream&, Sala&);
	friend class Film;
};

int Sala::nrTotalSali = 0; //static

/*Sala &operator++ (Sala s)
{
	s.nrRanduri ++;
	return s;
}*/

ostream& operator<< (ostream& out, Sala s)
{
	int locuriLibere = 0;

	out << "Detalii Sala:" << endl;
	out << "=========================" << endl;
	out << "Nr Sala: " << s.nrSala << endl;
	if (s.numeSala != nullptr)
	{
		out << "Nume sala: " << s.numeSala << endl;
	}
	out << "Tip sala: " << s.tipSala << endl;
	out << "Nr total de locuri in sala: " << s.nrRanduri * s.nrLocuriPeRand << endl << endl;
	out << "Locuri disponibile: " << endl;
	out << "-------------------------" << endl;
	for (int i = 0; i < s.nrRanduri; i++)
	{
		out << "Rand " << i + 1 << ": ";
		for (int j = 0; j < s.nrLocuriPeRand; j++)
		{
			out << " " << s.locuriSala[i][j];
			if (s.locuriSala[i][j] == 0)
				locuriLibere++;
		}
		out << endl;
	}
	out << "Nr de locuri libere in sala: " << locuriLibere << endl;
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

ofstream& operator<<(ofstream& of, Sala s)
{
	int locuriLibere = 0;

	if (of.is_open())
	{
		of << "Nume sala: " << s.numeSala << endl;
		of << "Tip sala: " << s.tipSala << endl;
		of << "Nr locuri in sala: " << s.nrRanduri * s.nrLocuriPeRand << endl << endl;
		of << "Locuri disponibile: " << endl;
		//of << "-------------------------" << endl;
		for (int i = 0; i < s.nrRanduri; i++)
		{
			of << "Rand " << i + 1 << ": ";
			for (int j = 0; j < s.nrLocuriPeRand; j++)
			{
				of << " " << s.locuriSala[i][j];
				if (s.locuriSala[i][j] == 0)
					locuriLibere++;
			}
			of << endl;
		}
		of << "Locuri libere in sala: " << locuriLibere << endl;
	}
	return of;
}

ifstream& operator>>(ifstream& iff, Sala& s)
{
	if (iff.is_open()) {
		string buffer;
		string buffer2;
		iff.ignore(100, '\n');
		iff.ignore(100, ' ');
		iff >> ws;
		getline(iff, buffer);
		s.numeSala = new char[buffer.length() + 1];
		strcpy_s(s.numeSala, buffer.length() + 1, buffer.c_str());
		iff.ignore(100, ':');
		iff.ignore(1, ' ');
		iff >> s.nrLocuriPeRand;
	}
	return iff;
	//out << "Au fost adaugate " << adaugareLocuripeRand << "locuri pe randul:" << rand <<endl;
}

class Film
{

private:
	const int idFilm;
	static int nrFilme;
	char* nume;
	int* zileRulare;
	int* ora_film;
	string gen;
	//string numeSala;
	int nr_proiectii;
	int durata;
	int pozitie_top;
	int idSala;
	//Sala* objSala;
	Sala sala;

public:
	Film() : idFilm(++nrFilme)
	{

		nume = nullptr;
		zileRulare = nullptr;
		ora_film = nullptr;
		gen = "";
		durata = 90;
		pozitie_top = 20;
		objSala = new Sala;
	}

	Film(char* nume, int* zileRulare, int* ora_Film, Sala* s) : idFilm(++nrFilme)
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

		if (zileRulare != nullptr)
		{
			this->zileRulare = new int[7];
			for (int indx{ 0 }; indx < 7; indx++)
			{
				this->zileRulare[indx] = zileRulare[indx];
			}
		}
		else
		{
			this->zileRulare = nullptr;
		}

		if (ora_film != nullptr)
		{
			this->ora_film = new int[nr_proiectii];
			for (int indx = 0; indx < nr_proiectii; indx++)
			{
				this->ora_film[indx] = ora_film[indx];
			}
		}
		else
		{
			ora_film = nullptr;
		}
		//objSala = s;
		gen = "";
		//numeSala = "";
		durata = 0;
		pozitie_top = 20;
		nr_proiectii = 0;

	}

	Film(char* nume, int* zileRulare, string gen, int durata, string sala, int nr_proiectii, int* ora_film, int pozitie_top = 20) :idFilm(++nrFilme)
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

		if (zileRulare != nullptr)
		{
			this->zileRulare = new int[7];
			for (int indx{ 0 }; indx < 7; indx++)
			{
				this->zileRulare[indx] = zileRulare[indx];
			}
		}
		else
		{
			this->zileRulare = nullptr;
		}

		if (ora_film != nullptr)
		{
			this->ora_film = new int[nr_proiectii];
			for (int indx = 0; indx < nr_proiectii; indx++)
			{
				this->ora_film[indx] = ora_film[indx];
			}
		}
		else
		{
			ora_film = nullptr;
		}

		this->nr_proiectii = nr_proiectii;
		this->gen = gen;
		this->durata = durata;
		this->numeSala = sala;

		if (pozitie_top > 0)
		{
			this->pozitie_top = pozitie_top;
		}
		objSala = new Sala;
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

		if (f.zileRulare != nullptr)
		{
			this->zileRulare = new int[7];

			for (int indx = 0; indx < 7; indx++)
			{
				this->zileRulare[indx] = f.zileRulare[indx];
			}
		}
		else
		{
			this->zileRulare = nullptr;
		}

		if (f.ora_film != nullptr)
		{
			this->ora_film = new int[f.nr_proiectii];
			for (int indx = 0; indx < f.nr_proiectii; indx++)
			{
				this->ora_film[indx] = f.ora_film[indx];
			}
		}
		else
		{
			this->ora_film = nullptr;
		}

		
		this->sala = f.sala;
		this->nr_proiectii = f.nr_proiectii;
		this->gen = f.gen;
		this->durata = f.durata;
		this->pozitie_top = f.pozitie_top;

	}


	Film& operator=(const Film& f)
	{

		delete[] nume;
		delete[] zileRulare;
		delete[] ora_film;

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

			if (f.zileRulare != nullptr)
			{

				this->zileRulare = new int[7];

				for (int indx = 0; indx < 7; indx++)
				{

					this->zileRulare[indx] = f.zileRulare[indx];
				}
			}
			else
			{

				this->zileRulare = nullptr;
			}

			if (f.ora_film != nullptr)
			{

				this->ora_film = new int[f.nr_proiectii]
					;
				for (int indx = 0; indx < f.nr_proiectii; indx++)
				{

					this->ora_film[indx] = f.ora_film[indx];

				}
			}
			else
			{

				this->ora_film = nullptr;
			}

			this->sala = f.sala;
			this->nr_proiectii = f.nr_proiectii;
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

			if (this->zileRulare[zi] == 1)
				ruleaza = true;
		}

		return ruleaza;

	}


	~Film()
	{

		delete[] nume;
		delete[] zileRulare;
		delete objSala;

	}

	void setSala(Sala& s)
	{

		this->sala = s;

	}

	int getidSala()
	{

		return this->idSala;

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

	int getidFilm()
	{

		return this->idFilm;

	}

	char* getnume()
	{

		return this->nume;

	}

	string getgen()
	{

		return this->gen;

	}

	int* getprogram()
	{

		return this->zileRulare;
	}

	int getnrproiectii()
	{

		return this->nr_proiectii;
	}

	int* getora_film()
	{

		return this->ora_film;

	}

	int getdurata()
	{

		return this->durata;
	}

	char* getNumeSala()
	{

		return this->sala.getDenumireSala();

	}

	//operatorul ++ creste frecventa rularii filmului cu 1 zi
	Film operator++()
	{

		bool alocare_zi = false;
		int indx = 6;

		do
		{

			if (this->zileRulare[indx] == 0)
			{

				this->zileRulare[indx] = 1;
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

			if (copie.zileRulare[indx] == 0)
			{

				copie.zileRulare[indx] = 1;
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

			if (this->zileRulare[indx] == 1)
				nr_zile_film1++;

			if (f.zileRulare[indx] == 1)
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

			if (this->zileRulare[indx] != f.zileRulare[indx])
				return false;
		}

		return true;

	}

	void serializare_film(ofstream& f, Film film)
	{
		int lungime_sir = 0;

		f.write(nume, (long long)strlen(nume) + 1);

		lungime_sir = gen.length() + 1;
		f.write((char*)&lungime_sir, sizeof(lungime_sir));
		f.write(gen.c_str(), lungime_sir);

		for (int i = 0; i < 7; i++)
		{
			f.write((char*)&zileRulare[i], sizeof(zileRulare[i]));
		}

		for (int i = 0; i < nr_proiectii; i++)
		{
			f.write((char*)&ora_film[i], sizeof(ora_film[i]));
		}

		f.write((char*)&durata, sizeof(durata));

		lungime_sir = numeSala.length() + 1;
		f.write((char*)&lungime_sir, sizeof(lungime_sir));
		f.write(numeSala.c_str(), lungime_sir);

		f.write("\n\r", sizeof("\n\r"));
	}

	friend ostream& operator<< (ostream&, Film);
	friend istream& operator>> (istream&, Film&);

};

int Film::nrFilme = 0;

//Operator afisare info Filme
ostream& operator<< (ostream& out, Film f)
{

	string zile_sapt[] = { "L", "Ma", "Mi", "J", "V", "S", "D" };

	out << setw(7) << left << f.getidFilm() << setw(15) << left << f.getnume() << setw(10) << left << f.gen;

	string program;
	for (int indx = 0; indx < 7.; indx++)
	{
		if (f.zileRulare[indx] != 0)
			program = program + zile_sapt[indx] + " ";

	}

	out << setw(20) << left << program;

	string ore;
	for (int indx = 0; indx < f.nr_proiectii; indx++)
	{

		ore = ore + to_string(f.ora_film[indx]) + " ";

	}

	out << setw(15) << left << ore << setw(15) << left << to_string(f.durata) + " min."
		<< setw(15) << left << f.getNumeSala() << endl;

	return out;
}

//Operator citire info Filme
istream& operator>> (istream& in, Film& f)
{

	string buffer;

	delete[] f.nume;
	cout << "Nume film: ";
	in >> ws;
	getline(in, buffer);
	f.nume = new char[buffer.length() + 1];
	strcpy_s(f.nume, buffer.length() + 1, buffer.c_str());

	delete[] f.zileRulare;
	f.zileRulare= new int[7];
	for (int indx = 0; indx < 7; indx++)
	{

		f.zileRulare[indx] = 0;
	}

	int nr_proiectii;
	int zi_rulare;

	cout << "De cate ori va rula filmul intr-o saptamana : ";
	in >> nr_proiectii;
	/*while (nr_proiectii > 0)
	{

		in >> nr_proiectii;

	};*/


	cout << "In ce zile va rula filmul [Se va introduce numarul zilei saptamanii (ex: 3 pt Miercur)]: " << endl;
	for (int indx = 1; indx <= nr_proiectii; indx++)
	{
		cout << "Ziua " << indx << ": ";
		in >> zi_rulare;
		f.zileRulare[zi_rulare - 1] = 1;

	}

	delete[] f.ora_film;
	cout << "Cate proiectii va avea filmul in fiecare zi : ";
	in >> f.nr_proiectii;

	cout << "La ce ore va rula filmul in fiecare zi: " << endl;
	f.ora_film = new int[f.nr_proiectii];
	for (int indx = 0; indx < f.nr_proiectii; indx++)
	{
		cout << "Proiecta " << indx + 1 << ": ";
		in >> f.ora_film[indx];

	}

	cout << "Genul filmului: ";
	in >> f.gen;

	cout << "Durata filmului: ";
	in >> f.durata;

	cout << "ID Sala in care ruleaza : ";
	in >> f.idSala;

	return in;

	return in;
}

class Bilete
{

private:
	const int codBilet;
	static int nrBileteEmise;
	char* dataBilet;
	string DataFilm; //Data cand ruleaza fimul
	int* Ore; // Pot fi emise bilete cu mai multe ore de vizionare si clientul alege la ce ore merge la film
	int nrOre;
	//string sala;
	//string nume_film;
	float pret;
	int idFilm;
	int rand;
	int loc;
	Film film;

public:

	Bilete() : codBilet{ ++nrBileteEmise }
	{

		dataBilet = nullptr;
		Ore = nullptr;
		idFilm = 0;
		pret = 0.0;
		rand = 0;
		loc = 0;

	}

	Bilete(Film* f, int rand, int loc) :codBilet(++nrBileteEmise)
	{
		film = f;
		dataBilet = new char[1];
		strcpy_s(dataBilet, 1, "");
		filme = nullptr;
		nrFilme = 0;
		sala = "";
		Ora = 0;
		pret = 0;
		this->rand = rand;
		this->loc = loc;
	}

	Bilete(char* dataBilet, string DataFilm, int* filme, int nrFilme, int idFilm, string sala, int Ora, string nume_film, float pret, int rand, int loc) : codBilet{ ++nrBileteEmise }
	{

		// Data se aloca automat
		if (dataBilet != nullptr)
		{

			this->dataBilet = new char[strlen(dataBilet) + 1];
			strcpy_s(this->dataBilet, strlen(dataBilet) + 1, dataBilet);

		}
		else
		{

			dataBilet = nullptr;

		}

		if (filme != nullptr)
		{

			this->filme = new int[nrFilme];
			for (int indx = 0; indx < nrFilme; indx++)
			{

				this->filme[indx] = filme[indx];

			}

		}
		else
		{

			this->filme = nullptr;

		}

		this->film = film;
		this->nrOre = nrOre;
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

		if (b.filme != nullptr)
		{

			this->filme = new int[b.nrFilme];
			for (int indx = 0; indx < b.nrFilme; indx++)
			{

				this->filme[indx] = b.filme[indx];

			}

		}
		else
		{

			this->filme = nullptr;

		}


		this->film = b.film;
		this->DataFilm = b.DataFilm;
		this->pret = b.pret;
		this->rand = b.rand;
		this->loc = b.loc;
		this->idFilm = b.idFilm;
		this->nrOre = b.nrOre;
	}

	Bilete& operator=(const Bilete& b)
	{

		delete[] dataBilet;
		delete[] filme;

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

			if (b.filme != nullptr)
			{

				this->filme = new int[b.nrFilme];
				for (int indx = 0; indx < b.nrFilme; indx++)
				{

					this->filme[indx] = b.filme[indx];

				}

			}
			else
			{

				this->filme = nullptr;

			}

			//this->sala = b.sala;
			this->film= b.film;
			this->DataFilm = b.DataFilm;
			this->pret = b.pret;
			this->rand = b.rand;
			this->loc = b.loc;
			this->idFilm = b.idFilm;
			this->nrOre = b.nrOre;
		return*this;

	}

	~Bilete()
	{

		delete[] dataBilet;
		delete[] filme;

	}


	void setFilm(Film& f)
	{

		this->film = f;

	}

	void setDataFilm(int zi, int luna, int an)
	{

		this->DataFilm = to_string(zi) + "." + to_string(luna) + "." + to_string(an);

	}

	//Se afiseaza daca biletul s-a emis pentru un anumit film
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

	//Se schimba locul de pe bilet un rand mai in spate
	Bilete operator++()
	{

		this->rand++;

		return *this;

	}

	Bilete operator++(int x)
	{

		Bilete copie_bilet = *this;

		copie_bilet.rand++;

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

	//Verifica care din bilete s-a emis pentru mai multe filme
	bool operator>=(Bilete& b)
	{

		if (this->nrFilme >= b.nrFilme)
			return true;
		else
			return false;

	}

	int getnrBilete()
	{

		return Bilete::nrBileteEmise;

	}

	int getIDFilm()
	{

		return this->idFilm;
	}

	void serializare_bilet(ofstream& f, Bilete bilete)
	{
		int lungime_sir = 0;

		f.write((char*)&idFilm, sizeof(idFilm));

		f.write(dataBilet, (long long)strlen(dataBilet) + 1);

		f.write((char*)&nrOre, sizeof(nrOre));
		for (int indx = 0; indx < nrOre; indx++)
		{
			f.write((char*)&Ore[indx], sizeof(Ore));
		}

		f.write((char*)&rand, sizeof(rand));
		f.write((char*)&loc, sizeof(loc));

		/*lungime_sir = sala.length() + 1;
		f.write((char*)&lungime_sir, sizeof(lungime_sir));
		f.write(sala.c_str(), lungime_sir);*/
		f.write((char*)&pret, sizeof(pret));

		f.write("\n\r", sizeof("\n\r"));
	}

	friend istream& operator>> (istream&, Bilete&);
	friend ostream& operator<< (ostream&, Bilete);
	friend ofstream& operator<<(ofstream&, Bilete);
};
int Bilete::nrBileteEmise = 0;

//Operator afisare info Bilete
ostream& operator<< (ostream& out, Bilete b)
{


	out << setw(7) << left << b.codBilet << setw(15) << left << b.film.getnume() << setw(15) << left << b.dataBilet;


	string ore;
	for (int indx = 0; indx < b.nrOre; indx++)
	{

		ore = ore + to_string(b.Ore[indx]) + " ";

	}

	
	out << setw(15) << left << ore << setw(7) << left << b.rand << setw(7) << left << b.loc
		<< setw(15) << left << b.film.getNumeSala() << setw(15) << left << b.pret << endl;

	return out;

}

//Operator citire info Bilete
istream& operator>> (istream& in, Bilete& b)
{

	string buffer;

	cout << "ID Film: ";
	in >> b.idFilm;
	
	delete[] b.dataBilet;
	cout << "Data emiterii (ZZ.LL.AAAA): ";
	in >> ws;

	getline(in, buffer);
	b.dataBilet = new char[buffer.length() + 1];
	strcpy_s(b.dataBilet, buffer.length() + 1, buffer.c_str());

	cout << "Data spectacol (ZZ.LL.AAAA): ";
	in >> ws;
	getline(in, b.DataFilm);

	cout << "Aveti posibilitatea de a emite biletul pentru mai multe proiectii in aceeazi zi \n"
		<< "si puteti alege la ce proiectie sa mergeti \n"
		<< " (pretul se va majora cu 10% pentru fiecare ora supimentara aleasa): ";

	in >> b.nrOre;

	delete[] b.Ore;
	b.Ore = new int[b.nrOre];
	for (int indx = 0; indx < b.nrOre; indx++)
	{

		cout << "Ora [" << indx + 1 << "]: ";
		in >> b.Ore[indx];

	}

	cout << "Rand: ";
	in >> b.rand;

	cout << "Loc: ";
	in >> b.loc;

	cout << "Pret de baza bilet (pretul se va majora cu 10% pentru fiecare ora supimentara aleasa): ";
	in >> b.pret;

	b.pret = b.pret * (1 + (b.nrOre - 1) * 0.1);

	return in;

}

//Operator info Bilete salvare in fisier 
ofstream& operator<<(ofstream& file_out, Bilete b)
{

	string buffer;

	if (file_out.is_open())
	{

		file_out << b.film.getnume() << endl;
		file_out << b.DataFilm << endl;
		file_out << b.nrOre << endl;
		for (int indx = 0; indx < b.nrOre; indx++)
		{

			file_out << b.Ore[indx] << " " << endl;
		}
		file_out << b.film.getidSala() << endl;
		file_out << b.rand << endl;
		file_out << b.loc << endl;

		return file_out;

	}
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

	Client(char* nume, int nrCarduri, int* nrAsociatCard, string email) : idClient(++nrClienti)
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
	char* getNume()
	{
		if (nume == nullptr)
			return nullptr;
		char* copie = new char[strlen(nume) + 1];
		strcpy_s(copie, strlen(nume) + 1, nume);
		return copie;
	}

	void setNume(char* nume)
	{
		if (nume != nullptr)
		{
			if (this->nume != nullptr)
				delete[]this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
	}


	int* getNrAsociatCard()
	{
		if (nrAsociatCard != nullptr)
		{
			int* copie = new int[nrCarduri];
			for (int i = 0; i < nrCarduri; i++)
			{
				copie[i] = nrAsociatCard[i];
			}
			return copie;
		}
		else
		{
			return nullptr;
		}
	}

	int getNrCarduri()
	{
		return nrCarduri;
	}

	void setNrAsociatCard(int* nrAsociatCard, int nrCarduri)
	{
		if (nrAsociatCard != nullptr && nrCarduri > 0)
		{
			if (this->nrAsociatCard != nullptr)
				delete[]this->nrAsociatCard;
			this->nrAsociatCard = new int[nrCarduri];
			for (int i = 0; i < nrCarduri; i++)
			{
				this->nrAsociatCard[i] = nrAsociatCard[i];
			}
		}
	}

	string getEmail()
	{
		return email;
	}

	void setEmail(string email)
	{
		this->email = email;
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

	//Verifica daca clientul a selectat un numar de carduri
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

	//Verifica daca doi clienti au selectat acelasi numar de carduri
	bool operator==(Client& c)
	{
		if (nrCarduri == c.nrClienti)
			return true;
		return false;
	}


	void serializeClient()
	{
		ofstream f("Client.bin", ios::binary);
		f.write(nume, (long long)strlen(nume) + 1);
		f.write((char*)&nrCarduri, sizeof(nrCarduri));
		for (int i = 0; i < nrCarduri; i++)
		{
			f.write((char*)&nrAsociatCard[i], sizeof(nrAsociatCard[i]));
		}
		f.write(email.c_str(), email.length());
		f.close();
	}

	void deserializeClient()
	{
		ifstream f("Client.bin", ios::binary);
		string buffer = "";
		char c = 0;
		while ((c = f.get()) != 0)
		{
			buffer += c;
		}
		delete[] nume;
		nume = new char[buffer.length() + 1];
		strcpy_s(nume, buffer.length() + 1, buffer.c_str());

		f.read((char*)&nrCarduri, sizeof(nrCarduri));
		delete[] nrAsociatCard;
		nrAsociatCard = new int[nrCarduri];
		for (int i = 0; i < nrCarduri; i++)
		{
			f.read((char*)&nrAsociatCard[i], sizeof(nrAsociatCard[i]));
		}

		int length = 0;
		f.read((char*)&length, sizeof(length));
		char* aux = new char[length];
		f.read(aux, length);
		email = aux;
		f.close();
	}

	friend ostream& operator<<(ostream&, Client);
	friend istream& operator>>(istream&, Client&);
	friend class Rezervare;
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
	cout << endl << "Nume: ";
	delete[] c.nume;
	char buffer[50];
	in >> ws;
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
	Client* client;
	Bilete* bilet;
	
public:
	Rezervare() :idRezervare(++nrRezervari)
	{
		dataRezervare = nullptr;
		nrBileteRezervate = nullptr;
		nrBilete = 0;
		achitat = false;
		client = new Client;
		bilet = new Bilete;
	}

	Rezervare(Client* c, int nrBilete, Bilete* b) :idRezervare(++nrRezervari)
	{
		this->client = c;
		dataRezervare = new char[1];
		strcpy_s(dataRezervare, 1, "");
		this->nrBilete = nrBilete;
		nrBileteRezervate = new int[nrBilete];
		achitat = false;
		this->bilet = b;
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
		client = new Client;
		bilet = new Bilete;
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

		if (r.client != nullptr)
		{
			client = new Client;
			if (r.client->nume != nullptr)
			{
				client->nume = new char[strlen(r.client->nume) + 1];
				strcpy_s(client->nume, strlen(r.client->nume) + 1, r.client->nume);
			}
			else
			{
				client->nume = nullptr;
			}

			if (r.client->nrAsociatCard != nullptr)
			{
				client->nrCarduri = r.client->nrCarduri;
				client->nrAsociatCard = new int[r.client->nrCarduri];
				for (int i = 0; i < r.client->nrCarduri; i++)
				{
					client->nrAsociatCard[i] = r.client->nrAsociatCard[i];
				}
			}
			else
			{
				client->nrAsociatCard = nullptr;
				client->nrCarduri = 0;
			}

			client->email = r.client->email;
		}
	}

	~Rezervare()
	{
		delete[]dataRezervare;
		delete[]nrBileteRezervate;
		delete client;
		delete bilet;
	}

	Rezervare& operator=(const Rezervare& r)
	{
		delete[]dataRezervare;
		delete[]nrBileteRezervate;
		delete client;
		delete bilet;
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
		
		if (r.client != nullptr)
		{
			client = new Client;
			if (r.client->nume != nullptr)
			{
				client->nume = new char[strlen(r.client->nume) + 1];
				strcpy_s(client->nume, strlen(r.client->nume) + 1, r.client->nume);
			}
			else
			{
				client->nume = nullptr;
			}

			if (r.client->nrAsociatCard != nullptr)
			{
				client->nrCarduri = r.client->nrCarduri;
				client->nrAsociatCard = new int[r.client->nrCarduri];
				for (int i = 0; i < r.client->nrCarduri; i++)
				{
					client->nrAsociatCard[i] = r.client->nrAsociatCard[i];
				}
			}
			else
			{
				client->nrAsociatCard = nullptr;
				client->nrCarduri = 0;
			}

			client->email = r.client->email;
		}

		return *this;
	}

	char* getDataRezervare()
	{
		if (dataRezervare == nullptr)
			return nullptr;
		char* copie = new char[strlen(dataRezervare) + 1];
		strcpy_s(copie, strlen(dataRezervare) + 1, dataRezervare);
		return copie;
	}

	void setDataRezervare(char* dataRezervare)
	{
		if (dataRezervare != nullptr)
		{
			if (this->dataRezervare != nullptr)
				delete[]this->dataRezervare;
			this->dataRezervare = new char[strlen(dataRezervare) + 1];
			strcpy_s(this->dataRezervare, strlen(dataRezervare) + 1, dataRezervare);

		}
	}

	int* getNrBileteRezervate()
	{
		if (nrBileteRezervate != nullptr)
		{
			int* copie = new int[nrBilete];
			for (int i = 0; i < nrBilete; i++)
			{
				copie[i] = nrBileteRezervate[i];
			}
			return copie;
		}
		return nullptr;
	}

	int getNrBilete()
	{
		return nrBilete;
	}

	void setNrBileteRezervate(int* nrBileteRezervate, int nrBilete)
	{
		if (nrBileteRezervate != nullptr && nrBilete > 0)
		{
			if (this->nrBileteRezervate != nullptr)
				delete[]this->nrBileteRezervate;
			this->nrBileteRezervate = new int[nrBilete];
			for (int i = 0; i < nrBilete; i++)
			{
				this->nrBileteRezervate[i] = nrBileteRezervate[i];
			}
		}
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

	void serializeRezervare()
	{
		ofstream f("Rezervare.bin", ios::binary);
		f.write(dataRezervare, (long long)strlen(dataRezervare) + 1);
		f.write((char*)&nrBilete, sizeof(nrBilete));
		for (int i = 0; i < nrBilete; i++)
		{
			f.write((char*)&nrBileteRezervate[i], sizeof(nrBileteRezervate[i]));
		}
		f.close();
	}

	void deserializeRezervare()
	{
		ifstream f("Rezervare.bin", ios::binary);
		string buffer = "";
		char c = 0;
		while ((c = f.get()) != 0)
		{
			buffer += c;
		}
		delete[] dataRezervare;
		dataRezervare = new char[buffer.length() + 1];
		strcpy_s(dataRezervare, buffer.length() + 1, buffer.c_str());

		f.read((char*)&nrBilete, sizeof(nrBilete));
		delete[] nrBileteRezervate;
		nrBileteRezervate = new int[nrBilete];
		for (int i = 0; i < nrBilete; i++)
		{
			f.read((char*)&nrBileteRezervate[i], sizeof(nrBileteRezervate[i]));
		}

		f.close();
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
	cout << "Introdu numarul de bilete pe care doresti sa le rezervi: ";
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

class null_exception : public exception
{
public:
	null_exception()
	{

	}

	null_exception(const char* message) : exception(message)
	{

	}
};

void Afisare_lista_filme(Film* lista_filme, int nr_filme)
{

	cout << "Detalii filme ce ruleaza in saptamana curenta " << endl;
	cout << "======================================================================================" << endl;
	cout << setw(7) << left << "ID" << setw(15) << left << "Titlu" << setw(10) << left << "Genul"
		<< setw(20) << left << "Program" << setw(15) << left << "Ore"
		<< setw(15) << left << "Durata" << setw(15) << left << "Sala" << endl;
	cout << "======================================================================================" << endl << endl;

	for (int indx = 0; indx < nr_filme; indx++)
	{

		cout << &lista_filme[indx];
	}


}

void Afisare_lista_filme(Film** lista_filme, int nr_filme)
{


	cout << "Detalii filme ce ruleaza in saptamana curenta " << endl;
	cout << "======================================================================================" << endl;
	cout << setw(7) << left << "ID" << setw(15) << left << "Titlu" << setw(10) << left << "Genul"
		<< setw(20) << left << "Program" << setw(15) << left << "Ore"
		<< setw(15) << left << "Durata" << setw(15) << left << "Sala" << endl;
	cout << "======================================================================================" << endl << endl;

	for (int indx = 0; indx < nr_filme; indx++)
	{

		if (lista_filme[indx] != nullptr)
			cout << (*lista_filme[indx]);

	}

}

void Afisare_lista_bilete(Bilete** lista_bilete, int nr_bilete)
{


	cout << "Detalii bilete emise " << endl;
	cout << "======================================================================================" << endl;
	cout << setw(7) << left << "ID" << setw(15) << left << "Film" << setw(15) << left << "Data bilet"
		<< setw(7) << left << "Ora" << setw(7) << left << "Rand" << setw(7) << left << "Loc"
		<< setw(15) << left << "Sala " << setw(15) << left << "Pret" << endl;
	cout << "======================================================================================" << endl << endl;

	for (int indx = 0; indx < nr_bilete; indx++)
	{

		if (lista_bilete[indx] != nullptr)
			cout << (*lista_bilete[indx]);

	}

}

oid Modificare_info_filme(Sala **lista_sali, int nr_sali, Film** lista_filme, int nr_filme)
{

	//2. Modificare film si afisare nuoa lista filme
	int idfilm = 1;

	cout << "Introduceti ID FIlm pe care doriti sa-l modificati ";
	do
	{

		cin >> idfilm;

	} while ((idfilm < 1) || (idfilm > nr_filme));

	cin >> (*lista_filme[idfilm - 1]);
	for (int indx_sali = 0; indx_sali < 3; indx_sali++)
	{
		if (lista_filme[idfilm-1]->getidSala() == (*lista_sali[indx_sali]).getnrsala())
			lista_filme[idfilm-1]->setSala(*lista_sali[indx_sali]);
	}



	Afisare_lista_filme(lista_filme, nr_filme);

}

vvoid Modificare_info_bilete(Film** lista_filme, int nr_filme, Bilete** lista_bilete, int nr_bilete)
{

	//2. Modificare film si afisare nuoa lista filme
	int idbilet = 1;

	cout << "Introduceti ID Bilet pe care doriti sa-l modificati ";
	do
	{

		cin >> idbilet;

	} while ((idbilet < 1) || (idbilet > nr_bilete));

	cin >> (*lista_bilete[idbilet - 1]);
	for (int indx_filme = 0; indx_filme < nr_filme; indx_filme++)
		{
			if (lista_bilete[idbilet - 1]->getIDFilm() == lista_filme[indx_filme]->getidFilm())
				lista_bilete[idbilet - 1]->setFilm(*lista_filme[indx_filme]);
		}

	Afisare_lista_bilete(lista_bilete, nr_bilete);

}

void Stergere_info_film(Film** lista_filme, int nr_filme)
{

	int idfilm = 1;

	cout << "Introduceti ID FIlm pe care doriti sa-l stergeti: ";

	do
	{

		cin >> idfilm;

	} while ((idfilm < 1) || (idfilm > nr_filme));

	lista_filme[idfilm - 1] = nullptr;

	Afisare_lista_filme(lista_filme, nr_filme);

}


void Stergere_info_bilet(Bilete** lista_bilete, int nr_bilete)
{

	int idbilet = 1;

	cout << endl;

	cout << "Introduceti ID Bilet pe care doriti sa-l stergeti: ";

	do
	{

		cin >> idbilet;

	} while ((idbilet < 1) || (idbilet > nr_bilete));

	lista_bilete[idbilet - 1] = nullptr;

	Afisare_lista_bilete(lista_bilete, nr_bilete);

}

void administrareCinema()
{
	int nr_filme = 0;
	Film** lista_filme = nullptr;

	int nr_bilete = 0;
	Bilete** lista_bilete = nullptr;
	

	int optiune = 0;
	int opt1 = 0;
	int opt2 = 0;
	int opt3 = 0;
	while (true)
	{
		cout << endl << "==== Meniu ====" << endl << endl <<
			"1. Administrare sala" << endl <<
			"2. Administrare film" << endl <<
			"3. Administrare tip bilet" << endl <<
			"0. Revenire la meniul anterior" << endl;

		cout <<endl << "Selecteaza optiunea: ";
		cin >> optiune;

		switch (optiune)
		{
		case 0:
			break;
		case 1:
			while (true)
			{
				cout << endl << "==== Meniu ====" << endl << endl <<
					"1. Adaugare sala" << endl <<
					"2. Modificare sala" << endl <<
					"3. Stergere sala" << endl <<
					"0. Revenire la meniul anterior" << endl;
				cout << endl << "Selecteaza optiunea: ";
				cin >> opt1;
				switch (opt1)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					cout << "Optiunea este invalida! Incearca din nou!" << endl;
				}
				break;
			}
			continue;
		case 2:
			while (true)
			{
				cout << endl << "==== Meniu ====" << endl << endl <<
					"1. Adaugare film" << endl <<
					"2. Modificare film" << endl <<
					"3. Stergere film" << endl <<
					"0. Revenire la meniul anterior" << endl;
				cout << endl << "Selecteaza optiunea: ";
				cin >> opt2;
				switch (opt2)
				{
				case 0:
					break;
				case 1:

					cout << "Introdu nr de filme ce urmeaza a fi inregistrate: ";
					do
					{
						cin >> nr_filme;

					} while (nr_filme < 0);

					lista_filme = new Film * [nr_filme];
					for (int indx_filme = 0; indx_filme < nr_filme; indx_filme++)
					{

						lista_filme[indx_filme] = new Film();
						cin >> (*lista_filme[indx_filme]);
						for (int indx_sali = 0; indx_sali < 3; indx_sali++)
						{
							if ((lista_sali[indx_sali] != nullptr) &&
								(lista_filme[indx_filme]->getidSala() == (*lista_sali[indx_sali]).getnrsala()))
							{

								lista_filme[indx_filme]->setSala(*lista_sali[indx_sali]);
							}
						}

						cout << endl;
					}
		
					Afisare_lista_filme(lista_filme, nr_filme);
					break;
				case 2:
					Modificare_info_filme(lista_filme, nr_filme);
					break;
				case 3:
					Stergere_info_film(lista_filme, nr_filme);
					break;
				default:
					cout << "Optiunea este invalida! Incearca din nou!" << endl;
				}
				break;
			}
			continue;
		case 3:
			while (true)
			{
				cout << endl << "==== Meniu ====" << endl << endl <<
					"1. Adaugare tip bilet" << endl <<
					"2. Modificare tip bilet" << endl <<
					"3. Stergere tip bilet" << endl <<
					"0. Revenire la meniul anterior" << endl;
				cout << endl << "Selecteaza optiunea: ";
				cin >> opt3;
				switch (opt3)
				{
				case 0:
					break;
				case 1:
					cout << "Introdu nr de Bilete: ";
					do
					{

						cin >> nr_bilete;

					} while (nr_bilete < 0);

					lista_bilete = new Bilete * [nr_bilete];

					for (int indx_bilete = 0; indx_bilete < nr_bilete; indx_bilete++)
					{

						lista_bilete[indx_bilete] = new Bilete();
						cin >> (*lista_bilete[indx_bilete]);
						for (int indx_filme = 0; indx_filme < nr_bilete; indx_filme++)
						{
							if ((lista_filme[indx_filme] != nullptr) &&
								(lista_bilete[indx_bilete]->getIDFilm() == lista_filme[indx_filme]->getidFilm()))
							{
								lista_bilete[indx_bilete]->setFilm(*lista_filme[indx_filme]);
							}
						}

						cout << endl;
					}

					Afisare_lista_bilete(lista_bilete, nr_bilete);
					break;
				case 2:
					Modificare_info_bilete(lista_bilete, nr_bilete);
					break;
				case 3:
					Stergere_info_bilet(lista_bilete, nr_bilete);
					break;
				default:
					cout << "Optiunea este invalida! Incearca din nou!" << endl;
				}
				break;
			}
			continue;
		default:
			cout << "Optiunea este invalida! Incearca din nou!" << endl;
		}
		break;
	}

}

int main()
{

	////4. Serializare filme
	//ofstream f("film.bin", ios::binary);
	//for (int indx = 0; indx < nr_filme; indx++)
	//{

	//	if (lista_filme[indx] != nullptr)
	//		lista_filme[indx]->serializare_film(f, (*lista_filme[indx]));

	//}

	//f.close();


	////OPERATIUNI BILETE

	////1. Adaugare Bilete si afisare lisa bilete emise

	////system("cls");


	////2. Modificare bilet
	//


	////3. Stergere bilet
	//

	////4. Salvare bilete in fisier
	//f.open("Info_bilete.txt");

	//for (int indx = 0; indx < nr_bilete; indx++)
	//{

	//	if (lista_bilete[indx] != nullptr)
	//		f << (*lista_bilete[indx]);

	//}

	//f.close();

	//	//5. Serializare filme
	//	f.open("bilet.bin", ios::binary);
	//for (int indx = 0; indx < nr_bilete; indx++)
	//{

	//	if (lista_bilete[indx] != nullptr)
	//		lista_bilete[indx]->serializare_bilet(f, (*lista_bilete[indx]));

	//}

	//f.close();

	//delete[] lista_filme;
	//delete[] lista_bilete;




	//Client c;
	//cin >> c;
	//cout << c;
	//int** matrice = new int* [4];
	//for (int i = 0; i < 2; i++)
	//{
	//	matrice[i] = new int[6];
	//}



	//Sala s1((char*)"Venus", 7, 5, "3D");
	//s1.getLocuriSala();
	//s1.setLocuriSala(3, 4);
	//s1.getLocuriSala();

	int ore[] = { 12, 18, 21 };
	int ff1[] = { 0, 1, 1, 0, 0, 1, 0 };
	Film f1((char*)"The Call of the Wild", ff1, "Aventura", 90, "Venus", 3, ore, 1);
	Film f2((char*)"The Christmas Chronicles II", ff1, "Comedie", 90, "Venus", 3, ore, 1);
	Film f3((char*)"Top Gun: Maverick", ff1, "Actiune", 90, "Venus", 3, ore, 1);

	Rezervare r;
	Sala s((char*)"Venus", 7, 5, "3D");
	Client c;

	vector<Film> vectorFilm;

	vectorFilm.push_back(f1);
	vectorFilm.push_back(f2);
	vectorFilm.push_back(f3);

	string username = "administrator";
	string password = "parola";
	string revenireMeniu = "1";
	int optiune = 0;
	int optiuneFilm = 0;
	int rand = 0;
	int loc = 0;


	while (true)
	{
		cout << endl <<
			"==== Meniu: ====" << endl << endl <<
			"1. Filme" << endl <<
			"2. Rezervare bilet" << endl <<
			"3. Modificare rezervare" << endl <<
			"4. Administrare cinema" << endl <<
			"0. Exit" << endl;

		cout << endl << "Selecteaza optiunea: ";

		cin >> optiune;
		//cout << endl;

		switch (optiune)
		{
		case 0:
			break;
		case 1:
			cout << endl;
			for (int i = 0; i < 3; i++)
			{
				cout << vectorFilm[i];
			}
			continue;
		case 2:

			cout << "Apasa 1 pentru autentificare" << endl <<
				"Apasa 2 pentru creare cont nou" << endl;
			cout << "// Momentan nu exista optiunea asta, se creeaza cont nou by default" << endl;
			cin >> c;
			cin >> r;

			for (int i = 0; i < 3; i++)
			{
				cout << endl << "Apasa " << i + 1 << " pentru filmul: " << endl;
				cout << vectorFilm[i];
			}

			cout << endl << "Selecteaza filmul: ";
			cin >> optiuneFilm;

			cout << endl << "Selecteaza randul si locul: " << endl;
			s.getLocuriSala();


			cout << "Rand: ";
			cin >> rand;
			cout << "Loc: ";
			cin >> loc;

			cout << endl << "Ati selectat filmul: " << endl << vectorFilm[optiuneFilm] << endl;
			cout << "Locul " << loc << " randul " << rand << endl;
			cout << "Rezervarea a fost facuta cu succes!" << endl << endl;

			break;
		case 3:
			break;
		case 4:
			while (true)
			{
				if (revenireMeniu == "0")
				{
					break;
				}
				cout << endl << "Autentificare: [nume default = 'administrator' parola default = 'parola']" << endl;
				cout << "numele de utilizator: ";
				cin >> ws;
				getline(cin, username);
				cout << "parola: ";
				getline(cin, password);

				if (username != "administrator" && password != "parola")
				{
					cout << endl << "---- Numele de utilizator sau parola sunt incorecte. Incearca din nou!----" << endl << endl <<
						"Pentru schimbarea parolei sau a numelui de utilizator adreseaza-te departamentului IT!" << endl <<
						"Apasa orice tasta pentru a incerca din nou, "
						"apasa 0 pentru revenirea la meniul anterior ";
					cin >> ws;
					getline(cin, revenireMeniu);
				}
				else
				{
					cout << endl << "Bine ai venit, " << username << "!" << endl;
					administrareCinema();
					break;
				}
			}			
			continue;
		default:
			cout << "Optiunea este invalida, incerca din nou!" << endl << endl;
		}
		break;

	}

	//Sala s1;
	//cin >> s1;
	//s1.getLocuriSala();
	//s1.setLocuriSala(2,3);

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

		/*int asociatCard[] = { 1,2,3,4,5,6,7 };
	string email = "vasile.ion@yahoo.com";
	Client c((char*)"Vasile Ion", asociatCard, 7, email);
	cout << c.getNume() << endl;
	cout << c.getNrCarduri() << endl;
	cout << c.getNrAsociatCard() << endl;
	cout << c.getEmail() << endl;
	string email1 = "vasile@yahoo.com";
	c.setEmail(email1);
	cout << c.getEmail();
		*/

		//int nrBilete[] = { 1,2,3,4,5,6,7,8 };
		//Rezervare r((char*)"12/10/2020", nrBilete, 8, true);
		//cout << r.getNrBileteRezervate();

}

