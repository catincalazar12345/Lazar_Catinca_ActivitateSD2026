#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Produs Produs;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Produs {
	unsigned int cod_produs;
	int nr_categorii;
	char** lista_categorii;
	char* nume_furnizor;
	float pret_unitar;
	float discount_procentual;
};

struct Nod {
	Produs info;
	Nod* next;
};

struct HashTable {
	int dim;
	Nod** head;
};

Produs citireProdusDinFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	Produs p;
	fgets(buffer, 100, f);

	char* aux = strtok(buffer, sep);
	p.cod_produs = (unsigned int)atoi(aux);

	aux = strtok(NULL, sep);
	p.nr_categorii = (unsigned int)atoi(aux);

	aux = strtok(NULL, sep);//aici am tot vectorul
	p.lista_categorii = (char**)malloc(sizeof(char*) * p.nr_categorii);
	for (int i = 0; i < p.nr_categorii; i++) {
		char* str;
		if (i == 0) str = strtok(aux, ";");
		else str = strtok(NULL, ";");
		p.lista_categorii[i] = malloc(strlen(str) + 1);
		strcpy_s(p.lista_categorii[i], strlen(str) + 1, str);
	}

	aux = strtok(NULL, sep);
	p.nume_furnizor = _strdup(aux);

	aux = strtok(NULL, sep);
	p.pret_unitar = (float)atof(aux);

	aux = strtok(NULL, sep);
	p.discount_procentual = (float)atof(aux);

	return p;
}

void afisareProdus(Produs p) {
	printf("\nCod: %d | Furnizor: %s", p.cod_produs, p.nume_furnizor);
	printf("\nPret: %.2f | Discount: %.1f%%", p.pret_unitar, p.discount_procentual);

	printf("\nCategorii (%d): ", p.nr_categorii);
	for (int i = 0; i < p.nr_categorii; i++) {
		printf("[%s] ", p.lista_categorii[i]);
	}
	printf("\n-------------------------------");
}

int main() {
	FILE* f = fopen("parfumuri.txt", "r");
	Produs p = citireProdusDinFisier(f);
	afisareProdus(p);
}