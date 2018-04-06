
*******************
# Compte rendu 
*******************
## Présentation

Ce projet réalisé dans le cadre de notre cours d'arduino en PEIP2 de l'école Polytech Nice-Sophia (prépa intégré) consiste à conevoir un robot permettant de cartographier une salle. Nous allons pour cela utiliser une carte arduino.

## Seance du 21 Décembre
 - ##### Création du projet sous Github pour la remise des comptes rendus ainsi que le dépot de nos codes.
 - ##### Mise en place du projet
 - ##### Commencement de la mise en place de la liste du materiel
 - ##### Création du schéma du projet
 ![Schéma projet](/documentation/Images/Schéma_wifi_lora.jpg)

 
 ## Travail personnel du 22 Décembre
 
  - ##### Commencement du [dessin 3d du robot](/robot) sous Autocad Inventor 
  La Base du robot sera constitué de deux planches en bois découpé à la découpe laser et reliés par quatre entretoises (en PVC ou métal). Un servomoteur sera placé sur la planche du dessus pour ensuite placer le télémetre laser dessus. Nous n'avons pas encore reçus les roues codeuses, et je n ai pas trouvé d'image 3D de celles-ci pour l'instant.
  
![Robot en 3D](/documentation/Images/robot_1.png)

## Seance du 10 Janvier 

 - ##### Reception du laser
 Notre professeur nous as soudé une alimentation permettant de faire fonctionné le Laser avec deux piles AA, ainsi ques les fils sur le pins Rx et Tx du laser. Félix à ainsi commencé a réaliser le code permettant de faire des mesures en boucle.
 
 - ##### Travail sur le servomoteur
  Le servomoteur que nous avons à disposition est un servomoteur étant sensé faire 180°.La rotation à 360° aurait été préférable, mais les servomteur pouvant réaliser des tours à 360° ne sont pas réellement des servomoteurs, ce sont des moteurs se comportant comme des moteurs à courant continues. Nous avons donc prévu d utiliser notre servomoteur de 180° et de demander à notre robot de faire un demi-tour sur lui meme si l 'on veux réaliser des points tout autour.  
