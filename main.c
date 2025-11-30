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
int Jour, Mois, Annee;

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
// gestion de la bib
void afficherLivres();
void ajouterLivre();
void supprimerLivre();
void modifierExp();
void rechercherLivre();
void afficherLivresDispo();

// touskie emprunts
void ajoutEmprunt();
void empruntsAdherent();

void EnregistrerRetour();
void afficherEmpruntsEnCours();
void afficherLivresEnRetard();
void afficherEmpruntsParDate();
void afficherEmpruntsParDate();
void supprimerEmpruntsParPeriode();

// touskie stat
void stats_compter();
void stats_livres_plus_empruntes();
void stats_livres_jamais_empruntes();
void stats_livres_plus_empruntes_periode();
void stats_emprunteurs_frequents();

// fonction pour la lecture de la date
int LectureDate(char date[]);


int LectureDate(char date[]) {
  scanf("%10s", date);
  
  if (date[2] != '/' || date[5] != '/') {
    printf("Format de date invalide. Utilisez jj/mm/aaaa.\n");
    return 0;
  }
  
  Jour = (date[0] - '0') * 10 + (date[1] - '0');
  Mois = (date[3] - '0') * 10 + (date[4] - '0');
  Annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + 
          (date[8] - '0') * 10 + (date[9] - '0');
  
  // controle de saisie de mois
  if (Mois < 1 || Mois > 12) {
      printf("Mois invalide.\n");
      return 0;
  }

  // controle de saisie du jour
  int max_jours = 31;
  if (Mois == 4 || Mois == 6 || Mois == 9 || Mois == 11) {
      max_jours = 30;
  } else if (Mois == 2) {
      if ((Annee % 4 == 0 && Annee % 100 != 0) || (Annee % 400 == 0)) {
          max_jours = 29;
      } else {
          max_jours = 28;
      }
  }

  if (Jour < 1 || Jour > max_jours) {
      printf("Jour invalide pour ce mois.\n");
      return 0;
  }
  
  return 1;
}

void initialiserLivres() {
  N = 5;
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
    printf("||     SYSTEME DE GESTION DE BIBLIOTHEQUE               ||\n");
    printf("----------------------------------------------------------\n");
    printf("||  1. Gestion de la bibliotheque                       ||\n");
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
      printf("Merci d'avoir utilise le systeme !...");
      break;
    default:
      printf("Choix invalide !\n");
    }
  } while (choix != 0);
}

void ajouterLivre() {
  ClearScreen();
  int exp;
  char c;
  do {
    T_NLivre[N] = 100 + (N + 1);
    getchar();

    printf("Donnez le titre du livre : ");
    fgets(T_Titre[N], 50, stdin);
    T_Titre[N][strcspn(T_Titre[N], "\n")] = '\0';

    if (T_Titre[N][0] == '\0') {
      printf("Le titre du livre ne peut pas être vide !\n");
      return;
    }

    printf("Entrez le nombre d'exemplaires : ");
    scanf("%d", &T_Nbr_exp[N]);
    if (T_Nbr_exp[N] < 0|| T_Nbr_exp[N] == 0) {
      printf("Le nombre d'exemplaires doit être positif et non nul !\n");
      return;
    }

    N++;

    printf("Voulez-vous ajouter un autre livre ? (O/N) : ");
    scanf(" %c", &c);
  } while (c == 'O' || c == 'o');
}
void afficherLivres() {
  ClearScreen();
  printf("----------------------------------------------------------\n");
  printf("||                LES LIVRES DISPONIBLES                ||\n");
  printf("----------------------------------------------------------\n");
  for (int i = 0; i < N; i++) {
    printf("||            %d . %s : %d                                \n",
           T_NLivre[i], T_Titre[i], T_Nbr_exp[i]);
  }
  printf("----------------------------------------------------------\n");
  printf("Appuyez sur Entree pour continuer...");
  getchar();
  getchar();
}

