#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "noyau.h"


/*Partie concernant le tri de tableaux d'entiers par l'algorithme du tri rapide*/
/********************************************************************************/
void permut_tab(int tab[],int s,int d){
    int x=tab[s];
    tab[s] = tab[d];
    tab[d] = x;
}
int partitionner(int tab[],int s,int n){
    int p=s,i=0;
    while(i<n){
        if(tab[s+i]<tab[s]){
            p++;
            permut_tab(tab,p,i+s);
        }
        i++;
    }
    permut_tab(tab,s,p);
    return p;
}
void triRapideAmeliore(int tab[],int s,int n){
    if(n<=1)return;
    int p=partitionner(tab,s,n);
    triRapideAmeliore(tab,0,p);
    triRapideAmeliore(tab,p+1,n-p-1);
}
void init_alea(int tab[],int n){
    int i=0;
    for(i=0;i<n;i++)tab[i]=rand()%150;
}

void tri_rapide(int tableau[],int longueur)
{
    triRapideAmeliore(tableau,0,longueur);
}
/***********************************************************************/



image_t *negatif(image_t *src)
	{
	image_t *nouvelleImage = copier_image(src);
	int i;	
	if(src->mini != 0){
		for(i=0;i<(nouvelleImage->h*nouvelleImage->w);i++){nouvelleImage->buff[i] = src->nivGris - src->buff[i];}
	}else{
		for(i=0;i<(nouvelleImage->h*nouvelleImage->w);i++){nouvelleImage->buffShort[i] = src->nivGris - src->buffShort[i];}
	}
	printf("negatif ok\n");
	return nouvelleImage;
	}

image_t *rotation(image_t *src, int angle)
	{
	
	if(!(angle == 90 || angle == 180 || angle == 270)){
		fprintf(stderr,"Erreur, valeur de l'angle de la rotation non convenable\n");
		return NULL;
		}
	image_t *nouvelleImage = creer_image();
	nouvelleImage->mini = src->mini;
	nouvelleImage->nivGris = src->nivGris;
	int i=0,j=0;
	if(angle==90){
		if(nouvelleImage->mini != 0)nouvelleImage->buff = malloc(src->h*src->w*sizeof(char));
		else{nouvelleImage->buffShort = malloc(src->h*src->w*sizeof(unsigned short));}
		nouvelleImage->h = src->w;
		nouvelleImage->w = src->h;
		if(nouvelleImage->mini != 0){
			for(i=0;i<src->h;i++){
				for(j = src->w - 1;j>=0;j--){
					VAL(nouvelleImage,nouvelleImage->h - j - 1,i) = VAL(src,i,j); 
				}
			}
		}else{
			for(i=0;i<src->h;i++){
				for(j = src->w - 1;j>=0;j--){
					VALSh(nouvelleImage,nouvelleImage->h - j - 1,i) = VALSh(src,i,j); 
				}
			}
		}
	}else if(angle == 180){
		/*nouvelleImage = rotation(rotation(src,90),90);
		*/
		if(nouvelleImage->mini != 0)nouvelleImage->buff = malloc(src->h*src->w*sizeof(char));
		else nouvelleImage->buffShort = malloc(src->h*src->w*sizeof(unsigned short));
		nouvelleImage->h = src->h;
		nouvelleImage->w = src->w;
		if(nouvelleImage->mini != 0){
			for(i=0; i<src->h; i++){
				for(j=0 ; j<src->w; j++){
					VAL(nouvelleImage,src->h-i-1,src->w-j-1) = VAL(src,i,j);
					}
				}
			}
		else{
			for(i=0; i<src->h; i++){
				for(j=0 ; j<src->w; j++){
					VALSh(nouvelleImage,src->h-i-1,src->w-j-1) = VALSh(src,i,j);
					}
				}
			}
		}else if(angle == 270){
		/*nouvelleImage = rotation(rotation(rotation(src,90),90),90);*/
			if(nouvelleImage->mini != 0)nouvelleImage->buff = malloc(src->h*src->w*sizeof(char));
			else nouvelleImage->buffShort = malloc(src->h*src->w*sizeof(unsigned short));
			nouvelleImage->h = src->w;
			nouvelleImage->w = src->h;
			if(nouvelleImage->mini != 0){
				for(i=0 ; i<src->h; i++){
					for(j=0 ;j<src->w;j++){
						VAL(nouvelleImage,j,src->h-1-i) = VAL(src,i,j);
					}
				}
			}
			else{
				for(i=0 ; i<src->h; i++){
					for(j=0 ;j<src->w;j++){
						VALSh(nouvelleImage,j,src->h-1-i) = VALSh(src,i,j);
					}
				}
			}
		}
	nouvelleImage->path = strdup(src->path);
	printf("rotation ok\n");
	return nouvelleImage;
	}

