#include "list.h"

int main()
{
	list* l;
	l = create_list();
	/*insert_value(l, 5);
	insert_value(l, 4);
	insert_value(l, 3);
	print_list(l);
	insert_at(l, 10, 0);
	print_list(l);
	insert_at(l, 12, 2);
	print_list(l);
	insert_at(l, 13, l->size - 1);
	print_list(l);
	insert_at(l, 14, 100);
	print_list(l);
	printf("Found %d at: %d\n", 13, find_value(l, 13));
	delete_value(l, 10);
	delete_value(l, 14);
	print_list(l);
	delete_index(l, 0);
	delete_index(l, l->size - 1);
	print_list(l);
	delete_index(l, 1);
	print_list(l);
	delete_value(l, 13);
	print_list(l);
	delete_value(l, 12);
	print_list(l);*/
	return 0;
}

list *create_list()
{
	/*
	 * alocam spatiu doar pentru lista!
	 *
	 * intrucat lista este goala, head va fi NULL
	 * intrucat nu am alocat memorie pentru niciun nod inca!
	 */

	list *l = (list*)malloc(sizeof(list));
	l->size = 0;
	l->head = NULL;
	return l;
}

void insert_value(list *l, int v)
{
	/*
	 * alocam spatiu pentru noua valoarea creand un
	 * nou element de tip nod.
	 *
	 * noul nod va prima valoarea pe care dorim sa o adaugam
	 *
	 */
	node *n = (node*)malloc(sizeof(node));
	n->val = v;
	n->next = NULL;

	/*
	 * daca lista nu are niciun element, adica head pointeaza catre NULL
	 * atunci trebuie sa modificam head-ul listei
	 */
	if (l->head == NULL) {
		l->head = n;
	} else {
		/*
		 * daca lista are elemente in ea atunci ne pozitionam pe ultimul element
		 * folosind o copie a pointerului capului de lista
		 */

		node* aux;
		aux = l->head;

		/*
		 * conditia de deplasare este ca atata timp cat nodul care urmeaza
		 * (aux->next)
		 * este diferit de NULL atunci eu nu ma aflu in coada listei
		 * ultimul element va pointa intotdeauna catre NULL
		 * (aux->next == NULL)
		 */
		while (aux->next!=NULL) {
			aux = aux->next;
		}

		/*
		 * ultimul element va pointa catre noul element
		 * incrementam dimensiunea listei intrucat am adaugat un nod
		 */
		aux->next = n;
	}
	l->size++;
}

int find_value(list *l, int v)
{
	/*
	 * folosim o copie a capului de lista pentru a ne deplasa prin lista
	 * folosim un index i care incepe de la 0
	 * incepem de la 0 pentru a pastra modul de la indexare utilizat si la
	 * vectori
	 *
	 * astfel, elementul de la indexul 0, este primul element din lista,
	 * iar elementul de la size - 1, este ultimul element
	 */
	node *aux = l->head;
	int i = 0;

	/*
	 * de aceasta data schimbam conditia de deplasare
	 * dorim sa inspectam toate elementele dupa aceeasi conditie
	 *
	 * cat timp nodul nu este NULL, ne uitam sa vedem daca valoarea
	 * sa coincide cu cea pe care o cautam
	 */

	while (aux != NULL) {

		/*
		 * daca da, atunci iesim din functie intorcand valoarea indexului
		 * pe care ne aflam
		 *
		 * ATENTIE, nu intoarcem nodul propiu zis, ci doar pozitia sa
		 * in lista
		 */
		if (aux->val == v) {
			return i;
		}

		/*
		 * daca nu, atunci trecem la urmatorul nod, si incrementam si
		 * indexul
		 */
		aux = aux->next;
		i++;
	}

	/*
	 * daca ajungem in acest punct inseamna ca valoarea introdusa nu
	 * se afla nicaeri in lista
	 *
	 * De ce?
	 *
	 * while-ul de mai sus, ne asigura ca va trece prin fiecare element din lista
	 * din moment ce stim ca ultimul element are valoarea de pe next NULL
	 * inseamna ca atunci cand aux == NULL inseamna ca am parcurs intreaga
	 * lista fara a gasi valoarea v
	 *
	 * intoarcem -1, intrucat acesta clar semnaleaza o eroare in cautare, deoarece
	 * nu putem avea indici negativi
	 */
	return -1;
}

