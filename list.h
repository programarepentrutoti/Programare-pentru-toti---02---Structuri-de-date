#ifndef __LIST_H__
#define __LIST_H__

#include "stdlib.h"
#include "stdio.h"

typedef struct node {
	int val;
    	struct node *next;
} node;

typedef struct list {
    int size;
    node *head;
} list;


/*
 * Indexarea incepe de la 0
 */

/*
 * Intoarce un pointer catre o lista goala
 */
list *create_list();

/*
 * Primeste ca parametrii lista in care vreau sa inserez o valoare
 * si valoarea pe care vreau sa o inserez in lista
 *
 * Valoarea este inserata automat la ultima pozitie din lista
 *
 * Nu intoarce nimic
 */
void insert_value(list *l, int v);

/*
 * Primeste ca parametrii lista l in care se cauta aparitia valorii v
 *
 * Intoarce indexul primei aparitii a valorii v in lista l
 * Intoarce -1 daca v nu se gaseste in l
 */
int find_value(list *l, int v);


/*
 * Primeste ca parametrii lista l in care se insereaza valoarea v
 * la indexul idx
 *
 * Intoarce pozitia la care a fost inserat elementul
 * Intoarce -1 daca elementul nu a putut fi inserat
 */
int insert_at(list *l, int v, int idx);

/*
 * Primeste ca parametrii lista l din care vrea sa se stearga valoarea v
 *
 * Intoarce 1 daca valoarea a fost stearsa
 * Intoarce 0 daca valoarea nu a fost stearsa
 */
int delete_value(list *l, int v);

/*
 * Primeste ca parametrii lista l din care vrea sa stearga valoarea de la
 * indexul idx
 *
 * Intoarce 1 daca elementul de la pozitia idx a fost sters
 * Intoarce 0 daca elementul de la pozitia idx nu a fost sters
 */
 int delete_index(list *l, int idx);

/*
 * Primeste ca parametrii lista l care se doreste afisata
 *
 * Nu intoarce nimic
 */
void print_list(list *l);
#endif