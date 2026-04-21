#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//liste simple
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
struct Nod {
	Masina info;
	struct Nod* next;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m;
	aux = strtok(buffer, sep);//prima linie
	m.id = atoi(aux);
	aux = strtok(NULL, sep);
	m.nrUsi = atoi(aux);
	aux = strtok(NULL, sep);
	m.pret = atof(aux);
	aux = strtok(NULL, sep);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);
	return m;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void adaugaMasinaInLista(Nod** head, Masina m) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;
	if ((*head) == NULL) {
		*head = nou; //ii asignez o adresa
		return;
	}
	/*if (*head == NULL) {
		*head = malloc(sizeof(Nod));
		(*head)->info = m;
		(*head)->next = NULL;
		return;
	}*/
		Nod* p = *head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
}

void afisareListaMasini(Nod* head) {
	Nod* p = head;
	if (head == NULL) {
		return;
	}
	while (p!=NULL) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void adaugaLaInceputInLista(Nod** head, Masina m) {
	Nod* nou = malloc(sizeof(Nod*));
	nou->info = m;
	nou->next = *head;
	*head = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	Nod* h = NULL;
	FILE* f;
	f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&h, m);
	}
	fclose(f);
}
void dezalocareListaMasini(Nod** head) {
	Nod* p = *head;
	Nod* urm = NULL;
	while (p != NULL) {
		urm = p->next;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
		p = urm;
	}
	*head = NULL;
}
//liste duble
typedef struct NodDublu NodDublu;
typedef struct Lista Lista;
struct NodDublu {
	Masina info;
	NodDublu* next;
	NodDublu* prev;
};

struct Lista {
	NodDublu* head;
	NodDublu* tail;
};

void afisareListaDublaMasini(Lista lista) {
	NodDublu* p = lista.head;
	while (p!=NULL) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaInversaMasini(Lista lista) {
	NodDublu* p = lista.tail;
	while (p != NULL) {
		afisareMasina(p->info);
		p = p->prev;
	}
}
void adaugaMasinaInListaDubla(Lista* lista, Masina m) {
	if (lista == NULL) return;
	NodDublu* nou = malloc(sizeof(NodDublu));
	nou->info = m;
	nou->next = NULL;
	nou->prev = lista->tail;
	if (lista->head != NULL) {
		if (lista->tail != NULL) {
			lista->tail->next = nou;
		}
		else {
			lista->head->next = nou;
		}
		lista->tail = nou;
	}
	else {
		lista->head = nou;
		lista->head->prev = NULL;
	}
}
Lista citireListaDublaMasiniFisier(const char* numeFisier) {
	Lista lista;
	lista.head = NULL;
	lista.tail = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInListaDubla(&lista, m);
	}
	return lista;
}
void dezalocareListaDubla(Lista* ls) {
	NodDublu* p = ls->head;
	NodDublu* urm = NULL;
	while (p != NULL) {
		urm = p->next;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
		p = urm;
	}
	ls->head = NULL;
	ls->tail = NULL;
}
int main() {

	Lista l = citireListaDublaMasiniFisier("masini.txt");
	afisareListaDublaMasini(l);
	return 0;
}