void supprimerLivre() {
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
    printf("Livre non trouve ! ");
    return;
  }

  for (i = found; i < N; i++) {
    T_NLivre[i] = T_NLivre[i + 1];
    strcpy(T_Titre[i], T_Titre[i + 1]);
    T_Nbr_exp[i] = T_Nbr_exp[i + 1];
  }

  N--;
  printf("Livre supprime !");
}

void modifierExp() {
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
    printf("Livre non trouve ! ");
    return;
  } else {
    printf("Il y'a %d exemplaire(s) de ce livre actuellement.\n",
           T_Nbr_exp[found]);
    printf("Donnez le nouveau nombre : ");
    scanf("%d", &num);
    T_Nbr_exp[found] = num;
    printf("Exemplaire(s) modifie !");
  }
}

void rechercherLivre() {
  ClearScreen();
  int num, found = -1;
  printf("----------------------------------------------------------\n");
  printf("||                  RECHERCHE DE LIVRE                  ||\n");
  printf("----------------------------------------------------------\n");
  printf("||  1. Recherche par ID                                 ||\n");
  printf("||  2. Recherche par Titre                              ||\n");
  printf("----------------------------------------------------------\n");
  printf("|| == > ");
  int choix;
  scanf("%d", &choix);
  if (choix == 1) {
    printf("Donnez le numero du livre que vous voulez trouver : ");
    scanf("%d", &num);
    for (int i = 0; i < N; i++) {
      if (T_NLivre[i] == num) {
        found = i;
        break;
      }
    }
  } else if (choix == 2) {
    printf("Donnez le titre du livre que vous voulez trouver : ");
    char titre[50];
    getchar(); // Clear newline from buffer
    fgets(titre, 50, stdin);
    titre[strcspn(titre, "\n")] = '\0'; // Remove newline char
    
    for (int i = 0; i < N; i++) {
      if (strcmp(T_Titre[i], titre) == 0) {
        found = i;
        break;
      }
    }
  }
  if (found == -1) {
    printf("Livre non trouve ! ");
    return;
  } else {
    printf("Livre trouve : \n");
    printf("%d . %s : %d", T_NLivre[found], T_Titre[found], T_Nbr_exp[found]);
    printf("\nAppuyez sur Entree pour continuer...");
    getchar();
    getchar();
    return;
  }
}

