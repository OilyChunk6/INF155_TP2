# INF155 · TP2 — Projet de départ

Équipe de trois personnes, **17 fonctions à écrire** : cinq pour le membre A,
six pour le membre B et six pour le membre C. La charge de travail et les
dépendances guident la répartition; le nombre n'est pas un quota uniforme.

## Répartition

Indiquer les logins COGNELO et suivre l'ordre conseillé pour débloquer les autres membres.

| Membre | Login COGNELO | Nombre | Fonctions, dans l’ordre conseillé |
| --- | --- | ---: | --- |
| Le membre A | [Login COGNELO du membre A] | 5 | `commande_est_valide`, `commande_liberer`, `commande_initialiser`, `simulation_selectionner_commande`, `atelier_supprimer` |
| Le membre B | [Login COGNELO du membre B] | 6 | `atelier_reinitialiser`, `atelier_rechercher`, `atelier_agrandir`, `atelier_ajouter`, `simulation_prochaine_arrivee`, `simulation_executer` |
| Le membre C | [Login COGNELO du membre C] | 6 | `lecture_agrandir_tampon`, `atelier_liberer`, `atelier_modifier_priorite`, `simulation_attente_moyenne`, `fichiers_sauvegarder_resultats`, `fichiers_charger_commandes` |

La répartition ne suggère PAS que chaque membre est uniquement responsable de ses propres fonctions. Chaque membre devrait réviser indépendamment les fonctions des autres membres du groupe (revue par les pairs)

Le membre B commence par la remise à zéro de l'atelier, le membre C par le tampon
de lecture et le membre A par la validation puis la libération et l'initialisation
d'une commande. Les lots indiquent qui pilote l'écriture; chacun révise les fonctions
des autres et l'équipe teste l'intégration.

## Allocation, ajout et libération

```c
Commande *commande_initialiser(int id, const char *description,
                               const char *demandeur, int duree,
                               int priorite, int arrivee);
Atelier *atelier_initialiser(void); /* Fournie. */
void atelier_reinitialiser(Atelier *atelier);
int atelier_ajouter(Atelier *atelier, const Commande *commande);
void commande_liberer(Commande *commande);
void atelier_liberer(Atelier *atelier);
```

`commande_initialiser` alloue la structure et le nom, puis définit les champs selon
les paramètres; `debut` et `fin` valent -1. Elle retourne un `Commande *`, ou NULL
si les données sont invalides ou une allocation échoue. Toute allocation partielle
est libérée avant un retour NULL. Les chaînes d'entrée restent inchangées.

`atelier_initialiser`, fournie, alloue un `Atelier`, appelle `atelier_reinitialiser`
et retourne son adresse, ou NULL si le malloc échoue. `atelier_reinitialiser` remet
les quatre champs à leur état vide, sans allocation ni libération. Elle s'utilise
sur une structure neuve ou ne possédant plus d'allocation. Elle ne sert pas à vider
un atelier occupé, car ses adresses seraient perdues.

**`atelier_ajouter` enregistre seulement l'adresse reçue. La commande reste allouée.**
La fonction ne copie, ne modifie et ne libère aucune commande. L'atelier peut agrandir
son tableau de pointeurs. Le `const` concerne cet appel; l'objet alloué reste ensuite
modifiable par la simulation et la modification de priorité.

Après un ajout réussi, la commande reste utilisable dans l'atelier jusqu'à sa
suppression ou à la destruction de l'atelier. Ne pas la libérer ailleurs pendant
qu'elle est dans la liste. Après un refus, elle reste aussi allouée : l'appelant
peut réessayer ou la libérer lorsqu'il décide de l'abandonner.

`atelier_supprimer` appelle `commande_liberer`, puis décale les pointeurs.
`commande_liberer` libère le nom et la structure; NULL est accepté.
`atelier_liberer` détruit chaque commande, puis le tableau et la structure Atelier
elle-même. Les pointeurs libérés ne doivent pas être réutilisés. Ne jamais passer
l'adresse d'une variable locale à ces fonctions de destruction.

## Deux chaînes dans chaque commande

