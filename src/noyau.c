#include <stdlib.h>
#include "noyau.h"
#include <stdio.h>
#include <string.h>

#define TMP_STR_SIZE 128

noyau_t *creer_noyau(unsigned int dim)
	{
	noyau_t *x = malloc(sizeof(noyau_t));
	x->dim = dim;
	x->coeffs = malloc(sizeof(int)*dim*dim);
	return x;
	}

void detruire_noyau(noyau_t *pn)
	{
		if(pn->coeffs != NULL)free(pn->coeffs);
		free(pn);
	}

noyau_t *charger_noyau(char *nom_fichier)
	{
		FILE *f = fopen(nom_fichier,"r");
		if(f == NULL){
			fprintf(stderr,"Erreur lors de l'ouverture du fichier noyau\n");
			return NULL;
			}
		noyau_t *n;
		int d=-1;
		fscanf(f,"%d\n",&d);
		if(d == -1){
			fprintf(stderr,"Erreur lors de la lecture de la dimension, le fichier est probablement de mauvais format\n");
			return NULL;
			}
		n = creer_noyau(d);
		int i,j,iCourant = 0;
		char ligneLue[TMP_STR_SIZE],*p,*next;
		for(i=0;i<d;i++){
			memset(ligneLue,'\0',TMP_STR_SIZE);
			fgets(ligneLue,TMP_STR_SIZE,f);
			p = strdup(ligneLue);
			for(j=0;j<d;j++){						
				n->coeffs[iCourant]=strtol(p,&next,0);
				if(p==next)break;
				p = next;
				iCourant++;
			}
		}
		return n;
	}
