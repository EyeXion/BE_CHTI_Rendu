# Bureau d'Etude CHTI Elies Robin (3MIC-IR Groupe D)
## Objectif 4 : Projet final

### Vérification des valeurs

Après avoir lancé le debugage et le logic analyser, vérifier que la valeur maximale pour les nb_occ[...] vaut bien 21 (dans le setup). Ouvrir la watch window et si il n'y est pas déjà présente, ajouter le tableau nb_occ pour visualiser les valeurs.

#### Avec tous les signaux

Il est possible de choisir le signal émis ***ligne 6 main.c***

On peut vérifier que le son est bien émis (signal comptabilisé) à chaque fois qu'un des nb_occ atteint 15 et que la valeur nb_occ correspondante est remise à 0 après cela.

### Avec le signal 0x33 (déjà dans le fichier)

Lancer ***l'exécution du programme pendant au moins 10s (pour voir les 3 premiers signaux)***.
On observe bien successivement : 
- 1 point compté pour tab_scores[0] 
- 2 points comptés pour tab_scores[1]
- 3 points comptés pour tab_scores[2]

(On peut continuer l'exécution plus longtemps pour vérifier les autres valeurs)
