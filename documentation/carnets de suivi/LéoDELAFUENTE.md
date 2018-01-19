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
 ![Schéma projet](/documentation/Images/Schéma.jpg)

 
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

##Séance du 19 Janvier

- ##### Reception des moteurs à roues codeuses
 AYnat reçu nos moteurs, je me suis penché sur leur fontionnement à l'aide d'un pont en H (L298N). Ce dernier permet de controler deux moteurs. 
 <img src="/documentation/Images/pont_en_h.JPG" alt="pont en h" height= 350px>
 <img src="/documentation/Images/roue_codeuse_1.JPG" alt="moteur à roues codeuses" height= 350px>
  <img src="/documentation/Images/roue_codeuse_2.JPG" alt="moteur à roues codeuses" height= 350px>
 
 Nous appliquons une tension de 12V grâce à un générateur de tension pour nos tests. La mise en place du fonctionnement des moteurs à pris beaucoup de temps car j'avais utilisé un fil défaillant. Après avoir trouvé l'erreur, l'exécuion du programme permet defaire fonctionner les moteurs dans le sens voulu et de les arréter grâce aux touches du clavier. Nous avons récupéré le code présent sur [ce site](http://www.instructables.com/id/Arduino-Modules-L298N-Dual-H-Bridge-Motor-Controll/), ainsi que suivi les instructions. Ce programme m'as ainsi permit de comprendre comment fonctionne les moteurs pour pouvoir dévelloper le code qui va servir à diriger le robot.
 Il faut maintenant récupérer le signal des roues codeuses pour connaitre précisément la rotation des moteurs.
