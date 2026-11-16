#include "atelier.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

/* FOURNIE - fonction complete, a conserver. */
Atelier *atelier_initialiser(void)
{
    Atelier *atelier = malloc(sizeof *atelier);
    if (atelier != NULL) {
        atelier_reinitialiser(atelier);
    }
    return atelier;
}

void atelier_reinitialiser(Atelier *atelier)
{
    /* TODO - MEMBRE B : atelier_reinitialiser.
       Retirer l'instruction provisoire et respecter le contrat de l'enonce. */
    (void)atelier;
}

int atelier_rechercher(const Atelier *atelier, int id)
{
    /* TODO - MEMBRE B : atelier_rechercher.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    (void)id;
    return -1;
}

int atelier_agrandir(Atelier *atelier)
{
    /* TODO - MEMBRE B : atelier_agrandir.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    return 0;
}

int atelier_ajouter(Atelier *atelier, const Commande *commande)
{
    /* TODO - MEMBRE B : atelier_ajouter.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    (void)commande;
    return 0;
}

int atelier_supprimer(Atelier *atelier, int id)
{
    /* TODO - MEMBRE A : atelier_supprimer.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    (void)id;
    return 0;
}

int atelier_modifier_priorite(Atelier *atelier, int id, int nouvelle_priorite)
{
    /* TODO - MEMBRE C : atelier_modifier_priorite.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
    (void)id;
    (void)nouvelle_priorite;
    return 0;
}

void atelier_liberer(Atelier *atelier)
{
    /* TODO - MEMBRE C : atelier_liberer.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)atelier;
}
