![Polytech](http://www.polytechnice.fr/jahia/jsp/jahia/templates/inc/img/polytech_nice-sophia.png)

Ce projet est réalisé dans le cadre de la formation de prépa intégrée de Polytech'Nice Sophia
* * *
# Mapping with an Arduino Robot
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Projet école de création d'un robot arduino permettant la cartographie d'une salle sans données GPS.

## Présentation

Slam Arduino Bot est un petit véhicule permettant de cartographier son environnement sans données GPS. 
Le robot est contrôlé par un utilisateur depuis un ordinateur. Il se déplace, mesure des distances et transmet les données. Du côté de l’ordinateur, une application traite les données reçues, trace la carte 2D en fonction des données et envoie les ordres au robot.
Au début du fonctionnement, le robot s’initialise puis se connecte à l’application de l’utilisateur par wifi. Puis le robot commence à réaliser des mesures afin de scruter sont environnement. Il transmet les données à l’application qui les traites, et affiche la carte réalisée.  L’application attend les ordres de l’utilisateur concernant ses déplacements. Après avoir effectué les déplacements nécessaires, le robot va réaliser de nouvelles mesures et ainsi de suite.

![Photo du robot](/documentation/Images/robot_final.jpg) 
  
Ce projet est principalement réalisé avec une carte arduino Mega pour le robot et le logiciel processing pour l'application du coté ordinateur.

![Logo Processing](/documentation/Images/processing3-logo.png) 
