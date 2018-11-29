#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv [], char *envp [])
{
	//printf("%s\n", envp[18]);
	int durchlauf = 0;
	list_t *Liste = (list_t *)malloc(sizeof(list_t)); // warum nicht list_init?
	struct list_elem *current = (struct list_elem *)malloc(sizeof(struct list_elem));
	bool ende = false;
	bool ende2 = false;
	char exit[4] = "exit";
	while(!ende2)
	{
		Liste = parse(envp);
		durchlauf = 1;
		ende = false;
		current = Liste->first;
		for(int i = 0; i<4; i++) // geht auch einfacher mit strncmp()
		{
			if((Liste->first->Elem)[i] == exit[i]) 
			{
				durchlauf++;
			}
		}
		if(durchlauf == 5 && Liste->first == Liste->last)
		{
			ende2 = true;
		}
		durchlauf = 1;
		while(!ende) // was macht das?
		{
			if(current->next == NULL || current->next == current)
			{
				ende = true;
			}
			printf("%i:%s\n", durchlauf, current->Elem);
			//sleep(1);
			current = current->next;
			durchlauf++;
		}
	}
	return 0;
}