void afficherLivresDispo() {
  ClearScreen();
  printf("----------------------------------------------------------\n");
  printf("||                LIVRES DISPONIBLES                    ||\n");
  printf("----------------------------------------------------------\n");
  int found = 0;
  for (int i = 0; i < N; i++) {
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
  printf("Appuyez sur Entree pour continuer...");
  getchar();
  getchar();
}

void gestBiblio() {
  ClearScreen();
  int choix;
  do {
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("||          GESTION DE LA BIBLIOTHEQUE                  ||\n");
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
      afficherLivres();
      break;
    case 2:
      ajouterLivre();
      break;

    case 3:
      supprimerLivre();
      break;

    case 4:
      modifierExp();
      break;

    case 5:
      rechercherLivre();
      break;
    case 6:
      afficherLivresDispo();
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
    printf("||  2. Consulter les emprunts d'un adherent             ||\n");
    printf("||  3. Enregistrer un retour                            ||\n");
    printf("||  4. Afficher les emprunts en cours                   ||\n");
    printf("||  5. Afficher les livres en retard                    ||\n");
    printf("||  6. Afficher par date de retour prevue               ||\n");
    printf("||  7. Supprimer des emprunts par periode               ||\n");
    printf("||  0. Retour au menu principal                         ||\n");
    printf("----------------------------------------------------------\n");
    printf("|| == > ");
    scanf("%d", &choix);
    switch (choix) {
    case 1:
      ajoutEmprunt();
      break;
    case 2:
      empruntsAdherent();
      break;
    case 3:
      EnregistrerRetour();
      break;
    case 4:
      afficherEmpruntsEnCours();
      break;
    case 5:
      afficherLivresEnRetard();
      break;
    case 6:
        afficherEmpruntsParDate();
        break;
    case 7:
        supprimerEmpruntsParPeriode();
        break;

    default:
      break;
    }
  } while (choix != 0);
}

void ajoutEmprunt() {
  ClearScreen();
  int cin, num;
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
    for (int k = 0; k < nb_emprunts; k++) {
      if (emprunts[k][0] == cin) {
        emprunts_adherent++;
      }
    }

    if (emprunts_adherent >= max_emprunts) {
      printf("Cet adherent a atteint la limite de %d emprunts.\n", max_emprunts);
      continue;
    }
    printf("Donnez le numero du livre : ");
    scanf("%d", &num);
    found = -1;
    for (int j = 0; j < N; j++) {
      if (T_NLivre[j] == num) {
        printf("Livre trouve !\n");
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
    if (!LectureDate(date)) {
      break;
    }
    switch (Mois) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if (Jour < 1 || Jour > 31) {
        printf("Date invalide !\n");
        return;
      } else {
        emprunts[nb_emprunts][0] = cin;
        emprunts[nb_emprunts][1] = num;
        emprunts[nb_emprunts][2] = Jour;
        emprunts[nb_emprunts][3] = Mois;
        emprunts[nb_emprunts][4] = Annee;
        int j2 = Jour + 30;
        int m2 = Mois;
        int a2 = Annee;

        if (j2 > 31) {
          j2 = j2 - 31;
          m2++;
          if (m2 > 12) {
            m2 = 1;
            a2++;
          }
        }

        emprunts[nb_emprunts][5] = j2;
        emprunts[nb_emprunts][6] = m2;
        emprunts[nb_emprunts][7] = a2;

        nb_emprunts++;
        T_Nbr_exp[found]--;
        printf("Emprunt ajoute avec succes !\n");
      }
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      if (Jour < 1 || Jour > 30) {
        printf("Date invalide !\n");
        return;
      } else {
        emprunts[nb_emprunts][0] = cin;
        emprunts[nb_emprunts][1] = num;
        emprunts[nb_emprunts][2] = Jour;
        emprunts[nb_emprunts][3] = Mois;
        emprunts[nb_emprunts][4] = Annee;

        int j2 = Jour + 30;
        int m2 = Mois;
        int a2 = Annee;

        if (j2 > 30) {
          j2 = j2 - 30;
          m2++;
          if (m2 > 12) {
            m2 = 1;
            a2++;
          }
        }

        emprunts[nb_emprunts][5] = j2;
        emprunts[nb_emprunts][6] = m2;
        emprunts[nb_emprunts][7] = a2;

        nb_emprunts++;
        T_Nbr_exp[found]--;
        printf("Emprunt ajoute avec succes !\n");
      }
      break;
    case 2: {
      int max_jours;
      if (Annee % 4 == 0 && (Annee % 100 != 0 || Annee % 400 == 0)) {
        max_jours = 29;
      } else {
        max_jours = 28;
      }
      if (Jour < 1 || Jour > max_jours) {
        printf("Date invalide !\n");
        return;
      } else {
        emprunts[nb_emprunts][0] = cin;
        emprunts[nb_emprunts][1] = num;
        emprunts[nb_emprunts][2] = Jour;
        emprunts[nb_emprunts][3] = Mois;
        emprunts[nb_emprunts][4] = Annee;

        int j2 = Jour + 30;
        int m2 = Mois;
        int a2 = Annee;

        if (j2 > max_jours) {
          j2 = j2 - max_jours;
          m2++;
          if (m2 > 12) {
            m2 = 1;
            a2++;
          }
        }

        emprunts[nb_emprunts][5] = j2;
        emprunts[nb_emprunts][6] = m2;
        emprunts[nb_emprunts][7] = a2;

        nb_emprunts++;
        T_Nbr_exp[found]--;
        printf("Emprunt ajoute avec succes !\n");
      }
      break;
    }
    default:
      printf("Date invalide !\n");
      return;
    }
  }
    if (found == -1) {
      printf("Livre non trouve !\n");
      return;
    }
}

void empruntsAdherent() {
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
    printf("||            EMPRUNTS DE L'ADHERENT %d                       ||\n", cin);
    printf("----------------------------------------------------------------\n");
  for (int i = 0; i < nb_emprunts; i++) {
    if (emprunts[i][0] == cin) {
      for (int j = 0; j < MAX; j++) {
        if (emprunts[i][1] == T_NLivre[j]) {
          printf("||            Livre ID %d : %10s                                \n", emprunts[i][1], T_Titre[j]);
          printf("||            Date d'emprunt : %02d/%02d/%d                    \n", emprunts[i][2], emprunts[i][3], emprunts[i][4]);
          printf("||            Date de retour prevue : %02d/%02d/%d              \n", emprunts[i][5], emprunts[i][6], emprunts[i][7]);
          printf("----------------------------------------------------------------\n");
          found = 1;
        }
      }
    }
  }
  if (found == 0) {
    printf("||            Aucun emprunt trouve pour ce CIN.                 \n");
  }
  printf("----------------------------------------------------------------\n");
  printf("Appuyez sur Entree pour continuer...");
  getchar();
  getchar();
}
}

