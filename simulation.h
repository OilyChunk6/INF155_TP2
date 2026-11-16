#ifndef SIMULATION_H
#define SIMULATION_H

#include "atelier.h"

int simulation_selectionner_commande(const Atelier *atelier, int instant);
int simulation_prochaine_arrivee(const Atelier *atelier);
/* Renvoie aussi 0 si une minute de fin depasserait INT_MAX (protection supplementaire du corrige). */
int simulation_executer(Atelier *atelier);
double simulation_attente_moyenne(const Atelier *atelier);
/* FOURNIE : calcul de la fin maximale. */
int simulation_duree_totale(const Atelier *atelier);

#endif
