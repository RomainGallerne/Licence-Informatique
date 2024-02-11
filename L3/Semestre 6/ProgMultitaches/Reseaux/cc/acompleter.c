#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>


/* Ce programme est à compléter et à déposer sur Moodle, sans changer le nom du fichier. N'ajouter aucun autre fichier sauf ceux qui peuvent être demandés pendant l'épreuve.

   Lire attentivement les instructions en commentaires pour compléter correctement ce programme.
 
   Les principales étapes de ce programme sont :
 
   1) contacter un serveur UDP
   
   2) recevoir une instruction à suivre en UDP et l'afficher. L'expéditeur de cette instruction a une adresse différente de celle du serveur que vous avez contacté en 1). Cela sera expliqué dans l'instruction.
 
   3) mettre en place un serveur TCP et échanger avec un client distant.
 
   4) faire une copie du programme et le modifier pour qu'il soit capable de traiter plusieurs clients de manière itérative.
 
   5) faire une copie du programme et le modifier pour qu'il soit capable de traiter plusieurs clients simultanément (en utilisant la fonction fork()).
 
   Attention : vous devez déposer un code qui compile. Exemple : si vous êtes à l'étape 3 qui n'est pas fonctionnelle, mettre cette dernière étape en commentaire pour que toutes les étapes d'avant soient validées.
  
*/

int sendTCP(int sock, void *msg, int sizeMsg){
  int w = send(sock, msg, sizeMsg, 0);
  if(w == EBADF){return 0;} //Socket fermée
  else if(w == -1){return -1;}  //Erreur du dépôt
  else if(w == sizeMsg){return w;} //Dépôt réussi
  else {return w+sendTCP(sock,(void *)((int *)msg+w),sizeMsg-w);} //Dépôt incomplet
}

int recvTCP(int sock, void *msg, int sizeMsg){
  int r = recv(sock, msg, sizeMsg, 0);
  if(r == EBADF){return 0;} //Socket fermée
  else if(r == -1){return r;}  //Erreur de lecture
  else if(r == sizeMsg) {return r;} //Lecture réussi
  else {return r+recvTCP(sock,(void *)((int *)msg+r),sizeMsg-r);} //Dépôt incomplet
}

//ATTENTION : Le fichier est à passer en c++ pour les entrées sorties.