void EnregistrerRetour() {
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
  for (int i = 0; i < nb_emprunts; i++) {
    if (emprunts[i][0] == cin && emprunts[i][1] == num) {
      found = i;
      break;
    }
  }

  if (found == -1) {
    printf("Aucun emprunt trouve pour ce CIN et ce Livre.\n");
    return;
  }
  for (int i = found; i < nb_emprunts - 1; i++) {
    for (int k = 0; k < 8; k++) {
      emprunts[i][k] = emprunts[i + 1][k];
    }
  }
  nb_emprunts--;
  for (int k = 0; k < N; k++) {
    if (T_NLivre[k] == num) {
      T_Nbr_exp[k]++;
      break;
    }
  }
  
  printf("Retour enregistre avec succes !\n");
}

void afficherEmpruntsEnCours() {
  ClearScreen();
  printf("----------------------------------------------------------------\n");
  printf("||            EMPRUNTS EN COURS                                ||\n");
  printf("----------------------------------------------------------------\n");

  for (int i = 0; i < nb_emprunts; i++) {
    for (int j = 0; j < MAX; j++){
      if (emprunts[i][1] == T_NLivre[j]) {
    printf("||           CIN : %d                                           \n", emprunts[i][0]);
    printf("||           Livre ID %d : %10s                                \n", emprunts[i][1], T_Titre[j]);
    printf("||           Date d'emprunt : %02d/%02d/%d                    \n", emprunts[i][2], emprunts[i][3], emprunts[i][4]);
    printf("||           Date de retour prevue : %02d/%02d/%d              \n", emprunts[i][5], emprunts[i][6], emprunts[i][7]);
    printf("----------------------------------------------------------------\n");
      }
    }
  }
  printf("Appuyez sur Entree pour continuer...");
  getchar();
  getchar();
}

void afficherLivresEnRetard() {
  ClearScreen();
  char date[11];
  printf("Donnez la date courante (jj/mm/aaaa) : ");
  if (!LectureDate(date)) {
    return;
  }

  printf("----------------------------------------------------------------\n");
  printf("||            EMPRUNTS EN RETARD                             ||\n");
  printf("----------------------------------------------------------------\n");

  for (int i = 0; i < nb_emprunts; i++) {
    for (int j = 0; j < MAX; j++){
      if (emprunts[i][1] == T_NLivre[j]) {
        if (emprunts[i][7] < Annee || emprunts[i][7] == Annee && emprunts[i][6] < Mois || emprunts[i][7] == Annee && emprunts[i][6] == Mois && emprunts[i][5] < Jour) {
    printf("||           CIN : %d                                           \n", emprunts[i][0]);
    printf("||           Livre ID %d : %10s                                \n", emprunts[i][1], T_Titre[j]);
    printf("||           Date d'emprunt : %02d/%02d/%d                    \n", emprunts[i][2], emprunts[i][3], emprunts[i][4]);
    printf("||           Date de retour prevue : %02d/%02d/%d              \n", emprunts[i][5], emprunts[i][6], emprunts[i][7]);
    printf("----------------------------------------------------------------\n");
      }
      else {
        printf("||           Aucun emprunt en retard.                          ||\n");
        printf("----------------------------------------------------------------\n");
        printf("Appuyez sur Entree pour continuer...");
        getchar();
        getchar();
        return;
      }
    }
  }
  printf("Appuyez sur Entree pour continuer...");
  getchar();
  getchar();
}

}

