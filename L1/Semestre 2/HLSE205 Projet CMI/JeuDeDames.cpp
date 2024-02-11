//Bibliothèques utilisé
#include <iostream>
#include <string>
#include <unistd.h>
#include <ctime>

//Pour ne pas avoir à toujours marquer "std"
using namespace std;

//Declaration des fonctions
  void DeuxiemeCoup(int y, int x); //Ligne 499
  bool prenable(int y, int x); //Ligne 26
  void update(int n, int y0, int x0, int y1, int x1); //Ligne 97
  void Jeu(); //Ligne 352
  void PlateauInitiale(int *Damier); //Ligne 547
  void Affiche(int *Damier); //Ligne 609
  bool Victoire(bool player); //Ligne 579
  void AI(); //Ligne 169
  //int main() Ligne 641

//Déclaration des variables globales
  int Damier[10][10]; //Le Damier est une matrice de 10 par 10
  bool player = 1; //Si player vaut 1, alors c'est les blancs qui joue, sinon c'est les noirs.
  bool IA = 1; //Si l'IA est activé ou non, elle l'est pas défault
  bool CouleurIA = 0; //On sauvegarde la couleur de l'IA (1 pour blanc et 0 pour noir, par défault : noir)

bool prenable(int y, int x)
{
  //Cette fonction a pour objectif de savoir si un pion (ou dame) peut prendre un pion (ou dame) adverse. Elle prend en paramètre les coordonnés de ce pion sous la forme (ligne, colonne).
  //Selon quel joueur joue, on change la valeur des pions
  int P_allie, P_ennemi, D_allie, D_ennemi, coef; //Ses valeurs vont représenter les pions alliés, enemis, les dames alliés et enemi.
  //Ces variables dépendent de quel couleur joue.
  //1 = pion blanc
  //2 = pion noir
  //3 = dame blanche
  //4 = dame noire
  if (player == 1)
  {
    P_allie = 1; P_ennemi = 2; D_allie = 3; D_ennemi = 4;
    coef = -1;
  }
  else
  {
    P_allie = 2; P_ennemi = 1; D_allie = 4; D_ennemi = 3;
    coef = 1;
  }
  //On vérifie que le pion entré est bien un pion possédé par le joueur
  if( (Damier[y][x] == P_allie) || (Damier[y][x] == D_allie))
  {
    //Supposons d'abord que ce soit un pion ou une dame qui avance
    //On vérifie que le pion peut bien avancer sur le terrain et n'en sortira pas en prenant, ici, dans la diagonale droite. On vérifie aussi que la case de derrière soit vide.
    if (!((y+coef < 0) || (y+coef > 9) || (y+2*coef < 0) || (y+2*coef > 9) || (x+1 > 9) || (x+2 > 9)) )
    {
      //La diagonale droite contient-elle une case ennemi ?
      if ( (Damier[y+coef][x+1] == P_ennemi) || (Damier[y+coef][x+1] == D_ennemi) )
      {
        if (Damier[y+2*coef][x+2] == 0) //Y a t-il une case libre derrière ?
        { return true;} //Si toutes ces conditions sont vérifié, alors oui, cette case peut prendre un pion
      }
    }
    //On effectue exactement la même chose pour la diagonale droite
    if (!((y+coef < 0) || (y+coef > 9) || (y+2*coef < 0) || (y+2*coef > 9) || (x-1 < 0) || (x-2 <0)) )
    {
      if ( (Damier[y+coef][x-1] == P_ennemi) ||  (Damier[y+coef][x-1] == D_ennemi) ) 
      {
        if (Damier[y+2*coef][x-2] == 0)
        { return true;}
      }
    }

    //On va maintenant supposer que c'est une dame
    if (Damier[y][x] == D_allie) //On vérifie d'abord si c'en est une.
    //Puis on effectue exactement le même raisonnement mais dans le sens opposé (-).
    { //Diagonale droite
      if (!(y-coef < 0) || (y-coef > 9) || (y-2*coef < 0) || (y-2*coef > 9) || (x+1 > 9))
      { if ( (Damier[y-coef][x+1] == P_ennemi) || (Damier[y-coef][x+1] == D_ennemi) ) 
        { 
          if (!(x+2 > 9))
          {if (Damier[y-2*coef][x+2] == 0)
            {return true;}
          }
        }
        //Diagonale gauche
        if (!((y-coef < 0) || (y-coef > 9) || (y-2*coef < 0) || (y-2*coef > 9) || (x-1 < 0)))
        {
          if ( (Damier[y-coef][x-1] == P_ennemi) || (Damier[y-coef][x-1] == D_ennemi)   )
          { if (!(x-2 < 0))
            { if (Damier[y-2*coef][x-2] == 0)
              {return true;}
            }
          }
        }
      }
    }   
  } return false; //Si on a rien trouvé, c'est qu'il n'y a pas de pion prenable
}