int insert_at(list *l, int v, int idx)
{
	/*
	 * ATENTIE!
	 *
	 * un aspect important al acestei functii este de a-i defini comportamentul
	 * in acest caz, alegem ca lista dupa inserare, sa contina la pozitia idx
	 * valoarea inserata, iar celelalte elemente sa fie impinse la dreapta.
	 *
	 * Exemplu:
	 *
	 * L: 1(idx = 0) 5(idx = 1) 8(idx = 2) <- insert_at(L, 13, 1)
	 * Dupa inserare:
	 * L: 1(idx = 0) 13(idx = 1) 5(idx = 2) 8(idx = 3)
	 *
	 * in momentul in care introducem un index mai mare decat size-ul listei,
	 * atunci pur si simplu vom insera valoarea la coada;
	 */

	/*
	 * Dupa ce am stabilit comportamentul dorit, incepem sa verificam
	 * conditiile de rulare
	 */

	if (idx < 0) {
		/*
		 * Daca indexul e mai mic ca 0, atunci dorim sa intoarcem cod de eroare
		 */
		printf("Index mai mic ca 0, valoarea trebuie sa fie mai mare ca 0\n");
		return -1;
	} else if (idx >= l->size) {
		/*
		 * Daca introducem un index mai mare sau egal ca dimensiunea listei,
		 * inseamna ca pur si simplu dorim sa facem o inserare simpla in coada
		 * listei, deci apelam functia normala de inserare
		 *
		 * size - 1 reprezinta intotdeauna pozitia ultimului element!
		 */
		insert_value(l, v);
		return l->size - 1;
	} else {
		/*
		 * Daca nu este inserare in coada listei, atunci alocam un nod
		 * nou, si ne deplasam pe pozitia in care trebuie inserat
		 */
		node *n = (node*)malloc(sizeof(node));
		n->val = v;
		n->next = NULL;
		l->size++;
		if (idx == 0) {
			/*
			 * Daca dorim sa inseram pe prima pozitie, adica sa modificam headul
			 * nu este nevoie sa ne deplasam si astfel facem modificarile aferente
			 *
			 * Stim ca noul nod va trebui sa se lege de headul listei
			 * asadar facem:
			 *
			 * n->next = l->head;
			 *
			 * In n->next se pune adresa de memorie a headului.
			 *
			 * Noul head al listei trebuie sa devina nodul introdus, intrucat
			 * acesta este primul element, asadar facem:
			 *
			 * l->head = n;
			 *
			 * In l->head punem adresa de memorie a lui n;
			 *
			 */
			n->next = l->head;
			l->head = n;
		} else {
			/*
			 * Daca nu trebuie sa inseram pe prima pozitie, ci undeva in corpul
			 * listei, atunci facem o copie dupa head pentru a ne deplasa prin lista
			 *
			 * Pornim cu un index i = 0 si ne deplasam prin lista cat timp acesta
			 * este diferit de idx - 1
			 *
			 * De ce?
			 *
			 * Daca ne-am situa direct pe elemntul de pozitia idx, atunci
			 * noi am pierda legatura cu ce avem in spate, asadar nu putem lega
			 * elementele din spate, de cele de dupa idx.
			 *
			 * Exemplu:
			 *
			 * .... 5(idx - 1) 10(idx) 12(idx + 1).....
			 * 		      ^
			 * Daca ne-am afla acolo cu nodul aux, atunci noi
			 * am avea informatie doar despre ce urmeaza dupa idx
			 * nu si ce se afla in spate.
			 *
			 * Cum noi dorim ca noul nod sa se afle pe idx
			 * si sa pointeze la valoarea ce se afla anterior pe idx
			 * ne pozitionam pe idx - 1
			 */
			int i = 0;
			node* aux = l->head;
			while (i != idx - 1) {
				aux = aux->next;
				i++;
			}
			/*
			 * Nodul nou va pointa catre nodul cu indexul idx
			 * Nodul din spatele nodului idx va pointa acum
			 * catre nodul nou. Astfel nu pierdem legaturile
			 * si obtine rezultatul dorit
			 */
			n->next = aux->next;
			aux->next = n;
		}
		return idx;
	}
}

