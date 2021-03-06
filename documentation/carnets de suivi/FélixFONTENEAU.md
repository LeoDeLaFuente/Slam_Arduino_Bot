# Cahier de suivi du projet de Félix Fonteneau


## Séance du 20 Décembre 2017

Tâches effectuées :

  + Recherches bibliographique des différentes options permettant d'aboutir à réaliser le traitement de données sur l'ordinateur (processing/ROS).

  + Décomposition des différents besoins matériels et informatiques nécessaires au projet. Schématisation de l'ensemble des modules et de leur utilités au brouillon : 
  <img src="/documentation/Images/Schéma_brouillon1.jpg" alt="brouillon" height="200">  
  <img src="/documentation/Images/Schéma_brouillon2.jpg" alt="brouillon2" height="200">
  <img src="/documentation/Images/Schéma_brouillon3.jpg" alt="brouillon3" height="200">
  
  + Mise en place et déveleppement du GitHub.  
  
***  

## Travail personnel entre les séances 

Tâches effectuées :
  + Recherches et dévellopements des idées à la réalisation.  
  
  + Liste du matériel : [liste](/documentation/liste_du_materiel.md)
 
 ***  

## Séance du 8 Janvier 2018

Tâches effectuées :
  + Réception et début d'utilisation du module laser. Débuts concluants pour les premiers tests avec le laser. En effet il marche parfaitement dans les conditions dont le souhaitons. Voir : [code basique laser automatique]( /code/arduino files/test_laser_san_delay/test_laser_san_delay.ino)
  <img src="documentation/Images/soudure_laser.jpg" alt="photo soudure" height="300"/>
  
  + Création de la présentation du module laser : [ici](/Construction_Projet/Laser.md)
  
  ***  
## Travail personnel entre les séances

Tâches effectuées :
  + Optimisation du code du laser
  
  + Amélioration de la vitesse des mesures
  
  ***  

## Séance du 19 Janvier 2018  

Tâches effectuées :
  + Réception des moteurs à roues codeuses (voir le carnet de léo)
  
  + Création de la première tourelle temporaire avec fil et scotch. La premiere tourelle est peu précise mais donne deja une premiere vision de la gestion des données et de comment ameliorer sa précision.
  <img src="/documentation/Images/Tourelle_premiere_version.JPG" alt="image tourelle" height="300"/>
  
  + Harmonisation du code entre servo moteur et laser [code laser](/code/arduino_files/Tourelle/Tourelle.ino )
  
    ***  

