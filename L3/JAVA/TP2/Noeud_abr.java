import java.util.ArrayList;
import java.util.Collections;


class Noeud_abr extends Noeud_ab {
 /**
 * Constructeur de la classe Noeud_abr
 * @param val valeur à stocker dans le noeud
 * @param pere référence vers le noeud père
 * @param g référence vers le sous-noeud gauche
 * @param d référence vers le sous-noeud droit
 */
  
  Noeud_abr gauche,droite;

  public Noeud_abr(Object val, Noeud_abr pere, Noeud_abr g, Noeud_abr d){
        super(val,pere,g,d);
  }

  /**
 * Ajoute un nouveau noeud à l'arbre
 * @param v valeur à ajouter
 */
  public void ajout(Object v){
    if(this.valeur == v){
        if(this.gauche == null)
          gauche = new Noeud_abr(v,this, null, null);
        else 
          this.gauche.ajout(v);
    }
    else{
      if(this.droite == null) 
        this.droite = new Noeud_abr(v,this, null, null);
      else 
        this.droite.ajout(v);
    }
  }

  /**
* Recherche un noeud dans l'arbre
* @param v valeur recherchée
* @return le noeud correspondant à la valeur recherchée, null si non trouvé
*/

  public Noeud_abr chercher(Object v){
    if(this.valeur == v) 
      return this;
    else if(this.compareTo(v)<0) { // si v est inférieur à this.valeur
      if(this.gauche == null) 
        return null;
      else return 
        this.gauche.chercher(v);
    }
    else{
        if(this.droite == null) 
          return null;
        else 
          return this.droite.chercher(v);
    }
  }

  Noeud_abr noeud_gauche(){
    if(gauche == null) 
      return this;
    else 
      return this.gauche.noeud_gauche();
  }

  Noeud_abr enlever_succ(){
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

  public Noeud_abr enlever(Object v){
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
            Noeud_abr succ = this.droite.noeud_gauche();
            succ.droite = this.droite.enlever_succ();
            succ.gauche = this.gauche;
            return succ;
        }
    }
  }



}