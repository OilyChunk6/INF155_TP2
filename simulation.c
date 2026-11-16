#include "simulation.h"

#include <limits.h>
#include <stddef.h>

/* FOURNIE - fonction complete, a conserver. */
static int precede(const Commande *candidate, const Commande *meilleure)
{
    if (candidate->priorite != meilleure->priorite) {
        return candidate->priorite < meilleure->priorite;
    }
    if (candidate->arrivee != meilleure->arrivee) {
        return candidate->arrivee < meilleure->arrivee;
    }
    return candidate->id < meilleure->id;
}

/* FOURNIE - fonction complete, a conserver. */
static void reinitialiser_resultats(Atelier *atelier)
{
    int i;
    atelier->simulation_valide = 0;
    for (i = 0; i < atelier->nb_commandes; ++i) {
        atelier->commandes[i]->debut = -1;
        atelier->commandes[i]->fin = -1;
    }
}

int simulation_selectionner_commande(const Atelier *atelier, int instant)
{
    /* TODO - MEMBRE A : simulation_selectionner_commande.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    (void)instant;
    (void)precede; /* Auxiliaire fourni a utiliser. */
    return -1;
}

int simulation_prochaine_arrivee(const Atelier *atelier)
{
    /* TODO - MEMBRE B : simulation_prochaine_arrivee.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    return -1;
}

int simulation_executer(Atelier *atelier)
{
    /* TODO - MEMBRE B : simulation_executer.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    (void)reinitialiser_resultats; /* Auxiliaire fourni a utiliser. */
    return 0;
}

double simulation_attente_moyenne(const Atelier *atelier)
{
    /* TODO - MEMBRE C : simulation_attente_moyenne.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    return -1.0;
}

/* FOURNIE - fonction complete, a conserver. */
int simulation_duree_totale(const Atelier *atelier)
{
    int derniere_fin = 0;
    int i;
    if (atelier == NULL || !atelier->simulation_valide ||
        atelier->nb_commandes == 0) {
        return -1;
    }
    for (i = 0; i < atelier->nb_commandes; ++i) {
        if (atelier->commandes[i]->fin > derniere_fin) {
            derniere_fin = atelier->commandes[i]->fin;
        }
    }
    return derniere_fin;
}
