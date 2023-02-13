package monappli.mvn;


import java.util.ArrayDeque;
import java.util.Iterator;

import javax.lang.model.element.Element;

 
public class Deque{
    Element tete;
    Element queue;

    Deque(){
        tete = null;
        queue = null;
        
    }

    public void ajout_tete(int v){
        Element nouv = new Element(v);
        nouv.valeur = v;
        nouv.suiv = tete;
        nouv.prec = null;
        if(this.deque_vide()){
            queue = nouv;
        }else{
            tete.prec = nouv;
        }
        tete = nouv;
    }

    public boolean deque_vide(){
        return this.tete.equals(null);

    }

    public int oter_tete(){
        if(this.tete!=null){
        Element v=this.tete;
        this.tete.suiv.prec=null;
        this.tete.suiv=this.tete;
        return v.valeur;
        }
        else 
            System.out.println("le deque est vide");
        return null;
    }

    public void ajout_queue(int v){
        if(this.queue!=null){
        this.queue.suiv=new Element(v,null,this.queue);
        this.queue.suiv=this.queue;
        }
        else{
            this.queue=new Element(v,null,null);
            this.tete=this.queue;
        }

    }
    public int oter_queue(){
        if(this.queue!=null){
            Element v=this.queue;
            this.queue.prec=this.queue;
        }
        return null;

    }

    public String toString(){
        return null;
    }
}