void update(int n, int y0, int x0, int y1, int x1)
{
  //Cette fonction a pour objectif de mettre à jour la plateau de jeu en fonction des informations transmises par la fonction jeu.
  //Il s'agit d'une fonction aveugle : elle ne fait aucune vérification et se contente de faire les changements.
  //Elle prend en paramètre les coordonnées de la case d'origine (x0,y0) et celle de la case d'arrivé (x1,y1) mais aussi un code symbolisé par l'entier n.
  //En effet, n=1 => déplacement simple alors que n=2 => prise d'un pion.
  int memoire; //mémoire qui servira à sauvegarder la valeur de la case plus tard
  if (n==1) //Dans le cas d'un déplacement
  {
    Damier[y1][x1] = Damier[y0][x0]; //L'origine prend la valeur de l'arrivé
    Damier[y0][x0] = 0; //L'origine est maintenant vide.
    if (player == 1) //Si c'est le joueur blanc
    {
      if (y1 == 0) //Et qu'il est arrivé tout en haut du plateau
      {Damier[y1][x1] = 3;} //Son pion devient une dame
    }
    else //Sinon, c'est le joueur noir
    {
      if (y1 == 9) //Et s'il est arrivé en bas du plateau
      {Damier[y1][x1] = 4;} //Son pion deivent une dame
    }
    player = !player; //On passe ensuite à l'autre joueur
  }

  else if (n==2) //Dans le cas d'une prise
  {
    Damier[y1][x1] = Damier[y0][x0]; //La destination prend la valeur de l'origine
    Damier[y0][x0] = 0; //L'origine est vide
    Damier[(y1+y0)/2][(x1+x0)/2] = 0; //On calcul les coordonnées du pion pris (que l'on ne connait donc pas) grâce à la moyenne de la destionation et de l'origine. On met cette valeur à 0 puisque cette case est désormais vide.
    //Même raisonnement pour les dames
    if (player == 1)
    {
      if (y1 == 0)
      {Damier[y1][x1] = 3;}
    }
    else
    {
      if (y1 == 9)
      {Damier[y1][x1] = 4;}
    }
    //On veut vérifier si le joueur peut enchainer avec un deuxième coup
    //Pour cela, on va executer prenable, cependant prenable, pour un pion, ne vérifie que si celui-ci peut prendre en avant or dans une double prise, un pion peut reculer.
    //On va donc transformer momentanément cette case en une dame, executer prenable, puis repasser à son état d'origine avant qu'elle ne soit affiché. (Le joueur ne voit donc rien)
    memoire = Damier[y1][x1]; //On stock la veleur de la case
    if (player == 1) //Si c'est le blanc
    {
      Damier[y1][x1] = 3; //ça devient une dame blanche
    }
    else //Sinon, c'est que c'est le noi
    {
      Damier[y1][x1] = 4; //Donc on met une dame noire
    } 
    //Pour rappel
    //1 = pion blanc
    //2 = pion noir
    //3 = dame blanche
    //4 = dame noire
    if (prenable(y1,x1)) //On execute donc prenable
    { 
      //Si c'est vrai
      Damier[y1][x1] = memoire; //On remet dans tout les cas la case à sa valeur de base
      DeuxiemeCoup(y1,x1); //On lance la focntion deuxième coup
    }
    else
    {
      //Sinon
      Damier[y1][x1] = memoire; //On remet dans tout les cas la case à sa valeur de base
      player = !player; //On passe au joueur suivant
    }
  }
}

