#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Film
{

private:
	const int idFilm;
	char* nume;
	int* frecventa;
	static int nrFilme;
	string gen;
	int durata;
	int pozitie_top;

	//Bilet Bilete;

public:
	Film() : idFilm(++nrFilme)
	{

		nume = nullptr;
		frecventa = nullptr;
		gen = "";
		durata = 0;
		pozitie_top = 0;
	}

	Film(char* nume, int* frecventa, string gen, int durata, int pozitie_top = 20) :idFilm(++nrFilme)
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

		if (frecventa != nullptr)
		{

			this->frecventa = new int[7];

			for (int indx{ 0 }; indx < 7; indx++)
			{

				this->frecventa[indx] = frecventa[indx];
			}
		}
		else
		{

			this->frecventa = nullptr;
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

		if (f.frecventa != nullptr)
		{

			this->frecventa = new int[7];

			for (int indx = 0; indx < 7; indx++)
			{

				this->frecventa[indx] = f.frecventa[indx];
			}
		}
		else
		{

			this->frecventa = nullptr;
		}


		this->gen = f.gen;
		this->durata = f.durata;
		this->pozitie_top = f.pozitie_top;

	}


	Film& operator=(const Film& f)
	{

		delete[] nume;
		delete[] frecventa;

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

			if (f.frecventa != nullptr)
			{

				this->frecventa = new int[7];

				for (int indx = 0; indx < 7; indx++)
				{

					this->frecventa[indx] = f.frecventa[indx];
				}
			}
			else
			{

				this->frecventa = nullptr;
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

			if (this->frecventa[zi] == 1)
				ruleaza = true;
		}

		return ruleaza;

	}


	~Film()
	{

		delete[] nume;
		delete[] frecventa;

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

	void setfrecventa(char* frecventa)
	{

		delete[] frecventa;
		this->frecventa = new int[7];

		for (int indx = 0; indx < 7; indx++)
		{
			this->frecventa[indx] = frecventa[indx];

		}

	}

	//operatorul ++ creste frecventa rularii filmului cu 1 zi
	Film operator++()
	{

		bool alocare_zi = false;
		int indx = 6;

		do
		{

			if (this->frecventa[indx] == 0)
			{

				this->frecventa[indx] = 1;
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

			if (copie.frecventa[indx] == 0)
			{

				copie.frecventa[indx] = 1;
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

			if (this->frecventa[indx] == 1)
				nr_zile_film1++;

			if (f.frecventa[indx] == 1)
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

			if (this->frecventa[indx] != f.frecventa[indx])
				return false;
		}

		return true;

	}

	friend ostream& operator<< (ostream&, Film);
	friend istream& operator>> (istream&, Film&);
};

int Film::nrFilme = 0;

ostream& operator<< (ostream& out, Film f)
{

	string zile_sapt[] = { "Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica" };

	out << "Detalii Film :" << endl;
	out << "=============================" << endl;

	if (f.nume != nullptr)
	{
		out << "Nume: " << f.nume << endl;
	}

	if (f.frecventa != nullptr)
	{
		out << "Frecventa: ";
		for (int indx = 0; indx < 7; indx++)
		{

			if (f.frecventa[indx] == 1)
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

	delete[] f.frecventa;
	f.frecventa = new int[7];
	for (int indx = 0; indx < 7; indx++)
	{

		f.frecventa[indx] = 0;
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
		f.frecventa[zi_rulare - 1] = 1;

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
	int* dateCard;
	string email;

public:
	Client() : idClient(++nrClienti)
	{
		nume = nullptr;
		nrCarduri = 0;
		dateCard = nullptr;
		email = "";
	}

	Client(char* nume, int* dateCard, int nrCarduri, string tipClient, bool abonat) : idClient(++nrClienti)
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

		if (dateCard != nullptr && nrCarduri > 0)
		{
			this->dateCard = new int[nrCarduri];
			for (int i = 0; i < nrCarduri; i++)
			{
				this->dateCard[i] = dateCard[i];
			}
			this->nrCarduri = nrCarduri;
		}
		else
		{
			this->dateCard = nullptr;
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

		if (c.dateCard != nullptr && c.nrCarduri > 0)
		{
			dateCard = new int[c.nrCarduri];
			for (int i = 0; i < c.nrCarduri; i++)
			{
				dateCard[i] = c.dateCard[i];
			}
			nrCarduri = c.nrCarduri;
		}
		else
		{
			dateCard = nullptr;
			nrCarduri = 0;
		}

		email = c.email;
	}

	~Client()
	{
		delete[] nume;
		delete[] dateCard;

	}

	Client& operator=(Client& c)
	{
		delete[] nume;
		delete[] dateCard;

		if (c.nume != nullptr)
		{
			nume = new char[strlen(c.nume) + 1];
			strcpy_s(nume, strlen(c.nume) + 1, c.nume);
		}
		else
		{
			nume = nullptr;
		}

		if (c.dateCard != nullptr && c.nrCarduri > 0)
		{
			dateCard = new int[c.nrCarduri];
			for (int i = 0; i < c.nrCarduri; i++)
			{
				dateCard[i] = c.dateCard[i];
			}
			nrCarduri = c.nrCarduri;
		}
		else
		{
			dateCard = nullptr;
			nrCarduri = 0;
		}

		email = c.email;

		return *this;
	}

	friend ostream& operator<<(ostream&, Client);
	friend istream& operator>>(istream&, Client&);
};

int Client::nrClienti = 0;

ostream& operator<<(ostream& out, Client c)
{
	if (c.nume != nullptr)
	{
		out << "Nume: " << c.nume << endl;
	}
	out << "Numar carduri inregistrate: " << c.nrCarduri << endl;
	if (c.dateCard != nullptr)
	{
		for (int i = 0; i < c.nrCarduri; i++)
		{
			out << "Numar card " << i + 1 << ": " << c.dateCard[i] << endl;
		}
	}
	out << "Email: " << c.email << endl;
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

	if (c.dateCard != nullptr)
	{
		delete[] c.dateCard;
	}
	cout << endl << "Numar carduri: ";
	in >> c.nrCarduri;
	if (c.nrCarduri > 0)
	{
		c.dateCard = new int[c.nrCarduri];
		for (int i = 0; i < c.nrCarduri; i++)
		{
			cout << endl << "Numar card " << i + 1 << ": ";
			in >> c.dateCard[i];
		}
	}
	else
	{
		c.nrCarduri = 0;
		c.dateCard = nullptr;
	}
	cout << endl << "Email: ";
	in >> ws;
	getline(in, c.email);
	cout << endl;

	return in;
}

int main()
{

	string zile_sapt[] = { "Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica" };

	/*Film film_nou;
	cin >> film_nou;
	cout << film_nou;*/

	int zile[] = { 0, 1, 1, 0, 0, 1, 0 };
	Film film_nou_1((char*)"Film 1", zile, "Comedie", 90, 15);

	int zile1[] = { 1, 1, 1, 0, 0, 1, 1 };
	Film film_nou_2((char*)"Film 2", zile1, "Comedie", 85, 11);

	int zile2[] = { 1, 0, 1, 0, 0, 1, 1 };
	Film film_nou_3((char*)"Film 3", zile2, "Actiune", 120, 12);

	Film filme[] = { film_nou_1, film_nou_2, film_nou_3 };

	cout << filme[1] << endl;
	cout << filme[2] << endl << endl;

	if (filme[1] == filme[2])
	{

		cout << "Filmele ruleaza concomitent!";
	}
	else
	{

		cout << "Filmele nu ruleaza in aceleasi zile";

	}

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
}

