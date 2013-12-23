/*Copyright (c) 2013, Hugo LEVY-FALK
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "color.h"

int live(int gauche, int cell, int droite, int regle[]); // la fonction qui fait "vivre" la cellule

int main(int argc, char* argv[])
{
	int i;// un premier buffer
	int buffer; // un second
	int nbFois; // le nombre de générations
	int nbCell; // le nombre de cellules

	int regle[8]; // la règle
	int regleIn;

	float conf; // pour récupérer la configuration de départ


	printf("zCellular\n");

	printf("Combien de cellules ? ");
	scanf("%d",&nbCell); // on renseigne le nombre de cellules
	
	printf("Combien de générations ?"); 
	scanf("%d",&nbFois); // idem pour le nombre de générations

	printf("Regle (0~255): ");
	scanf("%d",&regleIn);
	if(regleIn>255)
		return -1;
	buffer = 0;
	while(regleIn>=2)
	{
		regle[7-buffer]=regleIn%2;
		regleIn /= 2;
		buffer++;
	}
	regle[7-(buffer)] = regleIn;
	buffer ++;
	for(i=7-buffer; i>=0; i--)
		regle[i]=0;


	int *cellules = NULL; // pour mettre toutes les cellules
	int *sortie = NULL; // on écrira la nouvelle chaine de cellules dedans

	cellules = malloc(nbCell * sizeof(int)); // on donne leurs tailles aux deux tableaux
	sortie = malloc(nbCell * sizeof(int));

	printf("Configuration de départ : "); // et on les remplis
	scanf("%f",&conf);
	for(i=nbCell-1; i>=0; i--)
	{
		cellules[i] = (conf/10 - (int)(conf / 10)) * 10;
		conf = (int)(conf/10);
	}
	

	// boucle principale
	for(i=0; i<nbFois; i++) // on fait vivre le nombre de fois qu'il faut
	{
		for(buffer=0; buffer<nbCell; buffer++) // boucle de l'affichage et de l'appel à la fonction vivre
		{
			// affichage
			if(cellules[buffer]) // si la cellule est vivante, elle est rouge
			{
				couleur("41");
				couleur("31");
				printf("%d", cellules[buffer]);
				couleur("0");
			}
			else // sinon elle est blanche
			{
				couleur("47");
				printf("%d", cellules[buffer]);
				couleur("0");
			}

			//opérations
			if(buffer==0) // si c'est la première cellule, elle n'a pas de cellule à gauche
			{
				sortie[buffer]=live(0,cellules[buffer],cellules[buffer+1], regle);
			}
			else if(buffer==nbCell-1) // si c'est la dernière, elle n'a pas de cellule à droite
			{
				sortie[buffer]=live(cellules[buffer-1],cellules[buffer],0, regle);
			}
			else // sinon elle a deux voisins
			{
				sortie[buffer]=live(cellules[buffer-1], cellules[buffer], cellules[buffer+1], regle);
			}
		}

		for(buffer=0; buffer<nbCell; buffer++) // on récupère la chaine de sortie
		{
			cellules[buffer] = sortie[buffer];
		}
		printf("\n");
		
	}

	free(sortie); // on libère les deux tableaux alloués dynamiquement
	free(cellules);

	return 0;
}

int live(int gauche, int cell, int droite, int regle[]) // fonction qui fait vivre les cellules
{
	return regle[(gauche?0:4) + (cell?0:2) + (droite?0:1)] > 0;
/*	if((gauche && cell) && droite) 
	{
		if(regle[0]>0)
			return 1;
		else
			return 0;
	}
	if((gauche && cell) && !droite) 
	{
		if(regle[1]>0)
			return 1;
		else
			return 0;
	}
	if((gauche && !cell) && droite) 
	{
		if(regle[2]>0)
			return 1;
		else
			return 0;
	}
	if((gauche && !cell) && !droite) 
	{
		if(regle[3]>0)
			return 1;
		else
			return 0;
	}
	if((!gauche && cell) && droite) 
	{
		if(regle[4]>0)
			return 1;
		else
			return 0;
	}
	if((!gauche && cell) && !droite) 
	{
		if(regle[5]>0)
			return 1;
		else
			return 0;
	}
	if((!gauche && !cell) && droite) 
	{
		if(regle[6]>0)
			return 1;
		else
			return 0;
	}
	
	if((!gauche && !cell) && !droite) 
	{
		if(regle[7]>0)
			return 1;
		else
			return 0;
	}*/
}

