public class Personne extends Displayable {


    int vitesse;
    int direction;

    Personne(int dir,int vit,int x, int y,int c){
        //super(x, y, c); /* revoir le super avec tony */
        this.direction = dir;
        this.vitesse = vit;
    }

    public void move (){
        this.direction=2;
        this.vitesse = 1;
    }
}
