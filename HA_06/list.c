#include "list.h"
#include <stdlib.h>
#include <stdio.h>

list_t *list_init ()
{
    list_t *Liste = (list_t *) malloc(sizeof(list_t));
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
