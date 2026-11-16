#ifndef INTERFACE_H
#define INTERFACE_H

/* Toutes les fonctions de ce module sont FOURNIES. */

#include "atelier.h"

#include <stddef.h>

int interface_selection_menu(void);
/* Retourne une commande allouee, ou NULL en cas d'echec/abandon.
   L'appelant doit la transmettre a l'atelier ou appeler commande_liberer. */
Commande *interface_saisir_commande(void);
void interface_afficher_commandes(const Atelier *atelier);
void interface_afficher_resultats(const Atelier *atelier);

/* Auxiliaires pour que main ne contienne aucune logique de saisie. */
int interface_saisir_entier(const char *message, int minimum, int maximum, int *valeur);
int interface_saisir_texte(const char *message, char *texte, size_t capacite);

#endif
