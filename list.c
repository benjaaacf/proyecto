#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *lista = (List *)malloc(sizeof(List));

  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;

  return lista;
}

void *firstList(List *list) {

  // Verificamos si el primer dato existe
  if (list->head == NULL) {
    // Si no existe, retornamos NULL
    return NULL;
  }

  // Si el primer dato de la lista existe, actualizamos el puntero current para
  // que apunte al primer nodo
  list->current = list->head;

  // Por ultimo retornamos el dato del primer nodo
  return list->head->data;
}

void *nextList(List *list) {
  // Verificamos si el dato siguiente al current existe
  if (list->current == NULL || list->current->next == NULL) {
    // Si no existe, retornamos NULL
    return NULL;
  }

  // Si el siguiente dato del current existe, actualizamos el puntero current
  // para que apunte al siguiente nodo
  list->current = list->current->next;

  // Retornamos el dato del nodo siguiente
  return list->current->data;
}

void *lastList(List *list) {

  // Verificamos si el ultimo dato de la lista existe
  if (list->tail == NULL) {
    // Si no existe, retornamos NULL
    return NULL;
  }

  // Si el ultimo dato de la lista existe, actualizamos el puntero current para
  // que apunte al ultimo nodo
  list->current = list->tail;

  // Por ultimo retornamos el dato del ultimo nodo
  return list->tail->data;
}

void *prevList(List *list) {
  // Verificamos si el dato anterior al current existe
  if (list->current == NULL || list->current->prev == NULL) {
    // Si no existe, retornamos NULL
    return NULL;
  }

  // Si el anterior dato al current existe, actualizamos el puntero current para
  // que apunte al siguiente nodo
  list->current = list->current->prev;

  // Retornamos el dato del nodo anterior
  return list->current->data;
}

void pushFront(List *list, void *data) {
  Node *nuevoNodo = createNode(data);

  if (list->head == NULL) {
    // Si no hay datos en la lista, actualizamos los nodos de la lista con el
    // nuevo nodo
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  } else {
    // Si hay datos, agregamos el nuevo nodo al principio, actualizando los
    // nodos correspondientes
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  // Verificamos si existe un puntero en current, si es nulo, salimos de la
  // funcion
  if (list->current == NULL) {
    return;
  }

  // Si existe el puntero current creamos un nuevo nodo para el dato a agregar
  Node *nuevoNodo = createNode(data);

  // Actualizamos los nodos correspondientes del nodo creado
  nuevoNodo->prev = list->current;
  nuevoNodo->next = list->current->next;

  // Verificamos si el nodo current es el ultimo de la lista
  if (list->current->next != NULL) {
    // Si no es el ultimo, actualizamos el puntero prev del siguiente nodo a
    // current
    list->current->next->prev = nuevoNodo;
  } else {
    // Si es el ultimo, actualizamos el nodo tail de la lista con el nuevo nodo
    list->tail = nuevoNodo;
  }

  // Por ultimo actualizamos el puntero next del nodo current al nuevo nodo
  list->current->next = nuevoNodo;
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) {
  // Verificamos si existe un puntero en current, si es nulo, retornamos nulo
  if (list->current == NULL) {
    return NULL;
  }

  // Creamos el nodo que sera eliminado, el cual es el nodo current
  Node *nodoEliminado = list->current;
  // Creamos una variable con el dato a eliminar para retornarlo al final
  void *datoEliminado = nodoEliminado->data;

  // Comprobamos si el nodo a eliminar es el primero de la lista
  if (nodoEliminado == list->head) {
    // Actualizamos el head al puntero next del nodo a eliminar
    list->head = nodoEliminado->next;

    // Verificamos si el head recien actualizado existe o no
    if (list->head != NULL) {
      // Si existe actualizamos el puntero prev a NULL ya que es el primer nodo
      // de la lista
      list->head->prev = NULL;
    }
  } else {
    // Si el nodo a eliminar no es el head, entonces actualizamos el puntero
    // next del nodo anterior al eliminado con el puntero al siguiente despues
    // del eliminado
    nodoEliminado->prev->next = nodoEliminado->next;
  }

  // Comprobamos si el nodo a eliminar es el ultimo de la lista
  if (nodoEliminado == list->tail) {
    // Actualizamos el tail al puntero next del nodo a eliminar
    list->tail = nodoEliminado->prev;

    // Verificamos si el tail recien actualizado existe o no
    if (list->tail != NULL) {
      // Si existe actualizamos el puntero next a NULL ya que es el ultimo nodo
      // de la lista
      list->tail->next = NULL;
    }
  } else {
    // Si el nodo a eliminar no es el tail, entonces actualizamos el puntero
    // prev del nodo siguinte al eliminado con el puntero al nodo anterior al
    // nodo eliminado
    nodoEliminado->next->prev = nodoEliminado->prev;
  }

  // Liberamos la memoria del nodo eliminado
  free(nodoEliminado);

  // Se actualiza el current para que apunte al siguiente nodo
  if (list->current != NULL) {
    list->current = list->current->next;
  }

  // Se retorna el dato del nodo eliminado
  return datoEliminado;
}

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}

void *list_get(List *list, int seleccion) {
  if (list == NULL || seleccion < 0) {
    return NULL;
  }

  Node *current = list->head;
  int currentIndex = 0;

  while (current != NULL && currentIndex < seleccion) {
    current = current->next;
    currentIndex++;
  }

  if (current == NULL) {
    return NULL; // Índice fuera de límites
  }

  return current->data;
}