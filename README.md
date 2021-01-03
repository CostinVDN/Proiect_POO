# Proiect_POO
Echipa Luiza Tudorache, Florentina Saraidaneanu, Dan Serbu si Costin Vadanescu

Clase: Film, Bilet, Sala, Program, Client 
Film: 
•	idFilm: constant
•	nume: char*
•	frecventa: int* (3x/sapt)
•	nrFilme: static int
•	gen: string (actiune, comedie, drama)
•	durata: int
* top_20: int
•	bilet: Bilet
Bilet:
•	codBilet: constant int
•	dataBilet: char dinamic
•	codFilm: int*
•	nrBileteEmise: static int 
•	pret: float
•	rand: int 
* loc: int
Sala: 
•	nrSala: constant int
•	nrLocuriSala: int*
•	nrTotalSali: static int
•	numeSala: char*
* nrRanduri: int
* nrLocuriPeRand: int
•	tipSala – string (2d/3d, 4d) 
Rezervare:
•	idRezervare: constant
•	nrRezervari: static int
•	dataRezervarii: char*
•	BileteRezervate: int* (index=idClient valoare=idFilm)
•	achitat: bool
•	idCLient: int
* idBilet: int
* nrBilete: int
Client:
•	idClient: constant int
•	nrClienti: static int
•	nume: char* 
* DateCard: int* (9 caractere)
* nrCarduri:int
* e-mail: string
