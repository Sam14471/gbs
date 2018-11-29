#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

static bool Dollar = false;

list_t *AusgabeVorbereitung(list_t *Ausgabe, char *String, int Pos, bool change, char *envp[])
{
	int dollar = 0;
	bool gleich = false;
	//char Ausgabestring[1023];
	if(change)
	{
		for(int i = 0; i<Pos; i++)
		{
			if(String[i] == '$')
			{
				dollar = i+1;
			}
		}
		for(int i = 0; i<=18; i++)			//Es gibt Befehle von envp[0] bis envp[18]
		{
			//printf("envp[%i]:%s", i, envp[i]);
			for(int j = 0; j<20; j++)		//Längster Befehl ist 18 chars 
			{
				if(String[dollar+j] == envp[i][j])
				{
					gleich = true;
				}
				else if(envp[i][j] == '=' && gleich)
				{
					char Ausgabestring[1023];
					for(int p = 0; p<dollar-1 ; p++)
					{
						Ausgabestring[p] = String[p];
					}
					for(int p = dollar-1; p<200; p++)		//p<100 hab dann auf 900 erhöht ... anderer fehler ... dann auf 200 ... trotzdem wird Value abgeschnitten
					{
						if(envp[i][j+p+2-dollar] == '\0'){gleich = false;}
						if(gleich)
						{
							Ausgabestring[p] = envp[i][j+p+2-dollar];
						}
						else
						{
							Ausgabestring[p] = String[dollar+j];
						}
					}
					Ausgabe = list_add(Ausgabe, Ausgabestring, Pos);
					Dollar = false;
					return Ausgabe;
				}
				else
				{
					gleich = false;
					j = 100;
				}
			}
		}
	}
	Ausgabe = list_add(Ausgabe, String, Pos);
	Dollar = false;
	return Ausgabe;
}

list_t *parse (char *envp[])
{
<<<<<<< HEAD
	list_t *Ausgabe = (list_t *) malloc(sizeof(list_t)); // warum nicht list_init?
=======
	list_t *Ausgabe = (list_t *) malloc(sizeof(list_t));
>>>>>>> 4c3bf85648ab24c504bd355e8b033173f41db23c
	bool Backslash = false;
	bool ignore = false;			//für z.B. "     " -> " " 
	bool EinfacheAZ = false;
	bool DoppelteAZ = false;
<<<<<<< HEAD
	bool leer = false;
	int AnzString = 0;
	char next;					//char der aktuell behandelt wird
=======
	//bool exit = false;
	bool leer = false;
	char next;						//char der aktuell behandelt wird
>>>>>>> 4c3bf85648ab24c504bd355e8b033173f41db23c
	int Pos = 0;					//Position des nächsten chars im String
	char Eingabe[1024];
	char String[1024];
	printf("$ ");
	fgets(Eingabe, 1024, stdin);
	//sleep(1); //wozu?
	for(int i = 0; i < 1024; i++)
	{
		next = Eingabe[i];
		if(i == 1023 && next != '\0')
		{
			printf("Eingabe darf eine Länge von 1023 nicht überschreiten");
<<<<<<< HEAD
=======
			//exit = true;
>>>>>>> 4c3bf85648ab24c504bd355e8b033173f41db23c
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
		}
		else if(next == '\n')		//DONE
		{
			next = '\0';
		}
		else if(next == '$')	//DONE
		{
			if(!Backslash)
			{
				Dollar = true;		//wenn man "$PWD und $PWD" eingibt wird nur eines ersetzt ... int dollar statt bool übergeben ???
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
					String[Pos] = '\n';						//\n
					if(String[0] != '\0' && Pos != 0)
					{
						//AnzString++;
						Ausgabe = AusgabeVorbereitung(Ausgabe, String, Pos, Dollar, envp);
					}
					Pos = 0;
				}
				leer = false;
			}
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
					String[Pos] = '\n';				//\n
					if(String[0] != '\0' && Pos != 0)
					{
						Ausgabe = AusgabeVorbereitung(Ausgabe, String, Pos, Dollar, envp);
					}
					Pos = 0;
				}
			}
			leer = false;
		}
		else if(leer)
		{
			String[Pos] = '\n';
			if(String[0] != '\0' && Pos != 0)	//String[Pos]  ???
			{
				Ausgabe = AusgabeVorbereitung(Ausgabe, String, Pos, Dollar, envp);
			}
			Pos = 0;
			leer = false;
			ignore = false;
		}
<<<<<<< HEAD
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
=======
		
		//**********************************//
		
>>>>>>> 4c3bf85648ab24c504bd355e8b033173f41db23c
		if(next == '\\')	//DONE
		{
			if(!Backslash)
			{
				ignore = true;
				Backslash = true;
			}
			else
			{
				//ignore = true;
				Backslash = false;
			}
		}
		else	//DONE
		{
			Backslash = false;
		}


		if(next == '\n')	//Ein String Komplett
		{
			if(Pos == 0 && Eingabe[i-1] == '\\')		/*als Einagbe nur \*/
			{
				String[Pos] = '\\';
				Pos++;
			}
			String[Pos] = '\0';
			Ausgabe = AusgabeVorbereitung(Ausgabe, String, Pos, Dollar, envp);
			Pos = 0;
		}
		else if(next == '\0')	//Eingabe Komplett
		{
			if(Pos == 0 && Eingabe[i-1] == '\\')		/*als Eingabe nur \*/
			{
				String[Pos] = '\\';
				Pos++;
			}
			String[Pos] = '\0';
			return AusgabeVorbereitung(Ausgabe, String, Pos, Dollar, envp);
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
