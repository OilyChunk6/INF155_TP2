#ifndef FICHIERS_H
#define FICHIERS_H

#include "atelier.h"

/* Six champs : id;description;demandeur;duree;priorite;arrivee.
   Charge des commandes allouees et transfere leurs adresses a l'atelier.
   L'adresse de l'atelier fourni reste valide apres un chargement reussi. */
int fichiers_charger_commandes(const char *nom_fichier, Atelier *atelier);
int fichiers_sauvegarder_resultats(const char *nom_fichier, const Atelier *atelier);

#endif
