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
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

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

   bind(ds,(struct sockaddr*)&addrServeur, lgA);

   std::cout << "IP : " << "162.38.84.89" << "\n"; /*Adresse IP de la marchine Serveur*/
   std::cout << "port : " << ntohs(addrServeur.sin_port) << "\n";

   /* Etape 4 : recevoir un message du client (voir sujet pour plus de détails)*/
  struct sockaddr_in sockaddrRetour;
  socklen_t lgRetour = sizeof(sockaddrRetour);

  char rep [100];
  int recv = recvfrom(ds, &rep, 100,0,(struct sockaddr *)&sockaddrRetour,&lgRetour);
  if(recv==-1){
    perror("Serveur : Erreur du retour\n");
    exit(1);
  } else {
   std::cout << inet_ntoa(sockaddrRetour.sin_addr) << " - " <<  ntohs(sockaddrRetour.sin_port) << " : " << rep << "\n";
  }
  
  /* Etape 5 : envoyer un message au client  (voir sujet pour plus de détails)*/
  char msg [100];
  std::cout << "Serveur : ";
  scanf("%[^\n]",msg);
  //std::cin >> msg;
  int sendsize = sendto(ds,&msg,strlen(msg)+1,0, (sockaddr*)&sockaddrRetour, lgRetour);
  if(sendsize==-1){
    perror("Serveur : Erreur à l'envoi\n");
    exit(1);
  }
  
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  close(ds);
  printf("Serveur : je termine\n");
  return 0;
}
