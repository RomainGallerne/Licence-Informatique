#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <winsock2.h>
#include <windows.h>
#else
  #include <arpa/inet.h>
  #include <sys/socket.h>
  #include <netdb.h>
#endif

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

int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("utilisation : client ip_serveur port_serveur nom_fichier\n Remaque : le parametre nom_fichier correspond au nom d'un fichier existant dans le répertoire emission\n");
    exit(0);
  }

  /* etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  if (ds == -1){
    perror("Client : pb creation socket :");
    close(ds);
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  } else {printf("Client : creation de la socket réussie \n");}

  /* etape 2 : designer la socket du serveur */
  struct sockaddr_in addrClient;
  addrClient.sin_family = AF_INET;
  addrClient.sin_addr.s_addr = INADDR_ANY;
  addrClient.sin_port = htons((short)0);

  socklen_t lgA = sizeof(struct sockaddr_in);

  int bindReturn = bind(ds,(struct sockaddr*)&addrClient, lgA);
  if(bindReturn==-1){
    perror("Client : Erreur à l'attribution du port\n");
    close(ds);
    exit(1);
  } else {
    std::cout << "Attribution du port réussie\n";
  }

  /* etape 3 : demander une connexion */
  struct sockaddr_in sockaddrServeur;
  sockaddrServeur.sin_family = AF_INET;
  sockaddrServeur.sin_addr.s_addr = inet_addr(argv[1]);
  sockaddrServeur.sin_port = htons(atoi(argv[2]));

  int ConnectReturn = connect(ds,(struct sockaddr*)&sockaddrServeur, lgA);
  if(ConnectReturn==-1){
    perror("Serveur : Erreur à la connexion\n");
    close(ds);
    exit(1);
  } else {
    std::cout << "Connexion Réussie\n\n";
  }

  /* etape 4 : récupération du fichier */

  // construction du nom du chemin vers le fichier
  char* filepath = new char(strlen(argv[3])+16);
  filepath[0] = '\0';
  strcat(filepath, "./emission/");
  strcat(filepath, argv[3]);

  printf("Client : je vais envoyer %s\n", filepath);

  // obtenir la taille du fichier
  struct stat attributes;
  if(stat(filepath, &attributes) == -1){
    perror("Client : erreur stat");
    free(filepath);
    exit(1);
  }

  int file_size = attributes.st_size; // cette copie est uniquement informer d'où obtenir la taille du fichier.
  
  printf("Client : taille du fichier : %d octets\n", file_size);

  size_t Retoursend;
  int nb_send = 0;
  int total_lu = 0; //Nombre de caractères lu dans le fichier au total
  int totalSent = 0; // variable pour compter le nombre total d'octet effectivement envoyés au serveur du début à la fin des échanges.
  char buffer[MAX_BUFFER_SIZE];
  int tailleNomFichier = strlen(argv[3])+1;
  char* nomFichier;

  /*Taille du nom du fichier*/
  Retoursend = sendTCP(ds,(void *)&tailleNomFichier,sizeof(int));
    if(Retoursend<=0){
      perror("Client : Erreur à l'envoi\n");
      close(ds);
      exit(1);
    } else {
      nb_send += 1;
      totalSent += sizeof(file_size);
      std::cout << "Client : Taille du nom du fichier envoyée : " << strlen(argv[3])+1 << "o\n";
    }

  /*Nom du fichier*/
  Retoursend = sendTCP(ds,argv[3],strlen(argv[3])+1);
    if(Retoursend<0){
      perror("Client : Erreur à l'envoi\n");
      close(ds);
      exit(1);
    } else {
      nb_send += 1;
      totalSent += strlen(argv[3])+1;
      std::cout << "Client : Nom du fichier envoyé : " << argv[3] << "\n";
    }

  /*Taille du fichier*/
  Retoursend = sendTCP(ds, &file_size, sizeof(int));
    if(Retoursend<=0){
      perror("Client : Erreur à l'envoi\n");
      close(ds);
      exit(1);
    } else {
      nb_send += 1;
      totalSent += sizeof(file_size);
      std::cout << "Client : Taille du fichier envoyée : " << file_size << "o\n";
    }
  
  // lecture du contenu d'un fichier
  FILE* file = fopen(filepath, "rb");
  if(file == NULL){
    perror("Client : erreur ouverture fichier \n");
    free(filepath);
    exit(1);   
  }
  free(filepath);

  while(total_lu < file_size || totalSent < total_lu){
    size_t read = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    if(read == 0){
      if(ferror(file) != 0){
	      perror("Client : erreur lors de la lecture du fichier \n");
	      fclose(file);
	      exit(1);
      }else{
        printf("Client : arrivé a la fin du la lecture du fichier\n");// fin du fichier
	      break;
      }
    }
    total_lu += read;
    Retoursend = sendTCP(ds,buffer,read);
    if(Retoursend<=0){
      perror("Client : Erreur à l'envoi\n");
      close(ds);
      exit(1);
    } else {
      nb_send += 1;
      totalSent += strlen(buffer);
      std::cout << "Client : " << strlen(buffer) << " octets envoyés.\n";
    }
  }
  printf("%i octets ont été lus.\n%i octets ont été envoyés.\n",total_lu,totalSent);
  printf("Client : Fin de l'envoi du fichier.\n");

  /* etape 6 : fin d'execution */
  fclose(file); 
  close(ds);
  printf("Client : j'ai lu au total : %d octets \n", total_lu);  
  printf("Client : j'ai effectué %i appels à sendTCP\n", nb_send); 
  printf("Client : c'est fini\n");
  return 0;
}
