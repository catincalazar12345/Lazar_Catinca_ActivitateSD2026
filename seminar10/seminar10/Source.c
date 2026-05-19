#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

//creare structura pentru un nod dintr-un arbore binar de cautare
struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Masina info;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	Nod* nou=malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->stanga = NULL;
	nou->dreapta = NULL;
	if (*radacina == NULL) {
		*radacina = nou;
		return;
	}
	Nod* aux = radacina;
	while (aux->stanga!=NULL || aux->dreapta!=NULL) {
		if (nou->info.id < aux->info.id) {
			if (aux->stanga != NULL) {
				aux = aux->stanga;
			}
			else {
				aux->stanga = nou;
				break;
			}
		}
		else
			if (aux->dreapta != NULL) {
				aux = aux->dreapta;
			}
			else {
				aux->dreapta = nou;
				break;
			}
	}
}

void adaugaMasinaInArboreRecursiv(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->stanga = NULL;
	nou->dreapta = NULL;
	if (*radacina == NULL) {
		*radacina = nou;
		return;
	}
	//Nod* aux = radacina;
	if (masinaNoua.id < (*radacina)->info.id) {
		adaugaMasinaInArboreRecursiv(&(*radacina)->stanga, masinaNoua);
	}
	else {
		adaugaMasinaInArboreRecursiv(&(*radacina)->dreapta, masinaNoua);
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = malloc(sizeof(Nod));
	radacina = NULL;
	while (!feof(f)) {
		adaugaMasinaInArboreRecursiv(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	if (radacina == NULL) return;
	afisareMasiniDinArbore(radacina->stanga);
	afisareMasina(radacina->info);
	afisareMasiniDinArbore(radacina->dreapta);
}

void afisarePostordine(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	if (radacina == NULL) return;
	afisarePostordine(radacina->stanga);
	afisarePostordine(radacina->dreapta);
	afisareMasina(radacina->info);
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente

}

Masina getMasinaByID(/*arborele de masini*/int id) {
	Masina m;

	return m;	
}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {


	return 0;
}