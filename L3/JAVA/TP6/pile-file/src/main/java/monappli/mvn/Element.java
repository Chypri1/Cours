package monappli.mvn;

public class Element {
    int valeur;
    Element prec, suiv;

    /**
     * Constructeur Element
     * @param valeur
     */
    
    Element(int valeur,Element suiv,Element prec){
        this.valeur = valeur;
        this.prec = prec;
        this.suiv = suiv;
    }

    /**
     * Retourne la valeur
     */

    public int getValeur(){
        return valeur;
    }

    /**
     * ajoute l'élément précédent 
     * @param prec
     */

    public void setPrec(Element prec){
        this.prec=prec;
    }

    /**
     * ajoute l'élément suivant 
     * @param prec
     */

     public void setSuiv(Element suiv){
        this.suiv=suiv;
    }

    public void afficher(){
        System.out.println("Valeur : "+ valeur);
    }

    
}
