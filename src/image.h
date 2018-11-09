#ifndef IMAGE_H
#define IMAGE_H

#define VAL(img,i,j) (img)->buff[(i)*(img)->w+(j)]
#define VALSh(img,i,j) (img)->buffShort[(i)*(img)->w+(j)]

typedef struct
	{
	unsigned long w; // largeur en pixels
	unsigned long h; // hauteur en pixels
	char *path; // le chemin absolu du fichier correspondant
	unsigned char *buff; // w x h octets correspondant aux pixels
	unsigned short *buffShort;//Cas ou le niveau max de gris est > 255
	char mini;
	int nivGris;
	} image_t;

image_t *creer_image();

image_t *copier_image(image_t *src);

void detruire_image(image_t *p);
#endif
