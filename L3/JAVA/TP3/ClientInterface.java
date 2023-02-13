import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * Cette interface représente les méthodes utilisées par les clients dans un jeu de Morpion en réseau.
 * Les clients implémentent cette interface pour pouvoir communiquer avec le serveur.
 * @throws RemoteException
 * @author PENNACHI
 */
public interface ClientInterface extends Remote{
    
    /**
     * Mise à jour de l'affichage du Morpion sur l'interface du client.
     * @param c
     * @param x
     * @param y
     * @throws RemoteException
     */
    public void update(char c,int x,int y) throws RemoteException;

    /**
     * Obtention du symbole (X ou O) du joueur.
     * @return Le symbole du joueur
     * @throws RemoteException
     */
    public char symbole() throws RemoteException;
    
    /**
     * Définition du symbole (X ou O) du joueur.
     * @param c
     * @throws RemoteException
     */
    public void setSymbole(char c) throws RemoteException;
    
    /**
     * Création d'une nouvelle fenêtre pour l'affichage du Morpion sur l'interface du client.
     * @throws RemoteException
     */
    public void newFenetre() throws RemoteException;

    /**
     * Attente de l'action du joueur sur l'interface du client.
     * @throws RemoteException
     */
    public void attend() throws RemoteException;

    /**
     * Attente de la connexion d'un second joueur sur l'interface du client.
     * @throws RemoteException
     */
    public void attendJ2() throws RemoteException;

    /**
     * Notification au joueur qu'il peut jouer sur l'interface du client.
     * @throws RemoteException
     */
    public void joue() throws RemoteException;

    /**
     * Notification au joueur d'une égalité sur l'interface du client.
     * @throws RemoteException
     */
    public void egalite() throws RemoteException;

    /**
     * Notification au joueur d'une victoire sur l'interface du client.
     * @throws RemoteException
     */
    public void gagne() throws RemoteException;

    /**
     * Notification au joueur d'une défaite sur l'interface du client.
     * @throws RemoteException
     */
    public void perdu() throws RemoteException;

    /**
     * Attends que le joueur redémarre la partie
     * @throws RemoteException
     */
    public void waitPlayerRestart() throws RemoteException;
    
    /**
     * Le joueur refuse de redémarrer la partie
     * @throws RemoteException
     */
    public void refuser() throws RemoteException;

    /**
     * Redémarre la partie
     * @throws RemoteException
     */
    public void restart() throws RemoteException;
}
