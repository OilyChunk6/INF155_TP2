#include "fichiers.h"
#include "lecture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FOURNIE - fonction complete, a conserver. */
static Commande *analyser_commande(char *ligne)
{
    char *champs[6];
    char *separateur;
    int id, duree, priorite, arrivee;
    int i;
    champs[0] = ligne;
    for (i = 0; i < 5; ++i) {
        separateur = strchr(champs[i], ';');
        if (separateur == NULL) {
            return NULL;
        }
        *separateur = '\0';
        champs[i + 1] = separateur + 1;
    }
    if (strchr(champs[5], ';') != NULL ||
        !lecture_entier(champs[0], &id) ||
        !lecture_entier(champs[3], &duree) ||
        !lecture_entier(champs[4], &priorite) ||
        !lecture_entier(champs[5], &arrivee)) {
        return NULL;
    }
    return commande_initialiser(id, champs[1], champs[2], duree, priorite, arrivee);
}

int fichiers_charger_commandes(const char *nom_fichier, Atelier *atelier)
{
    /* TODO - MEMBRE C : fichiers_charger_commandes.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)nom_fichier;
    (void)atelier;
    (void)analyser_commande; /* Auxiliaire fourni a utiliser. */
    return 0;
}

int fichiers_sauvegarder_resultats(const char *nom_fichier, const Atelier *atelier)
{
    /* TODO - MEMBRE C : fichiers_sauvegarder_resultats.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)nom_fichier;
    (void)atelier;
    return 0;
}
