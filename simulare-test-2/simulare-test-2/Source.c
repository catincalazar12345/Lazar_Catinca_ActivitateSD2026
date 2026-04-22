#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Pacient Pacient;
typedef struct Nod Nod;
typedef struct Coada Coada;

struct Pacient {
	int cod_pacient;
	char* nume_pacient;
	int varsta;
	float grad_urgenta;
};
struct Nod {
	Pacient info;
	Nod* next;
	Nod* prev;
};
struct Coada {
	Nod* head;
	Nod* tail;
};
void afisarePacient(Pacient p) {
	printf("\nId: %d", p.cod_pacient);
	printf("\nNume pacient: %s", p.nume_pacient);
	printf("\nVarsta: %d", p.varsta);
	printf("\nGrad urgenta: %f", p.grad_urgenta);
	printf("\n-------------------------");
}
void enqueue(Coada* c, Pacient p) {
	//update tail
	//daca coada e nula, head=p, tail ramane null
	//altfel tail->next=nou, nou->prev=tail, tail=nou
	if (c == NULL) return;
	Nod* nou = malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;
	if (c->head == NULL) {
		c->head = nou;
	}
	else {
		if (c->tail == NULL) {
			nou->prev = c->head;
			c->head->next = nou;
		}
		else {
			nou->prev = c->tail;
			c->tail->next = nou;
		}
		c->tail = nou;
	}
}

Coada citireCoadaDinVector(Pacient pacienti[], int dim) {
	Coada c;
	c.head = NULL;
	c.tail = NULL;
	for (int i = 0; i < dim; i++) {
		enqueue(&c, pacienti[i]);
	}
	return c;
}
Pacient dequeue(Coada* c) {
	Pacient p;
	if (c == NULL) return;
	if (c->head == NULL) {
		p.cod_pacient = -1;
		return p;
	}
	else {
		if (c->tail == NULL) {
			//exista doar un nod
			//free(c->head);
			c->head = NULL;
			c->tail = NULL;
		}
		else {
			Nod* aux = c->head;
			c->head = c->head->next;
			c->head->prev = NULL;
			p = aux->info;
			//free(aux);
		}
	}
	return p;
}
void afisareCoada(Coada c) {
	Nod* aux = c.head;
	while (aux) {
		afisarePacient(aux->info);
		aux = aux->next;
	}
}
void pacientiBatrani(Pacient** batrani, Coada c) {
	int cnt = 0;
	Nod* aux = c.head;
	while (aux) {
		if (aux->info.varsta > 60) {
			(*batrani)[cnt++] = aux ->info;
		}
	}
}
int main() {
	Pacient pacienti[6] = {
	{2, "Daria Pora", 20, 1.0f},
	{3, "Ioana Popescu", 14, 2.4f},
	{4, "Vasile Georgescu", 65, 4.8f},
	{5, "Elena Ionescu", 72, 3.2f},
	{6, "Andrei Radu", 30, 5.0f},
	{7, "Elena Simion", 74, 4.3f} };
	Coada c = citireCoadaDinVector(pacienti, 6);
	afisareCoada(c);
	Pacient p = dequeue(&c);
	printf("Pacientul eliminat:");
	afisarePacient(p);
	printf("\nCoada:");
	afisareCoada(c);
}