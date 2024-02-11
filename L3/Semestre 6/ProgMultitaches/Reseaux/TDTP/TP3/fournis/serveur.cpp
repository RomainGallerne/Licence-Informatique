#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>

#define MAX_BUFFER_SIZE 146980

int sendTCP(int sock, void *msg, int sizeMsg){
  int w = send(sock, msg, sizeMsg, 0);
  if(w == EBADF){return 0;} //Socket fermée
  else if(w == -1){return -1;}  //Erreur du dépôt
  else if(w == sizeMsg){return w;} //Dépôt réussi
  else {return w+sendTCP(sock,msg+w,sizeMsg-w);} //Dépôt incomplet
}

int recvTCP(int sock, void *msg, int sizeMsg){
  int r = recv(sock, msg, sizeMsg, 0);
  if(r == EBADF){return 0;} //Socket fermée
  else if(r == -1){return -1;}  //Erreur de lecture
  else return r; //Lecture réussi
}

int main(int argc, char *argv[])
{
  /* etape 0 : gestion des paramètres si vous souhaitez en passer */
  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* etape 1 : creer une socket d'écoute des demandes de connexions*/
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  if (ds == -1){
    perror("Serveur : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  } else {printf("Serveur : creation de la socket réussie \n");}

  /* etape 2 : nommage de la socket */
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
  } else {std::cout << "Attribution du port réussie\n";}

   std::cout << "IP : " << "162.38.84.63" << "\n"; /*Adresse IP de la marchine Serveur*/
   std::cout << "port : " << ntohs(addrServeur.sin_port) << "\n";

  /* etape 3 : mise en ecoute des demandes de connexions */
  int tailleFile = 10; /*On pourra au maximum avoir tailleFile client dans la file d'attente*/
   
  int listenReturn = listen(ds,tailleFile); /*Mise en mode écoute*/
  if(listenReturn==-1){
    perror("Serveur : Erreur à l'écoute\n");
    close(ds);
    exit(1);
  } else {std::cout << "Mise sur écoute du serveur\n\n";}

  /* etape 4 : plus qu'a attendre la demadne d'un client */
  struct sockaddr_in sockaddrRetour;
  socklen_t lgRetour = sizeof(sockaddrRetour);
 
  //Traiter itérativement les clients
  while(1){

    int dSC = accept(ds,(struct sockaddr *)&sockaddrRetour,&lgRetour); /*On accepte la connexion*/
    if(dSC==-1){
      perror("Serveur : Erreur à l'acceptation de la connexion\n");
      close(ds);
      exit(1);
    } else {
      std::cout << "Connexion Acceptée depuis\nIP : " << inet_ntoa(sockaddrRetour.sin_addr) << "\nPort : " << ntohs(sockaddrRetour.sin_port) << "\n\n";
    }

    int nb_recv = 0;
    int recvRetour;
    char rep [4000];
    int tailleFichier;
    int tailleNomFichier;
    int totalRecv = 0; // un compteur du nombre total d'octets recus d'un client
    char buffer[MAX_BUFFER_SIZE];

    //On reçoie la taille du nom du fichier
    recvRetour = recvTCP(dSC, (void *)&tailleNomFichier, sizeof(int));
    if(recvRetour<=0){
      perror("Serveur : Erreur du retour\n");
      close(ds);
      close(dSC);
      exit(1);
    } else {
      nb_recv += 1;
      std::cout << inet_ntoa(sockaddrRetour.sin_addr) << " - " <<  ntohs(sockaddrRetour.sin_port) << " : Le nom du fichier envoyé fait " << tailleNomFichier << "o\n";
    }

    char nomFichier [tailleNomFichier];

    //On reçoie le nom du fichier
    recvRetour = recvTCP(dSC, nomFichier, tailleNomFichier);
    if(recvRetour<0){
      perror("Serveur : Erreur du retour\n");
      close(ds);
      close(dSC);
      exit(1);
    } else {
      nb_recv += 1;
      std::cout << inet_ntoa(sockaddrRetour.sin_addr) << " - " <<  ntohs(sockaddrRetour.sin_port) << " : Le fichier envoyé s'appelle " << nomFichier << "\n";
    }

    //On reçoie la taille du fichier
    recvRetour = recvTCP(dSC, (void *)&tailleFichier, sizeof(int));
    if(recvRetour<=0){
      perror("Serveur : Erreur du retour\n");
      close(ds);
      close(dSC);
      exit(1);
    } else {
      nb_recv += 1;
      std::cout << inet_ntoa(sockaddrRetour.sin_addr) << " - " <<  ntohs(sockaddrRetour.sin_port) << " : Le fichier envoyé fait " << tailleFichier << "o\n";
    }

    // construction du nom du chemin vers le fichier
    char* filepath = new char(strlen(argv[3])+16);
    filepath[0] = '\0';
    strcat(filepath, "./reception/");
    strcat(filepath, nomFichier);
   
    // On ouvre le fichier dans lequel on va écrire
    FILE* file = fopen(filepath, "wb");
    if(file == NULL){
      perror("Serveur : erreur ouverture fichier: \n");
      exit(1);  
    }

    /*Recpetion du message*/
    while(totalRecv < tailleFichier){
      recvRetour = recvTCP(dSC, (void *)buffer, MAX_BUFFER_SIZE);
      if(recvRetour<=0){
        perror("Serveur : Erreur du retour ");
        printf("%i\n",recvRetour);
        close(ds);
        close(dSC);
        exit(1);
      } else {
        nb_recv += 1;
        totalRecv += recvRetour;
        size_t written = fwrite(buffer, sizeof(char), recvRetour, file);
        if(written < recvRetour){  // cette ligne est valide uniquement pour ce simple exemple
          perror("Serveur : Erreur a l'ecriture du fichier \n");
        }
      }
    }
    std::cout << "Serveur : L'entiereté du fichier a bien été reçu.\n";
    printf("Serveur : ecriture dans fichier reussie. Vous pouvez vérifier la création du fichier et son contenu.\n");
    fclose(file); 
    close(dSC);
    printf("Serveur : j'ai effectué %i appels à recv \n", nb_recv); 
    std::cout << "\nServeur : Changement de client.\n\n";
  }
    
  printf("Serveur : c'est fini\n");
}








