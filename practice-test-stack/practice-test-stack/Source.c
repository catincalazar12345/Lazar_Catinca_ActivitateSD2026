#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Parfum Parfum;
typedef struct Nod Nod;

struct Parfum {
	char* marca;
	float pret;
	int cantitate_ml;
	int an_lansare;
};

struct Nod {
	Parfum info;
	Nod* next;
};

Parfum citireParfumDinFisier(FILE* f) {
	Parfum p;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);

	char* aux = strtok(buffer, sep);
	p.marca = malloc(strlen(aux) + 1);
	strcpy_s(p.marca, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	p.pret = atof(aux);

	aux = strtok(NULL, sep);
	p.cantitate_ml = atoi(aux);

	aux = strtok(NULL, sep);
	p.an_lansare = atoi(aux);
	return p;
}

void afisareParfum(Parfum p) {
	printf("\nMarca: %s", p.marca);
	printf("\nPret: %5.2f", p.pret);
	printf("\Cantitate in ml: %d", p.cantitate_ml);
	printf("\Anul lansarii: %d", p.an_lansare);
	printf("\n-------------------------------");
}

void push(Nod** stack, Parfum p) { //dau head ul
	Nod* nou = malloc(sizeof(Nod));
	nou->info = p;
	nou->next = *stack;
	(*stack) = nou;
}

Nod* citireStackDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* head = NULL;
	while (!feof(f)) {
		Parfum p = citireParfumDinFisier(f);
		push(&head, p);
	}
	return head;
}

void afisareStack(Nod* stack) {
	Nod* aux = stack;
	while (aux) {
		afisareParfum(aux->info);
		aux = aux->next;
	}
}
Parfum parfumScump(Nod* stack) {
	Parfum copie;
	Nod* aux = stack;
	float mx = -1;
	while (aux) {
		if ((aux->info).pret > mx) {
			mx = (aux->info).pret;
			copie.marca = malloc(strlen((aux->info).marca) + 1);
			strcpy_s(copie.marca, strlen((aux->info).marca) + 1, (aux->info).marca);
			copie.an_lansare = (aux->info).an_lansare;
			copie.pret = (aux->info).pret;
			copie.cantitate_ml = (aux->info).cantitate_ml;
		}
		aux = aux->next;
	}
	return copie;
}
void stergeParfum(Nod** stack, int an) {
	if (stack == NULL || *stack == NULL) {
		printf("\nStiva este goala.");
		return;
	}
	Nod* aux = *stack;	
	if (aux->info.an_lansare == an) {
		*stack = aux->next;
		free(aux->info.marca);
		free(aux);
		return;
	}
	while (aux->next!=NULL) {
		Nod* urm = aux->next;
		if (urm->info.an_lansare == an) {

				aux->next = urm->next;
				urm->next = NULL;
				free(urm->info.marca);
				free(urm);
				return;
		}
		aux = aux->next;
		
	}
}
void dezalocare(Nod** stack) {
	Nod* aux = *stack;
	while (aux!=NULL) {
		Nod* urm = aux;
		free(aux->info.marca);
		free(aux);
		aux = urm;
	}
	*stack = NULL;
}
int main() {
	Nod* stack = citireStackDinFisier("parfumuri.txt");
	afisareStack(stack);
	//afisareParfum(parfumScump(stack));
	stergeParfum(&stack, 2015);
	printf("\n\n\n\n\n\n");
	afisareStack(stack);
}