| Champ | Stockage | Règle |
| --- | --- | --- |
| `char description[TAILLE_DESCRIPTION]` | Tableau de 60 caractères dans la structure. | Au plus 59 octets utiles puis `\0`; aucun `free` séparé. |
| `char *demandeur` | Bloc indépendant alloué par `commande_initialiser`. | Allouer `strlen(demandeur) + 1` octets et copier le texte avec son `\0`. |

Les deux textes sont non vides et interdisent `;`, CR et LF. Le nom n'a pas de
limite fixe de longueur. Après l'initialisation, modifier ou libérer les chaînes
d'entrée n'affecte pas les données de la commande retournée.

## Code fourni et intégration

- `main.c` et `interface.c` : coordination, menu, saisies et affichages.
- `atelier.c` : `atelier_initialiser`, qui appelle votre `atelier_reinitialiser`.
- `simulation.c` : `precede`, `reinitialiser_resultats`, `simulation_duree_totale`.
- `fichiers.c` : `analyser_commande`, qui retourne une commande allouée ou NULL.
- `lecture.c` : `lecture_ligne`, `lecture_entier`.
- Tous les `.h` : structures, constantes et prototypes.

La saisie et le parseur fournis utilisent `commande_initialiser`. La commande
obtenue doit être ajoutée par adresse, ou libérée si elle est abandonnée après un
refus. Les tampons de lecture temporaires peuvent être libérés : la commande
possède ses propres chaînes.

Le chargement utilise un atelier temporaire alloué. En cas de réussite, échanger
les contenus des deux structures Atelier, puis détruire le temporaire contenant
les anciennes commandes. L'adresse de l'atelier de l'appelant reste ainsi valide.
En cas d'échec, détruire seulement le temporaire; l'atelier original reste intact.

## Ouvrir dans CLion

Ouvrir `Depart` dans CLion et utiliser sa configuration de projet. Les sept `.c`
et les en-têtes sont à la racine. Le programme utilise C11 et la bibliothèque
standard. Aucun Makefile ni CMakeLists.txt n'est fourni.

Les 17 corps sont marqués `TODO - MEMBRE A`, `TODO - MEMBRE B` ou `TODO - MEMBRE C`.
Conserver les signatures et les fonctions `FOURNIE`. Les instructions provisoires
permettent la compilation; compléter la remise à zéro de l'atelier et le tampon
de lecture avant de tester le menu.

## Format des fichiers

Six champs par ligne, sans en-tête :

```text
identifiant;description;demandeur;duree;priorite;arrivee
101;Porte-cles;Alice;5;3;0
```

Neuf colonnes dans l'export, avec cet en-tête :

```text
id;description;demandeur;arrivee;duree;priorite;debut;fin;attente
```

## Vérifications collectives

Utiliser le menu et les fichiers d'exemples, sans fonction de test supplémentaire
à écrire. Pour les chemins `donnees/...`, lancer le programme avec `Depart`
comme répertoire de travail dans CLion, ou saisir le chemin absolu du fichier.

| Fichier | Résultat attendu après chargement et simulation |
| --- | --- |
| `donnees/commandes.txt` | Débuts : 0, 5, 9; fins : 5, 9, 12; durée : 12; attente moyenne : 3,67. |
| `donnees/avec_inactivite.txt` | Durée : 18; attente moyenne : 2,75. |
| `donnees/croissance.txt` | 9 commandes; capacité du tableau : 16; durée : 9; attente moyenne : 4. |
| `donnees/tampon_long.txt` | Une ligne de plus de 256 caractères, avec des espaces avant l'ID : capacité du tampon 128, 256, puis 512; durée : 2; attente : 0. |
| `donnees/demandeur_long.txt` | Nom de plus de 256 octets conservé intégralement en mémoire, à l’affichage et à l’export; durée : 2; attente : 0. |
| `donnees/departages.txt` | Ordre : 40, 5, 10, 20, 70, 30, 60; durée : 32. |
| `donnees/invalide_*.txt` | Chargement refusé; commandes et résultats précédents conservés. |

L'export du premier exemple doit correspondre à `donnees/resultats_attendus.txt`.
Les résultats suivent l'ordre du tableau. Le fichier exporté contient neuf colonnes
et un en-tête; il ne se recharge pas comme un fichier de commandes.

Compléter avec les vérifications réellement réalisées :

| Scénario | Résultat attendu | Résultat observé |
| --- | --- | --- |
| [À compléter] | [À compléter] | [À compléter] |