int delete_value(list *l, int v)
{
	/*
	 * Daca dorim sa stergem o valoare anume avem 3 cazuri:
	 * 1. Valoarea nu exista
	 * 2. Valoarea exista si este prima pozitie
	 * 3. Valoarea se afla pe orice alta pozitie
	 */


	node *aux = l->head;
	/*
	 * Daca ne aflam in cazul 2, si anume se intampla ca valoarea
	 * sa fie chiar head-ul atunci
	 * punem in l->head adresa urmatorului element din lista
	 * eliberam memoria de la vechea adresa
	 */
	if (aux->val == v) {
		l->head = l->head->next;
		free(aux);
		aux = NULL;
		l->size--;
		return 1;
	} else {

		/*
		 * Pentru a determina daca ne aflam in cazurile 1 sau 3 atunci trebuie
		 * sa ne plimbam prin lista
		 *
		 * Cum am stabilit si mai sus, pentru a nu ne pierde legaturile din lista
		 * este nevoie sa ne situam in spatele nodului cu valoarea v
		 *
		 * Vom lega nodul in care ne situam va pointa catre nodul care urmeaza
		 * dupa cel cu valoarea v, iar lista va avea structura dorita
		 *
		 * Conditiile care ne intereseaza sunt:
		 * 1. Ce urmeaza dupa nodul nostru sa NU fie NULL
		 * (inseamna ca am ajuns in capatul listei si nu mai urmeaza nimic,
		 *  deci valoarea nu exista)
		 * 2. Ce urmeaza dupa nodul nostru sa nu fie valoarea v
		 * Daca ceea ce urmeaza este v, inseamna ca ne aflam pe pozitia dorita
		 */
		while (aux->next != NULL && aux->next->val != v) {
			aux = aux->next;
		}

		/*
		 * Daca urmatorul element este NULL atunci ne aflam in capatul listei
		 * deci niciun element nu este urmat de valoarea v, deci valoarea v nu se
		 * gaseste in lista.
		 */
		if (aux->next == NULL) {
			printf("Valoarea nu exista!\n");
			return 0;
		}

		/*
		 * Daca urmatorul element nu este NULL inseamna ca atunci l-am gasit pe v
		 * Copiam in tmp, adresa nodului cu valoarea v, iar nodul curent, il
		 * legam la nodul care urmeaza dupa nodul cu valoarea v
		 * in final eliberam memoria nodului cu valoarea v
		 */
		node* tmp = aux->next;
		aux->next = aux->next->next;
		free(tmp);
		tmp = NULL;
		l->size--;
		return 1;
	}

}

int delete_index(list *l, int idx)
{
	/*
	 * Cand stergem de pe o pozitie anume ne intereseaza ca pozitia
	 * aleasa sa fie o pozitie valida in cadrul listei
	 */

	if (idx < 0) {
		printf("Index mai mic ca 0, valoarea trebuie sa fie mai mare ca 0\n");
		return 0;
	} else if (idx >= l->size) {
		printf("Index mai mare ca %d, valoarea trebuie sa fie mai mica %d\n", l->size);
		return 0;
	} else if (idx == 0) {
		/*
		 * Daca dorim sa stergem primul element, adica headul listei
		 * atunci aplicam acelasi procedeu ca mai sus
		 */
		node *aux = l->head;
		l->head = l->head->next;
		free(aux);
		aux = NULL;
		l->size--;
		return 1;
	} else {
		/*
		 * Daca elementul pe care il stergem se afla in lista la fel,
		 * dorim sa ne deplasam in spatele lui pentru a ne putea pastra
		 * legaturile dupa stergere
		 *
		 * Ne vom deplasa folosind un index asa cum am facut-o si la inserare
		 * Pana in spatelui indexului trimis ca parametru
		 */
		int i = 0;
		node *aux = l->head;
		while (i != idx - 1) {
			aux = aux->next;
			i++;
		}
		/*
		 * Nodul il stergem asa cum l-am sters si la stergerea unei valori
		 * din cadrul listei
		 */
		node* tmp = aux->next;
		aux->next = aux->next->next;
		free(tmp);
		tmp = NULL;
		l->size--;
		return 1;
	}
}

void print_list(list *l)
{
	/*
	 * O functie simpla pentru afisarea listei
	 */
	node *aux = l->head;
	printf("Lista este:\n");
	while (aux != NULL) {
		printf("%d ", aux->val);
		aux = aux->next;
	}
	printf("\n");
}