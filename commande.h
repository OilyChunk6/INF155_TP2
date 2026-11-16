#ifndef COMMANDE_H
#define COMMANDE_H

#define TAILLE_DESCRIPTION 60

typedef struct {
    int id;
    char description[TAILLE_DESCRIPTION];
    char *demandeur; /* Chaine dynamique : copie independante dans l'atelier. */
    int duree;
    int priorite;
    int arrivee;
    int debut;
    int fin;
} Commande;

/* demandeur doit etre NULL ou pointer vers une chaine C accessible et terminee.
   NULL, chaine vide, ';', CR et LF sont refuses. Ne modifie ni ne libere rien. */
int commande_est_valide(const Commande *commande);

/* MEMBRE A. Alloue la structure et renseigne ses champs avec les valeurs recues.
   Copie description dans le tableau; alloue strlen(demandeur) + 1 octets pour le nom.
   Les chaines d'entree sont accessibles et terminees; elles restent inchangees.
   Retourne l'adresse de la nouvelle commande, ou NULL si les donnees sont invalides
   ou si une allocation echoue. Aucun bloc partiel ne subsiste en cas d'echec.
   debut et fin valent -1. La commande retournee appartient a l'appelant. */
Commande *commande_initialiser(int id, const char *description, const char *demandeur,
                               int duree, int priorite, int arrivee);

/* MEMBRE A. Libere le nom puis la structure. Accepte NULL.
   La commande doit provenir de commande_initialiser; la fonction sert aussi a
   nettoyer une initialisation partielle dont demandeur vaut NULL ou un bloc alloue.
   Ne pas lui passer l'adresse d'une variable locale. Le pointeur devient inutilisable. */
void commande_liberer(Commande *commande);

#endif
