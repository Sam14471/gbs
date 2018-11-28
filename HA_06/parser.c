#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

list_t *parse (char *pfad)
{
	list_t *Liste = list_init();
	list_t *Ausgabe = (list_t *) malloc(sizeof(list_t)); // warum nicht list_init?
	bool Backslash = false;
	bool ignore = false;				//für z.B. "     " -> " " 
	int Dollar = 0;
	bool EinfacheAZ = false;
	bool DoppelteAZ = false;
	bool exit = false;
	bool leer = false;
	int abbruch = 0;
	int AnzString = 0;
	char next;					//char der aktuell behandelt wird
	int Pos = 0;					//Position des nächsten chars im String
	char Eingabe[1024];
	char String[1024];
	printf("$ ");
	fgets(Eingabe, 1024, stdin);
	sleep(1);
	for(int i = 0; i < 1024; i++)
	{
		next = Eingabe[i];
		if(i == 1023 && next != '\0')
		{
			printf("Eingabe darf eine Länge von 1023 nicht überschreiten");
			exit = true;
			return Ausgabe;
		}
		else
		{
		if(next == ' ')			//DONE
		{
			if(!EinfacheAZ && !DoppelteAZ && !Backslash)
			{
				leer = true;
				ignore = true;
			}
			Dollar = 0;
		}
		else if(next == '\n')		//DONE
		{
			next = '\0';
			Dollar = 0;
		}
		else if(next == '$')	//DONE
		{
			if(!Backslash)
			{
				Dollar = 1;
			}
			else
			{
				Dollar = 0;
			}
		}
		else if(next == '\'' && !Backslash)	//DONE
		{
			if(EinfacheAZ)
			{
				ignore = true;
				EinfacheAZ = false;
				leer = false;
			}
			else if(!DoppelteAZ)
			{
				ignore = true;
				EinfacheAZ = true;
				if(leer)
				{
					String[Pos] = '\n';
					if(String[0] != '\0' && Pos != 0)
					{
						AnzString++;
						Ausgabe = list_add(Ausgabe, String, Pos);
					}
					Pos = 0;
					//String[Pos] = '\n';
				}
				leer = false;
			}
			Dollar = 0;
		}
		else if(next == '"' && !Backslash)	//DONE
		{
			//leer = false;
			if(DoppelteAZ)
			{
				ignore = true;
				DoppelteAZ = false;
			}
			else if(!EinfacheAZ)
			{
				ignore = true;
				DoppelteAZ = true;
				if(leer)
				{
					String[Pos] = '\n';
					if(String[0] != '\0' && Pos != 0)
					{
						AnzString++;
						Ausgabe = list_add(Ausgabe, String, Pos);
					}
					Pos = 0;
				}
			}
			leer = false;
			Dollar = 0;
		}
		else if(leer)
		{
			String[Pos] = '\n';
			if(String[Pos] != '\0' && Pos != 0)
			{
				AnzString++;
				Ausgabe = list_add(Ausgabe, String, Pos);
			}
			//String[Pos] = '\n';
			Pos = 0;
			leer = false;
			ignore = false;
		}
		else if(next != '\\')	//Alles Sonstige (Also auch * oder , oder : ...)
		{
			if(Dollar != 0) // sollte nicht nur mit PWD, sondern auch mit anderen variablen funktionieren
			{
				if(Dollar == 1 && next == 'P')
				{
					Dollar = 2;
				}
				else if(Dollar == 2 && next == 'W')
				{
					Dollar = 3;
				}
				else if(Dollar == 3 && next == 'D')
				{
					Dollar = 0;
					ignore = true;		//??
					Pos = Pos-3;
					for(int i = 4; i<1024; i++)
					{
						if(pfad[i] != '\0' && Pos <= 1023)
						{
							String[Pos] = pfad[i];
							Pos++;
						}
						else
						{
							i = 1024;
						}
					}
				}
				else
				{
					Dollar = 0;
				}
			}
		}
		if(next == '\\')	//DONE
		{
			if(!Backslash)
			{
				ignore = true;
				Backslash = true;
			}
			else
			{
				Backslash = false;
			}
			Dollar = 0;
		}
		else	//DONE
		{
			Backslash = false;
		}

		if(next == '\n')	//Ein String Komplett
		{
			String[Pos] = '\0';
			AnzString++;
			//printf("%i:%s\n",AnzString, String);
			Ausgabe = list_add(Ausgabe, String, Pos);
			Pos = 0;
		}
		else if(next == '\0')	//Eingabe Komplett
		{
			i = 1024;
			String[Pos] = '\0';
			AnzString++;
			//printf("%i:%s\n",AnzString,  String);
			Ausgabe = list_add(Ausgabe, String, Pos);
		}
		else if(!ignore)
		{
			String[Pos] = next;
			Pos++;
		}
		ignore = false;
		}
	}
	return Ausgabe;
}
