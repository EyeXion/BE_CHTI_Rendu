# Bureau d'Etude CHTI Elies robin

## Objectif 1 : Programmer la DFT en simulation sur un tableau de données imposées

Pour le signal actuellement mis en place dans KEIL, les valeurs attendues sont les suivantes :

pour k = 17 :

- Partie réeele    :       0x376C909D    env 0.866 * 2^30

- Partie imaginaire :     0xE000C6D7    env -0.5  * 2^30

- Module au carré :       0x0FFFA278    env 2^28

Note  :

pour cette valeur de module, nous trouvons 0x0FFFA277 car nous effectuons la somme des carrés après avoir retiré les bits de poids faible (comme expliqué par Mr Noullet sur Discord)


valeurs attendues pour k = 18 :

- Partie réeele    :       0xD2BDF5FC    env -sqrt(0.5) * 2^30

- Partie imaginaire :     0xD2BE8C7F    env -sqrt(0.5) * 2^30

- Module au carré :       0x10005BE5    env 2^28

pour les autres valeurs de k sauf les alias de 17 et 18 :

- Module au carré < 0x0000000F

### Vérification des valeurs
(Ouvrir les fichiers main.c et CalculModule.s pour mettre des points d'arrêt)

Pour changer la valeur de k modifier la variable ***ligne 12***

2 procédures différentes sont nécessaires suivant ce que l'on veut vérifier

#### Vérification du module, de la partie réelle et imaginaire
Pour vérifier les valeurs de partie réelle, imaginaire placer un point avant debug un point d'arrêt dans le ***main.c ligne 15***. Aller en mode debug au point d'arrêt précédement placé. Placer à ce moment les points d'arrêts indiqués dans le tableau et utiliser la commande "aller au prochain point d'arrêt" pour voir les valeurs désirées.

||Emplacement du point d'arrêt | Fichier | Variable / registre à observer | 
|---|:---:|:---:|:---:|
|Partie imaginaire|***ligne 23*** | CalculModule.s | r0 |
|Partie réelle|***ligne 18*** | CalculModule.s | r0 |
|Module au carrée|***ligne 26*** | CalculModule.s | r0 |

#### Vérification uniquement du module

Placer un point d'arrêt ***ligne 19 main.c*** et avec la watch window regarder la variable `res_verif`
### Vérification avec d'autres fichiers

Il est nécessaire d'enlever l'ancien signal f17p30__f18
