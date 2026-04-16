#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraFilm {
	int id;
	int nrMinute;
	float pret;
	char* nume;
	char* numeRegizor;
	unsigned char rating;
};
typedef struct StructuraFilm Film;

Film citireFilmDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Film m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrMinute= atoi(strtok(NULL, sep));
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
	printf("Nr. minute : %d\n", Film.nrMinute);
	printf("Pret: %.2f\n", Film.pret);
	printf("Nume: % s\n", Film.nume);
	printf("Nume regizor: %s\n", Film.numeRegizor);
	printf("Rating: %c\n\n", Film.rating);
}

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector

//folosesc lsi pentru ca la stiva am nevoie in principiu de ultimul nod
typedef Nod Nod;

struct Nod {
	Film info;
	Film* next;
};
void pushStack(Nod** stack, Film film) {//** pentru ca trebuie sa accesez si ce e in noduri
										//am adresa primului nod, care in sine e un pointer
	Nod* nou = malloc(sizeof(Film)); //nodul pe care trb sa il pun in lista
	//nodul head trb sa pointeze acum catre nodul nou. adica fac nou sa
	//pointeze la head si apoi realoc
	nou->info = film;
	nou->next = *stack; 

	*stack = nou;//the head becomes the new node
}

Film popStack(Nod** stack) {
	//creez un film dummy pt returnat in cazul in care stiva e nula
	Film film;
	film.id = -1;
	if (*stack == NULL) {
		return film; //daca nu as face asta => segmentation fault
	}
	Nod* aux = *stack;//salvez primul pointer ca sa il sterg
	film = aux->info;//salvez in film ce am de returnat, pt ca trb sa returnez noul head
	*stack =	(*stack)->next;
	free(aux);

	return film;
}

int emptyStack(Nod* stack) {
	return !stack; //actioneaza ca un bool
}

void* citireStackeDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate Filmele din fisier
	//prin apelul repetat al functiei citireFilmDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Nod* stack = NULL;
	while (!feof(f)) {
		pushStack(&stack, citireFilmDinFisier(f));
	}
	fclose(f);
	return stack;
}

void dezalocareStivaDeFilme(Nod** stack) {
	//sunt dezalocate toate Filmele si stiva de elemente
	while (*stack != NULL) {
		Film f=popStack(stack);
	}
}

int size(Nod* stack) {
	//returneaza numarul de elemente din stiva
	if (stack == NULL) 
		return 0;
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p = stack;
	int cnt = 1;
	while (p->next) {
		cnt++;
		p = p->next;
	}
	return cnt;
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
typedef Nod Nod;
typedef Queue Queue;
struct Nod {
	Film info;
	Nod* next;
	Nod* prev;
};
struct Queue {
	Nod* head;
	Nod* tail;
};
void enqueue(Queue* queue, Film film) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = film;
	nod->next = NULL;
	nod->prev = NULL;
	//daca am coada goala
	if (queue->head==NULL && queue->tail==NULL) {
		queue->head = nod;
		queue->tail = nod;
	}
	else {
		(queue->tail)->next = nod;
		nod->prev = queue->tail;
		queue->tail = nod;
	}

}

Film dequeue(Queue* queue) {
	Film f;
	f.id = -1;
	if (queue == NULL) {
		return f;
	}
	//trebuie sa returnez head si sa asignez head urmatorului nod
	f = queue->head->info;//filmul de returnat
	if (queue->head == queue->tail) {
		free(queue->head);
		queue->head = NULL;
		queue->tail = NULL;
	}
	else {
		queue->head = queue->head->next;
		free(queue->head);
		queue->head->prev = NULL;
	}
	return f;
}

Queue citireCoadaDeFilmeDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate Filmele din fisier
	//prin apelul repetat al functiei citireFilmDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Queue queue;
	queue.start = NULL;
	queue.end = NULL;
	while (!feof(f)) {
		enqueue(&queue, citireFilmDinFisier(f));
	}
	fclose(f);
	return queue;
}

void dezalocareCoadaDeFilme(/*coada*/) {
	//sunt dezalocate toate Filmele si coada de elemente
}


//metode de procesare
Film getFilmByID(Queue* queue, int id) {
	Queue aux;
	aux.tail = NULL;
	aux.head = NULL;

	Film rezultat;
	rezultat.id = -1;

	while (queue->head != NULL) {
		Film film = dequeue(queue);

		if (film.id == id) {
			rezultat = film;

			rezultat.nume = malloc(sizeof(char) * (strlen(film.nume) + 1));
			strcpy(rezultat.nume, film.nume);

			rezultat.numeRegizor = malloc(sizeof(char) * (strlen(film.numeRegizor) + 1));
			strcpy(rezultat.numeRegizor, film.numeRegizor);
		}
		enqueue(&aux, film);
	}

	queue->head = aux.head;
	queue->tail = aux.tail;

	return rezultat;
}

float calculeazaPretTotal(Queue queue) {


}

int main() {


	return 0;
}