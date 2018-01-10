<h1> Explication du module laser </h1>
Cette page est consacrée a l'utilisation du laser.  
<ul>
<li><h3>1-Présentation</h3>
&nbsp;&nbsp;&nbsp;Pour ce projet nous utilisons le laser <a href="https://fr.aliexpress.com/item/50m-164ft-Laser-Distance-Measuring-Sensor-Range-Finder-Module-Low-cost-Diastimeter-Single-Continuous-Measurement/32792768667.html?spm=a2g0w.10010108.1000013.1.51f42bb0M1R4Ws&traffic_analysisId=recommend_2088_1_90158_iswistore&scm=1007.13339.90158.0&pvid=f9d4958f-2d6c-4487-9ee1-a3cd3a2b37b9&tpp=1">hi50</a> de la marque HIREED.<br/>
&nbsp;&nbsp;&nbsp;Il se presente sous la forme d'un petit boitier de taille 45*25*12mm. La mesure de distance maximale est de 50m pour une precision de 1mm.<br/>
<img src="/documentation/Images/laser.jpg" alt="photo_lazer" height="500"/><br/>
 &nbsp;&nbsp;&nbsp;Il faut faire attention à la réflexion du laser sur les surfaces réfléchissantes. En effet le laser peut avoir des erreurs sur la distance mesurée voir pas de données mesurées.<br/>
 Cela peut arriver sur des vitres ou miroirs, mais aussi sur des surfaces de type carlage, ou plastique lisse non opaque avec un angle de réflexion très grand.
</li>
<hr/>
<br/>
<li><h3>2-branchements</h3>
   Les branchements s'effectuent de la manière suivante :
<img src="/documentation/Images/cablage_laser.jpg" alt="Image cablage" height="500"/><br/>
On effectue donc une liason serie TX-RX avec l'arduino.<br/>
Pour l'alimentation, on branche la masse à la masse commune du Robot, et le positif à 2 piles de 1,5 V.<br/>
<img src="/documentation/Images/pile.jpg" alt="piles" height="500"/><br/>
&nbsp;&nbsp;&nbsp;Le laser s'utilise simplement en envoyant un caractere via liaison serie. 
On envoi le charactère 'D' pour une mesure lente et 'F' pour une mesure rapide.<br/>
La mesure rapide s'effectue à une vitesse d'un peu plus de 0,3 sec (0,31 s) car 0,3 précisement provoque une erreur lors du transfer des données.


