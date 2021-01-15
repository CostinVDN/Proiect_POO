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
	static int nrTotalSali;
	char* numeSala;
	int nrRanduri;
	int nrLocuriPeRand;
	int** locuriSala;
	int** orarSala;
	int pretLocSala;
	string tipSala;

public:
	Sala() : nrSala(++nrTotalSali)
	{
		numeSala = nullptr;
		locuriSala = nullptr;
		tipSala = "2D";
		nrLocuriPeRand = 0;
		nrRanduri = 0;
		pretLocSala = 25;
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
					this->locuriSala[i][j] = 0;
				}
			}
		}
		else
		{
			this->locuriSala = nullptr;
		}

		orarSala = new int* [7];
		for (int i = 0; i < 7; i++)
		{
			orarSala[i] = new int[10];
		}
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				orarSala[i][j] = 0;
			}
		}

		this->nrRanduri = nrRanduri;
		this->nrLocuriPeRand = nrLocuriPeRand;
		this->tipSala = tipSala;
		pretLocSala = 25;
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
			locuriSala = new int* [s.nrRanduri];
			for (int i = 0; i < s.nrRanduri; i++)
			{
				locuriSala[i] = new int[s.nrLocuriPeRand];
			}
			for (int i = 0; i < s.nrRanduri; i++)
			{
				for (int j = 0; j < s.nrLocuriPeRand; j++)
				{
					locuriSala[i][j] = s.locuriSala[i][j];
				}
			}

		}
		else
		{
			this->locuriSala = nullptr;
		}

		orarSala = new int* [7];
		for (int i = 0; i < 7; i++)
		{
			orarSala[i] = new int[10];
		}
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				orarSala[i][j] = 0;
			}
		}

		this->nrRanduri = s.nrRanduri;
		this->nrLocuriPeRand = s.nrLocuriPeRand;
		this->tipSala = s.tipSala;
		this->pretLocSala = s.pretLocSala;
	}


	Sala& operator=(const Sala& s)
	{
		delete[] numeSala;
		delete[] locuriSala;
		delete[] orarSala;

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
						this->locuriSala[i][j] = s.locuriSala[i][j];	//modificat aici
					}
				}

			}
			else
			{
				this->locuriSala = nullptr;
			}

			orarSala = new int* [7];
			for (int i = 0; i < 7; i++)
			{
				orarSala[i] = new int[10];
			}
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					orarSala[i][j] = s.orarSala[i][j];
				}
			}

			this->nrRanduri = s.nrRanduri;
			this->nrLocuriPeRand = s.nrLocuriPeRand;
			this->tipSala = s.tipSala;
			this->pretLocSala = s.pretLocSala;
		}
		return *this;
	}

	~Sala()
	{
		delete[] numeSala;
		delete[] locuriSala;
		delete[] orarSala;
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

	void setPretLocSala(int pret)
	{
		pretLocSala = pret;
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
		return nullptr;
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

		f.write((char*)&nrSala, sizeof(nrSala));
		f.write(numeSala, (long long)strlen(numeSala) + 1);
		f.write((char*)&locuriSala, sizeof(locuriSala));
		f.write((char*)&nrLocuriPeRand, sizeof(nrLocuriPeRand));
		f.write((char*)&nrRanduri, sizeof(nrRanduri));

		f.write(tipSala.c_str(), tipSala.length() + 1);

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

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			out << " " << s.orarSala[i][j];
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
	int nrZile;
	int* zileProiectii;
	int nrProiectiiZi;
	int* oreProiectii;
	string gen;
	int durata;
	int idSala;

public:
	Film() : idFilm(++nrFilme)
	{
		nume = nullptr;
		nrZile = 0;
		zileProiectii = nullptr;
		nrProiectiiZi = 0;
		oreProiectii = nullptr;
		gen = "";
		durata = 90;
		idSala = 0;
	}

	Film(char* nume, int nrZile, int* zileProiectii, int nrProiectiiZi, int* oreProiectii, int idSala) : idFilm(++nrFilme)
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

		if (zileProiectii != nullptr && nrZile > 0)
		{
			this->nrZile = nrZile;
			this->zileProiectii = new int[nrZile];
			for (int i = 0; i < nrZile; i++)
			{
				this->zileProiectii[i] = zileProiectii[i];
			}
		}
		else
		{
			this->zileProiectii = nullptr;
			this->nrZile = 0;
		}

		if (oreProiectii != nullptr && nrProiectiiZi > 0)
		{
			this->nrProiectiiZi = nrProiectiiZi;
			this->oreProiectii = new int[nrProiectiiZi];
			for (int i = 0; i < nrProiectiiZi; i++)
			{
				this->oreProiectii[i] = oreProiectii[i];
			}
		}
		else
		{
			this->oreProiectii = nullptr;
			this->nrProiectiiZi = 0;
		}

		gen = "";
		durata = 90;
		this->idSala = idSala;
	}

	Film(const Film& f) :idFilm(f.idFilm)
	{

		if (f.nume != nullptr)
		{
			this->nume = new char[strlen(f.nume) + 1];
			strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
		}
		else
		{
			this->nume = nullptr;
		}

		if (f.zileProiectii != nullptr && f.nrZile > 0)
		{
			this->nrZile = f.nrZile;

			this->zileProiectii = new int[f.nrZile];

			for (int i = 0; i < f.nrZile; i++)
			{
				this->zileProiectii[i] = f.zileProiectii[i];
			}
		}
		else
		{
			this->zileProiectii = nullptr;
			this->nrZile = 0;
		}

		if (f.oreProiectii != nullptr && f.nrProiectiiZi > 0)
		{
			this->nrProiectiiZi = f.nrProiectiiZi;
			this->oreProiectii = new int[f.nrProiectiiZi];
			for (int i = 0; i < f.nrProiectiiZi; i++)
			{
				this->oreProiectii[i] = f.oreProiectii[i];
			}
		}
		else
		{
			this->oreProiectii = nullptr;
			this->nrProiectiiZi = 0;
		}

		this->gen = f.gen;
		this->durata = f.durata;
		this->idSala = f.idSala;
	}

	~Film()
	{
		delete[] nume;
		delete[] zileProiectii;
	}

	Film& operator=(const Film& f)
	{
		delete[] nume;
		delete[] zileProiectii;

		if (this != &f)
		{
			if (f.nume != nullptr)
			{
				this->nume = new char[strlen(f.nume) + 1];
				strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
			}
			else
			{
				this->nume = nullptr;
			}

			if (f.zileProiectii != nullptr && nrZile > 0)
			{
				this->zileProiectii = new int[nrZile];

				for (int i = 0; i < nrZile; i++)
				{
					this->zileProiectii[i] = f.zileProiectii[i];
				}
			}
			else
			{
				this->zileProiectii = nullptr;
				nrZile = 0;
			}

			this->gen = f.gen;
			this->durata = f.durata;
			this->idSala = f.idSala;
		}
		return *this;
	}

	//Verifica daca un film ruleaza intr-o anumita  zi
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!trebuie refacut!!!!!!!!!!!!!!!
	//bool operator[](int zi)
	//{
	//	bool ruleaza = false;
	//	for (int i = 0; i < 7; i++)
	//	{
	//		if (this->zileProiectii[zi] == 1)
	//			ruleaza = true;
	//	}
	//	return ruleaza;
	//}

	static int getnrFilme()
	{

		return nrFilme;

	}

	static void setnrFilme(int nrfilme)
	{

		Film::nrFilme = nrfilme;

	}

	void setNumeFilm(const char* nume)
	{
		if (this->nume != nullptr)
		{
			delete[] this->nume;
		}
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
		{
			this->nume = nullptr;
		}
	}

	int getIdFilm()
	{
		return idFilm;
	}

	char* getNume()
	{
		if (nume != nullptr)
		{
			return nume;
		}
		return nullptr;
	}

	string getGen()
	{
		return gen;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int* getProgram()
	{
		return this->zileProiectii;
	}

	int getDurata()
	{
		return durata;
	}

	//operatorul ++ creste frecventa rularii filmului cu 1 zi
	Film operator++()
	{
		bool alocare_zi = false;
		int indx = 6;
		do
		{
			if (this->zileProiectii[indx] == 0)
			{
				this->zileProiectii[indx] = 1;
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
			if (copie.zileProiectii[indx] == 0)
			{
				copie.zileProiectii[indx] = 1;
				alocare_zi = true;
			}
			indx--;
		} while ((indx < 0) || (!alocare_zi));
		return copie;
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! trebuie refacut !!!!!!!!!!!!!!!
	//Film operator+(int poz)
	//{
	//	this->pozitie_top -= poz;
	//	return *this;
	//}

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

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	////Returneaza daca filmul este in top 10
	//bool operator!()
	//{
	//	if (this->pozitie_top > 10)
	//		return true;
	//	else
	//		return false;
	//}

	//Care din filmele comparate ruleaza mai multe zile intr-o saptamana
	Film operator>=(const Film& f)
	{
		int nr_zile_film1 = 0, nr_zile_film2 = 0;
		for (int indx = 0; indx < 7; indx++)
		{
			if (this->zileProiectii[indx] == 1)
				nr_zile_film1++;

			if (f.zileProiectii[indx] == 1)
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
			if (this->zileProiectii[indx] != f.zileProiectii[indx])
				return false;
		}
		return true;
	}

	void serializareFilm(ofstream &f, Film film_crt)
	{

		f.write((char*)&idFilm, sizeof(idFilm));
		//f.write(nume, strlen(nume) + 1);

		f.write(nume, (long long)strlen(nume) + 1);

		f.write((char*)&nrZile, sizeof(nrZile));
		for (int i = 0; i < nrZile; i++)
		{
			f.write((char*)&zileProiectii[i], sizeof(zileProiectii[i]));
		}

		f.write((char*)&nrProiectiiZi, sizeof(nrProiectiiZi));
		for (int i = 0; i < nrProiectiiZi; i++)
		{
			f.write((char*)&oreProiectii[i], sizeof(oreProiectii[i]));
		}

		int length2 = gen.length() + 1;
		f.write((char*)&length2, sizeof(length2));
		f.write(gen.c_str(), length2);

		f.write((char*)&durata, sizeof(durata));
		f.write((char*)&idSala, sizeof(idSala));

	}

	void deserializareFilm(ifstream& f2, Film film_crt)
	{

		f2.read((char*)&idFilm, sizeof(idFilm));

		string buffer = "";
		char c = 0;
		while ((c = f2.get()) != 0)
		{
			buffer += c;
		}
		delete[] nume;
		nume = new char[buffer.length() + 1];
		strcpy_s(nume, buffer.length() + 1, buffer.c_str());

		f2.read((char*)&nrZile, sizeof(nrZile));

		delete[] zileProiectii;
		zileProiectii = new int[nrZile];
		for (int i = 0; i < nrZile; i++)
		{
			f2.read((char*)&zileProiectii[i], sizeof(zileProiectii[i]));
		}

		f2.read((char*)&nrProiectiiZi, sizeof(nrProiectiiZi));
		delete[] oreProiectii;
		oreProiectii = new int[nrProiectiiZi];
		for (int i = 0; i < nrProiectiiZi; i++)
		{
			f2.read((char*)&oreProiectii[i], sizeof(oreProiectii[i]));
		}

		int length2 = 0;
		f2.read((char*)&length2, sizeof(length2));
		char* aux = new char[length2];
		f2.read(aux, length2);
		gen = aux;

		f2.read((char*)&durata, sizeof(durata));
		f2.read((char*)&idSala, sizeof(idSala));

	}

	friend ostream& operator<< (ostream&, Film);
	friend istream& operator>> (istream&, Film&);
	friend class Bilet;
};

int Film::nrFilme = 0;

//Operator afisare info Filme
ostream& operator<< (ostream& out, Film f)
{
	out << endl;
	if (f.idFilm != 0)
		out << "ID Film: " << f.idFilm << endl;

	if (f.nume != nullptr)
	{
		out << "Nume film: " << f.nume;
	}
	
	out << endl;

	if (f.zileProiectii != nullptr && f.nrZile > 0)
	{
		cout << "Zile proiectii: ";
		for (int i = 0; i < f.nrZile; i++)
		{
			out << f.zileProiectii[i] << " ";
		}
	}

	out << endl;
	
	if (f.oreProiectii != nullptr && f.nrProiectiiZi > 0)
	{
		out << "Ore proiectii: ";
		for (int i = 0; i < f.nrProiectiiZi; i++)
		{
			out << f.oreProiectii[i] << " ";
		}
	}

	out << endl;

	cout << "Genul filmului: " << f.gen << endl;
	cout << "Durata filmului: " << f.durata << endl;
	cout << "Id sala: " << f.idSala << endl;

	return out;
}

//Operator citire info Filme
istream& operator>> (istream& in, Film& f)
{

	cout << endl <<"Nume film: ";
	delete[] f.nume;
	char buffer[50];
	in >> ws;
	in.getline(buffer, 49);
	f.nume = new char[strlen(buffer) + 1];
	strcpy_s(f.nume, strlen(buffer) + 1, buffer);

	cout << "Introdu numarul zilelor din saptamana in care va rula filmul: ";
	in >> f.nrZile;
	
	if (f.nrZile > 0)
	{
		cout << "Pentru ziua 'luni' introdu 1:" << endl;
		f.zileProiectii = new int[f.nrZile];
		for (int i = 0; i < f.nrZile; i++)
		{
			cout << "Zi " << i + 1 << ": ";
			in >> f.zileProiectii[i];
		}
	}

	cout << "Introdu numarul proiectiilor pe zi: ";
	in >> f.nrProiectiiZi;
	if (f.nrProiectiiZi > 0)
	{
		f.oreProiectii = new int[f.nrProiectiiZi];
		for (int i = 0; i < f.nrProiectiiZi; i++)
		{
			cout << "Ora [" << i + 1 << "]: ";
			in >> f.oreProiectii[i];
		}
	}

	cout << "Gen: ";
	in >> ws;
	getline(in, f.gen);

	cout << "Durata: ";
	in >> f.durata;

	cout << "Id sala: ";
	in >> f.idSala;

	return in;
}

class Bilet
{

private:
	const int codBilet;
	static int nrBileteEmise;
	char* dataFilm;
	int rand;
	int nrLocuri;
	int* locuri;
	int idFilm;

public:

	Bilet() : codBilet{ ++nrBileteEmise }
	{
		dataFilm = nullptr;
		rand = 0;
		nrLocuri = 0;
		locuri = nullptr;
		idFilm = 0;
	}

	Bilet(char* dataFilm, int rand, int nrLocuri, int* locuri, int idFilm) :codBilet(++nrBileteEmise)
	{

		if (dataFilm != nullptr)
		{

			this->dataFilm = new char[strlen(dataFilm)+1];
			strcpy_s(this->dataFilm,strlen(dataFilm)+1, dataFilm);

		}
		else
		{

			this->dataFilm = nullptr;

		}

		this->rand = rand;
		this->nrLocuri = nrLocuri;

		if (locuri != nullptr && nrLocuri > 0) 
		{
			this->locuri = new int[nrLocuri];
			for (int i = 0; i < nrLocuri; i++)
				this->locuri[i] = locuri[i];
		}
		else 
		{
			this->locuri = nullptr;
			this->nrLocuri = 0;
		}

		this->idFilm = idFilm;
	}

	Bilet(const Bilet& b) : codBilet{ b.codBilet }
	{
		if (b.dataFilm != nullptr)
		{

			this->dataFilm = new char[strlen(b.dataFilm) + 1];
			strcpy_s(this->dataFilm, strlen(b.dataFilm) + 1, dataFilm);

		}
		else
		{

			this->dataFilm = nullptr;
		}

		this->rand = b.rand;
		this->nrLocuri = b.nrLocuri;

		if (b.locuri != nullptr && b.nrLocuri > 0) 
		{
			locuri = new int[b.nrLocuri];
			for (int i = 0; i < b.nrLocuri; i++)
				locuri[i] = b.locuri[i];
			
		}
		else 
		{
			this->locuri = nullptr;
			this->nrLocuri = 0;
		}

		this->idFilm = b.idFilm;
	}

	Bilet& operator=(const Bilet& b)
	{

		delete[] dataFilm;
		delete[] locuri;

		if (this != &b)
		{

			if (b.dataFilm != nullptr)
			{

				this->dataFilm = new char[strlen(b.dataFilm) + 1];
				strcpy_s(this->dataFilm, strlen(b.dataFilm) + 1, dataFilm);

			}
			else
			{

				this->dataFilm = nullptr;
			}
			
			this->rand = b.rand;
			if (b.locuri != nullptr && b.nrLocuri > 0) 
			{
				this->nrLocuri = b.nrLocuri;
				this->locuri = new int[b.nrLocuri];
				
				for (int i = 0; i < b.nrLocuri; i++) 
					this->locuri[i] = b.locuri[i];
				
			}
			else 
			{
				this->locuri = nullptr;
				this->nrLocuri = 0;
			}

			this->idFilm = b.idFilm;
		}
		return*this;
	}

	~Bilet()
	{
		delete[] dataFilm;
		delete[] locuri;
	}


	//Se afiseaza daca biletul s-a emis pentru un anumit film
	//bool operator[](int indx)
	//{
	//	if (idFilm == indx)
	//	{
	//		return true;
	//	}
	//	return false;
	//}

	//Se acorda o reducere clientilor fideli de 10%,20%
	//Bilet operator-(float reducere)
	//{
	//	pret = pret * (1 - reducere / 100);
	//	return *this;
	//}

	//Se schimba ora cu urmatoarea proiecte peste 2 ore (ex.de la ora 10 la ora 12)
	//Daca ora > 20 se trece la ora 10
	Bilet operator++()
	{
		nrLocuri++;
		return *this;
	}

	Bilet operator++(int x)
	{
		Bilet copie_bilet = *this;
		copie_bilet.nrLocuri++;

		return copie_bilet;

	}

	explicit operator string()
	{
		return dataFilm;
	}

	//Returneaza true/false daca biletul s-a emis in aceeasi zi cu ziua  in care ruleaza filmul
	//bool operator!()
	//{
	//	if (DataFilm == dataFilm)
	//		return false;
	//	else
	//		return true;
	//}

	//Verifica daca biletele s-au emis pentru filme din aceeasi zi
	//string operator==(Bilet& b)
	//{

	//	//Se verifica ca biletele sa nu fie emis pentru acleasi film
	//	if (this->DataFilm == b.DataFilm)
	//	{

	//		return "Biletele sunt emise pentru filme ce ruleaza in aceeasi zi";
	//	}
	//	else
	//	{

	//		return "Biletele sunt emise pentru filme ce NU ruleaza in aceeasi zi";

	//	}

	//}

	bool operator>=(Bilet& b)
	{
		if (nrLocuri >= b.nrLocuri)
			return true;
		else
			return false;
	}

	int getNrBileteEmise()
	{
		return Bilet::nrBileteEmise;
	}

	void serializare_bilet()
	{
		ofstream f("bilet.bin", ios::binary);
		f.write((char*)&rand, sizeof(rand));
		f.write((char*)&idFilm, sizeof(idFilm));

		//f.write("\n\r", sizeof("\n\r"));
		f.close();
	}

	friend istream& operator>> (istream&, Bilet&);
	friend ostream& operator<< (ostream&, Bilet);
	friend ofstream& operator<<(ofstream&, Bilet);
	friend class Rezervare;
};
int Bilet::nrBileteEmise = 0;

//Operator afisare info Bilete
ostream& operator<< (ostream& out, Bilet b)
{

	cout << setw(7) << left << b.codBilet << setw(15) << left << setw(15) << left << b.dataFilm
		<< setw(7) << left << setw(7) << left << b.rand << setw(7)
		<< setw(15) << left << setw(15) << left << b.idFilm << endl;
	return out;
}

//Operator citire info Bilete
istream& operator>> (istream& in, Bilet& b)
{

	string buffer;

	delete[] b.dataFilm;
	cout << "Data Filmului (ZZ.LL.AAAA): ";
	getline(in, buffer);
	b.dataFilm = new char[buffer.length() + 1];
	strcpy_s(b.dataFilm, buffer.length() + 1, buffer.c_str());

	cout << "Nuarul randului: ";
	in >> b.rand;

	cout << "Nuarul de locuti dorite: ";
	in >> b.nrLocuri;

	delete[] b.locuri;
	b.locuri = new int[b.nrLocuri];
	for (int indx = 0; indx < b.nrLocuri; indx++)
	{

		cout << "Locul [" << indx + 1 << "]: ";
		in >> b.locuri[indx];

	}

	cout << "ID Film: ";
	in >> b.idFilm;

	return in;
}

//Operator info Bilete salvare in fisier 
ofstream& operator<<(ofstream& file_out, Bilet b)
{

	if (file_out.is_open())
	{
	
		file_out << b.dataFilm << endl;
		file_out << b.rand << endl;
		file_out << b.nrLocuri << endl;
		for (int indx = 0; indx < b.nrLocuri; indx++)
		{

			file_out << b.locuri[indx]<< endl;
		}
	}

	return file_out;
}

class Client
{
private:
	const int idClient;
	static int nrClienti;
	char* numeClient;
	int nrCarduri;
	int* nrAsociatCard;
	string numeUtilizatorClient;

public:
	Client() : idClient(++nrClienti)
	{
		numeClient = nullptr;
		nrCarduri = 0;
		nrAsociatCard = nullptr;
		numeUtilizatorClient = "";
	}

	Client(char* nume, int nrCarduri, int* nrAsociatCard, string numeUtilizatorClient) : idClient(++nrClienti)
	{
		if (nume != nullptr)
		{
			this->numeClient = new char[strlen(nume) + 1];
			strcpy_s(this->numeClient, strlen(nume) + 1, nume);
		}
		else
		{
			this->numeClient = nullptr;
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

		this->numeUtilizatorClient = numeUtilizatorClient;
	}

	Client(const Client& c) : idClient(c.idClient)
	{
		if (c.numeClient != nullptr)
		{
			numeClient = new char[strlen(c.numeClient) + 1];
			strcpy_s(numeClient, strlen(c.numeClient) + 1, c.numeClient);
		}
		else
		{
			numeClient = nullptr;
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

		numeUtilizatorClient = c.numeUtilizatorClient;
	}

	~Client()
	{
		delete[] numeClient;
		delete[] nrAsociatCard;
	}

	Client& operator=(Client& c)
	{
		delete[] numeClient;
		delete[] nrAsociatCard;

		if (c.numeClient != nullptr)
		{
			numeClient = new char[strlen(c.numeClient) + 1];
			strcpy_s(numeClient, strlen(c.numeClient) + 1, c.numeClient);
		}
		else
		{
			numeClient = nullptr;
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

		numeUtilizatorClient = c.numeUtilizatorClient;

		return *this;
	}
	char* getNume()
	{
		if (numeClient == nullptr)
			return nullptr;
		char* copie = new char[strlen(numeClient) + 1];
		strcpy_s(copie, strlen(numeClient) + 1, numeClient);
		return copie;
	}

	void setNume(char* nume)
	{
		if (nume != nullptr)
		{
			if (this->numeClient != nullptr)
				delete[]this->numeClient;
			this->numeClient = new char[strlen(nume) + 1];
			strcpy_s(this->numeClient, strlen(nume) + 1, nume);
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

	string getNumeUtilizatorClient()
	{
		return numeUtilizatorClient;
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
		return this->numeClient;
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
		f.write(numeClient, (long long)strlen(numeClient) + 1);
		f.write((char*)&nrCarduri, sizeof(nrCarduri));
		for (int i = 0; i < nrCarduri; i++)
		{
			f.write((char*)&nrAsociatCard[i], sizeof(nrAsociatCard[i]));
		}
		f.write(numeUtilizatorClient.c_str(), numeUtilizatorClient.length());
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
		delete[] numeClient;
		numeClient = new char[buffer.length() + 1];
		strcpy_s(numeClient, buffer.length() + 1, buffer.c_str());

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
		numeUtilizatorClient = aux;
		f.close();
	}

	friend ostream& operator<<(ostream&, Client);
	friend istream& operator>>(istream&, Client&);
	friend class Rezervare;
};

int Client::nrClienti = 0;

ostream& operator<<(ostream& out, Client c)
{
	if (c.numeClient != nullptr)
	{
		out << endl << "Nume: " << c.numeClient << endl;
	}
	out << "Email: " << c.numeUtilizatorClient << endl;

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
	delete[] c.numeClient;
	char buffer[50];
	in >> ws;
	in.getline(buffer, 49);
	c.numeClient = new char[strlen(buffer) + 1];
	strcpy_s(c.numeClient, strlen(buffer) + 1, buffer);

	cout << endl << "Email: ";
	//in >> ws;
	getline(in, c.numeUtilizatorClient);
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
	c.nrCarduri += x;
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
	string numeUtilizatorClient;

public:
	Rezervare() :idRezervare(++nrRezervari)
	{
		dataRezervare = nullptr;
		nrBileteRezervate = nullptr;
		nrBilete = 0;
		achitat = false;
		numeUtilizatorClient = "";
	}

	Rezervare(int nrBilete) :idRezervare(++nrRezervari)
	{
		dataRezervare = new char[] {""};
		this->nrBilete = nrBilete;
		nrBileteRezervate = new int[nrBilete];
		achitat = false;
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

		if (nrBileteRezervate != nullptr && nrBilete < 0)
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

		if (r.nrBileteRezervate != nullptr && nrBilete > 0)
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

	int operator[](int index)
	{
		if (index >= 0 && index < nrBilete / sizeof(int) && nrBileteRezervate != nullptr)
		{
			return nrBileteRezervate[index];
		}
		return 0;
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

//class Repo
//{
//public:
//
//
//	void administrareCinema()
//	{
//		int optiune = 0;
//		while (true)
//		{
//			cout << endl << "==== Meniu ====" << endl << endl <<
//				"1. Adaugare sala" << endl <<
//				"2. Modificare sala" << endl <<
//				"3. Stergere sala" << endl << endl <<
//				"4. Adaugare film" << endl <<
//				"5. Modificare film" << endl <<
//				"6. Stergere film" << endl << endl <<
//				"7. Adaugare bilet" << endl <<
//				"8. Modificare bilet" << endl <<
//				"9. Stergere bilet" << endl << endl <<
//				"0. Revenire la meniul anterior" << endl;
//
//			cout << endl << "Selecteaza optiunea: ";
//			cin >> optiune;
//
//			switch (optiune)
//			{
//			case 0:
//				break;
//			case 1:
//				break;
//			case 2:
//				brea;
//			case 3:
//				break;
//			case 4:
//				adaugareFilme();
//				continue;
//			case 5:
//				break;
//			case 6:
//				break;
//			default:
//				cout << "Optiunea este invalida, incerca din nou!" << endl << endl;
//			}
//			break;
//		}
//	}
//
//void adaugareFilme()
//	{
//		fstream find("film.bin", ios::_Nocreate | ios::binary | ios::in);
//		int size = sizeof(nrFilme);
//		find.seekg(-size, ios::end);
//		find.read((char*)&nrFilme, size);
//		find.close();
//		cout << nrFilme;
//
//		if (nrFilme > 0)
//		{
//			int sizeVector = nrFilme + 1;
//			vectorFilme = new Film * [sizeVector];
//			ifstream f("film.bin", ios::binary);
//
//			for (int i = 0; i < nrFilme; i++)
//			{
//				vectorFilme[i]->deserializareFilm();
//			}
//
//
//			f.read((char*)&nrFilme, sizeof(nrFilme));
//			vectorFilme[nrFilme + 1] = new Film();
//			cin >> *vectorFilme[nrFilme + 1];
//			f.close();
//		}
//		else if (nrFilme == 0)
//		{
//			vectorFilme = new Film * [nrFilme + 1];
//			vectorFilme[nrFilme] = new Film();
//			cin >> *vectorFilme[nrFilme];
//		}
//

		//cout << *vectorFilme[nrFilme];

		//for (int i = 0; i < nrFilme; i++)
		//{
		//	cout << *vectorFilme[i];
		//}
		/*nrFilme++;

		ofstream f("film.bin", ios::binary);
		for (int i = 0; i < nrFilme; i++)
		{
			vectorFilme[i]->serializareFilm();
		}
		f.write((char*)&nrFilme, sizeof(nrFilme));

		f.close();
	}
};*/

Film** administrare_filme(Film** lista_filme)
{
	int optiune;
	int nr_filme = 0;
	int nr_filme_noi = 0;
	bool exista_idfilm = false;
	ofstream f1;
	ifstream f2;

	system("cls");

	do
	{

		cout << endl <<
			"==== Administrare filme: ====" << endl << endl <<
			"1. Adaugare filme" << endl <<
			"2. Modificare film" << endl <<
			"3. Stergere film" << endl <<
			"4. Afisare info filme" << endl <<
			"0. Exit" << endl;

		cout << endl << "Selecteaza optiunea: ";

		cin >> optiune;

		//Se citesc nr. de filme salvate din fisier
		f2.open("film.bin", ios::_Nocreate | ios::binary);
		f2.read((char*)&nr_filme, sizeof(nr_filme)); //nr filme inregistrate in fisier

		if (nr_filme != 0)
		{
			if (optiune == 1)
			{

				cout << "Introduceti nr. de fime pe care doriti sa le adaugati:";
				cin >> nr_filme_noi;

				lista_filme = new Film * [nr_filme + nr_filme_noi];
			}
			else
			{

				lista_filme = new Film * [nr_filme];

			}

			//Se citesc filmele din fisierul binar
			for (int indx = 0; indx < nr_filme; indx++)
			{
				lista_filme[indx] = new Film();
				lista_filme[indx]->deserializareFilm(f2, *lista_filme[indx]);
			}

			cout << "Filmele salvate in fisierul binar au fost incarcate cu succes!" << endl;
		}
		else
		{

			if (optiune == 1)
			{

				cout << "Introduceti nr. de fime pe care doriti sa le adaugati:";
				cin >> nr_filme_noi;

				lista_filme = new Film * [nr_filme_noi];

			}
			else
			{
			
				cout << "Nu exista filme salvate in fisierul binar!" << endl;
			
			}

		}

		f2.close();

		switch (optiune)
		{

		case 1:
			//Inregistrare filme noi

			if (nr_filme !=0)
				Film::setnrFilme(nr_filme);

			for (int indx = nr_filme; indx < nr_filme + nr_filme_noi; indx++)
			{
				lista_filme[indx] = new Film();
				cin >> (*lista_filme[indx]);
			}

			// Se seteaza nr de file la nr de filme din fisierul bina + nr filme noi inregistrate 
			nr_filme += nr_filme_noi;

			break;

		case 2:
			// Modificare info film
			int IDFilm;

			if (nr_filme != 0)
			{
				cout << "Introduceti ID Film pe care doriti sa-l modificati ";
				do
				{

					cin >> IDFilm;

				} while ((IDFilm < 1) || (IDFilm > nr_filme));

				cin >> (*lista_filme[IDFilm - 1]);
			}
			break;

		case 3:
			//Stergere filme
			if (nr_filme != 0)
			{
				cout << "Introduceti ID Film pe care doriti sa-l stergeti ";
				cin >> IDFilm;

				for (int indx = 0; indx < nr_filme; indx++)
				{

					if (lista_filme[indx]->getIdFilm() == IDFilm)
					{

						exista_idfilm = true;
						delete lista_filme[indx];
						lista_filme[indx] = nullptr;

						//Setam nr filme cu unu mai putin
						nr_filme_noi = nr_filme - 1;

					}

				}

				if (!exista_idfilm)
					cout << "Nu exista Filmul cu ID-ul: " << IDFilm;
				
			}
			break;
		case 4:
			//Afisare lista filme			
			if (nr_filme != 0)
			{
				cout << "Lista filme inregistrate" << endl;
				cout << "===========================" << endl;

				for (int indx = 0; indx < nr_filme; indx++)
				{

					if (lista_filme[indx] != nullptr)
						cout << (*lista_filme[indx]);

				}
			}
			break;
			//case 5:
			//	f1.open("film.bin", ios::binary);
			//		
			//		//Se scrie nr. de filme in fisier
			//		f1.write((char*)&nr_filme, sizeof(nr_filme));
			//		for (int indx=0; indx < nr_filme; indx++)
			//			lista_filme[indx]->serializareFilm(f1, *lista_filme[indx]);

			//	f1.close();

			//	break;
			//case 6:
			//			break;'=
		}

		// La finalul oricarei operatiuni se inregistreaza filme in fisierul binar daca exista filem de inregistrat
		if (nr_filme != 0 && optiune != 4)
		{

			f1.open("film.bin", ios::binary);

			//Se scrie nr. de filme in fisier
			if (optiune == 3)
			{

				f1.write((char*)&nr_filme_noi, sizeof(nr_filme));

			}
			else
			{

				f1.write((char*)&nr_filme, sizeof(nr_filme));

			}

			for (int indx = 0; indx < nr_filme; indx++)
			{

				if (lista_filme[indx] != nullptr)
					lista_filme[indx]->serializareFilm(f1, *lista_filme[indx]);

			}
			
			f1.close();

			if (optiune == 3)
				nr_filme = nr_filme_noi;

			cout << "Datele despre filme au fost salvate in fisierul binar!" << endl;
		}

	} while (optiune != 0);

	return lista_filme;
}

int main()
{

	//Repo repo;
	string username = "administrator";
	string password = "parola";
	string revenireMeniu = "1";
	int nr_sali, nr_bilete, nr_clienti, nr_rezervari;
	int optiuneFilm = 0;
	int rand = 0;
	int loc = 0;
	int optiune;

	Sala** lista_sali= nullptr;
	Film** lista_filme = nullptr;
	Client** lista_clienti= nullptr;
	Bilet** lista_bilete = nullptr;
	Rezervare** lista_rezervari = nullptr;

	do
	{
		cout << endl <<
			"==== Meniu: ====" << endl << endl <<
			"1. Administrare sali" << endl <<
			"2. Administrare filme" << endl <<
			"3. Administrare bilete" << endl <<
			"4. Administrae rezervare" << endl <<
			"5. Administrare clienti" << endl <<
			"6. Cont client" << endl <<
			"0. Exit" << endl;

		cout << endl << "Selecteaza optiunea: ";

		cin >> optiune;

		switch (optiune)
		{
			case 1:
				break;
			case 2:
				administrare_filme(lista_filme);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
		}
	} while (optiune != 0);



	//while (true)
	//{
	//	cout << endl <<
	//		"==== Meniu: ====" << endl << endl <<
	//		"1. Afisare Filme" << endl <<
	//		"2. Rezervare bilet" << endl <<
	//		"3. Modificare rezervare" << endl <<
	//		"4. Administrare cinema" << endl <<
	//		"5. Cont client" << endl <<
	//		"0. Exit" << endl;

	//	cout << endl << "Selecteaza optiunea: ";

	//	cin >> optiune;
	//	//cout << endl;

	//	switch (optiune)
	//	{
	//	case 0:
	//		break;
	//	case 1:
	//		cout << endl;
	//		for (int i = 0; i < 3; i++)
	//		{
	//			//cout << vectorFilm[i];
	//		}
	//		continue;
	//	case 2:

	//		cout << "Apasa 1 pentru autentificare" << endl <<
	//			"Apasa 2 pentru creare cont nou" << endl;
	//		cout << "// Momentan nu exista optiunea asta, se creeaza cont nou by default" << endl;
	//		cin >> c;
	//		cin >> r;

	//		for (int i = 0; i < 3; i++)
	//		{
	//			cout << endl << "Apasa " << i + 1 << " pentru filmul: " << endl;
	//			//cout << vectorFilm[i];
	//		}

	//		cout << endl << "Selecteaza filmul: ";
	//		cin >> optiuneFilm;

	//		cout << endl << "Selecteaza randul si locul: " << endl;
	//		//s.getLocuriSala();


	//		cout << "Rand: ";
	//		cin >> rand;
	//		cout << "Loc: ";
	//		cin >> loc;

	//		cout << endl << "Ati selectat filmul: " << endl; // << vectorFilm[optiuneFilm] << endl;
	//		cout << "Locul " << loc << " randul " << rand << endl;
	//		cout << "Rezervarea a fost facuta cu succes!" << endl << endl;

	//		break;
	//	case 3:
	//		break;
	//	case 4:
	//		repo.administrareCinema();
	//		break;
	//		while (true)
	//		{
	//			if (revenireMeniu == "0")
	//			{
	//				break;
	//			}
	//			cout << endl << "Autentificare: [nume default = 'administrator' parola default = 'parola']" << endl;
	//			cout << "numele de utilizator: ";
	//			cin >> ws;
	//			getline(cin, username);
	//			cout << "parola: ";
	//			getline(cin, password);

	//			if (username != "administrator" && password != "parola")
	//			{
	//				cout << endl << "---- Numele de utilizator sau parola sunt incorecte. Incearca din nou!----" << endl << endl <<
	//					"Pentru schimbarea parolei sau a numelui de utilizator adreseaza-te departamentului IT!" << endl <<
	//					"Apasa orice tasta pentru a incerca din nou, "
	//					"apasa 0 pentru revenirea la meniul anterior ";
	//				cin >> ws;
	//				getline(cin, revenireMeniu);
	//			}
	//			else
	//			{
	//				cout << endl << "Bine ai venit, " << username << "!" << endl;
	//				repo.administrareCinema();
	//				break;
	//			}
	//		}
	//		continue;
	//	default:
	//		cout << "Optiunea este invalida, incerca din nou!" << endl << endl;
	//	}
	//	break;
	//}


	//vector<Film> vectorF;
	//Film f1;
	//Film f2;
	//Film f3;
	//vectorF.push_back(f1);
	//vectorF.push_back(f2);
	//vectorF.push_back(f3);
	//vector<Film> vectorDes;


	//for (int i = 0; i < 3; i++)
	//{
	//	vectorF[i].serializareFilm();
	//}

	//for (int i = 0; i < 3; i++)
	//{
	//	vectorDes[i].deserializareFilm();
	//}


	//Film f67;
	//Film f68;
	//cin >> f67;
	//f67.serializareFilm();
	//f68.deserializareFilm();
	////cout << f67;
	//cout << f68;


	////OPERATIUNI BILETE

	////1. Adaugare Bilete si afisare lisa bilete emise

	////system("cls");


	////2. Modificare bilet
	//


	////3. Stergere bilet
	//

	////4. Salvare bilete in fisier
	//f.open("Info_bilete.txt");

	//for (int i = 0; i < nr_bilete; i++)
	//{

	//	if (lista_bilete[i] != nullptr)
	//		f << (*lista_bilete[i]);

	//}

	//f.close();

	//	//5. Serializare filme
	//	f.open("bilet.bin", ios::binary);
	//for (int i = 0; i < nr_bilete; i++)
	//{

	//	if (lista_bilete[i] != nullptr)
	//		lista_bilete[i]->serializare_bilet(f, (*lista_bilete[i]));

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

	//int ore[] = { 12, 18, 21 };
	//int ff1[] = { 0, 1, 1, 0, 0, 1, 0 };
	//Film f1((char*)"The Call of the Wild", ff1, "Aventura", 90, "Venus", 3, ore, 1);
	//Film f2((char*)"The Christmas Chronicles II", ff1, "Comedie", 90, "Venus", 3, ore, 1);
	//Film f3((char*)"Top Gun: Maverick", ff1, "Actiune", 90, "Venus", 3, ore, 1);

	//Rezervare r;
	//Sala s((char*)"Venus", 7, 5, "3D");
	//Client c;



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
	string numeUtilizatorClient = "vasile.ion@yahoo.com";
	Client c((char*)"Vasile Ion", asociatCard, 7, numeUtilizatorClient);
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


