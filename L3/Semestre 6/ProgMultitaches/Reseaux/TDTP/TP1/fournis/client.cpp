#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

/* Programme client */

int main(int argc, char *argv[]) {

  /* je passe en paramètre l'adresse de la socket du serveur (IP et
     numéro de port) et un numéro de port à donner à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 4){
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Client : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  
  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Client : creation de la socket réussie \n");
  
  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.
  
  /* Etape 2 : Nommer la socket du client */
  
  /* Etape 3 : Désigner la socket du serveur */
  struct sockaddr_in sockaddrServeur;
  sockaddrServeur.sin_family = AF_INET;
  sockaddrServeur.sin_addr.s_addr = inet_addr(argv[1]);
  sockaddrServeur.sin_port = htons(atoi(argv[2]));

   socklen_t lgA = sizeof(struct sockaddr_in);
  
  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  char msg [100];
  std::cout << "Client : ";
  //std::cin >> msg;
  scanf("%[^\n]",msg);
  for(int i=0;i<10000;i++){
    msg[i]=i*10;
  }
  int sendsize = sendto(ds,msg,strlen(msg)+1,0, (sockaddr*)&sockaddrServeur, lgA);
  if(sendsize==-1){
    perror("Client : Erreur à l'envoi\n");
    exit(1);
  }
  else {
   std::cout << "Client : " << sendsize << " octets ont été envoyés\n"; 
  }
  
  /* Etape 5 : recevoir un message du serveur (voir sujet pour plus de détails)*/
  struct sockaddr_in sockaddrRetour;
  socklen_t lgRetour = sizeof(sockaddrRetour);

  char rep [100];
  int recv = recvfrom(ds, &rep, 100,0,(struct sockaddr *)&sockaddrRetour,&lgRetour);
  if(recv==-1){
    perror("Client : Erreur du retour\n");
    exit(1);
  } else {
   std::cout << "Serveur : " << rep << "\n";
   std::cout << recv << " octets ont été reçus de l'utilisateur (IP,port) :\n" <<  inet_ntoa(sockaddrRetour.sin_addr) << "\n" <<  ntohs(sockaddrRetour.sin_port) << "\n"; 
  }
  
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  close(ds);
  printf("Client : je termine\n");
  return 0;
}
