#include <stdlib.h>
#include <stdio.h>

struct list_elem {
    struct list_elem *next;
    char Elem[1024];
};

typedef struct list {
	struct list_elem *first;
	struct list_elem *last;
    int zaehler;
} list_t;

list_t *list_init ();
list_t *list_add(list_t *Liste, char String[], int length);
list_t *list_remove(list_t *liste, struct list_elem *elem);
//struct list_elem list_elem_init(const char String[], struct list_elem *n);
struct list_elem *list_first(list_t *Liste);
struct list_elem *list_last(list_t *Liste);
char *list_elem_elem(struct list_elem *Element);
struct list_elem *list_elem_next(struct list_elem *Element);
char **list_to_array(list_t *liste);
