/* FOURNIE - fonction main complete, a conserver. */
#include "atelier.h"
#include "fichiers.h"
#include "interface.h"
#include "simulation.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_CHEMIN 1024

int main(void)
{
    Atelier *atelier = atelier_initialiser();
    int choix;
    if (atelier == NULL) {
        puts("Impossible d'allouer l'atelier.");
        return EXIT_FAILURE;
    }

    do {
        int id;
        int priorite;
        Commande *commande;
        char nom_fichier[TAILLE_CHEMIN];

        choix = interface_selection_menu();
        /* Les preconditions du menu sont verifiees ici, comme demande. */
        if (choix >= 2 && choix <= 6 && atelier->nb_commandes == 0) {
            puts("L'atelier est vide. Ajoutez ou chargez des commandes.");
            continue;
        }
        if ((choix == 6 || choix == 8) && !atelier->simulation_valide) {
            puts("Aucun resultat valide. Executez d'abord la simulation.");
            continue;
        }

        switch (choix) {
        case 1:
            commande = interface_saisir_commande();
            if (commande != NULL) {
                if (atelier_ajouter(atelier, commande)) {
                    puts("Commande ajoutee.");
                } else {
                    commande_liberer(commande);
                    puts("Ajout refuse : identifiant deja utilise ou memoire insuffisante.");
                }
            } else {
                puts("Saisie annulee ou commande invalide.");
            }
            break;
        case 2:
            if (interface_saisir_entier("Identifiant a supprimer : ", 1, INT_MAX, &id)) {
                puts(atelier_supprimer(atelier, id)
                     ? "Commande supprimee." : "Identifiant introuvable.");
            }
            break;
        case 3:
            if (interface_saisir_entier("Identifiant a modifier : ", 1, INT_MAX, &id) &&
                interface_saisir_entier("Nouvelle priorite : ", 1, 3, &priorite)) {
                puts(atelier_modifier_priorite(atelier, id, priorite)
                     ? "Priorite enregistree." : "Modification impossible.");
            }
            break;
        case 4:
            interface_afficher_commandes(atelier);
            break;
        case 5:
            puts(simulation_executer(atelier)
                 ? "Simulation terminee."
                 : "Simulation impossible : une minute de fin depasse INT_MAX.");
            break;
        case 6:
            interface_afficher_resultats(atelier);
            break;
        case 7:
            if (interface_saisir_texte("Fichier de commandes : ", nom_fichier,
                                       sizeof nom_fichier)) {
                puts(fichiers_charger_commandes(nom_fichier, atelier)
                     ? "Chargement termine. Les anciennes commandes sont remplacees."
                     : "Echec du chargement. L'atelier est conserve integralement.");
            }
            break;
        case 8:
            if (interface_saisir_texte("Fichier de resultats : ", nom_fichier,
                                       sizeof nom_fichier)) {
                puts(fichiers_sauvegarder_resultats(nom_fichier, atelier)
                     ? "Resultats enregistres."
                     : "Echec de l'enregistrement (fichier inaccessible ou incomplet).");
            }
            break;
        case 0:
            break;
        }
    } while (choix != 0);

    atelier_liberer(atelier);
    puts("Au revoir.");
    return 0;
}
