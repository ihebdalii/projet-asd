#include <stdio.h>
#include <stdlib.h>

int T_NLivre[30];
char T_Titre[30][30];
int T_Nbr_exp[30];
int choix;

void afficherMenuPrincipal()
{
    do
    {
        printf("\n");
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║     SYSTÈME DE GESTION DE BIBLIOTHÈQUE                 ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║  1. Gestion de la bibliothèque                         ║\n");
        printf("║  2. Gestion des emprunts                               ║\n");
        printf("║  3. Statistiques                                       ║\n");
        printf("║  0. Quitter                                            ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
    } while (choix != 0);
}