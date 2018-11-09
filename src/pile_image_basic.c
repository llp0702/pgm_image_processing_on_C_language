#include <stdlib.h>
#include <gtk/gtk.h>
#include "pile_image.h"
#include "image.h"


struct pile_struct{
	image_t *img;
	struct pile_struct *next;
	};
typedef struct pile_struct pile_t;

void empiler(pile_t **tet, image_t *image){
	pile_t *nouvel_element = malloc(sizeof(pile_t));
	nouvel_element->img = image;
	nouvel_element->next = NULL;
	if((*tet)==NULL){
		 (*tet)= nouvel_element;
		}
	else{
		nouvel_element->next = (*tet);
		(*tet) = nouvel_element;
		}
	}
image_t *depiler(pile_t **tete){
	if((*tete)!=NULL){
		image_t *res = (*tete)->img;
		pile_t *nTete = (*tete)->next;
		free((*tete));
		(*tete) = nTete;
		return res;
		}
	return NULL;
	}
	
pile_t *pile=NULL;
image_t *cur_image;

extern GtkWidget *pLabel_Nomf;
extern GtkWidget *pLabel_Res;
extern GtkWidget *pDA;

void pile_new_image(image_t *new_image)
	{
	char str_res[32];

	//detruire_image(cur_image);
	//cur_image = new_image;
	empiler(&pile,new_image);
	cur_image = pile->img;
	gtk_label_set_text (GTK_LABEL (pLabel_Nomf), cur_image->path);
	snprintf(str_res, 32, "%ldx%ld", cur_image->w, cur_image->h);
	gtk_label_set_text (GTK_LABEL (pLabel_Res), str_res);
	gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);
	gtk_widget_show(pDA);
	}

void pile_free_images()
	{
	/*image_t *ancienne = depiler(&pile);
	if(pile == NULL){
		gtk_label_set_text (GTK_LABEL (pLabel_Nomf), "Pas d'image chargee");
		gtk_label_set_text (GTK_LABEL (pLabel_Res), "Resolution Image");
		cur_image = NULL;
		gtk_widget_queue_draw_area(pDA, 0, 0, 0, 0);
		gtk_widget_hide(pDA);
		}else{
		char str_res[32];
		cur_image = pile->img;
		gtk_label_set_text (GTK_LABEL (pLabel_Nomf), cur_image->path);
		snprintf(str_res, 32, "%ldx%ld", cur_image->w, cur_image->h);
		gtk_label_set_text (GTK_LABEL (pLabel_Res), str_res);
		gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);	
		}
	if(ancienne != NULL){
		detruire_image(ancienne);
		}*/
	if(cur_image != NULL){
		pile_t *prec = pile,*tmp = NULL;
		if(prec != NULL){
			if(prec->img == cur_image){
				gtk_label_set_text (GTK_LABEL (pLabel_Nomf), "Pas d'image chargee");
				gtk_label_set_text (GTK_LABEL (pLabel_Res), "Resolution Image");
				cur_image = NULL;
				gtk_widget_queue_draw_area(pDA, 0, 0, 0, 0);
				gtk_widget_hide(pDA);
				detruire_image(cur_image);
				prec->next = NULL;
				prec->img = NULL;
				free(prec);
				pile = NULL;
				prec = NULL;
				}
			else{
				while(prec->next != NULL && prec->next->img != cur_image){
					prec = prec->next;
					}
				if(prec->next != NULL){
						tmp = prec->next;
						prec->next = tmp->next;
						cur_image = prec->img;
						detruire_image(tmp->img);
						tmp->img = NULL;
						tmp->next = NULL;
						free(tmp);
						tmp = NULL;
						char str_res[32];
						gtk_label_set_text (GTK_LABEL (pLabel_Nomf), cur_image->path);
						snprintf(str_res, 32, "%ldx%ld", cur_image->w, cur_image->h);
						gtk_label_set_text (GTK_LABEL (pLabel_Res), str_res);
						gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);
						gtk_widget_show(pDA);
					}
				}
			}
		}
	}

void pile_undo()
	{
	// non dispo das la version basique
	pile_t *p = pile;
	while(p->img != cur_image){
		p = p->next;
		}
	p = p->next;
	if(p != NULL){
		char str_res[32];
		cur_image = p->img;
		gtk_label_set_text (GTK_LABEL (pLabel_Nomf), cur_image->path);
		snprintf(str_res, 32, "%ldx%ld", cur_image->w, cur_image->h);
		gtk_label_set_text (GTK_LABEL (pLabel_Res), str_res);
		gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);	
		gtk_widget_show(pDA);
		}
	}

void pile_redo()
	{
	pile_t *p = pile;
	if((p != NULL) && (p->img != cur_image)){
		while(p->next->img != cur_image){
			p = p->next;
			if (p->next == NULL)break;
			}
		if(p->next != NULL){
			char str_res[32];
			cur_image = p->img;
			gtk_label_set_text (GTK_LABEL (pLabel_Nomf), cur_image->path);
			snprintf(str_res, 32, "%ldx%ld", cur_image->w, cur_image->h);
			gtk_label_set_text (GTK_LABEL (pLabel_Res), str_res);
			gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);	
			gtk_widget_show(pDA);	
			}
		}
	}
