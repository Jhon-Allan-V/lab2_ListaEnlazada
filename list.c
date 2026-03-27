#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// 1. Programe la función List* createList(), la cual retorna el puntero del tipo de dato List con sus valores inicializados en NULL.
// Recuerda reservar memoria al puntero usando malloc o calloc.

List * createList() {
    
    List * l = malloc(sizeof(List));
    if (l == NULL) exit(EXIT_FAILURE);
    
    l -> head = NULL;
    l -> tail = NULL;
    l -> current = NULL;
    
     return l;
}

// 2. Programe las funciones void * firstList(List * list) y void * nextList(List * list).
//   - La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
//   - La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.

void * firstList(List * list) {

    if (list -> head == NULL) return NULL;

    list -> current = list -> head;
    
    return list -> head -> data;

}

void * nextList(List * list) {

    if (list -> current == NULL) return NULL;
    if (list -> current -> next == NULL) return NULL;

    list -> current = list -> current -> next;
    
    return list -> current -> data;
    
}

// 3. Programe las funciones void * lastList(List * list) y void * prevList(List * list).
//   - La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
//   - La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.

void * lastList(List * list) {

    if (list -> tail == NULL) return NULL;
    list -> current = list -> tail;

    return list -> current -> data;

}

void * prevList(List * list) {
    
    if (list -> current == NULL) return NULL;
    if (list -> current -> prev == NULL) return NULL;
    list -> current = list -> current -> prev;

    return list -> current -> data;
    
}

// 4. Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.
// Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

void pushFront(List * list, void * data) {

    Node *nodo = createNode(data);

    if (list -> head == NULL){ //lista vacia.
        list -> head = nodo;
        list -> tail = nodo;
        return;
    }
    
    nodo -> next = list -> head; // lista tiene datos;
    list -> head -> prev = nodo;
    list -> head = nodo;
    
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

// 5. Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

void pushCurrent(List * list, void * data) {

    if (list -> current == NULL) return; //lista vacia.
    
    Node * nodo = createNode(data);
    
    if (list -> current == list -> tail){ // current esta al final de la lista.
        list -> tail = nodo;
        list -> current -> next = nodo;
        nodo -> prev = list -> current;
        return;
    } 

    // current esta entre datos.
    nodo -> prev = list -> current;
    nodo -> next = list -> current -> next;
    list -> current -> next = nodo;
    list -> current -> next -> prev = nodo;
    
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
// Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

void * popCurrent(List * list) {

    if (list -> current == NULL) return NULL; // no existen datos en la lista o lista vacia.
    
    void * dataCurrent = list -> current -> data; // dato del current auxiliar.
    Node * auxCurrent = list -> current;          // current auxiliar. (puntero)
    Node *prevCurrent = list -> current -> prev;  // antes de current.
    Node *nextCurrent = list -> current -> next;  // despues de current.

    if (prevCurrent == NULL && nextCurrent == NULL){ //current es el unico dato.
        list -> head = NULL;
        list -> tail = NULL;
        list -> current = NULL;
    }

    else if (list -> current == list -> head && nextCurrent != NULL){ // current es el primer dato de todos los demas.
        list -> head = nextCurrent;
        nextCurrent -> prev = NULL;
        list -> current = list -> head;
    }

    else if (list -> current == list -> tail && prevCurrent != NULL){ // current es el ultimo dato de todos los demas.
        list -> tail = prevCurrent;
        prevCurrent -> next = NULL;
        //list -> current = list -> tail;
        list -> current = NULL;
    }

    else { // current esta entre los datos.
        prevCurrent -> next = nextCurrent;
        nextCurrent -> prev = prevCurrent;
        list -> current = nextCurrent;
    }
    
    free(auxCurrent);
    
    return dataCurrent;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