## Séance du 22 Janvier
 
 - ##### Pésentation de notre projet devant nos deux professeur et notre classe.
 [La présentation est visible ici](https://github.com/LeoDeLaFuente/Slam_Arduino_Bot/blob/master/documentation/Slam_arduino_bot_presentation.pdf)
 
   ***  

 
## Travail personel durant la semaine de ski

Tâches effectuées : 
  + Création d'une simulation du laser pour débuter la programation, <a href="code/computer files/processing/execution_p/execution_p.pde"> code processing </a>
  
  + Début du traitement des données sur processing. 
  
  + Création de l'interface et de l'affichage de la carte en fonction des données reçues  
  <a href="code/computer files/processing/execution_p/execution_p.pde"> code </a>
  Cela permet de nous donner une base afin de pouvoir commencer la partie programmation en parallèle de la partie électronique.  
  
  + Le code  et l'interface sont plutôt ajustable pour convenir a des quelconques changements de projet.
  
    ***  

  
## Séance du 07 Février
 
 - PROBLEME   Face au trajet durant la semaine de ski, le laser a du faire un faux contact avec les piles probablement.
 
 - Tentative de ressoudage des soudures en vain.
 
 - Comparaison de l'impédance totale du laser avec l'impédence d'un laser fonctionel de même marque.  
 On remarque que les impédences sont totalement différentes (laser test de l'ordre de la dizaine d'Ohms, laser fonctionel de l'ordre du méga Ohms)
 
 - Solution : pret d'un nouveau laser pour continuer le projet.
 
   ***  

 
 ## Travail personel entre les séances  
 
  - Remise en état de la tourelle, mais problèmes de précision ainsi que de montage concernant cette dernière. En effet fixer stablement et précisement le laser sur la tourelle est délicat. Les cables reliant le laser au module arduino sont peu souples et tirent lors des changement d'orientation pouvant potentiellement troubler les mesures.
 
   ***  

## Séance du 21 Février

  - Changement de voie pour les mesures télémétriques du robot. 
  
  - En effet la tourelle munie d'un servo moteur permet d'effectuer environs 3 mesures par secondes avec une précision à revoir (stabilité sur la tourelle).
  
  - Mr P. Masson a commandé un Lidar pour tester cette posibilité.  
  Le lidar permetrai des mesures en "continu" et sur un axe en rotation continu. Cela augmenterai la rapidité de cartographie de notre systeme.
  
  - Les avantages :
    + Beaucoup plus de mesures effectuées.
    + Une meilleure précision grace à un nombre plus conséquent de mesures.
    + Lidar en rotation sur un axe. Cette rotation s'effectuera avec un moteur à rotation continu et une roue codeuse (pour savoir la vitesse angulaire du Lidar).
  
  - Les désavantages sont :
    + Une moins bonne précision et capacité de mesure des distances (12 m pour le Lidar, 40m pour le laser actuel). 
    + Mise en place d'une tourelle à rotation.
    + Transfert difficile pour les câbles (gestion de l'entortillement des câbles du lidar sur la tourelle).
  
  - La solution pour cette dernière difficultée est de peut être d'utiliser un slip-ring pour faire passer les cables.
  
  ***
  
## Travail personel entre les séances  
 
  - Peu de travail fut fourni sur la tourelle entre ces deux séance, j'étais en attente des pieces. Donc j'ai profité pour améliorer le code Processing. 
  
  - Arrivé du lidar peu de temps avant la scéance du 28 Mars.
  
  ***
  
## Séance du 28 Mars
  
  - Récupération d'un lidar monté sur deux servo moteur. 
  
  <img src="/documentation/Images/lidar.jpg" height="200"/> 
  
  - Ce Lidar n'est pas monté sur un moteur à rotation continue, il n'a donc pas besoin de slip ring pour faire passer les câbles. 
  
  - Lidar rapide (100Hz) mais la vitesse d'execution stable est plus lente environ 60Hz. 
  
  - Le lidar beug parfois et affiche une valeur en boucle pendant une centaine de mesures, problème à corriger par la suite.
  
  - Mais avant tout ce Lidar est bien mieux adapté à notre projet.
  
  - Il reste maintenant à bien adapter le fonctionnement de ce lidar au code déjà existant. Puis il faut que j'attaque les communications RF.
  
  
   ***
  
## Séance du 05 Avril 

  - Présentation de l'avancement de notre projet au reste du groupe. La voici : <a href="documentation/Slam_arduino_bot_mi-parcours.pdf" > ici </a>.
  
  - Problèmes de mesure avec le lidar. Il y a des sursaut avec le lidar de plus l'arduino mega a parfois du mal à gérer le servos moteurs aisi que les mesures.
  
 ***
  
## Travail personel entre les séances 

  - Début de construction du module RF reliant le robot à l'ordinateur. Pour cela nous allons changer un peu le le schéma de notre projet. En effet, vu le débit d'informations possibles à passer, nous allons utiliser la carte ESP 32 avec son port wifi. Le robot pourra donc immédiatement communiquer avec l'ordinateur avec une communication wifi. Le robot et l'ordinateur seront dans un premier temps connecté à un réseau commun.
  

  
  ***
  
## Séance du 10 Avril 

  - Continuité de la télécomunication wifi avec la carte esp32. 
   - Fin du module laser ! Le lidar marche enfin (presque à la perfection) et le code d'affichage est opérationnel. 
   <img src="/documentation/Images/tracé.jpg" height="200"/>

  
***
  
## Travail personel entre les séances 

  - Travail long et fastidieux sur la carte esp32.

  - L'utilisation de la carte esp 32 est difficile au début. En effet elle demande pas mal de documentation sur son paramétrage avec l'IDE arduino. De plus la connexion Wifi n'est pas très facile à gérer et demande beaucoup de temps.
  
  - Fin de la communication Wifi entre la carte esp 32 et processing. Pour cela, la carte esp 32 va se connecter à l'ip de l'ordinateur et arriver sur le server processing. Le code sur processing est très similaire à n'importe quel serveur java. Pour optimisation, on va d'abord connecter les deux éléments ensemble avec un mot de passe etc. Puis par soucis d'éfficacité, n'envoyer que les informations nécessaires par wifi.
  Cette partie m'a pris beaucoup de temps et d'investissement car elle a été difficile à cerner, puis à réaliser avec de nombreux diffonctionnements entre les connexions avec un hotspot wifi. 
  
    ***
  
## Séance du 04 Mai

  - Harmonisation du code du serveur processing, et du code de traçage de la carte en 2d.
  - Optimisation de l'application.
  
  ***
  
## Travail personel entre les séances 

  - Améliorations des échanges entre l'esp32 et l'application processing.
  
  - Création d'une simulation de nuage de points avec l'esp32 à distance.
  
   ***
  
## Séance du 14 Mai
  
  - Soudure des pins de l'esp32.
  
  ***
## Travail personel final 

  - Harmonisation finale des deux cartes (méga et esp32). Cette tâche fut de loin la plus dure et la plus compliquée. Elle fait intervenir plusieurs éléments avec beaucoup de lignes de code. Une capacité d'abstraction et de prise de recule fut nécessaire pour faire face aux problèmes rencontré. 
  
  - Au final, la connexion série entre l'esp32 et la Méga pose beaucoup de problèmes. Après de nombreusess heures à être passé à essayer de recabler ou de filtrer les données transmises. Nous n'avons pas reussi à gerer cette petite liaison qui aura causé la chute de notre projet. 
  <img scr="/documentation/Images/IMG_1142.jpg" height="200"/>
  
   