void AI()
{
  //Ceci est l'intelligence artificiel qui peut être activé ou non dans le menu Option
  //Son fonctionnement et son algorithme est détaillé dans le rapport
  int i,j; //Déclaration des variables pour les boucles
  int P_allie, D_allie, P_ennemi, D_ennemi; //Déclaration habituelles des pions ennemis et alliés
  int nb_element_prenable = 0; //Pour compter le nombre d'élément prenable
  int decallage;

  if (CouleurIA == 1) //Si l'IA est le joueur blanc
  {
    decallage = 1;
    P_allie = 1; P_ennemi = 2; D_allie = 3; D_ennemi = 4;
  }
  else //Sinon l'IA est le joueur noir
  {
    decallage = -1;
    P_allie = 2; P_ennemi = 1; D_allie = 4; D_ennemi = 3;
  }

  for (i=0;i<10;i++)
  {
    for (j=0;j<10;j++)
    {
      if (prenable(i,j))
      {
        nb_element_prenable++; //On compte le nombre de pion que l'IA peut prendre
      }
    }
  }

  bool valide = false;
  if (nb_element_prenable != 0) //Si l'IA peut en prendre au moins 1, alors elle est obligé de le faire
  {
    int *Tabx = new int[nb_element_prenable]; //On crée un tableau des coordonnées en x des cases qui peuvent prendre
    int *Taby = new int[nb_element_prenable]; //On crée un tableau des coordonnées en y des cases qui peuvent prendre
    int n=0; //Compteur de l'emplacement du tableau
    for (i=0;i<10;i++)
    {
      for (j=0;j<10;j++)
      {
        if (prenable(i,j))
        {
          //On remplit ces tableaux de tel forme :
          //Tabx[] = {x0,x1,x2,x3...}
          //Taby[] = {y0,y1,y2,y3...} avec (y1,x1) les coordonnées d'un pion qui peut prendre
          Taby[n] = i;
          Tabx[n] = j;
          n++;
        }
      }
    }
    
    srand(time(NULL));
    int coup = rand()%nb_element_prenable; //On tire aléatoirement le pion que va déplacer l'IA (le rang du tableau)

    int y0 = Taby[coup]; //Le couple (y0,x0) incarne ce choix
    int x0 = Tabx[coup];
    int x1, y1; //On va décider de (y1,x1), la destination

    if (coup%2 == 0) //On veut du pseudo aléatoire pour savoir si on regarde en premier à gauche ou à droite, pour cela on regarde le numéro de coup choisit dans le tableau (évidemment ce n'est pas du vrai aléatoire mais cela simplifie le code)
      {x1 = x0+2;} //Si c'est pair on regarde à droite
    else
      {x1 = x0-2;} //Sinon on regarde à gauche
    
    while(!valide) //On ne sortira de ce while que lorsque le déplacement aura été validé par la variable valide
    {
      cout << y0 << " " << x0 << "  " << y1 << " " << x1 << endl;
      y1 = y0-2*decallage; //On détermine y1 tel un pion ou une dame qui avance
      if (Damier[y1][x1] == 0) //La case de derrière est-elle libre ?
      {
        if ( (Damier[(y1+y0)/2][(x1+x0)/2]==P_ennemi) || (Damier[(y1+y0)/2][(x1+x0)/2]==D_ennemi) ) //On utilise comme dans prenable la technique de la moyenne et on regarde si la case par dessus laquel on saute contient bien un ennemi.
        { 
          //Si oui
          valide = true; //Tout est bon
          cout << y0 << " " << x0 << "  " << y1 << " " << x1 << endl;
          update(2,y0,x0,y1,x1); //On lance update avec le code n=2
        }
        //Sinon on se demande si c'est une dame qui mange en arrière
        //Et on effectue exactement le même raisonnement
      }
      else if (Damier[y0][x0] == D_allie) 
      {
        y1 = y0+2*decallage;
        if ( (Damier[(y1+y0)/2][(x1+x0)/2]==P_ennemi) || (Damier[(y1+y0)/2][(x1+x0)/2]==D_ennemi) ) 
        {
          valide = true;
          cout << y0 << " " << x0 << "  " << y1 << " " << x1 << endl;
          update(2,y0,x0,y1,x1);
        }  
      }
      if (coup%2 == 0) //Si aucune des conditions du dessus n'a aboutit c'est qu'on a choisit le mauvais côté, on regarde donc de l'autre côté. (puisque on sait que le pion (y0,x0) peut prendre, on sait que cette boucle sera faite au maximim deux fois)
        {x1 = x0-2;}
      else
        {x1 = x0+2;}
    }
    delete[] Tabx;
    delete[] Taby;
  }
  else //Sinon, c'est juste un déplacement
  {
    //On regarde d'abord si on peut faire une dame
    if (CouleurIA == 1) //Si c'est l'IA est blanche
    {
      for (i=0;i<10;i++)
      {
        if (Damier[1][i] == P_allie) //Y-a-t'il un pion à un déplacement de devenir une dame ?
        {
          if (Damier[0][i+1] == 0) //La case en diagonale droite est-elle libre ?
          {
            update(1,1,i,0,i+1); //Alors on fait une dame
            valide = true;
          }
          else if (Damier[0][i-1] == 0) //La case en diagonale gauche est-elle libre ?
          {
            update(1,1,i,0,i-1); //Alors on fait une dame
            valide = true;
          }
        }
      }
    }
    else //Sinon, l'IA est forcément noire
    //Même raisonnement
    {
      for (i=0;i<10;i++)
      {
        if (Damier[8][i] == P_allie)
        {
          if (Damier[9][i+1] == 0)
          {
            update(1,8,i,9,i+1);
            valide = true;
          }
          else if (Damier[9][i-1] == 0)
          {
            update(1,8,i,9,i-1);
            valide = true;
          }
        }
      }
    }

    while(!valide) //Sinon, c'est un déplacement quelquonque, aléatoire (et valide est donc toujours faux)
    {
      int y0,x0,y1,x1; //On créer nos variables
      srand(time(NULL));
      x0 = rand()%10; //On choisit un x0 au hasard sur le plateau
      srand(time(NULL));
      y0 = rand()%10; //On choisit un y0 au hasard sur le plateau

      if ((Damier[y0][x0] == P_allie) || (Damier[y0][x0] == D_allie))
      { //Si cette case est controllé par l'IA
      srand(time(NULL));
        if (rand()%2==0 && x0!=9) //On tire aléatoirement la direction
          {x1 = x0+1;} //Droite
        else if (x0!=0)
          {x1 = x0-1;} //Gauche
        else
          {x1 = x0+1;}

        y1 = y0 - decallage; //y1 ici, dans le cas d'un pion ou d'une dame qui avance
        if (Damier[y1][x1] == 0) //Si la case est bien libre
        {
          valide = true; //Tout est bon
          cout << y0 << " " << x0 << "  " << y1 << " " << x1 << endl;
          update(1,y0,x0,y1,x1); //On lance update avec le code n=1
        }
        //Puis éventuellement comme un dame qui recule
        else if (Damier[y0][x0] == D_allie) 
        { 
          y1 = y0 + decallage;
          if (Damier[y1][x1] == 0) //Si la case est bien libre
          {
            valide = true; //Tout est bon
            cout << y0 << " " << x0 << "  " << y1 << " " << x1 << endl;
            update(1,y0,x0,y1,x1); //On lance update avec le code n=1
          }
        }
      }
    }
  }
}

