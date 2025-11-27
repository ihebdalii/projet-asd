#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define max_emprunts 7

int T_NLivre[100];
char T_Titre[100][50];
int T_Nbr_exp[100];
int N = 5;
int emprunts[100][8];
int nb_emprunts = 0;

void ClearScreen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void afficherMenuPrincipal();
void gestBiblio();
void gestEmprunts();
void stats();
// Fonctions de la gestion de la bibliothèque
void afficherLivres(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                    int *N);
void ajouterLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N);
void supprimerLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                    int *N);
void modifierExp(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N);
void rechercherLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                     int *N);
void afficherLivresDispo(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                         int *N);

// Fonctions de la gestion des emprunts
void ajoutEmprunt(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                  char T_Titre[][50], int T_Nbr_exp[], int *N);
void empruntsAdherent(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                      char T_Titre[][50], int T_Nbr_exp[], int *N);

void EnregistrerRetour(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                       char T_Titre[][50], int T_Nbr_exp[], int *N);
void afficherEmpruntsEnCours(int emprunts[][8], int *nb_emprunts,
                             char T_Titre[][50]);
void afficherLivresEnRetard(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                            char T_Titre[][50], int *N);
void afficherEmpruntsParDate(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                             char T_Titre[][50], int *N);
void supprimerEmpruntsParPeriode(int emprunts[][8], int *nb_emprunts);

// Les Livres initiaux

void initialiserLivres(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                       int *N) {

  *N = 5;
  T_NLivre[0] = 101;
  strcpy(T_Titre[0], "Le Petit Prince");
  T_Nbr_exp[0] = 1;

  T_NLivre[1] = 102;
  strcpy(T_Titre[1], "Les Miserables");
  T_Nbr_exp[1] = 1;

  T_NLivre[2] = 103;
  strcpy(T_Titre[2], "Atomic Habits");
  T_Nbr_exp[2] = 1;

  T_NLivre[3] = 104;
  strcpy(T_Titre[3], "The Psychology of Money");
  T_Nbr_exp[3] = 1;

  T_NLivre[4] = 105;
  strcpy(T_Titre[4], "The 48 Laws Of Power");
  T_Nbr_exp[4] = 1;
}

