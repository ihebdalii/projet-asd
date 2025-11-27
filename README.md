# Projet ASD1 2025-2026 --- Gestion des prêts de livres d'une bibliothèque

## Sujet

Développer un programme en langage C assurant la gestion de prêt de
livres d'une bibliothèque.

Trois parties principales : 1. **Gestion de la bibliothèque** 2.
**Gestion des emprunts** 3. **Statistiques**

------------------------------------------------------------------------

## Structure des données

### Livres

Un livre est défini par : - un numéro - un titre - un nombre
d'exemplaires

Trois tableaux utilisés : - `T_NLivre` : Numéros des livres - `T_Titre`
: Titres des livres - `T_Nbr_exp` : Nombre d'exemplaires

### Emprunts

Tableau 2D :

  N_CIN   N_livre   J1               M1                      A1   J2   M2   A2
  ------- --------- ---------------- ----------------------- ---- ---- ---- ----
  CIN     Livre     Date d'emprunt   Date de retour prévue                  

Chaque emprunt est défini par : - Numéro CIN de l'emprunteur - Numéro du
livre - Date d'emprunt (J1/M1/A1) - Date de retour prévue (J2/M2/A2)

------------------------------------------------------------------------

# PARTIE 1 --- Gestion de la bibliothèque

Cette partie permet au bibliothécaire de gérer les livres.

### Questions

1.  Afficher tous les livres
2.  Ajouter un nouveau livre
3.  Supprimer un livre (s'il n'est pas emprunté)
4.  Modifier le nombre d'exemplaires
5.  Rechercher un livre (par titre ou numéro)
6.  Afficher les livres disponibles et leurs exemplaires

------------------------------------------------------------------------

# PARTIE 2 --- Gestion des emprunts

Cette partie gère les interactions avec les adhérents.

Règles : - L'application affiche tous les livres existants. - Durée
maximale d'emprunt : **1 mois** - Un adhérent peut emprunter **max 7
livres** - Si un livre n'est pas dispo, afficher la date estimée de
retour - L'adhérent peut consulter ses emprunts

### Questions

1.  Ajouter un emprunt
2.  Consulter les emprunts d'un adhérent donné
3.  Enregistrer le retour d'un livre
4.  Afficher les emprunts en cours
5.  Afficher les livres en retard (selon une date courante)
6.  Afficher les emprunts d'une date de retour prévue donnée
7.  Supprimer des emprunts selon période (date emprunt + date retour)

------------------------------------------------------------------------

# PARTIE 3 --- Statistiques

Objectif : analyse de l'activité de la bibliothèque.

### Questions

1.  Compter livres, adhérents, emprunts
2.  Afficher le(s) livre(s) les plus empruntés
3.  Afficher le(s) livre(s) jamais empruntés
4.  Afficher les livres les plus empruntés durant une période donnée
5.  Afficher les emprunteurs les plus fréquents

------------------------------------------------------------------------

## Codification

-   L'utilisateur doit pouvoir revenir au menu principal après chaque
    tâche.
-   Contrôle de saisie obligatoire.
-   Messages d'affichage clairs et informatifs.

## Remarques

-   Les tableaux sont chargés en RAM au démarrage.
-   Les emprunts couvrent plusieurs années.

## Interface

-   Affichage **textuel**
-   Interface graphique **non exigée**
