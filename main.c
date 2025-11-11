#include <stdio.h>
#include <stdlib.h>

int T_NLivre[30];
char T_Titre[30][30];
int T_Nbr_exp[30];

void afficherMenuPrincipal();
void gestBiblio();
void gestEmprunts();
void stats();

void afficherMenuPrincipal()
{
    int choix;
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
        printf("|| ==> ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            gestBiblio();
            break;
        case 2:
            gestEmprunts();
            break;
        case 3:
            stats();
            break;
        default:
            break;
        }
    } while (choix != 0);
}

void gestBiblio()
{
    int choix;
    do
    {
        printf("\n");
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║          GESTION DE LA BIBLIOTHÈQUE                    ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║  1. Afficher tous les livres                           ║\n");
        printf("║  2. Ajouter un nouveau livre                           ║\n");
        printf("║  3. Supprimer un livre                                 ║\n");
        printf("║  4. Modifier le nombre d'exemplaires                   ║\n");
        printf("║  5. Rechercher un livre                                ║\n");
        printf("║  6. Afficher les livres disponibles                    ║\n");
        printf("║  0. Retour au menu principal                           ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        printf("|| == > ");
        scanf("%d", &choix);
    } while (choix != 0);
}

void gestEmprunts()
{
    int choix;
    do
    {
        printf("\n");
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║            GESTION DES EMPRUNTS                        ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║  1. Ajouter un emprunt                                 ║\n");
        printf("║  2. Consulter les emprunts d'un adhérent               ║\n");
        printf("║  3. Enregistrer un retour                              ║\n");
        printf("║  4. Afficher les emprunts en cours                     ║\n");
        printf("║  5. Afficher les livres en retard                      ║\n");
        printf("║  6. Afficher par date de retour prévue                 ║\n");
        printf("║  7. Supprimer des emprunts par période                 ║\n");
        printf("║  0. Retour au menu principal                           ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        printf("|| == > ");
        scanf("%d", &choix);
    } while (choix != 0);
}

void stats()
{
    int choix;
    do
    {
        printf("\n");
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║               STATISTIQUES                             ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║  1. Compter livres, adhérents et emprunts              ║\n");
        printf("║  2. Livres les plus empruntés                          ║\n");
        printf("║  3. Livres jamais empruntés                            ║\n");
        printf("║  4. Livres les plus empruntés (période)                ║\n");
        printf("║  5. Emprunteurs les plus fréquents                     ║\n");
        printf("║  0. Retour au menu principal                           ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        printf("|| == > ");
        scanf("%d", &choix);
    } while (choix != 0);
}

int main()
{
    afficherMenuPrincipal();
    return 0;
}