image_t *modifier_lumin(image_t *src, int pourcent)
	{
		image_t *img = copier_image(src);
		int i;
		char val;
		float f = pourcent/100.;
		if(src->mini != 0){
			for(i=0;i<(src->h*src->w);i++){
				val = (unsigned char)(f * img->buff[i]);
				img->buff[i] = (val>img->nivGris)?img->nivGris:val;
			}
		}
		else{
			for(i=0;i<(src->h*src->w);i++){
				val = (unsigned short)(f * img->buffShort[i]);
				img->buffShort[i] = (val>img->nivGris)?img->nivGris:val;
			}
		}
		printf("modifier luminosite ok\n");
		return img;
	}

image_t *bruiter_image(image_t *src, int pourcent)
	{
		image_t *img = copier_image(src);
		int i;
		if(img->mini){
			for(i=0 ; i<img->h*img->w ; i++){
				if(rand()%99<pourcent){
					img->buff[i] = rand()%255;
					}
				}
		}else{
			for(i=0 ; i<img->h*img->w ; i++){
				if(rand()%99<pourcent){
					img->buffShort[i] = rand()%img->nivGris;
					}
			}
		}	
		printf("bruiter ok\n");
		return img;
	}
//Arrive ici
image_t *filtrer_median(image_t *src)
{
    image_t *img = copier_image(src);
    int i,j,tab[20],iCourant=0;
    if(img->mini){
		for(i=0 ; i<img->h; i++){
			for(j=0 ; j< img->w ; j++){
				if(i>=2 && j>=1)tab[iCourant++] = VAL(img,i-2,j-1);
				if(i>=2)tab[iCourant++] = VAL(img,i-2,j);
				if(i>=2 && j<= img->w-2)tab[iCourant++] = VAL(img,i-2,j+1);
				if(i>=1 && j >=2)tab[iCourant++] = VAL(img,i-1,j-2);
				if(i>=1 && j>=1)tab[iCourant++] = VAL(img,i-1,j-1);
				if(i>=1)tab[iCourant++] = VAL(img,i-1,j);
				if(i>=1 && j<=img->w-2)tab[iCourant++] = VAL(img,i-1,j+1);
				if(i>=1 && j<=img->w-3)tab[iCourant++] = VAL(img,i-1,j+2);
				if(j>=2)tab[iCourant++] = VAL(img,i,j-2);
				if(j>=1)tab[iCourant++] = VAL(img,i,j-1);
				if(j <= img->w-2)tab[iCourant++] = VAL(img,i,j+1);
				if(j <= img->w-3)tab[iCourant++] = VAL(img,i,j+2);
				if(i <= img->h-2 && j >= 2)tab[iCourant++] = VAL(img,i+1,j-2);
				if(i <= img->h-2 && j >= 1)tab[iCourant++] = VAL(img,i+1,j-1);
				if(i <= img->h-2)tab[iCourant++] = VAL(img,i+1,j);
				if(i <= img->h-2 && j <= img->w-2)tab[iCourant++] = VAL(img,i+1,j+1);
				if(i <= img->h-2 && j <= img->w-3)tab[iCourant++] = VAL(img,i+1,j+2);
				if(i <= img->h-3 && j >= 1)tab[iCourant++] = VAL(img,i+2,j-1);
				if(i <= img->h-3)tab[iCourant++] = VAL(img,i+2,j);
				if(i <= img->h-3 && j <= img->w-2)tab[iCourant++] = VAL(img,i+2,j+1);
				tri_rapide(tab,iCourant);
				VAL(img,i,j) = tab[iCourant/2];
				iCourant = 0;
			}
		}
	}
	else{
		for(i=0 ; i<img->h; i++){
			for(j=0 ; j< img->w ; j++){
				if(i>=2 && j>=1)tab[iCourant++] = VALSh(img,i-2,j-1);
				if(i>=2)tab[iCourant++] = VALSh(img,i-2,j);
				if(i>=2 && j<= img->w-2)tab[iCourant++] = VALSh(img,i-2,j+1);
				if(i>=1 && j >=2)tab[iCourant++] = VALSh(img,i-1,j-2);
				if(i>=1 && j>=1)tab[iCourant++] = VALSh(img,i-1,j-1);
				if(i>=1)tab[iCourant++] = VALSh(img,i-1,j);
				if(i>=1 && j<=img->w-2)tab[iCourant++] = VALSh(img,i-1,j+1);
				if(i>=1 && j<=img->w-3)tab[iCourant++] = VALSh(img,i-1,j+2);
				if(j>=2)tab[iCourant++] = VALSh(img,i,j-2);
				if(j>=1)tab[iCourant++] = VALSh(img,i,j-1);
				if(j <= img->w-2)tab[iCourant++] = VALSh(img,i,j+1);
				if(j <= img->w-3)tab[iCourant++] = VALSh(img,i,j+2);
				if(i <= img->h-2 && j >= 2)tab[iCourant++] = VALSh(img,i+1,j-2);
				if(i <= img->h-2 && j >= 1)tab[iCourant++] = VALSh(img,i+1,j-1);
				if(i <= img->h-2)tab[iCourant++] = VALSh(img,i+1,j);
				if(i <= img->h-2 && j <= img->w-2)tab[iCourant++] = VALSh(img,i+1,j+1);
				if(i <= img->h-2 && j <= img->w-3)tab[iCourant++] = VALSh(img,i+1,j+2);
				if(i <= img->h-3 && j >= 1)tab[iCourant++] = VALSh(img,i+2,j-1);
				if(i <= img->h-3)tab[iCourant++] = VALSh(img,i+2,j);
				if(i <= img->h-3 && j <= img->w-2)tab[iCourant++] = VALSh(img,i+2,j+1);
				tri_rapide(tab,iCourant);
				VALSh(img,i,j) = tab[iCourant/2];
				iCourant = 0;
			}
			
		}
    }
    printf("filtre median ok\n");
    return img;
}

