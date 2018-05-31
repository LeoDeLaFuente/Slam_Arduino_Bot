float x=400, y=300, l=200, q=400, s=300, f=400, a=400, z=300, r=600;

float i=300, j=300, p=600, o=450, c=400, w=300, t=20;

int b=0, g=400, h=300, tf=800, TF=600;


void setup()

{

  size(600,800);

  background(255);

}


void draw()

{

  nettoyer();

  bouger();

  lignesentrecarres();

  carre();

  nitro();

}


void nettoyer()

{

  background(0);

}


void bouger()

{

  println(b);

  background(0);  

  l=l+2;

  f=f+2;

  r=r+2;

    

  if (l>600)

  {

   l=0;

   b=b+1;//compteur

  } 

  if (f>600)

  {

   f=0;

   b=b+1;

  } 

  if (r>600)

  {

   r=0;  

   b=b+1;

  } 

  

  //gauche - droite

  if (b >= 4 && b <= 5)

  {

    x=x+.3;

    q=q+.5;

    a=a+.7;

  }

  

  if (b >= 6 && b <= 7)

  {

    x=x-.3;

    q=q-.5;

    a=a-.7;

  }

  

  //haut-bas

  if (b >= 9 && b <= 10)

  {

    y=y+.7;

    s=s+.5;

    z=z+.3;

  }

  

  if (b >= 11 && b <= 12)

  {

    y=y-.7;

    s=s-.5;

    z=z-.3;

  }

  

}


void lignesentrecarres()

{

  //lignes des coins 

  stroke(255);

  if (f > l & f > r)

   {

     line(0,600,q-(f/2),s+(f/2));

     line(800,600,q+(f/2),s+(f/2));

     line(0,0,q-(f/2),s-(f/2));

     line(800,0,q+(f/2),s-(f/2));

   }

  

  if (f < l & f < r && l > f && l > r)

  {

    line(0,600,x-(l/2),y+(l/2));

    line(800,600,x+(l/2),y+(l/2));

    line(0,0,x-(l/2),y-(l/2));

    line(800,0,x+(l/2),y-(l/2));

   }

   

   else if (r > l && r > f)

   {

     line(0,600,a-(r/2),z+(r/2));

     line(800,600,a+(r/2),z+(r/2));

     line(0,0,a-(r/2),z-(r/2));

     line(800,0,a+(r/2),z-(r/2));

   }

   

   //lignes entre carre 1 et2

   if (f > l & f > r)

   {

     //entre f et l

     line(q-(f/2),s+(f/2),x-(l/2),y+(l/2));

     line(q+(f/2),s+(f/2),x+(l/2),y+(l/2));     

     line(q-(f/2),s-(f/2),x-(l/2),y-(l/2));

     line(q+(f/2),s-(f/2),x+(l/2),y-(l/2));

   }

  

  if (f < l & f < r && l > f && l > r)

  {

     //entre r et l

     line(a-(r/2),z+(r/2),x-(l/2),y+(l/2));

     line(a+(r/2),z+(r/2),x+(l/2),y+(l/2));     

     line(a-(r/2),z-(r/2),x-(l/2),y-(l/2));

     line(a+(r/2),z-(r/2),x+(l/2),y-(l/2));

   }

   

   else if (r > l && r > f)

   {

     //entre f et r 

     line(q-(f/2),s+(f/2),a-(r/2),z+(r/2));

     line(q+(f/2),s+(f/2),a+(r/2),z+(r/2));      

     line(q-(f/2),s-(f/2),a-(r/2),z-(r/2));

     line(q+(f/2),s-(f/2),a+(r/2),z-(r/2));

   }

     

     //lignes entre carre 2 et 3

     if (f > l & f > r)

   {

     //entre l et r 

     line(a-(r/2),z+(r/2),x-(l/2),y+(l/2));

     line(a+(r/2),z+(r/2),x+(l/2),y+(l/2));     

     line(a-(r/2),z-(r/2),x-(l/2),y-(l/2));

     line(a+(r/2),z-(r/2),x+(l/2),y-(l/2));

   }

   

  if (f < l & f < r && l > f && l > r)

  {

     //entre r et f

     line(q-(f/2),s+(f/2),a-(r/2),z+(r/2));

     line(q+(f/2),s+(f/2),a+(r/2),z+(r/2));      

     line(q-(f/2),s-(f/2),a-(r/2),z-(r/2));

     line(q+(f/2),s-(f/2),a+(r/2),z-(r/2));

   }

   

   else if (r > l && r > f)

   {

     //entre f et l 

     line(q-(f/2),s+(f/2),x-(l/2),y+(l/2));

     line(q+(f/2),s+(f/2),x+(l/2),y+(l/2));     

     line(q-(f/2),s-(f/2),x-(l/2),y-(l/2));

     line(q+(f/2),s-(f/2),x+(l/2),y-(l/2));

   }

   

   //lignes entre carres 3 et fixe

   if (f < l & f < r)

   {

     //entre f et fixe 

     line(q-(f/2),s+(f/2),c-(t/2),w+(t/2));

     line(q+(f/2),s+(f/2),c+(t/2),w+(t/2));     

     line(q-(f/2),s-(f/2),c-(t/2),w-(t/2));

     line(q+(f/2),s-(f/2),c+(t/2),w-(t/2));

   }

   

  if (r < f & r < l)

  {

     //entre r et fixe

     line(c-(t/2),w+(t/2),a-(r/2),z+(r/2));

     line(c+(t/2),w+(t/2),a+(r/2),z+(r/2));      

     line(c-(t/2),w-(t/2),a-(r/2),z-(r/2));

     line(c+(t/2),w-(t/2),a+(r/2),z-(r/2));

   }

   

   else if (l < r && l < f)

   {

     //entre l et fixe

     line(c-(t/2),w+(t/2),x-(l/2),y+(l/2));

     line(c+(t/2),w+(t/2),x+(l/2),y+(l/2));      

     line(c-(t/2),w-(t/2),x-(l/2),y-(l/2));

     line(c+(t/2),w-(t/2),x+(l/2),y-(l/2));

   }

   }

   

 void carre()

