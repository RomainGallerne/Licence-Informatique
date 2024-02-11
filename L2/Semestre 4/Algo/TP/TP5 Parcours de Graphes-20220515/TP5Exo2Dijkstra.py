from random import *
from math import sqrt
from itertools import *
import matplotlib.pyplot as plt

###########################################

def AfficheGraph(points,G):
    n=len(points)
    plt.plot([p[0] for p in points],[p[1] for p in points],'bo',markersize =5,zorder=3)
    #zorder: plus c'est eleve, plus c'est devant. Par defaut, les lignes sont a 2, les point a 1
    plt.title('Graphe G')
    nomSommets=[i for i in range(0,n)]
    for i in range(0,n):
        plt.text(points[i][0]+10,points[i][1]+10,nomSommets[i], fontsize=14)
    for i in range(0,len(G)):
        for j in range(0,len(G[i])): #on relie i a son jeme voinsin
            plt.plot([points[i][0],points[G[i][j]][0]],[points[i][1],points[G[i][j]][1]],'r-') 
    plt.show()

def AfficheGraphEtArbre(points,G,pere):
    n=len(points)
    plt.plot([p[0] for p in points],[p[1] for p in points],'bo',markersize =5,zorder=3)
    #zorder: plus c'est eleve, plus c'est devant. Par defaut, les lignes sont a 2, les point a 1
    plt.title('Graphe G')
    nomSommets=[i for i in range(0,n)]
    for i in range(0,n):
        plt.text(points[i][0]+10,points[i][1]+10,nomSommets[i], fontsize=10)
    for i in range(0,len(G)):
        for j in range(0,len(G[i])): #on relie i a son jeme voinsin
            plt.plot([points[i][0],points[G[i][j]][0]],[points[i][1],points[G[i][j]][1]],'0.9')
    for i in range(1,n):
        plt.plot([points[i][0],points[pere[i]][0]],[points[i][1],points[pere[i]][1]],'r-',zorder=2.5)
    plt.show()

#######Initialisation Graphe########

def InitGraphFix(points,G,longueur):
    points.extend([[962,909],[601,645],[813,594],[997,439],[373,383],[782,172],[526,403],[400,742],[281,148],[158,530]])
    G.extend([[1,2,3,7],[0,2,6,7],[0,1,3,5,6],[0,2,5],[6,7,8,9],[2,3,6,8],[1,2,4,5,8],[0,1,4,9],[4,5,6,9],[4,7,8]])
    for i in range(0,10):
        longueur.append([10000]*10)
    longueur[0][1]=longueur[1][0]=5    
    longueur[0][2]=longueur[2][0]=3
    longueur[0][3]=longueur[3][0]=11
    longueur[0][7]=longueur[7][0]=9
    longueur[1][2]=longueur[2][1]=1
    longueur[1][6]=longueur[6][1]=2
    longueur[1][7]=longueur[7][1]=4
    longueur[2][3]=longueur[3][2]=6
    longueur[2][5]=longueur[5][2]=4
    longueur[2][6]=longueur[6][2]=2
    longueur[3][5]=longueur[5][3]=2
    longueur[4][6]=longueur[6][4]=1
    longueur[4][7]=longueur[7][4]=4
    longueur[4][8]=longueur[8][4]=3
    longueur[4][9]=longueur[9][4]=2
    longueur[5][6]=longueur[6][5]=1
    longueur[5][8]=longueur[8][5]=4
    longueur[6][8]=longueur[8][6]=3
    longueur[7][9]=longueur[9][7]=2
    longueur[8][9]=longueur[9][8]=1


#######Algorithme de Dijkstra########
def ChoixATraiterMin(traite,dist):
    n=len(traite)
    min=10000
    indiceMin=-1
    #
    # A COMPLETER
    #
    return indiceMin

def Dijkstra(G,longueur,pere,dist):
    n=len(G)
    traite=[0]*n
    dist[0]=0
    pere[0]=0
    nbtraite=1
    #while nbtraite<n:
    #
    # A COMPLETER
    #


#######Programme Principal########
points=[]
G=[]
longueur=[]
InitGraphFix(points, G, longueur)
AfficheGraph(points, G)

print("Calcul de distance avec Dijkstra:")
n=len(G)
dist=[10000]*n
pere=[-1]*n
Dijkstra(G,longueur,pere,dist)

print("Pere:",pere)
print("Distance:",dist)
#AfficheGraphEtArbre(points,G,pere)