void afficherEmpruntsParDate() {
  ClearScreen();
  int found = -1;
  char date[11];
  printf("Donnez la date (jj/mm/aaaa) : ");
  if (!LectureDate(date)) {
    return;
  }

  printf("----------------------------------------------------------------\n");
  printf("||            EMPRUNTS PAR DATE                             ||\n");
  printf("----------------------------------------------------------------\n");

  for (int i = 0; i < nb_emprunts; i++) {
    for (int j = 0; j < MAX; j++){
      if (emprunts[i][1] == T_NLivre[j] && emprunts[i][5] == Jour && emprunts[i][6] == Mois && emprunts[i][7] == Annee) {
        found = 1;
        printf("||           CIN : %d                                           \n", emprunts[i][0]);
        printf("||           Livre ID %d : %10s                                \n", emprunts[i][1], T_Titre[j]);
        printf("||           Date d'emprunt : %02d/%02d/%d                    \n", emprunts[i][2], emprunts[i][3], emprunts[i][4]);
        printf("||           Date de retour prevue : %02d/%02d/%d              \n", emprunts[i][5], emprunts[i][6], emprunts[i][7]);
        printf("----------------------------------------------------------------\n");
      }
    }
  }
  if (found == -1) {
    printf("||           Aucun emprunt trouve pour cette date.              ||\n");
    printf("----------------------------------------------------------------\n");
    printf("Appuyez sur Entree pour continuer...");
    getchar();
    getchar();
    return;
}
  printf("Appuyez sur Entree pour continuer...");
  getchar();
  getchar();
}

void supprimerEmpruntsParPeriode() {
  ClearScreen();
  afficherEmpruntsEnCours();
  char date[11];
  int jj, mm, aaaa,jj2,mm2,aaaa2;
  printf("Donnez la date d'emprunt (jj/mm/aaaa) : ");
  if (!LectureDate(date)) {
    return;
  }
  jj = Jour;
  mm = Mois;
  aaaa = Annee;

  printf("Donnez la date de retour (jj/mm/aaaa) : ");
  if (!LectureDate(date)) {
    return;
  }
  jj2 = Jour;
  mm2 = Mois;
  aaaa2 = Annee;

  for (int i = 0; i < nb_emprunts; i++) {
    if (emprunts[i][2] == jj && emprunts[i][3] == mm && emprunts[i][4] == aaaa && emprunts[i][5] == jj2 && emprunts[i][6] == mm2 && emprunts[i][7] == aaaa2) {
      for (int j = 0; j < nb_emprunts - 1; j++) {
    for (int k = 0; k < 8; k++) {
      emprunts[j][k] = emprunts[j + 1][k];
    }
  }
  nb_emprunts--;
  for (int p = 0; p < N; p++) {
    if (T_NLivre[p] == emprunts[i][1]) {
      T_Nbr_exp[p]++;
      break;
    }
  }
    }
  }
}


void stats_compter() {
    ClearScreen();
    printf("----------------------------------------------------------\n");
    printf("||       STATISTIQUES : COMPTES GLOBAUX                 ||\n");
    printf("----------------------------------------------------------\n");
    
    int total_exemplaires = 0;
    for(int i=0; i<N; i++) {
        total_exemplaires += T_Nbr_exp[i];
    }
    total_exemplaires += nb_emprunts; 

    int nb_adherents = 0;
    int liste_cin[100];
    
    for(int i=0; i<nb_emprunts; i++) {
        int cin_actuel = emprunts[i][0];
        int est_present = 0;
        
        for(int j=0; j<nb_adherents; j++) {
            if(liste_cin[j] == cin_actuel) {
                est_present = 1;
                break;
            }
        }
        
        if(!est_present) {
            liste_cin[nb_adherents] = cin_actuel;
            nb_adherents++;
        }
    }

    printf("|| Nombre total de titres : %d\n", N);
    printf("|| Nombre total d'exemplaires (dispo + empruntes) : %d\n", total_exemplaires);
    printf("|| Nombre d'emprunts en cours : %d\n", nb_emprunts);
    printf("|| Nombre d'adherents actifs : %d\n", nb_adherents);
    printf("----------------------------------------------------------\n");
    printf("Appuyez sur Entree pour continuer...");
    getchar(); 
    getchar();
}

