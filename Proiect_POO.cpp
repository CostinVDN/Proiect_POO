#include <iostream>
#include <string>

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
	//Bilet Bilete;

public:
	Film() : idFilm(++nrFilme)
	{

		nume = nullptr;

		frecventa = nullptr;

		gen = "";

		durata = 0;
	}
	
	Film(char* nume, int* frecventa, string gen, int durata):idFilm(++nrFilme)
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

			for (int indx{ 0 }; indx <7; indx++)
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
	
	}

	Film(const Film& f):idFilm(f.idFilm)
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
				strcpy_s(this->nume, strlen(f.nume) + 1, nume);
			}
			else
			{

				this->nume = nullptr;
			}

			if (f.frecventa != nullptr)
			{

				this->frecventa = new int[7];

				for (int indx =0 ; indx < 7; indx++)
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

		}

		return *this;

	}

	~Film()
	{

		delete[] nume;
		delete[] frecventa;

	}

	friend ostream& operator<< (ostream&, Film);
	friend istream& operator>> (istream&, Film&);
};

int Film::nrFilme = 0;

ostream& operator<< (ostream& out, Film f)
{

	string zile_sapt[] = {"Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica" };

	out << "Detalii Film :" << endl;
	out << "============================="<< endl;
	
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
		f.frecventa[zi_rulare -1 ] = 1;

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

int main()
{
   
	Film film_nou;
	cin >> film_nou;
	cout << film_nou;

}
