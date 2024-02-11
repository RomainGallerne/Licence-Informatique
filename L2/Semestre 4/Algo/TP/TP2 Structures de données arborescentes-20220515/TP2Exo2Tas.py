import matplotlib.pyplot as plt
from random import *

#######Classe Noeud#######
class Noeud:
   def __init__(self, val=None):
      self.val = val
      self.FilsG = None
      self.FilsD = None
      self.Pere = None

   def HauteurNoeud(self):
       hg=0
       hd=0
       if self.FilsG!=None:
           hg=self.FilsG.HauteurNoeud()
       if self.FilsD!=None:
           hd=self.FilsD.HauteurNoeud()
       return max(hd,hg)+1

 
#######Classe Arbre Binaire#######
class ArbreBinaire:
   def __init__(self):
        self.rac=None

   def AjoutRacine(self,val):
       nouvNoeud=Noeud(val)
       self.rac=nouvNoeud

   def AjoutNoeudFilsG(self,x,val):
       if x.FilsG==None:
           nouvNoeud=Noeud(val)
           x.FilsG=nouvNoeud
           nouvNoeud.Pere=x

   def AjoutNoeudFilsD(self,x,val):
       if x.FilsD==None:
           nouvNoeud=Noeud(val)
           x.FilsD=nouvNoeud
           nouvNoeud.Pere=x

   def DessinArbreNiveau(self,nx,rect,dy):
       if nx==None: return
       x1, x2, y1, y2 = rect
       xm = (x1 + x2) // 2
       self.DessinArbreNiveau(nx.FilsG, (x1, xm, y1, y2 - dy), dy)
       self.DessinArbreNiveau(nx.FilsD, (xm, x2, y1, y2 - dy), dy)
       plt.text(xm + 10, y2, str(nx.val), fontsize=10, horizontalalignment='left',verticalalignment='bottom')
       if nx.FilsG!=None:
          a, b = ((xm, (x1 + xm) // 2), (y2, y2 - dy))
          plt.plot(a, b, 'k', marker='s')
       if nx.FilsD!=None:
          c, d = ((xm, (x2 + xm) // 2), (y2, y2 - dy))
          plt.plot(c, d, 'k', marker='s')

   def DessinArbre(self):
        d = 512
        pad = 20
        dy = (d - 2 * pad) / self.rac.HauteurNoeud()
        self.DessinArbreNiveau(self.rac, (pad, d - pad, pad, d - pad), dy)
        plt.axis([0, d, 0, d])
        plt.axis('off')
        plt.show()

###########################################

def DessineTasArbre(L):
    arbre=ArbreBinaire()
    if len(L)!=0:
        arbre.AjoutRacine(L[0])
        TabNoeud=[arbre.rac]
        for i in range(1,len(L)):
            if i%2==1:
                arbre.AjoutNoeudFilsG(TabNoeud[(i-1)//2], L[i])
                TabNoeud.append(TabNoeud[(i-1)//2].FilsG)
            else:
                arbre.AjoutNoeudFilsD(TabNoeud[(i-1)//2], L[i])
                TabNoeud.append(TabNoeud[(i-1)//2].FilsD)
        arbre.DessinArbre()
                

def TableauAuHasard(n):
    TabHasard=[]
    #
    # A COMPLETER
    # 
    return TabHasard

def Remonter(L,i):
    #
    # A COMPLETER
    #

def CreerTas(L):
    Tas=[]
    #
    # A COMPLETER
    #
    return Tas

#######Tas########
L=[15,9,12,4,8,13,1,2,32,5,7,3]
DessineTasArbre(L)
#DessineTasArbre(CreerTas(L))

#DessineTasArbre(CreerTas(TableauAuHasard(100)))