void stats_livres_plus_empruntes() {
    ClearScreen();
    printf("----------------------------------------------------------\n");
    printf("||       LIVRES LES PLUS EMPRUNTES (ACTUELLEMENT)       ||\n");
    printf("----------------------------------------------------------\n");

    int compteur_emprunts[100] = {0}; 
    
    for(int i=0; i<nb_emprunts; i++) {
        int id_livre = emprunts[i][1];
        for(int j=0; j<N; j++) {
            if(T_NLivre[j] == id_livre) {
                compteur_emprunts[j]++;
                break;
            }
        }
    }

    int indices[100];
    for(int i=0; i<N; i++) indices[i] = i;

    for(int i=0; i < N-1; i++) {
        for(int j=0; j < N-i-1; j++) {
            if(compteur_emprunts[indices[j]] < compteur_emprunts[indices[j+1]]) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }

    for(int i=0; i < 3 && i < N; i++) {
        int idx = indices[i];
        if(compteur_emprunts[idx] > 0) {
            printf("|| %d. %s (%d emprunts)\n", i+1, T_Titre[idx], compteur_emprunts[idx]);
        }
    }
    printf("----------------------------------------------------------\n");
    printf("Appuyez sur Entree pour continuer...");
    getchar(); getchar();
}

void stats_livres_jamais_empruntes() {
    ClearScreen();
    printf("----------------------------------------------------------\n");
    printf("||       LIVRES JAMAIS EMPRUNTES (ACTUELLEMENT)         ||\n");
    printf("----------------------------------------------------------\n");

    int au_moins_un_trouve = 0;
    for(int i=0; i < N; i++) {
        int est_emprunte = 0;
        for(int j=0; j < nb_emprunts; j++) {
            if(emprunts[j][1] == T_NLivre[i]) {
                est_emprunte = 1;
                break;
            }
        }
        if(!est_emprunte) {
            printf("|| - %s (ID: %d)\n", T_Titre[i], T_NLivre[i]);
            au_moins_un_trouve = 1;
        }
    }

    if(!au_moins_un_trouve) {
        printf("|| Tous les livres sont actuellement empruntes au moins une fois.\n");
    }
    printf("----------------------------------------------------------\n");
    printf("Appuyez sur Entree pour continuer...");
    getchar(); getchar();
}
int compare_dates(int d1, int m1, int y1, int d2, int m2, int y2) {
    if (y1 != y2) return y1 - y2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}
void stats_livres_plus_empruntes_periode() {
    ClearScreen();
    printf("----------------------------------------------------------\n");
    printf("||       LIVRES PLUS EMPRUNTES (PERIODE)                ||\n");
    printf("----------------------------------------------------------\n");

    char date[11];
    int j1, m1, a1, j2, m2, a2;
    
    printf("Date debut (jj/mm/aaaa) : ");
    if(!LectureDate(date)) return;
    j1 = Jour;
    m1 = Mois;
    a1 = Annee;
    
    printf("Date fin (jj/mm/aaaa) : ");
    if(!LectureDate(date)) return;
    j2 = Jour;
    m2 = Mois;
    a2 = Annee;

    int compteur_emprunts[100] = {0};
    
    for(int i=0; i<nb_emprunts; i++) {
        int date_j = emprunts[i][2];
        int date_m = emprunts[i][3];
        int date_a = emprunts[i][4];
        
        if(compare_dates(date_j, date_m, date_a, j1, m1, a1) >= 0 && 
           compare_dates(date_j, date_m, date_a, j2, m2, a2) <= 0) {
            
            int id_livre = emprunts[i][1];
            for(int k=0; k<N; k++) {
                if(T_NLivre[k] == id_livre) {
                    compteur_emprunts[k]++;
                    break;
                }
            }
        }
    }
    int indices[100];
    for(int i=0; i<N; i++) indices[i] = i;

    for(int i=0; i<N-1; i++) {
        for(int j=0; j<N-i-1; j++) {
            if(compteur_emprunts[indices[j]] < compteur_emprunts[indices[j+1]]) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }
    printf("\nTop livres du %02d/%02d/%04d au %02d/%02d/%04d :\n", j1, m1, a1, j2, m2, a2);
    int affiche = 0;
    for(int i=0; i<3 && i<N; i++) {
        int idx = indices[i];
        if(compteur_emprunts[idx] > 0) {
            printf("|| %d. %s (%d emprunts)\n", i+1, T_Titre[idx], compteur_emprunts[idx]);
            affiche = 1;
        }
    }
    if(!affiche) printf("|| Aucun emprunt dans cette periode.\n");
    
    printf("----------------------------------------------------------\n");
    printf("Appuyez sur Entree pour continuer...");
    getchar(); getchar();
}
void stats_emprunteurs_frequents() {
    ClearScreen();
    printf("----------------------------------------------------------\n");
    printf("||       EMPRUNTEURS LES PLUS FREQUENTS                 ||\n");
    printf("----------------------------------------------------------\n");

    int liste_cin[100];
    int compteur_emprunts[100] = {0};
    int nb_emprunteurs = 0;

    for(int i=0; i<nb_emprunts; i++) {
        int cin = emprunts[i][0];
        int index_trouve = -1;
        for(int j=0; j<nb_emprunteurs; j++) {
            if(liste_cin[j] == cin) {
                index_trouve = j;
                break;
            }
        }
        
        if(index_trouve != -1) {
            compteur_emprunts[index_trouve]++;
        } else {
            liste_cin[nb_emprunteurs] = cin;
            compteur_emprunts[nb_emprunteurs] = 1;
            nb_emprunteurs++;
        }
    }
    int indices[100];
    for(int i=0; i<nb_emprunteurs; i++) indices[i] = i;

    for(int i=0; i<nb_emprunteurs-1; i++) {
        for(int j=0; j<nb_emprunteurs-i-1; j++) {
            if(compteur_emprunts[indices[j]] < compteur_emprunts[indices[j+1]]) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }

    for(int i=0; i<3 && i<nb_emprunteurs; i++) {
        int idx = indices[i];
        printf("|| %d. CIN: %d (%d emprunts)\n", i+1, liste_cin[idx], compteur_emprunts[idx]);
    }
    
    if(nb_emprunteurs == 0) printf("|| Aucun emprunteur.\n");

    printf("----------------------------------------------------------\n");
    printf("Appuyez sur Entree pour continuer...");
    getchar(); getchar();
}

void stats() {
  ClearScreen();
  int choix;
  do {
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("||               STATISTIQUES                           ||\n");
    printf("----------------------------------------------------------\n");
    printf("||  1. Compter livres, adherents et emprunts            ||\n");
    printf("||  2. Livres les plus empruntes                        ||\n");
    printf("||  3. Livres jamais empruntes                          ||\n");
    printf("||  4. Livres les plus empruntes (periode)              ||\n");
    printf("||  5. Emprunteurs les plus frequents                   ||\n");
    printf("||  0. Retour au menu principal                         ||\n");
    printf("----------------------------------------------------------\n");
    printf("|| == > ");
    scanf("%d", &choix);
    switch (choix) {
    case 1:
      stats_compter();
      break;
    case 2:
      stats_livres_plus_empruntes();
      break;
    case 3:
      stats_livres_jamais_empruntes();
      break;
    case 4:
      stats_livres_plus_empruntes_periode();
      break;
    case 5:
      stats_emprunteurs_frequents();
      break;
    case 0:
      break;
    default:
      printf("Choix invalide !\n");
    }
  } while (choix != 0);
}

int main() {
  initialiserLivres();
  afficherMenuPrincipal();
  return 0;
}