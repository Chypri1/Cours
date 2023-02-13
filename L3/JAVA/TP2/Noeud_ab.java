import java.lang.Math;
import java.util.ArrayList;
import java.util.Collections;



public class Noeud_ab extends Noeud {
    Noeud_ab gauche,droite;
    public Noeud_ab (Object val, Noeud_ab pere,Noeud_ab g,Noeud_ab d){
        super(val,pere);
        this.gauche = g;
        this.droite = d;
    }

/**
 * Vérifie si un noeud est une feuille (pas de sous-noeud)
 * @return true si c'est une feuille, false sinon
 */
    boolean estFeuille(){
        return this.gauche == null & this.droite  == null;
    }

/**
 * Ajoute un nouveau noeud à l'arbre
 * @param v valeur à ajouter
 */
    public void ajout(Object v){
        if((int)Math.random()==1){ // le noeud sera ajouté dans les fils actuelle si il y a de la place
          if((this.gauche == null)){
            this.gauche= new Noeud_ab(v, this, null, null);
          }
          else if(this.droite== null){
            this.droite= new Noeud_ab(v, this, null, null);
          }
        }
        else{
          if(Math.random()==0){
            this.droite.ajout(v);
          }
          else{
            this.gauche.ajout(v);
          }
        }
      }
/**
* Recherche un noeud dans l'arbre
* @param v valeur recherchée
* @return le noeud correspondant à la valeur recherchée, null si non trouvé
*/
      public Noeud_ab chercher(Object v){
        if(this.compareTo(v)==0){
          return this;
        }
        else if(this.gauche!=null)
          this.gauche.chercher(v);
        else if(this.droite!=null)
          this.droite.chercher(v);
        
        return null;
      }

      
  Noeud_ab noeud_gauche(){
    if(gauche == null) 
      return this;
    else 
      return this.gauche.noeud_gauche();
  }

  Noeud_ab enlever_succ(){
    if(this.gauche == null) 
      return this.droite;
    else{
      this.gauche = this.gauche.enlever_succ();
      return this;
    }
  }
/**
*@param v valeur à enlever
*@return le noeud racine de l'arbre après suppression
*/

  public Noeud_ab enlever(Object v){
    if (this.compareTo(v)<0){           // v est inférieur à this.valeur
        if(this.gauche == null) 
          return this;
        else{
          this.gauche = this.gauche.enlever(v);
          return this;
        }
    }
    else if(this.compareTo(v)>0){     // v est supérieur à this.valeur
        if(this.droite == null) 
          return this;
        else{
          this.droite = this.droite.enlever(v);
          return this;
        }
    }
    else{
        if(this.gauche == null) 
          return this.droite;
        else if(droite == null) 
          return this.gauche;
        else{
            Noeud_ab succ = this.droite.noeud_gauche();
            succ.droite = this.droite.enlever_succ();
            succ.gauche = this.gauche;
            return succ;
        }
    }
  }

  public void afficher(){
    System.out.println(this.valeur);
  }

/**
*Calcule la hauteur de l'arbre
*@return hauteur de l'arbre
*/
      public int hauteur(){
        return(this.hauteurBis(0));
    }

/**
*Calcule la hauteur de l'arbre en parcourant les sous-noeuds récursivement
*@param hauteur hauteur actuelle
*@return hauteur de l'arbre
*/
    private int hauteurBis(int hauteur){
        ArrayList<Integer> liste_max= new ArrayList<>();
        if(this.estFeuille()){
            return hauteur;
        }
        else if(this.gauche!= null){
            liste_max.add( this.gauche.hauteurBis(hauteur+1));
        }
        else if(this.droite!= null){
            liste_max.add( this.droite.hauteurBis(hauteur+1));
        }
        return(Collections.max(liste_max));
    }

/**
*Effectue un parcours préfixe de l'arbre en visitant d'abord la racine, puis les sous-noeuds gauche et droit récursivement.
*La méthode afficher() est utilisée pour afficher la valeur du noeud courant avant de continuer à parcourir les sous-noeuds.
*/
    protected void parcours_prefixe(){
      this.afficher();
      if(this.gauche!=null)
        this.gauche.parcours_prefixe();
      if(this.droite!=null)
        this.droite.parcours_prefixe();
    }

/**
*Effectue un parcours postfixe de l'arbre en visitant d'abord les sous-noeuds gauche et droit récursivement, puis la racine.
*La méthode afficher() est utilisée pour afficher la valeur du noeud courant après avoir parcouru les sous-noeuds.
*/

    protected void parcours_postfixe(){
      if(this.gauche!=null)
        this.gauche.parcours_prefixe();
      if(this.droite!=null)
        this.droite.parcours_prefixe();
      this.afficher();
    }
 
}