int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("Utilisation : %s ip_serveurUDP  port_serveurUDP  port_votre_serveur_TCP\n - ip_serveurUDP  et port_serveurUDP : donnés par l'intervenant(e). Il s'agit de l'adresse d'un serveur UDP qui est en attente d'un message que vous allez envoyer.\n - port_votre_serveur_TCP : un numero de votre choix pour un serveur TCP qui sera a implementer\n", argv[0]);
    exit(0);
  }
  
  /* Etape 1 : envoyer un message au serveur UDP (adresse passée en parametres) et recevoir une réponse 
  
     Début :
 
     - envoyer un message de type chaine de caractères. Cette chaine est à saisir au clavier (dites bonjour au serveur UDP).
  */
   
  char premierMsg[200];
  printf("CC : saisir un message a envoyer (moins de 200 caracteres) \n");
  fgets(premierMsg, sizeof(premierMsg), stdin); 
  premierMsg[strlen(premierMsg)-1]  = '\0';                      
   
  int dSUDP = socket(PF_INET, SOCK_DGRAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (dSUDP == -1){
    perror("CC : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépend de la réussite de la création de cette socket.
  }
  
  /* Ajouter des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("CC : creation de la socket réussie \n");
 
  struct sockaddr_in sockaddrServeur;
  sockaddrServeur.sin_family = AF_INET;
  sockaddrServeur.sin_addr.s_addr = inet_addr(argv[1]);
  sockaddrServeur.sin_port = htons(atoi(argv[2]));

  socklen_t lgA = sizeof(struct sockaddr_in);

  int sendsize = sendto(dSUDP,premierMsg,strlen(premierMsg)+1,0, (sockaddr*)&sockaddrServeur, lgA);
  if(sendsize==-1){
    perror("Moi : Erreur à l'envoi\n");
    exit(1);
  }
  else {
   printf("Moi : %i octets ont été envoyés\n",sendsize); 
  }

  struct sockaddr_in sockaddrRetour;
  socklen_t lgRetour = sizeof(sockaddrRetour);

  char nouvelleInstruction[2024];
  int recvfromsize = recvfrom(dSUDP, &nouvelleInstruction, 2024,0,(struct sockaddr *)&sockaddrRetour,&lgRetour);
  if(recvfromsize==-1){
    perror("Moi : Erreur du retour\n");
    exit(1);
  } else {
   printf("Expéditeur : %s\n",nouvelleInstruction);
   std::cout << "\nL'expéditeur est :\n" <<  inet_ntoa(sockaddrRetour.sin_addr) << "\n" <<  ntohs(sockaddrRetour.sin_port) << "\n";
    tableau recu vers ce client ;
 - recevoir en reponse une chaine de caracteres dont la taille est connue par le client et l'afficher (a vous, encore une fois, de savoir ce qui est necessaire de faire) ;
 - terminer l'echange avec le client
 Fin instruction

162.38.83.72 - 37248 : Tableau d'entiers reçu
Moi : Envoi du tableau d'entiers
Moi : Le tableau d'entiers a bien été
  struct sockaddr_in addrServeur;
  addrServeur.sin_family = AF_INET;
  addrServeur.sin_addr.s_addr = INADDR_ANY;
  addrServeur.sin_port = htons(atoi(argv[3]));

  int bindReturn = bind(dsTCP,(struct sockaddr*)&addrServeur, lgA);
   if(bindReturn==-1){
    perror("Moi : Erreur à l'attribution du port\n");
    close(dsTCP);
    exit(1);
  } else {
    std::cout << "Moi : Attribution du port réussie\n";
  }

  int tailleFile = 1; /*On pourra au maximum avoir tailleFile client dans la file d'attente*/

  int listenReturn = listen(dsTCP,tailleFile); /*Mise en mode écoute*/
   if(listenReturn==-1){
    perror("Moi : Erreur à l'écoute\n");
    close(dsTCP);
    exit(1);
  } else {
    std::cout << "Moi : Mise sur écoute du serveur\n\n";
  }

  //Envoi de la socket TCP en UDP
  sendsize = sendto(dSUDP,&addrServeur,sizeof(addrServeur),0, (sockaddr*)&sockaddrRetour, lgA);
  if(sendsize==-1){
    perror("Moi : Erreur à l'envoi\n");
    exit(1);
  }
  else {
   printf("Moi : %i octets ont été envoyés\n",sendsize); 
  }

  //Fin échanges UDP
  close(dSUDP);
  printf("Moi : je termine les échanges UDP\n");

  //On attend l'arrivée d'un client TCP
  int dSC = accept(dsTCP,(struct sockaddr *)&sockaddrRetour,&lgRetour); /*On accepte la connexion*/
  if(dSC==-1){
    perror("Moi : Erreur à l'acceptation de la connexion\n");
    close(dsTCP);
    exit(1);
  } else {
    std::cout << "Connexion Acceptée depuis\nIP : " << inet_ntoa(sockaddrRetour.sin_addr) << "\nPort : " << ntohs(sockaddrRetour.sin_port) << "\n\n";
  }

  /*Reception de la taille du message*/
  int tailleRep1;
  int recvsize = recvTCP(dSC, &tailleRep1, sizeof(int));
  if(recvsize<=0){
    perror("Moi : Erreur du retour de la taille du message\n");
    close(dsTCP);
    close(dSC);
    exit(1);
  } else {
    std::cout << "Un message de " << tailleRep1 << " octets va être envoyé.\n";
  }

  /*Recpetion du message*/
  char rep1[tailleRep1];
  recvsize = recvTCP(dSC, &rep1, tailleRep1);
  if(recvsize<=0){
    perror("Moi : Erreur du retour\n");
    close(dsTCP);
    close(dSC);
    exit(1);
  } else {
    std::cout << inet_ntoa(sockaddrRetour.sin_addr) << " - " <<  ntohs(sockaddrRetour.sin_port) << " : " << rep1 << "\n";
  }

  // Fin étape 2
  
  // Début étape 3

  //Réception d'un tableau de 320000 entiers
  int tabEntier[320000];
  recvsize = recvTCP(dSC, &tabEntier, 320000);
  if(recvsize<=0){
    perror("Moi : Erreur du retour\n");
    close(dsTCP);
    close(dSC);
    exit(1);
  } else {
    std::cout << inet_ntoa(sockaddrRetour.sin_addr) << " - " <<  ntohs(sockaddrRetour.sin_port) << " : Tableau d'entiers reçu\n";
  }

  //Renvoi du tabeau de 320000 entiers
  std::cout << "Moi : Envoi du tableau d'entiers\n";
  sendsize = sendTCP(dSC,tabEntier,320000); /*strlen(msg)+1*/
  if(sendsize<=0){
    perror("Moi : Erreur à l'envoi\n");
    close(dsTCP);
    close(dSC);
    exit(1);
  } else {
    std::cout << "Moi : Le tableau d'entiers a bien été envoyé.\n";
  }

  //On se prépare à reçevoir une chaine de caractères

  /*Reception de la taille du message*/
  int tailleRep2;
  int recvsize2 = recvTCP(dSC, &tailleRep2, sizeof(int));
  if(recvsize2<=0){
    perror("Moi : Erreur du retour de la taille du message\n");
    close(dsTCP);
    close(dSC);
    exit(1);
  } else {
    std:t compiler sans erreur, peu importe l'étape à laquelle vous vous êtes arrêté (mettre en commentaire ce qui n'est pas abouti et qui ne compile :cout << "Un message de " << tailleRep2 << " octets va être envoyé.\n";
  }

  /*Recpetion du message*/
  char rep2[tailleRep2];
  int recvsize3 = recvTCP(dSC, &rep2, tailleRep2);
  if(recvsize3<=0){
    perror("Moi : Erreur du retour\n");
    close(dsTCP);
    close(dSC);
    exit(1);
  } else {
    std::cout << "Retour : " << rep2 << "\n";
  }

  // etc, etc.

}