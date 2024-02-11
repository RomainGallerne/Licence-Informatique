#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

/* Programme serveur */

int sendTCP(int sock, void *msg, int sizeMsg){
  int w = write(sock, msg, sizeMsg);
  if(w == EBADF){return 0;} //Socket fermée
  else if(w == -1){return -1;}  //Erreur du dépôt
  else if(w == sizeMsg){return 1;} //Dépôt réussi
  else {return sendTCP(sock,msg+w,sizeMsg-w);} //Dépôt incomplet
}

int recvTCP(int sock, void *msg, int sizeMsg){
  int r = read(sock, msg, sizeMsg);
  if(r == EBADF){return 0;} //Socket fermée
  else if(r == -1){return -1;}  //Erreur de lecture
  else return 1; //Lecture réussi
}

int main(int argc, char *argv[]) {

  /* Je passe en paramètre le numéro de port qui sera donné à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Serveur : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  
  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Serveur : creation de la socket réussie \n");
  
  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.
  
  /* Etape 2 : Nommer la socket du serveur */
   struct sockaddr_in addrServeur;
   addrServeur.sin_family = AF_INET;
   addrServeur.sin_addr.s_addr = INADDR_ANY;
   addrServeur.sin_port = htons(atoi(argv[1]));

   socklen_t lgA = sizeof(struct sockaddr_in);

   int bindReturn = bind(ds,(struct sockaddr*)&addrServeur, lgA);
   if(bindReturn==-1){
    perror("Serveur : Erreur à l'attribution du port\n");
    close(ds);
    exit(1);
  } else {
    std::cout << "Attribution du port réussie\n";
  }

   std::cout << "IP : " << "162.38.83.131" << "\n"; /*Adresse IP de la marchine Serveur*/
   std::cout << "port : " << ntohs(addrServeur.sin_port) << "\n";

   int tailleFile = 1; /*On pourra au maximum avoir tailleFile client dans la file d'attente*/
   
   int listenReturn = listen(ds,tailleFile); /*Mise en mode écoute*/
   if(listenReturn==-1){
    perror("Serveur : Erreur à l'écoute\n");
    close(ds);
    exit(1);
  } else {
    std::cout << "Mise sur écoute du serveur\n\n";
  }

   /* Etape 4 : recevoir un message du client (voir sujet pour plus de détails)*/
  struct sockaddr_in sockaddrRetour;
  socklen_t lgRetour = sizeof(sockaddrRetour);

  int dSC = accept(ds,(struct sockaddr *)&sockaddrRetour,&lgRetour); /*On accepte la connexion*/
  if(dSC==-1){
    perror("Serveur : Erreur à l'acceptation de la connexion\n");
    close(ds);
    exit(1);
  } else {
    std::cout << "Connexion Acceptée depuis\nIP : " << inet_ntoa(sockaddrRetour.sin_addr) << "\nPort : " << ntohs(sockaddrRetour.sin_port) << "\n\n";
  }

  /*Boucle de récéption*/

  int send;
  int recv;
  char rep [4000];

  /*Recpetion du message*/
  recv = recvTCP(dSC, (void *)rep, 4000);
  if(recv<=0){
    perror("Serveur : Erreur du retour\n");
    close(ds);
    close(dSC);
    exit(1);
  } else {
    std::cout << inet_ntoa(sockaddrRetour.sin_addr) << " - " <<  ntohs(sockaddrRetour.sin_port) << " : " << rep << "\n";
  }

  /*Envoi du message au client*/
  char msg [50] = "J'accuse réception du message"; 

  send = sendTCP(dSC,(void *)msg,strlen(msg)+1);
  if(send<=0){
    perror("Serveur : Erreur à l'envoi\n");
    close(ds);
    close(dSC);
    exit(1);
  } else {
    std::cout << "Serveur : " << msg << "\n";
    std::cout << "Serveur : " << strlen(msg)+1 << " octets envoyés.\n";
  }
  
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  close(ds);
  close(dSC);
  printf("Serveur : je termine\n");
  return 0;
}
