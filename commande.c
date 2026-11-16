#include "commande.h"

#include <stdlib.h>
#include <string.h>

int commande_est_valide(const Commande *commande)
{
    /* TODO - MEMBRE A : commande_est_valide.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)commande;
    return 0;
}

Commande *commande_initialiser(int id, const char *description, const char *demandeur,
                               int duree, int priorite, int arrivee)
{
    /* TODO - MEMBRE A : commande_initialiser.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)id;
    (void)description;
    (void)demandeur;
    (void)duree;
    (void)priorite;
    (void)arrivee;
    return NULL;
}

void commande_liberer(Commande *commande)
{
    /* TODO - MEMBRE A : commande_liberer.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)commande;
}
