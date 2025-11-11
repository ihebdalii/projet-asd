#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T_NLivre[100];
char T_Titre[100][50];
int T_Nbr_exp[100];
int N = 5;

void afficherMenuPrincipal();
void gestBiblio();
void gestEmprunts();
void stats();
void afficherLivres(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N);
void ajouterLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N);

// Les Livres initiaux

void initialiserLivres(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N)
{

    *N = 5;
    T_NLivre[0] = 101;
    strcpy(T_Titre[0], "Le Petit Prince");
    T_Nbr_exp[0] = 3;

    T_NLivre[1] = 102;
    strcpy(T_Titre[1], "Les Miserables");
    T_Nbr_exp[1] = 5;

    T_NLivre[2] = 103;
    strcpy(T_Titre[2], "Atomic Habits");
    T_Nbr_exp[2] = 3;

    T_NLivre[3] = 104;
    strcpy(T_Titre[3], "The Psychology of Money");
    T_Nbr_exp[3] = 7;

    T_NLivre[4] = 105;
    strcpy(T_Titre[4], "The 48 Laws Of Power");
    T_Nbr_exp[4] = 1;
}

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
        case 0:
            printf("Merci d'avoir utilisé le système !...");
            break;
        default:
            printf("Choix invalide !\n");
        }
    } while (choix != 0);
}

void ajouterLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N)
{
    int exp;
    char c;
    do
    {
        T_NLivre[*N] = 100 + (*N + 1);
        getchar();

        printf("Donnez le titre du livre : ");
        fgets(T_Titre[*N], 50, stdin);
        T_Titre[*N][strcspn(T_Titre[*N], "\n")] = '\0';

        printf("Entrez le nombre d'exemplaires : ");
        scanf("%d", &T_Nbr_exp[*N]);

        (*N)++;

        printf("Voulez-vous ajouter un autre livre ? (O/N) : ");
        scanf(" %c", &c);
    } while (c == 'O' || c == 'o');
}
void afficherLivres(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N)
{
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                   LES LIVRES DISPONIBLES               ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    for (int i = 0; i < *N; i++)
    {
        printf("║            %d . %s : %d                                \n", T_NLivre[i], T_Titre[i], T_Nbr_exp[i]);
    }
    printf("╚════════════════════════════════════════════════════════╝\n");
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
        switch (choix)
        {
        case 1:
            afficherLivres(T_NLivre, T_Titre, T_Nbr_exp, &N);
            break;
        case 2:
            ajouterLivre(T_NLivre, T_Titre, T_Nbr_exp, &N);
            break;

        default:
            break;
        }
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
    initialiserLivres(T_NLivre, T_Titre, T_Nbr_exp, &N);
    afficherMenuPrincipal();
    return 0;
}