void Jeu()
{
  //Ceci est la fonction principal du jeu qui ne prend aucun paramètre en entrée.
  //C'est elle qui lancera presque toutes les autres fonctions
  //Déclaration des variables :
  bool valide = false; //Variable qui servira à vérifier la validité du coup
  int x0, y0, x1, y1; //On prépare les coordonnés pour les déplacements et prises
  int P_allie, P_ennemi, D_allie, D_ennemi; //Variable qui serviront à déterminer la valeur des pions alliés et ennmis

  int decallage; //Le joueur est blanc, il va vers l'avant; l'IA va vers l'arrière
    if (player == 1) {decallage = -1;}
    else {decallage = 1;}

  //Selon quel joueur joue, on change la valeur des pions
  //Pour rappel
  //1 = pion blanc
  //2 = pion noir
  //3 = dame blanche
  //4 = dame noire
  if (player == 1)
  {
    P_allie = 1; P_ennemi = 2; D_allie = 3; D_ennemi = 4;
  }
  else
  {
    P_allie = 2; P_ennemi = 1; D_allie = 4; D_ennemi = 3;
  }

  bool attaque = false; //Si attaque passe à True, le joueur peut prendre un pion <=> il est obligé de le faire.

  if ((player==CouleurIA) && IA) //Si c'est à l'IA de jouer et qu'elle est activé
  {
    cout << "Execution de l'IA..." << endl;
    AI(); //On lance l'IA
    valide = true; //C'est valide => on s'arrête ici et le while ne sera pas executé
  }

  while(!valide) //Si valide n'a pas été vérifié, on relance et on redemande au joueur.
  //Si valide est vérifié, on a executé update, on sort donc de la fonction pour retourner dans main 
  { 
    //boucle principale qui ne s'arrête pas tant que valide == false.
    if (player == 1) //Si blanc
    {
      cout << "Joueur Blanc : " << endl;
      cout << "Entrez les coordonnées du pion que vous voulez déplacer" << endl;
      cin >> y0 >> x0;
      cout<<"Joueur Blanc : " << endl;
      cout << "Entrez les coordonnées de la destionation" << endl;
      cin >> y1 >> x1;
    }
    else //Sinon, noir
    {
      cout << "Joueur Noir : " << endl;
      cout << "Entrez les coordonnées du pion que vous voulez déplacer" << endl;
      cin >> y0 >> x0;
      cout<<"Joueur Noir : " << endl;
      cout << "Entrez les coordonnées de la destionation" << endl;
      cin >> y1 >> x1;
    }

    if (!IA || player!=CouleurIA)
    {
      if (x0>=0 && x0<10) //Si le x de départ existe
      {
        if (y0>=0 && y0<10) //Si le y de départ existe
        {
          if (x1>=0 && x1<10) //Si le x d'arrivé existe
          {
            if (y1>=0 && y1<10) //Si le y d'arrivé existe
            {
              if ((Damier[y0][x0] == P_allie) || (Damier[y0][x0] == D_allie)) //Si la case contient bien un pion allié
              {
                for (int i=0;i<10;i++) //On regarde si il y a des pions prenable dans le plateau
                {
                  for (int j=0;j<10;j++)
                  {
                    if (prenable(i,j))
                      {attaque = true;} //Si oui, on met attaque à True
                  }
                }
                if (attaque) //Si il y a des pions prenable, le joueur est obligé d'en prendre un
                {
                  if (prenable(y0,x0)) //Si la case séléctionné est effectivement une case qui peut attaquer
                  {
                    if (Damier[y1][x1] == 0) //La case de derrière est-elle libre ?
                    {
                      //On considère d'abord la case comme un pion
                      if ( ((x1==x0+2*decallage || (x1==x0-2*decallage)) && (y1==y0+2*decallage)))
                      //est ce que les coordonnées sont les mêmes que le pion qu'on veut prendre ?
                      {
                        if ( (Damier[(y1+y0)/2][(x1+x0)/2]==P_ennemi) || (Damier[(y1+y0)/2][(x1+x0)/2]==D_ennemi) ) //On utilise comme dans prenable la technique de la moyenne et on regarde si la case par dessus laquel on saute contient bien un ennemi.
                        { 
                          //Si oui
                          valide = true; //Tout est bon
                          update(2,y0,x0,y1,x1); //On lance update avec le code n=2
                        }
                      }
                      //Sinon on se demande si c'est une dame qui mange en arrière
                      //Et on effectue exactement le même raisonnement
                      else if (Damier[y0][x0] == D_allie) 
                      {
                        if ( (x1==x0+2*decallage || (x1==x0-2*decallage)) && (y1==y0-2*decallage) )
                        { 
                          if ( (Damier[(y1+y0)/2][(x1+x0)/2]==P_ennemi) || (Damier[(y1+y0)/2][(x1+x0)/2]==D_ennemi) ) 
                          {
                            valide = true;
                            update(2,y0,x0,y1,x1);
                          }  
                        } else {cout << "Vous êtes dans l'obligation de prendre un pion" << endl;}
                      } else {cout << "Vous êtes dans l'obligation de prendre un pion" << endl;}
                    } else {cout << "Cette case n'est pas libre" << endl;}
                  } else {cout << "Vous êtes dans l'obligation de prendre un pion, le pion entrée ne peut pas prendre" << endl;}
                  attaque = false;
                  } 
                  else //Sinon, cela veut dire qu'on ne peut pas attaquer, on va donc se déplacer
                  {
                    if (Damier[y1][x1] == 0)
                    {
                      //On considère d'abord un pion ou une dame qui avance
                      //Si la destination est bien atteignable par l'origine
                      if  ( (y1==y0+decallage) && ((x1==x0-decallage) || ((x1==x0+decallage) ) ))
                      { 
                        valide = true; //Tout est bon
                        update(1,y0,x0,y1,x1); //On lance update avec le code n=1
                      }
                      //Puis éventuellement comme un dame qui recule
                      //Si la destination est bien atteignable par l'origine
                      else if (Damier[y0][x0] == D_allie) 
                      { 
                        if  ( (y1==y0-decallage) && ( (x1==x0+decallage) || ((x1==x0-decallage) ) ) )
                        {
                          valide = true; //Tout est bon
                          update(1,y0,x0,y1,x1); //On lance update avec le code n=1
                        }
  //On prévoie diverses erreurs pour guider le joueur
                      }  else {cout << "L'action demandée est impossible" << endl;}
                    } else {cout << "La destination n'est pas libre" << endl;}
                  } 
              } else {cout << "Il semblerait que cette case ne contienne pas un de vos pions :D" << endl;}
            } else {cout << "La ligne d'arrivée entrée n'existe pas" << endl;}
          } else {cout << "La colonne d'arrivée entrée n'existe pas" << endl;}
        } else {cout << "La ligne de départ entrée n'existe pas" << endl;}
      } else {cout << "La colonne de départ entrée n'existe pas" << endl;}
    }
  }
}

