#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#define TMP_STR_SIZE 256

image_t *charger_image_pgm(char *nom_fichier)
	{
	
	//Vérifications liées au nom du fichier (doit se terminer par .pgm)
	if(nom_fichier == NULL){
		fprintf(stderr,"Aucun nom de fichier donne en parametre\n");
		return NULL;
		}
	
	char *motDuNom = strtok(strdup(nom_fichier),".");
	char *motSuivant = strtok(NULL,".");
	if(motSuivant == NULL){
		fprintf(stderr,"Format de l'image non specifie dans le nom de fichier\n");
		return NULL;
		}
	while(motSuivant != NULL){
		motDuNom = strdup(motSuivant);
		motSuivant = strtok(NULL,".");
		}
	if(strcmp(motDuNom,"pgm")!=0){
		fprintf(stderr,"Probleme dans le nom de fichier, extension differente de .pgm\n");
		return NULL;
		}
	
	FILE *f;
	f = fopen(nom_fichier,"r");
	
	if(f == NULL){
		fprintf(stderr,"Erreur lors de l'ouverture du fichier, fichier non existant\n");
		return NULL;
		}
	
	
	
	image_t *img;
	unsigned int nb_niveaux_gris;
	char ligne_lue[TMP_STR_SIZE];
	enum format {BIN, ASCII} pgm_form;
	
	//Lire la 1ère ligne (voir si c'est P2 ou pas)
	fgets(ligne_lue,TMP_STR_SIZE,f);
	if(strncmp(ligne_lue,"P2",2) == 0){
		pgm_form = ASCII;
		}
	else if(strncmp(ligne_lue,"P5",2) == 0){
		pgm_form = BIN;
		}
	else{
		fprintf(stderr,"Erreur, car le fichier n'est ni en ascii ni en binaire : %s\n",ligne_lue);
		return NULL;
		}
	char *pc;
	do{
		pc = fgets(ligne_lue,TMP_STR_SIZE,f);
	}while(pc != NULL && ligne_lue[0] == '#');
	if(pc == NULL){
		return NULL;
		}
	img = creer_image();
	sscanf(ligne_lue,"%lu %lu\n",&(img->w),&(img->h));
	img->path = strdup(nom_fichier);
	do{
		pc = fgets(ligne_lue,TMP_STR_SIZE,f);
	}while(pc != NULL && ligne_lue[0] == '#');
	if(pc == NULL){
		return img;
		}
		
	sscanf(ligne_lue,"%u\n",&nb_niveaux_gris);
	if(nb_niveaux_gris > 255){
		img->mini = 0;
		}
	img->nivGris = nb_niveaux_gris;
	if(img->mini == 1){
		img->buff = (unsigned char *)malloc(img->w*img->h*sizeof(unsigned char));
		if(pgm_form == ASCII){
			int i=0;
			for(i = 0;i<img->w*img->h;i++){
			fscanf(f," %hhu ",&(img->buff[i]));
			}
		}else{
			fread(img->buff,sizeof(unsigned char),img->w*img->h,f);
		}
	}else{
		img->buffShort = (unsigned short *)malloc(img->w*img->h*sizeof(unsigned short));
		if(pgm_form == ASCII){
			int i=0;
			for(i = 0;i<img->w*img->h;i++){
			fscanf(f," %hu ",&(img->buffShort[i]));
			}
		}else{
			fread(img->buffShort,sizeof(unsigned char),img->w*img->h,f);
		}
	}
	fclose(f);
	printf("Lecture reussie\n");
	return img;
	}

int sauver_image_pgm(char *nom_fichier, image_t *img)
	{
	
	FILE *f = fopen(nom_fichier,"w");
	if(img == NULL){
		fprintf(stderr,"Erreur de sauvegadre, aucune image selectionnee\n");
		return 0;
		}
	if(f == NULL){
		fprintf(stderr,"Erreur lors de la creation du nouveau fichier\n");
		return 0;
		}
	fprintf(f,"P2\n%lu %lu\n%d\n",img->w,img->h,img->nivGris);
	int i=0,indiceCourant = 0;
	if(img->mini != 0){
		while(indiceCourant < (img->w*img->h)){
			for(i=0;i<69;i++){
				fprintf(f,"%d ",img->buff[indiceCourant]);
				indiceCourant++;
				if(indiceCourant >= (img->w*img->h))break;
				}
			if(indiceCourant >= (img->w*img->h))break;
			fprintf(f,"%d\n",img->buff[indiceCourant]);
			indiceCourant++;
			}
	}else{
		while(indiceCourant < (img->w*img->h)){
			for(i=0;i<69;i++){
				fprintf(f,"%d ",img->buffShort[indiceCourant]);
				indiceCourant++;
				if(indiceCourant >= (img->w*img->h))break;
				}
			if(indiceCourant >= (img->w*img->h))break;
			fprintf(f,"%d\n",img->buffShort[indiceCourant]);
			indiceCourant++;
			}
	}
	fclose(f);
	return 1;
	}
