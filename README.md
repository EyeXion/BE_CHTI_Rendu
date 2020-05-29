# Bureau d'Etude CHTI Elies Robin (3MIC-IR Groupe D)
## Objectif 3 : Gestion du son ; Vérification des valeurs

Placer un point d'arrêt ***ligne 16 sound.s*** puis effectuer la différence entre deux points d'arrêt avec la valeur de ***Max time du logic analyser*** Cela permet de voir que la durée entre chaque échantillon est de 91µs (ou 0.091 ms).

Vérifier en mode debug, après avoir lancé le viewport, que ***TIM3_CCR3*** a bien une échelle ***entre 0 et 653***. Si ce n'est pas le cas modifier cela dans le setup.

Lancer la simulation jusqu'à ce que le signal revienne à 0. Faire un ***zoom -> All*** pour voir tout le signal. Il devrait ressembler à celui attendu dans le document d'évaluation. (Penser à enlever le point d'arrêt pour voir le signale en entier).