void DeuxiemeCoup(int y0, int x0)
{
  //Cette fonction a pour objectif de gérer les cas dans lesquels le joueur peut faire un coup multiples (prendre plusieurs pion d'un coup). Elle est lancé par la fonction update qui vérifie si l'arrivé après une prise permet une double prise. Elle prend donc en paramètre les coordonnées d'origine de la double prise qui ne sont donc pas libre)
  //Cette fonction est moins détaillé car son fonctionnement ressemble énormément à celui de la fonction Jeu
  bool valide = false;
  int x1, y1;
  int P_ennemi, D_ennemi; //On a ici pas besoin de connaitre le pion allié ou la Dame allié

  //La double prise permet de reculer, on a donc pas besoin de coef de décallage.

  system("clear");
  Affiche(&Damier[0][0]); //On réaffiche le damier pour que le joueur voit où il en est

  do{ if (player == 1) //Boucle principal gérer par la variable valide
      {
        cout << "Joueur Blanc : " << endl;
        cout << "Poursuivez l'enchainement" << endl;
        cin >> y1 >>  x1;
      }
      else
      {
        cout << "Joueur Noir : " << endl;
        cout << "Poursuivez l'enchainement" << endl;
        cin >> y1 >>  x1;
      }
      if (x1>=0 && x1<10)
      {
        if (y1>=0 && y1<10)
        {
        //Si les cases entrés existent
          if (Damier[y1][x1] == 0) //La case de derrière est-elle libre ?
          {
            //On considère d'abord la case comme un pion
            if ((x1==x0+2 || (x1==x0-2)) && ((y1==y0+2) || (y1==y0-2)) )
            {
              if ( (Damier[(y1+y0)/2][(x1+x0)/2]==P_ennemi) || (Damier[(y1+y0)/2][(x1+x0)/2]==D_ennemi) )
              { 
                valide = true;
                update(2,y0,x0,y1,x1);
  //On prévoie les erreurs possible pour guider le joueur
              } else {cout << "Vous êtes dans l'obligation de prendre un pion" << endl;}
            } else {cout << "Vous êtes dans l'obligation de prendre un pion" << endl;}
          } else {cout << "Cette case n'est pas libre" << endl;}
        } else {cout << "La ligne entrée n'est pas valide" << endl;}
      } else {cout << "La colonne entrée n'est pas valide" << endl;}
    }while(!valide); 
}

