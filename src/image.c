#include <stdlib.h>
#include <string.h>
#include "image.h"


image_t *creer_image(){
	image_t *ptrImg_t = (image_t *) malloc(sizeof(image_t));
	ptrImg_t->w = 0;
	ptrImg_t->h = 0;
	ptrImg_t->nivGris = 0;
	ptrImg_t->path = NULL;
	ptrImg_t->buff = NULL;
	ptrImg_t->buffShort = NULL;
	ptrImg_t->mini = 1;
	return ptrImg_t;
	}

image_t *copier_image(image_t *src){
	image_t *newImage = creer_image();
	newImage->w = src->w;
	newImage->h = src->h;
	newImage->path = strdup(src->path);
	newImage->mini = src->mini;
	newImage->nivGris = src->nivGris;
	int i;
	if(newImage->mini){
		newImage->buff = malloc(src->w*src->h*sizeof(unsigned char));
		for(i=0;i<(src->w*src->h);i++)newImage->buff[i] = src->buff[i];
	}else{
		newImage->buffShort = malloc(src->w*src->h*sizeof(unsigned short));
		for(i=0;i<(src->w*src->h);i++)newImage->buffShort[i] = src->buffShort[i];
		}
	return newImage;
	}

void detruire_image(image_t *p){
	if(p != NULL){
		if(p->path != NULL)free(p->path);
		if(p->buff != NULL)free(p->buff);
		if(p->buffShort != NULL)free(p->buffShort);
		free(p);
		}
	}
