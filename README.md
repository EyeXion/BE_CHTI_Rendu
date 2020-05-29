# Bureau d'Etude CHTI Elies Robin (3MIC-IR Groupe D)
## Objectif 2 : Faire tourner la DFT « en réel » et gérer le score des 6 joueurs

Pour changer les valeurs des signaux envoyés, modifier ***ligne 5 main.c*** le define suivant la documentation donnée avec l'énoncé.

Ouvrir le logic analyser pour visualiser le résultat (il est déjà configuré)

Avec la configration de base (celle quand vous pullez la branche), si vous laissez tourner le programme quelques secondes, le joueur 1 doit avoir 1 point, puis le joueur 2 2 points, puis le joueur 3 3 points etc... (le joueur 6 n'a pas de points).

Pour voir le nombre de scores de chaque joueurs, ouvrez la watch window 1, et regardez les valeurs de tab_scores (cliquer sur le plus pour dérouler le tableau). Le logic analyser est aussi un bon moyen de voir l'évolution du "nombre d'occurences" pour chaque joueur.
