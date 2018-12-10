/*

 ****AUTOR:
 Joan Garcia i Tormo
 
 ****DESCRIPCIÓ DEL PROGRAMA:
 Versió casolana del mastermind: l'ordinador es pensa P dígits diferents i tenim N intents per encertar-los. Un mort és un nombre encertat a la posició on toca, i un ferit és un nombre que hi és però que no està a la posició correcta.

*/


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int buida_buffer (void);
long int possibilitats (int n, int p, int morts, int ferits);
void panic (int err, char *s);

int main (void){

	int i, j, k, n, p, d, a, intents, morts, ferits, num[1000], resp[1000];
	char c;

	srand ((unsigned) time (NULL)*getpid());

	d=1;
	i=0;
	
	printf ("\nBenvingut. Això és una versió casolana del mastermind. Dóna\'m el nombre de números que voldràs encertar, i el rang (el nombre màxim, el més petit serà el 0, i anirem amb naturals). Pensa que els nombres no es poden repetir, i que per tant el número més gran possible ha de ser més gran o igual que el nombre de números que hi ha a encertar.\n\n");

	printf ("Nombre de números a endevinar (més petit de 1000): ");
	scanf ("%d", &p);
	scanf ("%c", &c);
	if (p>999 || p<=0 || (c!=' ' && c!='\n'))
		panic (-2, "dada incorrecta");
	
	printf ("Número més gran possible (rang): ");
	scanf ("%d", &n);
	scanf ("%c", &c);
	if (n<p || (c!=' ' && c!='\n'))
		panic (-2, "dada incorrecta");
	
	printf ("Quants intents vols tenir?\n");
	scanf ("%d", &intents);
	scanf ("%c", &c);
	if (c!=' ' && c!='\n')
		panic (-2, "dada incorrecta");


	while (n>d)
		d = d * 10;

	do {
		num[i] = rand()%d;
		k=0;
		if (num[i]>n)
			k=1;
		else 
			for (j=0; j<i; j++)
				if (num[i]==num[j])
					k=1;
		if (!k)
			i++;
	} while (i<p);

	for (i=0; i<intents; i++){
		morts=0;
		ferits=0;
		do {
			printf ("\n\nTirades restants: %d\n\n", intents-i);
			printf ("Tira:\n");
			for (k=0; k<p; k++){
				scanf ("%d", &resp[k]);
				scanf ("%c",&c);
				d=0;
				if (c!= ' ' && c!= '\n' ){ 
					k=0;
					d=1;
					break;
				}	
			}
			if (!d)
				for (j=0; j<p; j++)
					for (a=0; a<p; a++)
						if (resp[j]==resp[a] && j!=a)
							k=0;
			
			
		} while (k!=p);
		for (j=0; j<p; j++){
			if (resp[j]==num[j])
				morts++;
		
		}
		
		for (j=0; j<p; j++){
			for (k=0; k<p; k++){
				if (k==j);
				else if (resp[j]==num[k])
					ferits++;
			}
		}

		printf ("%d ferits, %d morts\n", ferits, morts);

		for (k=0; k<p; k++){
			if (resp[k]<0){
				printf ("PISTA: ");
				for (k=0; k<p; k++){
					if (num[k]>n-4)
						printf ("%d ", (num[k]+3)%10);
					else 
						printf ("%d ", num [k]+3);
				}
				printf ("\n");
				break;
			}
		}

		if (morts == p){
			printf ("HAS GUANYAT!!!\n");
			exit (1);
		}
		
		if (possibilitats (n, p, morts, ferits) < 0)
			printf ("Et queden moltíssimes possibilitats\n");
		else
			printf ("Et queden %ld possibles tirades", possibilitats (n, p, morts, ferits));
	}

	printf ("T'has quedat sense intents, has perdut!!!\n");

	exit (-1);
}

int buida_buffer(void){

	char c;
	int n;

	c = '\0';

	while (c != '\n'){
		n = scanf("%c", &c);
		if (n == EOF)
		return -1;
	}
	return 0;
}

long int possibilitats (int n, int p, int morts, int ferits){ /*Suposem que sabem on estan els morts i els ferits*/
	
	int i;
	long int pos;

	pos=1;

	for (i=morts; i<p; i++, ferits--){
		if (ferits>0){
			if (p-1-i==0);
			else {
				pos = pos * (p-1-i);
			}
		}
		else
			pos = pos * (n-i);
	}

	return (pos);
}

void panic(int err, char *s){
	printf(" *** ERROR: %s\n", s);
	exit(err);
}