void PlateauInitiale(int *Damier) 
{
  //cette fonction a pour objectif de générer le plateau de jeu initiale
  //Elle prend en paramètre l'adresse du premier élément du tableau
  int x,y;
  //On met des 0 partout
    for(x=0;x<100;x++){
      *(Damier+x) = 0;
    }

  //On place les pions noirs

  for(y=0;y<40;y+=20){
    for(x=1;x<10;x+=2){
      *(Damier+y+x) = 2;
    }
    for(x=10;x<20;x+=2){
      *(Damier+y+x) = 2;
    }
  }

  //On place les pions blancs
  for(y=60;y<100;y+=20){
    for(x=1;x<10;x+=2){
      *(Damier+y+x) = 1;
    }
    for(x=10;x<20;x+=2){
      *(Damier+y+x) = 1;
    }
  }
}

bool Victoire(bool player)
{
  //Cette fonction a pour but de vérifier si un joueur a gagner
  //Pour cela elle prend en paramètre player qui indique true pour blanc et false pour noir
  int P_ennemi,D_ennemi,i,j; //On place nos variables habituelles ainsi que i et j pour faire des boucles
  bool win = 1; //Par défault on considère qu'il a gagné, on va essayer de contredire cela

  if (player)
  {
    P_ennemi = 2; D_ennemi = 4;
  }
  else
  {
    P_ennemi = 1; D_ennemi = 3;
  }

  //On va "scanner" chaque case du Damier pour vérifier si il existe une case occupé par un ennemi
  for (i=0;i<10;i++) 
  {
    for (j=0;j<10;j++)
    {
      if (Damier[i][j] == P_ennemi || Damier[i][j] == D_ennemi)
      {
        win = 0; //Si on en trouve une, le joueur en question n'a pas encore gagné
      }
    }
  } 
  return win; //On retourne simplement la valeur de win : 1 pour gagné, 0 pour pas encore
}

