#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraFilm {
	int id;
	int nrMinute;
	float pretBilet;
	char* denumire;
	char* regizor;
	unsigned char rating;
};
typedef struct StructuraFilm Film;

struct Nod {
	Film info;
	Nod* next;
};
typedef struct Nod Nod;


Film citireFilmDinFisier(FILE* file) {
	char buffer[100];
	char separator[3] = ',\n'; //folosesc separatorii
	fgets(buffer, 100, file);
	char* aux;
	Film f1;
	aux = strtok(buffer, separator);
	f1.id = atoi(aux);
	f1.nrMinute = atoi(strtok(NULL, separator));
	f1.pretBilet = atof(strtok(NULL, separator));
	aux = strtok(NULL, separator);
	f1.denumire = malloc(strlen(aux) + 1);
	strcpy_s(f1.denumire, strlen(aux) + 1, aux);
	aux = strtok(NULL, separator);
	f1.regizor = malloc(strlen(aux) + 1);
	strcpy_s(f1.regizor, strlen(aux) + 1, aux);
	f1.rating = *strtok(NULL, separator);//dereferentiez
	return f1;
}

void afisareFilm(Film film) {
	printf("Id: %d\n", film.id);
	printf("Durata (minute) : %d\n", film.nrMinute);
	printf("Pret bilet: %.2f\n", film.pretBilet);
	printf("Denumire: %s\n", film.denumire);
	printf("Nume regizor: %s\n", film.regizor);
	printf("Rating: %c\n\n", film.rating);
}

void afisareListaFilme(Nod* head) {//pasez pointerul la head
	while (head != NULL) {
		afisareFilm(head->info);	
		head = head->next;
	}
}

void adaugaFilmInLista(Nod** lista, Film filmNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = filmNou;
	nou->next = NULL;
	Nod* point = lista;
	if ((*lista) != NULL) {
		while (point->next != NULL) {
			point = point->next;
		}
		point->next = nou;
	}
	else {
		(*lista) = nou;
	}
}

void adaugaLaInceputInLista(Nod** lista, Film filmNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = filmNou;
	nou->next = lista;
}

void* citireListaFilmeDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");//read
	Nod* lista = NULL;
	while (!feof(file)) {
		adaugaFilmInLista(&lista, citireFilmDinFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareListaFilme(struct Nod** lista) {
	struct Nod* head = *lista;
	struct Nod* next = NULL;
	while (head != NULL) {
		next = head->next;
		free(head->info.denumire);
		free(head->info.regizor);
		free(head);
		head = next;
	}
	*lista = NULL;
}

float calculeazaPretMediu(Nod* lista) {
	float sum = 0;
	int numar = 0;
	while (lista) {
		sum += lista->info.pretBilet;
		numar++;
		lista = lista->next;
	}
	return (sum / numar);
}

void stergeFilmeDinRating(Nod** lista, char ratingCautat) {
	//retin anteriorul si curentul. daca curent este cautat, anterior.next=curent.next
	//astfel daca filmul cautat e primul, il voi verifica separat
	//daca este ultimul, nu ma afecteaza pt ca va fi retinut in curent
	Nod* anterior = *lista;
	Nod* curent = anterior->next;
	while (*lista!=NULL && (*lista)->info.rating == ratingCautat) {
		 Nod* desters= *lista;
		 *lista = (*lista)->next;
		 anterior = *lista;
		 curent = anterior->next;
		 free(desters);
	}//daca toate sunt la inceput
	if (*lista == NULL) return;
	while (curent != NULL) {
		if (curent->info.rating == ratingCautat) {
			anterior->next = curent->next;
			Nod* desters2 = curent;
			curent = curent->next;
			free(desters2);
		}
		else {
			anterior = anterior->next;
			curent = curent->next;
		}
	}
}

float calculeazaPretulFilmelorUnuiRegizor(Nod* lista, const char* numeRegizor) {
	float sum = 0;
	while (lista != NULL) {
		if (!strcmp(lista->info.denumire, numeRegizor)) sum += lista->info.pretBilet;
		lista = lista->next;
	}
	return sum;
}

int main() {


	return 0;
}