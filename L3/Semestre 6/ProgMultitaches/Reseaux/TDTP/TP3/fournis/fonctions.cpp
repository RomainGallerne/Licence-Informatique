int sendTCP(int sock, void *msg, int sizeMsg){
  int w = write(sock, msg, sizeMsg);
  if(w == EBADF){return 0;} //Socket fermée
  else if(w == -1){return -1;}  //Erreur du dépôt
  else if(w == sizeMsg){return 1;} //Dépôt réussi
  else{return sendTCP(sock,msg+w,sizeMsg-w);} //Dépôt incomplet
}

int recvTCP(int sock, void *msg, int sizeMsg){
  int r = read(sock, msg, sizeMsg);
  if(r == EBADF){return 0;} //Socket fermée
  else if(r == -1){return -1;}  //Erreur de lecture
  else return 1; //Lecture réussi
}