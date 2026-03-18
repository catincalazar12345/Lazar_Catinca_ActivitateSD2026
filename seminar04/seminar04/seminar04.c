#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	Nod* next;
};

typedef struct Nod Nod;

//creare structura pentru un nod dintr-o lista simplu inlantuita

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

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

void afisareListaMasini(Nod* head) {
	while (head != NULL) {
		afisareMasina(head->info);
		head = head->next;
	}
}

void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //shallow copy
	nou->next = NULL;
	Nod* p = *lista;
	if ((*lista) != NULL) {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		(*lista) = nou;
	}
}

void adaugaLaInceputInLista(struct Nod* head, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	struct Nod* nodNou = (Nod*)malloc(sizeof(struct Nod));
	nodNou->info = masinaNoua;
	nodNou->next = head;
	head = nodNou;
}

void* citireListaMasiniDinFisier(const char* numeFisier) { // void* = template => returneaza orice
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(file)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareListaMasini(struct Nod** lista) {
	struct Nod* head = *lista;
	struct Nod* next = NULL;

	while (head != NULL) {
		next = head->next;
		free(head->info.model);
		free(head->info.numeSofer);
		free(head);
		head = next;
	}

	*lista = NULL;
}

float calculeazaPretMediu(struct Nod* lista) {
	float pretMediu = 0;
	int nr = 0;

	while (lista) {
		pretMediu += lista->info.pret;
		nr++;

		lista = lista->next;
	}

	if (nr)
		return pretMediu / nr;

	return pretMediu;
}


void stergeMasiniDinSeria(struct Nod** head, char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	struct Nod* curr = *head;
	struct Nod* prev = NULL;

	while (curr != NULL) {
		if (curr->info.serie == serieCautata) {
			struct Nod* deSters = curr;
			if (prev == NULL) {
				*head = curr->next;
				curr = *head;
			}
			else {
				prev->next = curr->next;
				curr = curr->next;
			}
			free(deSters->info.model);
			free(deSters->info.numeSofer);
			free(deSters);
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}

}

float calculeazaPretulMasinilorUnuiSofer(struct Nod* head, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	float pretMasina = 0.0f;
	struct Nod* aux = head;
	while (aux != NULL) {
		if (strcmp(numeSofer, aux->info.numeSofer) == 0) {
			pretMasina += aux->info.pret;
		}
		aux = aux->next;
	}

	return pretMasina;
}

int main() {
	Nod* lista = (Nod*)citireListaMasiniDinFisier("/Users/catalin/Documents/Facultate/SDD/Seminar4/masini.txt");
	// afisareListaMasini(lista);
	stergeMasiniDinSeria(&lista, 'A');
	afisareListaMasini(lista);
	return 0;
}