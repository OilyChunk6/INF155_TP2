#include "interface.h"
#include "lecture.h"
#include "simulation.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FOURNIE - fonction complete, a conserver. */
int interface_saisir_entier(const char *message, int minimum, int maximum, int *valeur)
{
    int nombre;
    char *ligne = NULL;
    int statut;
    if (valeur == NULL) {
        return 0;
    }
    for (;;) {
        printf("%s", message);
        fflush(stdout);
        statut = lecture_ligne(stdin, &ligne);
        if (statut != LECTURE_OK) {
            if (statut == LECTURE_ERREUR) {
                puts("Erreur de lecture de la saisie.");
            }
            return 0;
        }
        statut = lecture_entier(ligne, &nombre);
        free(ligne);
        ligne = NULL;
        if (statut && nombre >= minimum && nombre <= maximum) {
            *valeur = nombre;
            return 1;
        }
        printf("Entrez un entier entre %d et %d.\n", minimum, maximum);
    }
}

/* FOURNIE - fonction complete, a conserver. */
int interface_saisir_texte(const char *message, char *texte, size_t capacite)
{
    char *ligne = NULL;
    size_t longueur;
    if (texte == NULL || capacite == 0) {
        return 0;
    }
    printf("%s", message);
    fflush(stdout);
    if (lecture_ligne(stdin, &ligne) != LECTURE_OK) {
        return 0;
    }
    longueur = strlen(ligne);
    if (longueur == 0 || longueur >= capacite) {
        printf("Texte attendu : de 1 a %zu octets.\n", capacite - 1);
        free(ligne);
        return 0;
    }
    memcpy(texte, ligne, longueur + 1);
    free(ligne);
    return 1;
}

/* FOURNIE - fonction complete, a conserver. */
int interface_selection_menu(void)
{
    int choix;
    puts("\n========== ATELIER D'IMPRESSION 3D ==========\n"
         "1. Ajouter une commande\n"
         "2. Supprimer une commande\n"
         "3. Modifier la priorite d'une commande\n"
         "4. Afficher les commandes\n"
         "5. Executer la simulation\n"
         "6. Afficher les resultats de la simulation\n"
         "7. Charger les commandes d'un fichier texte\n"
         "8. Enregistrer les resultats dans un fichier texte\n"
         "0. Quitter");
    if (!interface_saisir_entier("Votre choix : ", 0, 8, &choix)) {
        return 0; /* EOF : quitter proprement, sans boucle infinie. */
    }
    return choix;
}

/* FOURNIE - fonction complete, a conserver. */
Commande *interface_saisir_commande(void)
{
    int id, duree, priorite, arrivee;
    char description[TAILLE_DESCRIPTION];
    char *demandeur = NULL;
    Commande *commande;
    if (!interface_saisir_entier("Identifiant : ", 1, INT_MAX, &id) ||
        !interface_saisir_texte("Description (59 octets maximum, sans ;) : ",
                               description, sizeof description)) {
        return NULL;
    }
    printf("Nom du demandeur (sans ;) : ");
    fflush(stdout);
    if (lecture_ligne(stdin, &demandeur) != LECTURE_OK) {
        return NULL;
    }
    if (!interface_saisir_entier("Duree en minutes : ", 1, INT_MAX, &duree) ||
        !interface_saisir_entier("Priorite (1, 2 ou 3) : ", 1, 3, &priorite) ||
        !interface_saisir_entier("Minute d'arrivee : ", 0, INT_MAX, &arrivee)) {
        free(demandeur);
        return NULL;
    }
    commande = commande_initialiser(id, description, demandeur, duree, priorite, arrivee);
    free(demandeur); /* commande_initialiser a alloue sa propre chaine. */
    return commande;
}

/* FOURNIE - fonction complete, a conserver. */
void interface_afficher_commandes(const Atelier *atelier)
{
    int i;
    if (atelier == NULL || atelier->nb_commandes == 0) {
        puts("L'atelier est vide.");
        return;
    }
    puts("\nID | DESCRIPTION | DEMANDEUR | ARRIVEE | DUREE | PRIORITE");
    for (i = 0; i < atelier->nb_commandes; ++i) {
        const Commande *c = atelier->commandes[i];
        printf("%d | %s | %s | %d | %d | %d\n", c->id, c->description, c->demandeur,
               c->arrivee, c->duree, c->priorite);
    }
}

/* FOURNIE - fonction complete, a conserver. */
void interface_afficher_resultats(const Atelier *atelier)
{
    int i;
    if (atelier == NULL || !atelier->simulation_valide || atelier->nb_commandes == 0) {
        puts("Aucun resultat valide. Executez d'abord la simulation.");
        return;
    }
    puts("\n================ RESULTATS ================\n"
         "ID | DESCRIPTION | DEMANDEUR | ARR | DUREE | PRIO | DEBUT | FIN | ATTENTE");
    for (i = 0; i < atelier->nb_commandes; ++i) {
        const Commande *c = atelier->commandes[i];
        printf("%d | %s | %s | %d | %d | %d | %d | %d | %d\n", c->id,
               c->description, c->demandeur, c->arrivee, c->duree, c->priorite,
               c->debut, c->fin, c->debut - c->arrivee);
    }
    printf("Duree totale : %d min\n", simulation_duree_totale(atelier));
    printf("Temps d'attente moyen : %.2f min\n", simulation_attente_moyenne(atelier));
}
