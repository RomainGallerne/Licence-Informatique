########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/client  bin/serveur

# liste des fichiers sources 
SRCS0=client.cpp
SRCS1=serveur.cpp

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	g++ -Wall -Iinclude -c $< -o $@

bin/client: $(SRCS0:%.cpp=obj/%.o)
	g++ -o $@ $+

bin/serveur: $(SRCS1:%.cpp=obj/%.o)
	g++ -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~