{

  line (x-(l/2),y-(l/2),x+(l/2),y-(l/2));

  line (x+(l/2),y-(l/2),x+(l/2),y+(l/2));

  line (x-(l/2),y-(l/2),x-(l/2),y+(l/2));

  

  line (q-(f/2),s-(f/2),q+(f/2),s-(f/2));

  line (q+(f/2),s-(f/2),q+(f/2),s+(f/2));

  line (q-(f/2),s-(f/2),q-(f/2),s+(f/2));

  

  line (a-(r/2),z-(r/2),a+(r/2),z-(r/2));

  line (a+(r/2),z-(r/2),a+(r/2),z+(r/2));

  line (a-(r/2),z-(r/2),a-(r/2),z+(r/2));

  

  //carre fixe

  line (c-(t/2),w-(t/2),c+(t/2),w-(t/2));

  line (c+(t/2),w-(t/2),c+(t/2),w+(t/2));

  line (c-(t/2),w-(t/2),c-(t/2),w+(t/2));

}



void nitro()

{

 if (key == 'a')

   {

     frameRate(1000);

    }

  else if (key == 'z')

  {

    frameRate(60);

  }

}


void departarrivee()

{

  if (b > 0 && b < 1)

  {

    PFont maTypo = loadFont("Stencil-48.vlw"); // choix de la typo

textFont(maTypo, 64);  // Définition de la taille de la typo

text(" Départ",250,270);

  }

  

  if (b >= 20)

  {

    PFont maTypo = loadFont("Stencil-48.vlw"); // choix de la typo

    textFont(maTypo, 64);  // Définition de la taille de la typo

    text("Arrivée",270,270);

    l=l;

    f=f;

    r=r;

  }

}


void recommencer()

{

  if (keyPressed)

  {

    if (key == ENTER)

    {

      loop();

      b=1;

      l=l+3;

      f=f+3;

      r=r+3;

    }

  }

}