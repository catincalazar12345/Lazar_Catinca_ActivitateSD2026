#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul filme.txt
//sau va creati un alt fisier cu alte date

struct StructuraFilm {
	int id;
	int nrMinute;
	float pret;
	char* nume;
	char* numeRegizor;
	unsigned char rating;
};
typedef struct StructuraFilm Film;
typedef struct Nod Nod;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Film info;
	Nod* next;
};

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	Nod** head;
};
typedef struct HashTable HashTable;

Film citireFilmDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Film m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrMinute = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.nume = malloc(strlen(aux) + 1);
	strcpy_s(m1.nume, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeRegizor = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeRegizor, strlen(aux) + 1, aux);

	m1.rating = *strtok(NULL, sep);
	return m1;
}

void afisareFilm(Film Film) {
	printf("Id: %d\n", Film.id);
	printf("Nr. minute: %d\n", Film.nrMinute);
	printf("Pret: %.2f\n", Film.pret);
	printf("Nume: %s\n", Film.nume);
	printf("Nume regizor: %s\n", Film.numeRegizor);
	printf("Rating: %c\n\n", Film.rating);
}

void afisareListaFilme(Nod* head) {
	//afiseaza toate elemente de tip Film din lista dublu inlantuita
	//prin apelarea functiei afisareFilm()
	while (head) {
		afisareFilm(head->info);
		head = head->next;
	}
}

void adaugaFilmInLista(Nod** head, Film filmNou) {
	//adauga la final in lista primita o noua Film pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = filmNou;
	nou->next = NULL;
	Nod* p;
	if (*head == NULL) {
		*head = nou;
	}
	else {
		p = *head;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.head = malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.head[i] = NULL;
	}
	return ht;
}

int calculeazaHash(int id, int dimensiune) {
	return (id * 31) % dimensiune; //numar prim, pentru dispersie mai buna
}

void inserareFilmInTabela(HashTable* hash, Film galerie) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	int index = calculeazaHash(galerie.id, hash->dim);
	adaugaFilmInLista(&hash->head[index], galerie);
}

HashTable citireFilmeDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate filmele din fisier
	//prin apelul repetat al functiei citireFilmDinFisier()
	// aceste filme sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	
	HashTable ht=initializareHashTable(5);
	while (!feof(f)) {
		Film film = citireFilmDinFisier(f);	
		inserareFilmInTabela(&ht, film);
	}
	fclose(f);
	return ht;
}

void afisareTabelaDeFilme(HashTable ht) {
	//sunt afisate toate filmele cu evidentierea clusterelor realizate
	for (int i = 0; i < ht.dim; i++) {
		printf("\nPozitia %d", i);
		printf("\n------------------------\n");
		if (ht.head[i] == NULL) {
			printf("Nicio inregistrare.\n");
		}
		else{
			Nod* aux = ht.head[i];
			while (aux) {
				afisareFilm(aux->info);
				printf("->");
				aux = aux->next;
			}
		}
	}
}

void dezalocareTabelaDeFilme(HashTable *ht) {
	//sunt dezalocate toate filmele din tabela de dispersie
	for (int i = 0; i < ht->dim; i++) {
		if (ht->head[i] != NULL) {
			Nod* p = ht->head[i];
			Nod* next = NULL;

			while (p != NULL) {
				free(p->info.nume);
				free(p->info.numeRegizor);

				next = p->next;
				free(p);
				p = next;
			}
		}
	}
	free(ht->head);
	ht->head = NULL;
	ht->dim = 0;
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al filmelor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin filme
	
	return NULL;
}

Film getFilmDupaCheie(HashTable ht /*valoarea pentru Film cautata*/) {
	Film m;
	//cauta Film dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	return m;
}

int main() {
	
	HashTable ht = citireFilmeDinFisier("filme.txt");
	afisareTabelaDeFilme(ht);
	return 0;
}