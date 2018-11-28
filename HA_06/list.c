#include "list.h"
#include <stdlib.h>
#include <stdio.h>

list_t *list_init ()
{
    list_t *Liste = (list_t *) malloc(sizeof(list_t));
	Liste->zaehler = 0;
    return Liste;
}

list_t *list_add(list_t *liste, char String[], int length)
{
	struct list_elem *newElem  = (struct list_elem *)malloc(sizeof(struct list_elem));
	for(int i = 0; i<length; i++)
	{
		(newElem->Elem)[i] = String[i];
	}
	//printf("length:'%i'\tstring:'%s'\n", length, newElem->Elem);
	if(liste->last == NULL && liste->first == NULL)
	{
		liste->last = newElem;
		liste->first = newElem;
		newElem->next = newElem;
	}
	else
	{
		liste->last->next = newElem;
		liste->last = newElem;
	}
	//printf("Ausgabeliste->first->Elem = %s\n", liste->first->Elem);
	liste->zaehler++;
	return liste;
}

list_t *list_remove(list_t *liste, struct list_elem *elem) {
	struct list_elem *before = NULL;
	struct list_elem *search = list_first(liste);
	while (search != elem && search != NULL) {
		before = search;
		search = list_elem_next(search);
	}
	if (search == NULL) {
		return NULL;
	}
	if (search->next == NULL) {
		liste->last = before;
	}
	if (before != NULL) {
		before->next = search->next;
	}
	else {
		liste->first = search->next;
	}
	free(search);
	return liste;
}

struct list_elem *list_last(list_t *Liste)
{
	return Liste->last;
}

struct list_elem *list_first(list_t *Liste)
{
	return Liste->first;
}

char *list_elem_elem(struct list_elem *Element)
{
	return Element->Elem;
}

struct list_elem *list_elem_next(struct list_elem *Element)
{
	return Element->next;
}

char **list_to_array(list_t *liste) {
	char **Array = (char **) malloc(sizeof(char *) * liste->zaehler + 1);
	for (int i = 0; i < liste->zaehler; ++i) {
		*(Array+i) = list_first(liste)->Elem;
		list_remove(liste, list_first(liste));
	}
	*(Array + liste->zaehler) = NULL;
	return Array;
}
