#include <stdio.h>
#include <string.h>
#include "structures.h"

void afficherDonnees(struct Pilote pilotes[], int lignes) {
        int colonnes = 6; // Nombre de colonnes
    int largeurs[colonnes];
	char* titres[] = {"Classement", "Nom du Pilote", "Temps 1", "Temps 2", "Temps 3", "Temps 4"};
    for (int j = 0; j < colonnes; ++j) {
        largeurs[j] = strlen(titres[j]);
    }

    for (int i = 0; i < lignes; ++i) {
        if (strlen(pilotes[i].nom) > largeurs[1]) {
            largeurs[1] = strlen(pilotes[i].nom);
        }
        for (int j = 0; j < 3; ++j) {
            int longueur = snprintf(NULL, 0, "%d", pilotes[i].tempsTour[j]);
            if (longueur > largeurs[j + 2]) {
                largeurs[j + 2] = longueur;
            }
        }
        int longueur = snprintf(NULL, 0, "%d", pilotes[i].temps);
        if (longueur > largeurs[4]) {
            largeurs[4] = longueur;
        }
    }

    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    printf("|");
    for (int j = 0; j < colonnes; ++j) {
        printf("%-*s |", largeurs[j], titres[j]);
    }
    printf("\n");

    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    for (int i = 0; i < lignes; ++i) {
        printf("|");
        printf("%-*d |", largeurs[0], i );
        printf("%-*s |", largeurs[1], pilotes[i].nom);
        for (int j = 0; j < 3; ++j) {
            printf("%-*d |", largeurs[j + 2], pilotes[i].tempsTour[j]);
        }
        printf("%-*d |", largeurs[4], pilotes[i].temps);
        printf("\n");

        if (i < lignes - 1) {
            printf("+");
            for (int j = 0; j < colonnes; ++j) {
                for (int k = 0; k < largeurs[j] + 1; ++k) {
                    printf("-");
                }
                printf("+");
            }
            printf("\n");
        }
    }

    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

void afficheCourse(struct Course course) {
    int num = course.num;
    char ville[100];
    strcpy(ville, course.ville);
    char pays[100];
    strcpy(pays, course.pays);
    char ci[200];
    strcpy(ci, course.circuit);
    char taille[10];
    strcpy(taille, course.taille);
    char gp[200];
    strcpy(gp, course.gp);
    char date[100];
    strcpy(date, course.date);
    printf("numéro course: %d\n", num);
    printf("ville course: %s\n", ville);
    printf("pays: %s\n", pays);
    printf("circuit: %s\n", ci);
    printf("taille circuit: %s\n", taille);
    printf("Grand prix: %s\n", gp);
    printf("Date: %s\n", date);
}

void affichePilote(struct Pilote pilote) {
    int num = pilote.num;
    printf("Num du Pilote: %d\n", num);
    char prenom[50];
    strcpy(prenom, pilote.prenom);
    printf("Prénom du pilote: %s\n", prenom);
    char nom[50];
    strcpy(nom, pilote.nom);
    printf("Nom du pilote: %s\n", nom);
    char team[50];
    strcpy(team, pilote.team);
    printf("Equipe du coureur: %s \n", team);
    char bday[50];
    strcpy(bday, pilote.bday);
    printf("Date de naissance du Pilote: %s\n", bday);
}

void afficheTemps(struct Pilote pilote) {
    int temps = pilote.temps;
    int num = pilote.num;
    // printf("temps du pilote:%d",temps);
    printf("Le temps du pilote num %d est de : %d \n", num, temps);
    printf("Le temps du tour 1 : %d\n",pilote.tempsTour[0]);
    printf("Le temps du tour 2 : %d\n",pilote.tempsTour[1]);
    printf("Le temps du tour 3 : %d\n",pilote.tempsTour[2]);
}
