import java.net.InetAddress;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

import javax.swing.ImageIcon;

/**
 * Cette classe implémente l'interface ClientInterface pour représenter un client dans une partie de morpion en réseau.
 * Elle se connecte à un serveur qui utilise le protocole RMI en partageant l'objet
 * MorpionInterface pour jouer au jeu.
 * @author PENNACHI
 */
public class Client extends UnicastRemoteObject implements ClientInterface{
    
    /**
     * Objet implémentant l'interface MorpionInterface pour permettre la communication avec le serveur.
     */
    private MorpionInterface m;
    /**
     * Caractère représentant le symbole du joueur (X ou O).
     */
    private char symbole;
    /**
     * Interface graphique utilisée pour afficher le jeu.
     */
    private Interface fenetre;

    /**
     * Constructeur qui lance le client et effectue une connexion au serveur via RMI.
     * Affiche un message indiquant que le client est lancé.
     * @throws RemoteException
     */
    public Client() throws RemoteException{
        System.out.println("Lancement du client");
        try {
            System.out.println(InetAddress.getLocalHost().getHostAddress());
            String url="rmi://"+"172.18.245.209:2002"+"/TP3";
            this.m=(MorpionInterface)Naming.lookup(url);
            this.m.add(this);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Renvoie l'objet MorpionInterface
     * @return MorpionInterface
     */
    public MorpionInterface m(){
        return this.m;
    }

    /**
     * Renvoie le symbole
     * @return symbole
     */
    public char symbole(){
        return this.symbole;
    }

    /**
     * Renvoie l'objet Interface la fenetre
     * @return Interface
     */
    public Interface fenetre(){
        return this.fenetre;
    }

    /**
     * Affecte le symbole donnée en paramètre
     */
    public void setSymbole(char c){
        this.symbole=c;
    }
    
    /**
     * Affect une nouvelle fenetre
     */
    public void newFenetre(){
        this.fenetre=new Interface(this);
    }

    /**
     * Mis à jour du plateau du joueur
     * @param c
     * @param x
     * @param y
     */
    public void update(char c,int x,int y){
        if(c=='O'){
            this.fenetre.getButtons()[x][y].setIcon(new ImageIcon("cercle.gif"));
        }
        else 
            if(c=='X')
                this.fenetre.getButtons()[x][y].setIcon(new ImageIcon("croix.gif"));
    }


    /**
     * Demande à la fenetre d'attendre son tour
     */
    public void attend(){
        this.fenetre.attendre();
    }
    
    /**
     * Demande à la fenetre d'attendre un adversaire
     */
    public void attendJ2(){
        this.fenetre.attendreJ2();
    }

    /**
     * Demande à la fenetre de jouer
     */
    public void joue(){
        this.fenetre.joue();
    }

    /**
     * Demande à la fenetre d'afficher la fenetre d'égalité
     */
    public void egalite(){
        this.fenetre.egalite();
    }

    /**
     * Demande à la fenetre d'afficher la fenetre de victoire
     */
    public void gagne(){
        this.fenetre.gagne();
    }

    /**
     * Demande à la fenetre d'afficher la fenetre de loser
     */
    public void perdu(){
        this.fenetre.perdu();
    }

    /**
     * Demande à la fenetre d'afficher la fenetre de choix de l'acceptation du redémarrage de la partie
     */
    public void waitPlayerRestart(){
        this.fenetre.waitPlayerRestart();
    }

    /**
     * Demande à la fenetre de refuser la demande de rédémarrage de la partie
     */
    public void refuser(){
        this.fenetre.refuser();
    }

    /**
     * Demande à la fenetre de réinitialiser le plateau
     */
    public void restart(){
        this.fenetre.restart();
    }

    public static void main(String[] args){
        try {
            new Client();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