void Affiche(int *Damier)
{
  //Ceci est la fonction d'affichage
  //Elle prend en entrée la Matrice du Damier et le formate pour l'afficher joliement en console
  //Uniquement de l'affichage, on retrouve tout ces éléments lorsque on joue
  int x,y; //variable utile pour calculer les coordonnées
  cout << "    0 1 2 3 4 5 6 7 8 9" << endl;
  //On affiche les bordures à l'aide de barre oblique qui sont des caractères ASCII. On les affiche donc avec leur code ASCII.
  cout << "  \u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513" << endl; //Barre horizontale du haut
  for(y=0;y<100;y+=10){ //Pour chaque ligne du Damier
    std::cout << y/10; //On affiche le numéro de la ligne qui correspond à première coordonnées de la ligne / 10
    if (y/10 < 10) {cout << " ";}
    std::cout << "\u2503 "; //Barre verticale
    for(x=0;x<10;x++){
      if(*(Damier+y+x)==1) {std::cout << "\u25CF" << " ";} 
      //Si c'est un 1 on affiche un rond blanc
      else if(*(Damier+y+x)==2) {cout << "\u25CB" << " ";}
      //Si c'est un 2 on affiche un rond noir
      else if(*(Damier+y+x)==3) {cout << "\u265A" << " ";}
      //Si c'est un 3 on affiche une couronne blanche
      else if(*(Damier+y+x)==4) {cout << "\u2654" << " ";}
      //Si c'est un 4 on affiche une couronne noire
      else {cout << "  ";}	
      //Sinon, il n'y a rien on affiche donc un espace
      
    }
    cout << "\u2503" << endl; //Barre verticale de fin de ligne
  }
  cout << "  \u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251B" << endl; //Barre horizontale du bas
}