void afficherMenuPrincipal() {
  int choix;
  do {
    ClearScreen();
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("||     SYSTÈME DE GESTION DE BIBLIOTHÈQUE               ||\n");
    printf("----------------------------------------------------------\n");
    printf("||  1. Gestion de la bibliothèque                       ||\n");
    printf("||  2. Gestion des emprunts                             ||\n");
    printf("||  3. Statistiques                                     ||\n");
    printf("||  0. Quitter                                          ||\n");
    printf("----------------------------------------------------------\n");
    printf("|| ==> ");
    scanf("%d", &choix);
    switch (choix) {
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

void ajouterLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N) {
  ClearScreen();
  int exp;
  char c;
  do {
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
void afficherLivres(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                    int *N) {
  ClearScreen();
  printf("----------------------------------------------------------\n");
  printf("||                LES LIVRES DISPONIBLES                ||\n");
  printf("----------------------------------------------------------\n");
  for (int i = 0; i < *N; i++) {
    printf("||            %d . %s : %d                                \n",
           T_NLivre[i], T_Titre[i], T_Nbr_exp[i]);
  }
  printf("----------------------------------------------------------\n");
}

void supprimerLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                    int *N) {
  ClearScreen();
  int num, found = -1, i;
  printf("Donnez le numero du livre : ");
  scanf("%d", &num);
  for (i = 0; i <= num; i++) {
    if (T_NLivre[i] == num) {
      found = i;
      break;
    }
  }
  if (found == -1) {
    printf("Livre non trouvé ! ");
    return;
  }

  for (i = found; i < *N; i++) {
    T_NLivre[i] = T_NLivre[i + 1];
    strcpy(T_Titre[i], T_Titre[i + 1]);
    T_Nbr_exp[i] = T_Nbr_exp[i + 1];
  }

  (*N)--;
  printf("Livre supprimé !");
}

void modifierExp(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[], int *N) {
  ClearScreen();
  int num, found = -1;
  printf("Donnez le numero du livre a modifier : ");
  scanf("%d", &num);

  for (int i = 0; i <= num; i++) {
    if (T_NLivre[i] == num) {
      found = i;
    }
  }
  if (found == -1) {
    printf("Livre non trouvé ! ");
    return;
  } else {
    printf("Il y'a %d exemplaire(s) de ce livre actuellement.\n",
           T_Nbr_exp[found]);
    printf("Donnez le nouveau nombre : ");
    scanf("%d", &num);
    T_Nbr_exp[found] = num;
    printf("Exemplaire(s) modifié !");
  }
}

void rechercherLivre(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                     int *N) {
  ClearScreen();
  int num, found = -1;
  printf("Donnez le numero du livre que vous voulez trouver : ");
  scanf("%d", &num);
  for (int i = 0; i <= num; i++) {
    if (T_NLivre[i] == num) {
      found = i;
    }
  }
  if (found == -1) {
    printf("Livre non trouvé ! ");
    return;
  } else {
    printf("Livre trouvé : \n");
    printf("%d . %s : %d", T_NLivre[found], T_Titre[found], T_Nbr_exp[found]);
    return;
  }
}

void afficherLivresDispo(int T_NLivre[], char T_Titre[][50], int T_Nbr_exp[],
                         int *N) {
  ClearScreen();
  printf("----------------------------------------------------------\n");
  printf("||                LIVRES DISPONIBLES                    ||\n");
  printf("----------------------------------------------------------\n");
  int found = 0;
  for (int i = 0; i < *N; i++) {
    if (T_Nbr_exp[i] > 0) {
      printf("||            %d . %s : %d                                \n",
             T_NLivre[i], T_Titre[i], T_Nbr_exp[i]);
      found = 1;
    }
  }
  if (!found) {
    printf("||            Aucun livre disponible.                           \n");
  }
  printf("----------------------------------------------------------\n");
  printf("Appuyez sur Entrée pour continuer...");
  getchar();
  getchar();
}

void gestBiblio() {
  ClearScreen();
  int choix;
  do {
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("||          GESTION DE LA BIBLIOTHÈQUE                  ||\n");
    printf("----------------------------------------------------------\n");
    printf("||  1. Afficher tous les livres                         ||\n");
    printf("||  2. Ajouter un nouveau livre                         ||\n");
    printf("||  3. Supprimer un livre                               ||\n");
    printf("||  4. Modifier le nombre d'exemplaires                 ||\n");
    printf("||  5. Rechercher un livre                              ||\n");
    printf("||  6. Afficher les livres disponibles                  ||\n");
    printf("||  0. Retour au menu principal                         ||\n");
    printf("----------------------------------------------------------\n");
    printf("|| == > ");
    scanf("%d", &choix);
    switch (choix) {
    case 1:
      afficherLivres(T_NLivre, T_Titre, T_Nbr_exp, &N);
      break;
    case 2:
      ajouterLivre(T_NLivre, T_Titre, T_Nbr_exp, &N);
      break;

    case 3:
      supprimerLivre(T_NLivre, T_Titre, T_Nbr_exp, &N);
      break;

    case 4:
      modifierExp(T_NLivre, T_Titre, T_Nbr_exp, &N);
      break;

    case 5:
      rechercherLivre(T_NLivre, T_Titre, T_Nbr_exp, &N);
      break;
    case 6:
      afficherLivresDispo(T_NLivre, T_Titre, T_Nbr_exp, &N);
      break;

    default:
      break;
    }
  } while (choix != 0);
}

void gestEmprunts() {
  ClearScreen();
  int choix;
  do {
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("||            GESTION DES EMPRUNTS                      ||\n");
    printf("----------------------------------------------------------\n");
    printf("||  1. Ajouter un emprunt                               ||\n");
    printf("||  2. Consulter les emprunts d'un adhérent             ||\n");
    printf("||  3. Enregistrer un retour                            ||\n");
    printf("||  4. Afficher les emprunts en cours                   ||\n");
    printf("||  5. Afficher les livres en retard                    ||\n");
    printf("||  6. Afficher par date de retour prévue               ||\n");
    printf("||  7. Supprimer des emprunts par période               ||\n");
    printf("||  0. Retour au menu principal                         ||\n");
    printf("----------------------------------------------------------\n");
    printf("|| == > ");
    scanf("%d", &choix);
    switch (choix) {
    case 1:
      ajoutEmprunt(emprunts, &nb_emprunts, T_NLivre, T_Titre, T_Nbr_exp, &N);
      break;
    case 2:
      empruntsAdherent(emprunts, &nb_emprunts, T_NLivre, T_Titre, T_Nbr_exp,
                       &N);
      break;
    case 3:
      EnregistrerRetour(emprunts, &nb_emprunts, T_NLivre, T_Titre, T_Nbr_exp,
                        &N);
      break;
    case 4:
      afficherEmpruntsEnCours(emprunts, &nb_emprunts, T_Titre);
      break;

    default:
      break;
    }
  } while (choix != 0);
}

void ajoutEmprunt(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                  char T_Titre[][50], int T_Nbr_exp[], int *N) {
  ClearScreen();
  int cin, num;
  int jj, mm, aaaa;
  int found = -1;
  char date[11];
  int nb_emprunts_a_ajouter;
  printf("Combien d'emprunts voulez-vous ajouter ? ");
  scanf("%d", &nb_emprunts_a_ajouter);
  if (nb_emprunts_a_ajouter < 0) {
    printf("Le nombre d'emprunts ne peut pas etre negatif.\n");
    return;
  }
  for (int i = 0; i < nb_emprunts_a_ajouter; i++) {
    printf("Donnez le numero CIN de l'adherent : ");
    scanf("%d", &cin);
    if (cin < 0) {
      printf("Le numero CIN ne peut pas etre negatif.\n");
      return;
    }

    int emprunts_adherent = 0;
    for (int k = 0; k < *nb_emprunts; k++) {
      if (emprunts[k][0] == cin) {
        emprunts_adherent++;
      }
    }

    if (emprunts_adherent >= max_emprunts) {
      printf("Cet adhérent a atteint la limite de %d emprunts.\n", max_emprunts);
      continue;
    }
    printf("Donnez le numero du livre : ");
    scanf("%d", &num);
    found = -1;
    for (int j = 0; j < *N; j++) {
      if (T_NLivre[j] == num) {
        printf("Livre trouvé !\n");
        found = j;
        if (T_Nbr_exp[j] > 0) {
          found = j;
          break;
        } else {
          printf("Le livre est deja empruntee !\n");
          printf("Sa date de retour est : %d/%d/%d\n", emprunts[j][5],
                 emprunts[j][6], emprunts[j][7]);
          return;
        }
      }
    }
    printf("Donnez la date d'emprunt jj/mm/aaaa : ");
    scanf("%10s", date);
    if (date[2] != '/' || date[5] != '/') {
      printf("La date d'emprunt doit etre au format jj/mm/aaaa.\n");
      break;
    }
    jj = (date[0] - '0') * 10 + (date[1] - '0');
    mm = (date[3] - '0') * 10 + (date[4] - '0');
    aaaa = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
           (date[8] - '0') * 10 + (date[9] - '0');
    switch (mm) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if (jj < 1 || jj > 31) {
        printf("Date invalide !\n");
        return;
      } else {
        emprunts[*nb_emprunts][0] = cin;
        emprunts[*nb_emprunts][1] = num;
        emprunts[*nb_emprunts][2] = jj;
        emprunts[*nb_emprunts][3] = mm;
        emprunts[*nb_emprunts][4] = aaaa;
        int j2 = jj + 30;
        int m2 = mm;
        int a2 = aaaa;

        if (j2 > 31) {
          j2 = j2 - 31;
          m2++;
          if (m2 > 12) {
            m2 = 1;
            a2++;
          }
        }

        emprunts[*nb_emprunts][5] = j2;
        emprunts[*nb_emprunts][6] = m2;
        emprunts[*nb_emprunts][7] = a2;

        (*nb_emprunts)++;
        T_Nbr_exp[found]--;
        printf("Emprunt ajouté avec succès !\n");
      }
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      if (jj < 1 || jj > 30) {
        printf("Date invalide !\n");
        return;
      } else {
        emprunts[*nb_emprunts][0] = cin;
        emprunts[*nb_emprunts][1] = num;
        emprunts[*nb_emprunts][2] = jj;
        emprunts[*nb_emprunts][3] = mm;
        emprunts[*nb_emprunts][4] = aaaa;

        int j2 = jj + 30;
        int m2 = mm;
        int a2 = aaaa;

        if (j2 > 30) {
          j2 = j2 - 30;
          m2++;
          if (m2 > 12) {
            m2 = 1;
            a2++;
          }
        }

        emprunts[*nb_emprunts][5] = j2;
        emprunts[*nb_emprunts][6] = m2;
        emprunts[*nb_emprunts][7] = a2;

        (*nb_emprunts)++;
        T_Nbr_exp[found]--;
        printf("Emprunt ajouté avec succès !\n");
      }
      break;
    case 2: {
      int max_jours;
      if (aaaa % 4 == 0 && (aaaa % 100 != 0 || aaaa % 400 == 0)) {
        max_jours = 29;
      } else {
        max_jours = 28;
      }
      if (jj < 1 || jj > max_jours) {
        printf("Date invalide !\n");
        return;
      } else {
        emprunts[*nb_emprunts][0] = cin;
        emprunts[*nb_emprunts][1] = num;
        emprunts[*nb_emprunts][2] = jj;
        emprunts[*nb_emprunts][3] = mm;
        emprunts[*nb_emprunts][4] = aaaa;

        int j2 = jj + 30;
        int m2 = mm;
        int a2 = aaaa;

        if (j2 > max_jours) {
          j2 = j2 - max_jours;
          m2++;
          if (m2 > 12) {
            m2 = 1;
            a2++;
          }
        }

        emprunts[*nb_emprunts][5] = j2;
        emprunts[*nb_emprunts][6] = m2;
        emprunts[*nb_emprunts][7] = a2;

        (*nb_emprunts)++;
        T_Nbr_exp[found]--;
        printf("Emprunt ajouté avec succès !\n");
      }
      break;
    }
    default:
      printf("Date invalide !\n");
      return;
    }
  }
    if (found == -1) {
      printf("Livre non trouvé !\n");
      return;
    }
}

void empruntsAdherent(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                      char T_Titre[][50], int T_Nbr_exp[], int *N) {
  ClearScreen();
  int cin;
  int found = 0;
  printf("Donnez le numero CIN de l'adherent : ");
  scanf("%d", &cin);
  if (cin < 0) {
    printf("Le numero CIN ne peut pas etre negatif.\n");
    return;
  }
  else {
    printf("----------------------------------------------------------------\n");
    printf("||            EMPRUNTS DE L'ADHÉRENT %d                       ||\n", cin);
    printf("----------------------------------------------------------------\n");
  for (int i = 0; i < *nb_emprunts; i++) {
    if (emprunts[i][0] == cin) {
      for (int j = 0; j < MAX; j++) {
        if (emprunts[i][1] == T_NLivre[j]) {
          printf("||            Livre ID %d : %10s                                \n", emprunts[i][1], T_Titre[j]);
          printf("||            Date d'emprunt : %02d/%02d/%d                    \n", emprunts[i][2], emprunts[i][3], emprunts[i][4]);
          printf("||            Date de retour prévue : %02d/%02d/%d              \n", emprunts[i][5], emprunts[i][6], emprunts[i][7]);
          printf("----------------------------------------------------------------\n");
          found = 1;
        }
      }
    }
  }
  if (found == 0) {
    printf("||            Aucun emprunt trouvé pour ce CIN.                 \n");
  }
  printf("----------------------------------------------------------------\n");
}
}

void EnregistrerRetour(int emprunts[][8], int *nb_emprunts, int T_NLivre[],
                       char T_Titre[][50], int T_Nbr_exp[], int *N) {
  ClearScreen();
  int cin;
  int found = -1;
  int num;
  printf("Donnez le numero CIN de l'adherent : ");
  scanf("%d",&cin);
  if (cin < 0) {
    printf("Le numero CIN ne peut pas etre negatif.\n");
    return;
  }
  printf("Donnez le numero ID du livre : ");
  scanf("%d",&num);
  if (num < 0) {
    printf("Le numero ID du livre ne peut pas etre negatif.\n");
    return;
  }
  for (int i = 0; i < *nb_emprunts; i++) {
    if (emprunts[i][0] == cin && emprunts[i][1] == num) {
      found = i;
      break;
    }
  }

  if (found == -1) {
    printf("Aucun emprunt trouvé pour ce CIN et ce Livre.\n");
    return;
  }
  for (int i = found; i < *nb_emprunts - 1; i++) {
    for (int k = 0; k < 8; k++) {
      emprunts[i][k] = emprunts[i + 1][k];
    }
  }
  (*nb_emprunts)--;
  for (int k = 0; k < *N; k++) {
    if (T_NLivre[k] == num) {
      T_Nbr_exp[k]++;
      break;
    }
  }
  
  printf("Retour enregistré avec succès !\n");
}

void afficherEmpruntsEnCours(int emprunts[][8], int *nb_emprunts,
                       char T_Titre[][50]) {
  ClearScreen();
  printf("----------------------------------------------------------------\n");
  printf("||            EMPRUNTS EN COURS                                ||\n");
  printf("----------------------------------------------------------------\n");

  for (int i = 0; i < *nb_emprunts; i++) {
    for (int j = 0; j < MAX; j++){
      if (emprunts[i][1] == T_NLivre[j]) {
    printf("||           CIN : %d                                           \n", emprunts[i][0]);
    printf("||           Livre ID %d : %10s                                \n", emprunts[i][1], T_Titre[j]);
    printf("||           Date d'emprunt : %02d/%02d/%d                    \n", emprunts[i][2], emprunts[i][3], emprunts[i][4]);
    printf("||           Date de retour prévue : %02d/%02d/%d              \n", emprunts[i][5], emprunts[i][6], emprunts[i][7]);
    printf("----------------------------------------------------------------\n");
      }
    }
  }
}


void stats() {
  ClearScreen();
  int choix;
  do {
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("||               STATISTIQUES                           ||\n");
    printf("----------------------------------------------------------\n");
    printf("||  1. Compter livres, adhérents et emprunts            ||\n");
    printf("||  2. Livres les plus empruntés                        ||\n");
    printf("||  3. Livres jamais empruntés                          ||\n");
    printf("||  4. Livres les plus empruntés (période)              ||\n");
    printf("||  5. Emprunteurs les plus fréquents                   ||\n");
    printf("||  0. Retour au menu principal                         ||\n");
    printf("----------------------------------------------------------\n");
    printf("|| == > ");
    scanf("%d", &choix);
  } while (choix != 0);
}

int main() {
  initialiserLivres(T_NLivre, T_Titre, T_Nbr_exp, &N);
  afficherMenuPrincipal();
  return 0;
}