image_t *convoluer(image_t *src, noyau_t *pn)
	{
	image_t *img = creer_image();
	img->path = strdup(src->path);
    if(src->mini)img->buff = malloc(src->h*src->w*sizeof(unsigned char));
    else img->buffShort = malloc(src->h*src->w*sizeof(unsigned short));
    img->h = src->h;
    img->w = src->w;
    img->mini = src->mini;
    img->nivGris = src->nivGris;
    if(src->mini)memset(img->buff,'\0',src->h*src->w);
    else memset(img->buffShort,'\0',src->h*src->w);
    long i,j,x,y,sum=0,xx=0,yy=0,sumProd=0;
    for(i=0 ; i<pn->dim*pn->dim; i++)sum+=pn->coeffs[i];
    if(sum == 0)sum = 1;
    for(i=0 ; i<img->h ; i++){
        for(j=0 ; j<img->w ; j++){
			for(y=0 ; y < pn->dim; y++){
                for(x = 0; x< pn->dim ; x++){
                    xx = j - (pn->dim/2) + x;
                    if(xx < 0)xx = 0;
                    else if(xx >= img->w) xx = img->w - 1;
                    yy = i - (pn->dim/2) + y;
                    if(yy < 0)yy = 0;
                    if(src->mini)sumProd += VAL(src,yy,xx) * VALN(pn,y,x);
					else sumProd += VALSh(src,yy,xx) * VALN(pn,y,x);
				}
            }
            
            if(img->mini)VAL(img,i,j) =(unsigned char) (sumProd/sum);
            else VALSh(img,i,j) =(unsigned char) (sumProd/sum);
            sumProd = 0;
        }
    }
    printf("convolution ok\n");
    return img;
}
