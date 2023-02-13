public class Personne {
    String nom ;
    int age ;
    Personne ( String nom , int age ) {
    this.nom = nom ;
    this.age = age ;
    }
    String getNom ( ) {
    return this.nom ;
    }
    int getAge ( ) {
    return this.age ;
    }
    void setAge (int a) {
    this.age = a ;
    }

    public String toString(){
        return "nom : "+this.nom +" age : " +this.age;
    }

    public static void main(String args[]){

        Personne pers1= new Personne("didier",45);
        Personne pers2= new Personne("yvon",12);

       
        System.out.println(pers1.toString());

        System.out.println(pers2.toString());

        pers1.setAge(5);
        System.out.println(pers1.toString());

        System.exit(0);
    }
}