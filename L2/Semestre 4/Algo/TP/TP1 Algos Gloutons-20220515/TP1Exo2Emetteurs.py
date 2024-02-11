from random import *
from math import sqrt
from itertools import *
import matplotlib.pyplot as plt

def AfficheMaisons(Maison):
    n=len(Maison)
    plt.plot([m[0] for m in Maison],[m[1] for m in Maison],'bo',markersize =3,label='maison')
    plt.title(str(n)+' Maisons')
    plt.legend()
    plt.axis('equal')
    plt.show()

def AfficheEmetteurs(Maison,Emetteur,rayon):
    n=len(Maison)
    fig, ax = plt.subplots()
    for i in range(n):
        if Emetteur[i]==1:
            circle=plt.Circle(Maison[i],rayon, color='r')
            ax.add_artist(circle)
    AfficheMaisons(Maison)


def GenererMaisons(Maison,n):
    #
    # A remplir
    #
    pass

def Couvre(Maison,i,j):
    #
    # A remplir
    #
    pass


def choixMaison(Maison,MaisonsRestantes):#MaisonsRestantes[i]=0 ssi i n'est pas couverte
    i0=-1
    #
    # A remplir
    #
    return i0

#Approx gloutonne
def choixEmetteurGlouton(Maison):
    n=len(Maison)
    Emetteur=[0]*n
    MaisonsRestantes=[0]*n
    #
    # A remplir
    #
    return Emetteur
    
    
rayon=120 # rayon de l'émetteur
n=100 #nombre de maisons
Maison=[] #contient les coordonnees cartesiennes des maisons dans [1,1000]x[1,1000]
GenererMaisons(Maison,n)
AfficheMaisons(Maison)
Emetteur=choixEmetteurGlouton(Maison)
print("L'algo glouton place",len(Emetteur),"émetteurs")
AfficheEmetteurs(Maison,Emetteur,rayon)
