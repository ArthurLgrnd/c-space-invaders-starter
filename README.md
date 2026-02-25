# Projet final C — Space Invaders (SDL2)

## Instructions de compilation

La compilation du code se fait simplement en tapant **make** dans le terminal ouvert au sein du dossier contenant ce makefile.
Le fichier compilé obtenu se nomme **space_invaders** et peut donc être lancé avec la commande ./space-invaders .

## Informations sur le jeu

Ce jeu space invaders possède une infinité de rounds. Les ennemis présent dans les vagues 1 à 15 sont prédéterminés, tandis que les rouds suivants sont aléatoires, jusqu'à la défaite du joueur.

Le joueur demarre initialement avec 3 vies. Il perd lorsqu'il n'a plus de vie ou qu'un ennemi atteint le bas de l'écran.
Au cours de sa partie, il accumule des points en fonction des ennemis tués.

Les rounds muttiples de 5 sont des rounds **boss**. Vaincre ce boss vous offre une vie supplémentaire.
*NB : Par manque de temps, je n'ai pas eu le temps de réaliser ce projet de boss, qui sont dont remplacé par un simple ennemi classique facile à vaincre.*

Les autres rounds possèdes différents types d'ennemis :
- **Classique** : L'ennemi classique de space invaders. Rien de plus.
- **Healer** : Reconnaissable avec son chapeau champignon, son premier tire est un champignon qui vous offre une vie supplémentaire si vous le récupéré. 
- **Schield** : Un ennemi plus résistant : frappez le trois fois pour le vaincre.
- **Military** : Ce soldat avec un casque militaire sur la tête tire plus souvent que les autres ennemis. A chaque tir ennemi, il a une chance sur quatre d'également tirer une balle.
- **Fast_shoot** : Ce colérique ennemi rouge tir des balles 2 fois plus rapides que les autres adversaires.
- **Fast** : Ce soldat bleu paré d'un terrible éclair se déplace deux fois plus vite que les autres ennemis. Leurs déscentes sont indépendantes de celles des autres ennemis.
*NB : Un bug sur les ennemis fast subsiste. Si une partie de ces ennemis sont tués tôt, cela peut provoquer qu'ils descendent moins vite que les ennemis classiques, et se retrouvent alors superposés. Ce bug n'est pas souhaité, mais n'empêche pas le jeu de continuer.*

De plus, vous pourrez voir apparaître en haut de l'écran des vaisseaux rouges. Ce sont des **bonus**. Abattez-les pour remporter une vie supplémentaire (une chance sur 4) ou bien 200 points.


Le jeu est compliqué, et atteindre le round 16 correspondant à la fin des niveaux pré-paramétrés peut s'averrer très difficile avec les paramètres intialement choisis. Afin de découvrir le jeu de manière plus paisible, vous pouvez aller à la ligne 32 du fichier main.c et changer à votre gise le nombre de vie initial. Votre nombre de vie doit seulement ne pas dépasser 255 (Uint8)

## Inforamtions sur l'organisation du code
L'ensemble des fonctions utilisés sont répartis sur 3 fichiers : 
- **video.c** contient l'ensemble des fonctions permettant la gestion de l'affichage.
- **enemy.c** contient l'ensemble des fonctions qui ne concernent que les comportements des ennemis.
- **game.c** contient permet de capter les choix de l'utilisateur, gère les déplacements continus (non saccadés) et gère les interractions entre ennemis et joueurs (collisions de balles).

Les struct, enum et constantes (avec #define) sont définis dans les différents fichier .h en fonction du thème auquel elles se réfèrent davantage.



Bon jeu ! 🚀


