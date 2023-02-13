import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * Cette interface définit les méthodes à distance pouvant être invoquées sur l'objet Morpion.
 * @version 5.0
 * @author TAN
 */

public interface MorpionInterface extends Remote{

       /**
        * Initialise une nouvelle partie avec un client.
        * @param c
        * @throws RemoteException
        */
       public void newPartie(ClientInterface c) throws RemoteException;
       /**
        * Définit la valeur d'une case sur le plateau de jeu.
        * @param c
        * @param x
        * @param y
        * @throws RemoteException
        */
       public void setCase(char c,int x,int y) throws RemoteException;

       /**
        * Ajoute un client à la liste de joueurs.
        * @param c
        * @throws RemoteException
        */
       public void add(ClientInterface c) throws RemoteException;
       /**
        * Supprime un client de la liste de joueurs.
        * @param c
        * @throws RemoteException
        */
       public void remove(ClientInterface c) throws RemoteException;
       /**
        * Renvoie le nombre de joueurs enregistrés.
        * @return
        * @throws RemoteException
        */
       public int nbrJoueur() throws RemoteException;
       /**
        * Demande à l'autre joueur si il veut recommencer la partie.
        * @param c
        * @throws RemoteException
        */
       public void waitPlayerRestart(ClientInterface c) throws RemoteException;
       /**
        * Dit à l'autre joueur qu'il a refuser sa demande de recommencer la partie.
        * @param c
        * @throws RemoteException
        */
       public void refuser(ClientInterface c) throws RemoteException;
}
