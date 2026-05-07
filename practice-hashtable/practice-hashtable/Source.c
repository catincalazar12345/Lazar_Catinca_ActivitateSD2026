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

Produs creeazaProdus(unsigned int cod, int nrCat, const char* categorii[], const char* furnizor, float pret, float disc) {
	Produs p;
	p.cod_produs = cod;
	p.nr_categorii = nrCat;

	// Alocam vectorul de pointeri pentru categorii
	p.lista_categorii = (char**)malloc(sizeof(char*) * nrCat);
	for (int i = 0; i < nrCat; i++) {
		p.lista_categorii[i] = _strdup(categorii[i]); // Alocare + Copiere string
	}

	p.nume_furnizor = _strdup(furnizor);
	p.pret_unitar = pret;
	p.discount_procentual = disc;

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

int calculeazaHash(int dim, int cheie) {
	int index;
	cheie = (cheie >> 16) ^ cheie;
	index = cheie % dim;
	return index;
}
HashTable initializareHash(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.head =(Nod**) malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		ht.head[i] = NULL;
	}
	return ht;
}
void adaugaProdusInHash(HashTable* hash, Produs p) {
	int index = calculeazaHash(hash->dim, p.nr_categorii);
	printf("%d", index);
	Nod* nou = malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;
	nou->next = hash->head[index];
	hash->head[index] = nou;
}
HashTable preiaHashDinVector(Produs inventar[], int dimensiune) {
	HashTable ht = initializareHash(5);
	for (int i = 0; i < dimensiune; i++){
		adaugaProdusInHash(&ht, inventar[i]);
	}
	return ht;
}

void afisareHash(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		Nod* aux = ht.head[i];
		if (aux == NULL) {
			printf("\nNicio inregistrare la pozitia %d", i);
		}
		else {
			printf("\nLa pozitia %d se afla ", i);
			while (aux) {
				afisareProdus(aux->info);
				aux = aux->next;
			}
		}
		printf("\n--------------------------------------");
	}

}
void valoareStocPerCategorie(HashTable ht, int numarCateg) {
	int index = calculeazaHash(ht.dim, numarCateg);
	if (ht.head[index] == NULL) {
		printf("Nu exista stoc");
		return;
	}
	else {
		Nod* aux = ht.head[index];
		float sum = 0;
		while (aux) {
			sum += aux->info.pret_unitar;
			aux = aux->next;
		}
	}

}
int main() {
	const char* c1[] = { "IT", "Gaming" };
	const char* c2[] = { "Home", "Deco", "Garden" };
	const char* c3[] = { "Beauty" };
	const char* c4[] = { "Sport", "Outdoor" };
	const char* c5[] = { "Auto", "Accesorii" };
	Produs inventar[5];
	inventar[0] = creeazaProdus(101, 2, c1, "Logitech", 250.5, 10);
	inventar[1] = creeazaProdus(102, 3, c2, "IKEA", 890.0, 5);
	inventar[2] = creeazaProdus(103, 1, c3, "Sephora", 120.0, 15);
	inventar[3] = creeazaProdus(104, 2, c4, "Decathlon", 310.2, 0);
	inventar[4] = creeazaProdus(105, 2, c5, "Emag", 54.9, 20);
	HashTable ht = preiaHashDinVector(inventar, 5);
	afisareHash(ht);
}
