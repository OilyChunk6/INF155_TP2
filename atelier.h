#ifndef ATELIER_H
#define ATELIER_H

#include "commande.h"

typedef struct {
    Commande **commandes; /* Tableau de pointeurs, chaque commande est allouee separement. */
    int nb_commandes;
    int capacite;
    int simulation_valide;
} Atelier;

/* FOURNIE. Alloue un atelier vide : commandes NULL, compteurs et indicateur a 0.
   Retourne NULL si l'allocation echoue. A detruire avec atelier_liberer. */
Atelier *atelier_initialiser(void);
/* MEMBRE B. Remet les quatre champs a l'etat vide, sans allocation ni liberation.
   Reserve a une structure neuve ou ne possedant plus aucune allocation.
   Ne pas l'utiliser pour vider un atelier occupe : ses allocations seraient perdues. */
void atelier_reinitialiser(Atelier *atelier);
int atelier_rechercher(const Atelier *atelier, int id);
/* MEMBRE B. Assure une place libre : capacite 4 au premier appel,
   puis doublement seulement si le tableau est plein. Retourne 1 si une
   place est disponible, 0 en cas d'echec (atelier integralement inchange).
   Ne modifie ni nb_commandes, ni les objets, ni simulation_valide. */
int atelier_agrandir(Atelier *atelier);
/* Enregistre uniquement l'adresse, sans copier ni modifier la commande.
   La commande provient de commande_initialiser et n'appartient a aucun atelier.
   Au succes, l'atelier devient proprietaire et la liberera; ne plus la liberer ailleurs.
   En cas d'echec, l'appelant en reste proprietaire et doit la liberer ou reutiliser.
   L'objet reste modifiable ensuite (simulation/priorite), malgre le const de cet appel. */
int atelier_ajouter(Atelier *atelier, const Commande *commande);
/* Detruire la commande avec commande_liberer, puis decaler les pointeurs. */
int atelier_supprimer(Atelier *atelier, int id);
int atelier_modifier_priorite(Atelier *atelier, int id, int nouvelle_priorite);
/* Appeler commande_liberer pour chaque commande, puis liberer le tableau et l'Atelier.
   Accepte NULL. Ne pas reutiliser le pointeur apres sa liberation. */
void atelier_liberer(Atelier *atelier);

#endif