int main()
{
  //Fonction principale, c'est elle qui rythme le programme et gère une partie de l'affichage console
  //Déclaration des variables
  string temp="";
  string gagnant;
  string Mode;
  bool ok_aide;
  bool ok_jouer;

  while (true) //Boucle infin qui ne sera terminé que par un return, cela mettra fin à l'execution de la fonction et donc sortira de la boucle
  {

    //On affiche un menu, le texte en caractère ASCII a été géneré grâce au site rakko.tools qui est libre d'utilisation.
    system("clear");
    cout << "     ##  #######  ##   ##       #####    ####### " << endl;
    cout << "     ##   ##   #  ##   ##        ## ##    ##   # " << endl;
    cout << "     ##   ##      ##   ##        ##  ##   ##     " << endl;
    cout << "     ##   ####    ##   ##        ##  ##   ####   " << endl;
    cout << "##   ##   ##      ##   ##        ##  ##   ##     " << endl;
    cout << " ## ##    ##   #  ##   ##        ## ##    ##   # " << endl;
    cout << "  ###    #######   #####        #####    ####### " << endl << endl;
    cout << "   #####      ###    ##   ##  #######   ###### " << endl;
    cout << "    ## ##    ## ##   ### ###   ##   #  ###     " << endl;
    cout << "    ##  ##  ##   ##  #######   ##      ##      " << endl;
    cout << "    ##  ##  ##   ##  ## # ##   ####     #####  " << endl;
    cout << "    ##  ##  #######  ##   ##   ##           ## " << endl;
    cout << "    ## ##   ##   ##  ##   ##   ##   #      ### " << endl;
    cout << "   #####    ##   ##  ##   ##  #######  ######  " << endl << endl;

    cout << "> Jouer" << endl;
    cout << "> Option" << endl;
    cout << "> Aide" << endl;
    cout << "> Quitter" << endl << endl;

    cout << "Choisissez la catégorie à laquelle vous voulez accéder :" << endl;
    cin >> Mode;

    if (Mode == "Jouer")
    {
      //On déclenche le Jeu
      PlateauInitiale(&Damier[0][0]); //On intialise le plateau
      system("clear"); //On nettoie le console
      Affiche(&Damier[0][0]); //On l'affiche
      //Lancement du Jeu
      while(!(Victoire(!player))) //Tant que l'autre joueur n'a pas gagner, le joueur actuel peut jouer
      {
        Jeu(); //Fonction principal
        system("clear");
        Affiche(&Damier[0][0]); //On affiche après chaque tour
        sleep(1); //Pour laisser le temps au joueur de voir l'action produite, notamment avant l'affichage d'une victoire.
      }

      if (!player) //Le joueur ayant gagné est celui qui vient de jouer (puisque Jeu change de joueur à la fin de son execution)
      {
        gagnant = "JOUEUR BLANC";
      }
      else
      {
        gagnant = "JOUEUR NOIR";
      }

      ok_jouer = 0; //Variable qui nous fera retourner au menu lorsque elle passe à true
      while (!ok_jouer)
      {
        //Affichage de victoire
        //ASCII art géneré par le site rakko.tool libre d'utilisation
        system("clear");
        cout << "                  @@                  " << endl;
        cout << "@@               @==@               @@" << endl;
        cout << "@@##%@        @%#====#%@        @%##@@" << endl;
        cout << "@@#==+#%@    @-========-@    @%#+==#@@" << endl;
        cout << "@@#======****============****======#@@" << endl;
        cout << "@@#================================#@@" << endl;
        cout << "@@#================================#@@" << endl;
        cout << "@@#================================#@@" << endl;
        cout << "@@#================================#@@" << endl;
        cout << "@@#================================#@@" << endl;
        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;  
        cout << "VICTOIRE du " << gagnant << " !" << endl << endl << endl;
        cout << "Entrez 'Menu' pour revenir au Menu" << endl;;
        cin >> Mode;
        if (Mode == "Menu")
        {
          ok_jouer = 1; //Alors on peut retourner au menu
        }
      }
    }
    else if (Mode == "Option") //On entre dans le mode option
    {
      //Variable qui nous feront retourner au menu lorsque elles passeront à true
      //On propose ici de choisir le premier joueur, pour cela on change la valeur de base de player qui est par default sur blanc.
      //On propose aussi d'activer ou de séactiver l'IA.
      bool ok_couleur = 0;
      bool ok_IA = 0;
      while (!ok_couleur) 
      {
        cout << "Choisissez la couleur du premier joueur :" << endl;
        cout << "> Blanc" << endl;
        cout << "> Noir" << endl;
        cin >> Mode;

        if (Mode == "Blanc")
        {
          player = 1;
          CouleurIA = 0;
          ok_couleur = 1;

        }
        else if (Mode == "Noir")
        {
          player = 0;
          CouleurIA = 1;
          ok_couleur = 1;
        }
        else
        {
          cout << "Entrée non reconnu, réentrez la couleur" << endl;
        }
      }

      while (!ok_IA) 
      {
        cout << "Voulez-vous jouer contre l'IA :" << endl;
        cout << "> Oui" << endl;
        cout << "> Non" << endl;
        cin >> Mode;

        if (Mode == "Oui")
        {
          IA = 1;
          ok_IA = 1;
        }
        else if (Mode == "Non")
        {
          IA = 0;
          ok_IA = 1;
        }
        else
        {
          cout << "Entrée non reconnu, réentrez la réponse" << endl;
        }
      }
    }
    else if (Mode == "Aide") //Mode Aide
    {
      ok_aide = 0; //Variable qui nous fera retourner au menu lorsque elle passe à true
      while(!ok_aide)
      {
        cout << "Le Jeu de Dame si présent utilise les règles modernisé du jeu de Dame : L'objectif est d'être le dernier joueur à avoir des pions sur le plateau. Le Jeu devra respecter les règles du Jeu de Dames suivantes : " << endl;
        cout << "- Le Damier mesure 10 par 10 et contient 20 pions blancs et 20 pions noir au commencement de la partie." << endl;
        cout << "- Les pions blancs ne peuvent qu’avancer et les pions noirs que reculer le tout en diagonale" << endl;
        cout << "- Lors d’une prise, le pion prenant « saute » par dessus le pion pris et se retrouve derrière lui, à condition que cette case soit vide. Le pion prit disparaît." << endl;
        cout << "- Si le pion prenant peut reprendre tout de suite après une première prise alors il peut enchaîner directement avec ce coup et ce autant de fois qu’il le veut." << endl;
        cout << "- Lorsque un pion enchaîne plusieurs coup il peut le faire en arrière, c’est le seul cas dans lequel un pion peut reculer." << endl;
        cout << "- Si un pion atteint la bordure adverse du plateau il devient une dame, le nombre de dame n’est pas limité" << endl;
        cout << "- La dame est le seul pion à pouvoir reculer en plus d’avancer lors d’un simple déplacement mais elle est toujours limité à une seule case de portée." << endl;
        cout << "- La victoire est déclaré lorsque plus aucune pièce d’une couleur n’est présente sur le terrain" << endl;
        cout << "- On est obligé de prendre lorsque c’est possible Pour cela vous devrez entrer la case de derrière (qui doit être libre)." << endl;
        cout << "Pour vous déplacer, vous devez entrer les coordonnées de la case sous la forme 'ligne colonne', exemple : '5 4'." << endl << endl;
        cout << "Entrez 'Retour' pour quitter" << endl;
        cin >> Mode;
        if (Mode == "Retour")
        {
          ok_aide = 1; //On retourne au menu
        }
      }
    }
    else if (Mode == "Quitter") //Mode quitter servant à fermer le programme
    {
      system("clear");
      return 0; //On sort de la boucle, et on ferme le programme
    }
    else
    {
      cout << "Entrée non reconnu, réentrez votre choix" << endl;
    }
  }
}