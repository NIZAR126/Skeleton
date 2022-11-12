#include <stdlib.h>
#include <stdio.h>
#include "fonctions_fichiers.h"

char** allouer_tab_2D(int n, int m) {
    char** tab = (char**) malloc(n * sizeof(char*));
    if (tab == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        tab[i] = (char*) malloc(m * sizeof(char));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tab[i][j] = ' ';
        }
    }
    return tab;
}

void desallouer_tab_2D(char** tab, int n) {
    for(int i = 0; i < n; i++) {
        free(tab[i]);
    }
    free(tab);
    tab = NULL;
}

void afficher_tab_2D(char** tab, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol) {
    FILE* fichier = fopen(nomFichier, "r");
    char c;
    int n = 0;
    *nbLig = 0;
    *nbCol = 0;
    if (fichier == NULL) {
        perror("Error opening file");
    } else {
        do {
            c = fgetc(fichier);
            if(c == '\n' || c == '\r' || c == EOF) {
                *nbLig += 1;
                if (*nbCol < n) {
                    *nbCol = n;
                } 
                c = fgetc(fichier);
                n = 0;
            } else {
                n += 1;
            }     
        } while (c != EOF);
    }
    fclose(fichier);
}

char** lire_fichier(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    char c;
    int nbLig = 0;
    int nbCol = 0;
    taille_fichier(nomFichier, &nbLig, &nbCol);
    char** tab = allouer_tab_2D(nbLig, nbCol);

    int abs = 0;
    int ord = 0;
    if (fichier == NULL) {
        perror("Error opening file");
    } else {
        do {
            c = fgetc(fichier);
            if(c == '\n' || c =='\r' || c == EOF) {
                ord += 1;
                abs = 0;
            } else {
                tab[ord][abs] = c;
                abs += 1;
            }
        } while (c != EOF);
    }
    fclose(fichier);
    return tab;
}

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tab[i][j] == ancien) {
                tab[i][j] = nouveau;
            }
        }
    }
    return tab;
}

void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
    FILE* fichier = fopen(nomFichier, "w");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            fputc(tab[i][j], fichier);
        }
        fputc('\n', fichier);
    }
}
