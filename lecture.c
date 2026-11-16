#include "lecture.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

int lecture_agrandir_tampon(char **tampon, size_t *capacite)
{
    /* TODO - MEMBRE C : lecture_agrandir_tampon.
       Retirer les instructions provisoires et respecter le contrat de l'enonce. */
    (void)tampon;
    (void)capacite;
    return 0;
}

/* FOURNIE - fonction complete, a conserver. */
int lecture_ligne(FILE *flux, char **texte)
{
    char *ligne = NULL;
    size_t capacite = 0;
    size_t longueur = 0;
    int caractere;
    int lu = 0;
    int erreur = 0;
    int retour_chariot = 0;

    if (texte == NULL) {
        return LECTURE_ERREUR;
    }
    *texte = NULL;
    if (flux == NULL) {
        return LECTURE_ERREUR;
    }
    if (!lecture_agrandir_tampon(&ligne, &capacite)) {
        return LECTURE_ERREUR;
    }
    while ((caractere = fgetc(flux)) != EOF && caractere != '\n') {
        lu = 1;
        /* Un CR n'est permis qu'a la toute fin de la ligne (CRLF). */
        if (retour_chariot) {
            erreur = 1;
        }
        if (caractere == '\r') {
            retour_chariot = 1;
        } else if (caractere == '\0') {
            erreur = 1;
        } else if (!erreur) {
            if (longueur == capacite - 1) {
                if (!lecture_agrandir_tampon(&ligne, &capacite)) {
                    erreur = 1;
                }
            }
            if (!erreur) {
                ligne[longueur++] = (char)caractere;
            }
        }
    }
    ligne[longueur] = '\0';
    if (ferror(flux) || erreur || (retour_chariot && caractere == EOF)) {
        free(ligne);
        return LECTURE_ERREUR;
    }
    if (caractere == EOF && !lu) {
        free(ligne);
        return LECTURE_FIN;
    }
    *texte = ligne;
    return LECTURE_OK;
}

/* FOURNIE - fonction complete, a conserver. */
int lecture_entier(const char *texte, int *valeur)
{
    char *fin;
    long nombre;
    if (texte == NULL || valeur == NULL) {
        return 0;
    }
    errno = 0;
    nombre = strtol(texte, &fin, 10);
    if (fin == texte || errno == ERANGE || nombre < INT_MIN || nombre > INT_MAX) {
        return 0;
    }
    while (isspace((unsigned char)*fin)) {
        ++fin;
    }
    if (*fin != '\0') {
        return 0;
    }
    *valeur = (int)nombre;
    return 1;
}
