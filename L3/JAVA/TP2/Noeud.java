import java.lang.Comparable;

/**
* Classe Noeud représente un noeud d'un arbre.
* Il contient une valeur de type Object et un référence à son père de type Noeud.
*/

public class Noeud implements Comparable{
    
    Object valeur;
    protected Noeud pere;

/**
* Constructeur de la classe Noeud
* @param val valeur à stocker dans le noeud
* @param pere référence vers le noeud père
*/

    public Noeud(Object val, Noeud pere){
        this.valeur=val;
        this.pere=pere;
    }

/**
 * Compare la valeur de l'objet courant à celle passée en paramètre.
 * @param valeur valeur à comparer
 * @return un entier inférieur, égal ou supérieur à 0 en fonction de l'ordre de comparaison
 */

    @Override
    public int compareTo(Object valeur) {
        if(valeur instanceof String && this.valeur instanceof String)
            return ((String) this.valeur).compareTo((String)valeur);
        else if(valeur instanceof Integer && this.valeur instanceof Integer)
            return ((Integer) this.valeur).compareTo((Integer)valeur);
        return 0;
    }

/**
 * Récupère la valeur stockée dans le noeud
 * @return la valeur stockée dans le noeud
 */

    public Object getValue(){
        return valeur;
    }


/**
 * Change la valeur stockée dans le noeud
 * @param valeur nouvelle valeur à stocker
 */
 
    public void setValue(Object valeur){
        this.valeur = valeur;
    }
}
