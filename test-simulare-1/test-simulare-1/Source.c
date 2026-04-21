#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct HashTable HashTable;
struct Carte {
	unsigned int id_carte;
	char* titlu;
	char* autor;
	float pret_imprumut;
	unsigned int numar_pagini;
};

struct Nod {
	Carte info;
	Nod* next;
};

struct HashTable {
	int dim;
	Nod** head;//vectorul 
};

Carte citireCarteDinFisier(FILE* f) {
	Carte c;
	char buffer[100];
	char sep[3] = ",\n";
	//citesc in buffer, strtok buffer, adaug toate tokenurile in respectivele campuri
	fgets(buffer, 100, f);
	char* aux;

	aux = strtok(buffer, sep);
	c.id_carte = atoi(aux);

	aux = strtok(NULL, sep);
	c.titlu = malloc(strlen(aux) + 1);
	strcpy_s(c.titlu, strlen(aux)+1, aux);

	aux = strtok(NULL, sep);
	c.autor = malloc(strlen(aux) + 1);
	strcpy_s(c.autor, strlen(aux)+1, aux);

	aux = strtok(NULL, sep);
	c.pret_imprumut = atof(aux);

	aux = strtok(NULL, sep);
	c.numar_pagini = atoi(aux);

	return c;
}

void afisareCarte(Carte c) {
	printf("\nId: %d", c.id_carte);
	printf("\nTitlu: %s", c.titlu);
	printf("\nAutor: %s", c.autor);
	printf("\nPret imprumut: %f", c.pret_imprumut);
	printf("\nNr pagini: %d", c.numar_pagini);
	printf("\n----------------------------------\n");
}

int functieHash(int dim, const char* cheie) {
	unsigned long hash = 0;
	for (int i = 0; i < strlen(cheie); i++) {
		hash = hash * 31 +cheie[i];
	}
	return (int)(hash % dim);
}

HashTable initializeazaHash(int dim) {
	HashTable h;
	h.dim = dim;
	h.head = malloc(sizeof(Nod) * dim);
	for (int i = 0; i < dim; i++) {
		h.head[i] = NULL;
	}
	return h;
}

void adaugaInTabel(HashTable* h, Carte c) {
	if (h == NULL) return;
	int index = functieHash(h->dim, c.autor);//deci voi baga in h.head[index];
	Nod* nou = malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	if (h->head[index] == NULL) {
		h->head[index] = nou;
	}
	else {
		Nod* p = h->head[index];
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}

}

HashTable citireDinFisierInTabel(const char* numeFisier) {
	HashTable h = initializeazaHash(8);
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Carte c = citireCarteDinFisier(f);
		adaugaInTabel(&h, c);
	}
	fclose(f);
	return h;
}

void afisareHash(HashTable h) {
	for (int i = 0; i < h.dim; i++) {
		if (h.head[i] == NULL) {
			printf("Nu exista inregistrare la pozitia %d\n", i);
		}
		else {
			Nod* p = h.head[i];
			printf("La pozitia %d se afla:\n", i);
			while (p) {
				afisareCarte(p->info);
				p = p->next;
			}
		}
	}
}

float sumaPretPerAutor(HashTable h, const char* autor) {
	int index = functieHash(h.dim, autor);
	float sum = 0;
	if (h.head[index] == NULL) return 0;
	else {
		Nod* p = h.head[index];
		while (p) {
			sum += p->info.pret_imprumut;
		}
	}
	return sum;
}

void stergeEntry(HashTable* h, const char* cheie) {
	int index = functieHash(h->dim, cheie);
	if (h->head[index] == NULL) {
		printf("La indexul %d (autor: %s) nu exista elemente de sters.\n", index, cheie);
		return;
	}
	Nod* aux = h->head[index];
	h->head[index] = aux->next;//noul head al listei
	free(aux->info.autor);
	free(aux->info.titlu);
	free(aux);
}
void stabilesteCartiMari(HashTable h, Carte** cartiMari, int prag) {
	int cnt = 0;
	for (int i = 0; i < h.dim; i++) {
		if (h.head[i] != NULL) {
			Nod* p = h.head[i];
			while (p) {
				if (p->info.numar_pagini > prag) {
					(*cartiMari)[cnt++] = p->info;
				}
				p = p->next;
			}
		}
	}
	printf("\n\n\n Cartile sunt:\n");
	for (int i = 0; i < cnt; i++) {
		afisareCarte((*cartiMari)[i]);
	}
}

int main() {
	HashTable h = citireDinFisierInTabel("masini.txt");
	afisareHash(h);
	Carte* cartiMari = malloc(sizeof(Carte) * 10);
	stabilesteCartiMari(h, &cartiMari, 200);

}