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
•	bilet: Bilet
Bilet:
•	codBilet: constant int
•	dataBilet: char dinamic
•	codFilm: int*
•	nrBileteEmise: static int 
•	pret: float
•	metodaPlata (card/numerar) – string
•	rand: int
•	loc: int
Sala: 
•	nrSala: constant int
•	nrLocuriSala: int*
•	nrSali: static int
•	numeSala: char*
•	tipSala – string (2d/3d, 4d) 
Rezervare:
•	idRezervare: constant
•	nrRezervari: static int
•	dataRezervarii: char*
•	listaRezervari: int* (index=idClient valoare=idFilm)
•	achitat: bool
•	idFilm: int 
Client:
•	idClient: constant int
•	nrClienti: static int
•	nume: char* 
•	nrBileteRezervate: int*(index=idClient, valoarea=nrBilete)
•	codRezervare: int
•	tipClient: regular/VIP
•	abonat: bool
