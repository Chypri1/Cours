import numpy
import pickle
class Mixture:
    def __init__(self):
        self.w = numpy.empty(1) # des numpy arrays vide de 1 dimension
        self.mu= numpy.empty(1)
        self.invcov= numpy.empty(1)
        self.cst= numpy.empty(1)
        self.det= numpy.empty(1)
        
    def __repr__(self): #c'est comme la fonction str ça renvoie une chaine de caractère
        return f'Mixture("{self.w}","{self.mu}","{self.invcov}","{self.cst}","{self.det}")'
    
    
    def read(f): #lit un objet de type Mixture à partir d'un objet pickle(pareil que Marshall c'est une serialisation).
        with open('data','rb') as f: print(pickle.load(f)) #je prend le fichier pris en paramètre pour charger l'objet se trouvant dedans
        f.close()
        
    @classmethod
    def somme(x,y): #retourne la somme des deux arguments
        return x+y
    
    


    