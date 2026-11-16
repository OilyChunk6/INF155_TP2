#ifndef LECTURE_H
#define LECTURE_H

#include <stddef.h>
#include <stdio.h>

/* Auxiliaires communs aux saisies clavier et aux fichiers texte.
   Ils ne dependent d'aucun module metier. */
#define LECTURE_ERREUR (-1)
#define LECTURE_FIN 0
#define LECTURE_OK 1

/* MEMBRE C. Au premier appel, *tampon == NULL et *capacite == 0.
   Alloue 128 caracteres avec malloc; aux appels suivants, double la capacite
   avec realloc, en conservant le contenu. Retourne 1 en cas de succes,
   0 sans modifier le pointeur, la capacite ni le contenu en cas d'echec.
   capacite est l'adresse d'un size_t (type fourni par <stddef.h>).
   Ne lit aucun caractere et ne termine pas la chaine. L'appelant libere
   le tampon; lecture_ligne, fournie ci-dessous, gere ces responsabilites. */
int lecture_agrandir_tampon(char **tampon, size_t *capacite);

/* FOURNIE. Alloue une ligne sans longueur maximale arbitraire. L'appelant doit la
   liberer avec free. Accepte LF et CRLF, sans conserver la fin de ligne.
   Un EOF apres des caracteres termine une derniere ligne valide.
   En cas d'erreur ou de fin de fichier, *texte vaut NULL. */
int lecture_ligne(FILE *flux, char **texte);

/* FOURNIE. Base 10, signe facultatif, espaces autour acceptes, aucun suffixe accepte.
   Ne modifie *valeur qu'en cas de reussite. */
int lecture_entier(const char *texte, int *valeur);

#endif
