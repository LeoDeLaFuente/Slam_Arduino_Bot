![Polytech](http://www.polytechnice.fr/jahia/jsp/jahia/templates/inc/img/polytech_nice-sophia.png)

Ce projet est réalisé dans le cadre de la formation de prépa intégrée de Polytech'Nice Sophia
* * *
# Slam Arduino Bot
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Projet école de création d'un robot arduino permettant la cartographie d'une salle sans données GPS.

## Présentation
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Ce projet à pour but de réaliser une carte (2D) d'une salle à l aide d'un robot se déplaçant dans cette pièce et réalisant des mesures graçe à un télémètre Laser. Ce robot sera dans un premier temps dirigé par utilisateur graçe à un ordinateur et une connexion sans fil. Nous utiliserons pour cela le logiciel processing permettant de traiter les données, afficher la carte et interpréter les commandes de l'utilisateur.

![logo Processing](/Images/processing3-logo.png) ![logo ROS](/Images/rosLarge.png) 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Le but ultime de ce projet serait que le robot se déplace de manière autonome dans la pièce. Cette technique appelé SLAM (Simultaneous Location and Mapping Robot) est très complexe, et c'est pourquoi nous utiliserions le l'outil ROS (qui est une surcouche de Linux permettant lacréation de logiciel pour la robotique) qui est très utilisé dans le domaine des robots et comporte des bilbliotèque open sources de SLAM. Nous plaçons cette partie de projet dans un second plan, car c'est une partie très informatique (le cours est de base axé sur la création d'un projet arduino), et ROS est un outils très complexe qui nous ai pour l'instant inconnue.  

# Mise en place du schéma

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Suite à la séance du 21 Décembre 2017 nous avons créé un schéma récapitulatif du projet.

![Schéma projet](/Images/schéma.jpeg)