Après avoir tester notre servomoteur 180°  nous avons constaté qu' il ne fait qu'environ 160° (amplitude exacte à définir.) Nous allons donc continuer avec celui-ci pour l instant, mais nous allons aussi surement voire pour commander un servomoteur effectuant 270° [comme celui-ci](https://fr.aliexpress.com/item/DOMAN-RC-DM-S0603D-40g-0-14s-5-5kg-cm-plastic-gear-300degree-robot-6kg-digital/32231859181.html?spm=a2g0w.search0306.3.131.799e1c75vhheSy&ws_ab_test=searchweb0_0,searchweb201602_0_10152_10151_10613_10615_10614_10059_10314_10534_10084_100031_10083_10184_10305_10304_10307_10604_10306_10341_10065_10142_10340_10068_10343_10342_10103_10344_10302,searchweb201603_0,ppcSwitch_0&algo_pvid=1373983d-8d1d-41ea-bd80-e2dcfdbb8e0c&algo_expid=1373983d-8d1d-41ea-bd80-e2dcfdbb8e0c-20). 

## Séance du 19 Janvier

- ##### Reception des moteurs à roues codeuses
 Ayant reçu nos moteurs, je me suis penché sur leur fontionnement à l'aide d'un pont en H (L298N). Ce dernier permet de controler deux moteurs.  
 
 <img src="/documentation/Images/pont_en_h_.JPG" alt="pont en h" height= 350px>
 <img src="/documentation/Images/roue_codeuse_1_.JPG" alt="moteur à roues codeuses" height= 350px>
  <img src="/documentation/Images/roue_codeuse_2_.JPG" alt="moteur à roues codeuses" height= 350px>
 
 Nous appliquons une tension de 12V grâce à un générateur de tension pour nos tests. La mise en place du fonctionnement des moteurs à pris beaucoup de temps car j'avais utilisé un fil défaillant. Après avoir trouvé l'erreur, l'exécuion du programme permet defaire fonctionner les moteurs dans le sens voulu et de les arréter grâce aux touches du clavier. Nous avons récupéré le code présent sur [ce site](http://www.instructables.com/id/Arduino-Modules-L298N-Dual-H-Bridge-Motor-Controll/), ainsi que suivi les instructions. Ce programme m'as ainsi permit de comprendre comment fonctionne les moteurs pour pouvoir dévelloper le code qui va servir à diriger le robot.
 Il faut maintenant récupérer le signal des roues codeuses pour connaitre précisément la rotation des moteurs.  
 
 ## Séance du 22 Janvier
 
 - ##### Pésentation de notre projet devant nos deux professeur et notre classe.
 [La présentation est visible ici](https://github.com/LeoDeLaFuente/Slam_Arduino_Bot/blob/master/documentation/Slam_arduino_bot_presentation.pdf)
 
 - ##### Soudure des cables des roues codeuses.
 J ai effectué des soudure sur les fils des roues codeuse pour permettre le branchement sur notre plaque de test et relié ainsi le codage à l'arduino.
 
 ## Séance du 6 Fervier
 
 - #### Fonctionnement des roues codeuse.
  J ai fait plusieurs recherches pour trouver comment cabler la roue codeuse, et est trouvé un schéma qui n'était pas bon est qui a grillé les roues codeuse ( celle ci fontionne avec des leds, et je n'avait pas mis de résistances, sachant que le circuit de la roue codeuse n'en contient pas). J ai pu récupéré une roue codeuse avec un circuit de protection intégré qui fonctionne avec l'arduino. Il faut maintenant écrire le code permettant d'utiliser cette dernière, et acheter une seconde roue codeuse.
  
## Travail personnel du 9 Février

- #### Codage roue codeuse.
  J'ai réalisé un code ("moteur_execution") permettant defaire tourner une roue sur une longueur demandé en cm. Le programme prend donc une longueur l en cm, la convertit en "tour de roue", puis fais tourner la roue en comptant le nombre de tour graçeà la roue codeuse.


## Séance du 21 Février
- #### Fabrication du premier robot en carton.
 J'ai fabriqué le premier essai de robot en carton. Celui-ci va me permettre de faire premiers essai avec les roues codeuses et d'améliorer le fonctionnement de mon code.
 
<img src="/documentation/Images/robot_carton_1.jpg" height=300px alt="premier robot en carton" />


## Travail personnel du 22 Février
 - #### Mise en route du robot
    Après avoir récupéré une roue codeuse sur un robot d'un autre groupe qui ne s'en servait pas, j ai commencé à faire les essais pour faire tourner les roues du robot en même temps et commencer à programmer les mouvements élémentaires du robot. Je me suis aperçu que mes moteurs tournaient lentement, et pense que celà est dû au fait que j'alimente le pont en H et l'arduino avec la même pile de 9v qui n'est pas assez puissante.
    
## Séance du 12 Mars
 - #### Changement du support du robot
   J'ai récupéré un support différent permettant de faire de vrai test sur les déplacements du robot, mais il faut réadapter les moteurs pour qu'ils se fixent sur le support.
 
 ## fab lab le 20 Mars
 - #### Création d'une pièce d'adaptation
  J'ai réalisé à l'aide de la découpe laser une pièce permettant d'adaptater les moteurs à des equerres pour fixer le tout au support du robot. Il manque juste des rivets et la fixation sur le support.
  
 ## Séance du 28 Mars
 
 - #### Mouvements élémentaire
  J'ai réalisé une fonction permettant de faire avancer et reculer le robot, mais je n'ai pas pu le tester, car le robot n'est pas fini d'être monté. Je me suis par contre aperçu que les deux moteurs ne tournent pas à la même vitesse. Il va donc falloir réaliser un asservissement en vitesse sur les moteurs.
  
 ## fab lab le 3 Avril
 
 - #### Fixation des pièces avec rivets
 Après avoir acheté les rivets, je suis allé au fab lab pour fixer les moteurs aux equerres graçe aux pièces réalisé le 20 Mars. J ai aussi commencé à percer le support pour assembler les équerres au support.

 <img src="/documentation/Images/29995243_1791994864186311_792137066_o.jpg" height="300" alt="assemblage equerre et moteur" /> 
 
 ## séance du 5 Avril
 
 - #### Présentation de mi-parcous auprès de nos professeur. 
 [Celle-ci est visible ici](https://github.com/LeoDeLaFuente/Slam_Arduino_Bot/blob/master/documentation/Slam_arduino_bot_mi-parcours.pdf). Elle nous a permit de rédéfinir notre planning et de faire le point sur notre projet.
 
 - #### Fixation des moteurs+équerres sur le support. 
 J ai rivetté les equerres sur le support, ce qui m'a permis de placer l'arduino et la batterie et de recabler le tout. 
 
 [Voici la vidéo du premier branchement](https://youtu.be/iydBeL7KhAE).
 
 Il manque un pièce sur le devant pour surélever au dessus de la roue folle pour que le support reste bien plat, mais celui-ci n'est pas necessaire pour coder les déplacements du robot.
 
 
 ## fab lab et travail personnel du 6 Avril
 
 - #### Création de la dernière pièce manquante pour le robot : une pièce en bois se situant entre le support et la roue folle pour que le dessus du robot soir de niveau.
 <img src="/documentation/Images/piece_bois.jpg" alt="pièce en bois réalisé" rotate="260" height=300px />
 
 - #### Dévellopement du code sur le robot
 Le robot peut maintenant être commandé pou se déplacer en ligne droite sur une certaine distance, reculer, et tourner sur lui même dans les sens horaire et anti-horaire. [Cette vidéo montre les déplacements pouvants être effectués](https://youtu.be/h0HItliRpBA). On remarque que le robot ne se déplace pas en ligne bien droite, et que les tours sur lui même ne respectent pas bien les angles demandés (180 degrés puis 360 degrés). Cela est dû au fait que les moteurs ne tournent pas à la même vitesse. Il faut donc améliorer cela.
 
 - #### Recherche sur l'asservissement PID
  En effectuant des recherche sur l'asservissement des moteurs, j ai trouvé un code permettant de réaliser un asserviement PID, mais je n'arrive pas à adapter les constantes de proportionalité, de dérivation et d'intégration à nos moteurs.
 
 

 
