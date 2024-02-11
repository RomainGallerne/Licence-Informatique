import matplotlib.pyplot as plt

###########################################

def Init(E,n1,n2):
    #
    # A COMPLETER
    #
    
    pass


def DistanceEdition(S1,S2,E):
    n1=len(S1)
    n2=len(S2)
    Init(E,n1,n2)
    
    #
    # A COMPLETER
    #
        
    return E[n2][n1]    

def Alignement(S1,S2,E):
    i1=len(S1)
    i2=len(S2)
    #while i1>0 and i2>0:
        #
        # A COMPLETER
        #    
        
    #while i1>0:
        #
        # A COMPLETER
        #    
     
    #while i2>0:
        #
        # A COMPLETER
        #    
    
    return S1,S2        

#######Programme Principal########

S1=input("Entrer S1 la première chaine de caractères: ")
S2=input("Entrer S2 la seconde chaine de caractères: ")
print()

n1=len(S1)
n2=len(S2)
E = [[0 for i in range(0,n1+1)] for j in range(0,n2+1)]

print("Les deux chaines S1 et S2 sont à distance: ", DistanceEdition(S1, S2,E),'\n')

print("Tableau des distances partielles: ")
for i in range(0,n2+1):
    print(E[i])
print()

A,B=Alignement(S1, S2, E)
print("Alignement de S1 et S2:")
print(A)
print(B)

