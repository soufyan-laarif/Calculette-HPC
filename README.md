# Projet Calculette HPC

## Objectif
Le projet vise à créer une application de calcul HPC avec une interface graphique conviviale. Le front-end est développé en Java, offrant une gestion intuitive des interfaces utilisateur. Le back-end est en C, permettant une gestion efficace des processus et une synchronisation optimale entre eux.

## Techniques utilisées
- Langage front-end : Java
- Langage back-end : C
- Utilisation de sémaphores Unix en C pour la synchronisation entre les processus
- Utilisation de files de messages pour le transfert de données inter-processus

## Hierarchie du projet
Le projet est organisé en plusieurs classes Java et fichiers C :
- Calculette.java : interface principale de l'application.
- Resultat.java : affichage des résultats et temps d'exécution.
- Taches_calcul.java : gestion des opérations arithmétiques.
- InitVal.java : initialisation des variables.
- sequentiel.c et file_message.c : fichiers backend pour le calcul avec IPC.
- Fichiers .txt pour le transfert de données entre frontend et backend.

  ![Calculette HPC](https://github.com/soufyan-laarif/Calculette-HPC/blob/main/Calculette%20HPC.PNG)


