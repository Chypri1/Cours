import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

/**
 * La classe Morpion étend UnicastRemoteObject et implémente l'interface MorpionInterface.
 * Elle représente une partie de morpion en réseau.
 * @author Tan
 */
public class Morpion extends UnicastRemoteObject implements MorpionInterface{
    /**
     * La table de jeu, une matrice de caractères 3x3.
     */
    private char[][] table;
    /**
     * La liste de joueurs participant à la partie
     */
    private ArrayList<ClientInterface> joueurs;
    /**
     * Le joueur qui joue actuellement.
     */
    private char joueur_courant;
    
    /**
     * Constructeur de cette classe.
     * Il initialise la table de jeu, la liste des joueurs et le joueur courant.
     * @throws RemoteException
     */
    Morpion() throws RemoteException{
        super();
        this.table=new char[3][3];
        this.joueurs=new ArrayList<>();
        this.joueur_courant='O';
        newPartie(null);
    }

    /**
     * Renvoie le nombre de joueurs dans la liste.
     */
    public int nbrJoueur() throws RemoteException{
        return joueurs.size();
    }

    /**
     * La méthode add ajoute un joueur à la partie de morpion.
     * Elle vérifie si le nombre de joueurs est inférieur ou égal à 2,
     * puis définit le symbole du joueur et met à jour la table de jeu pour refléter les actions du joueur.
     * @param c
     * @throws RemoteException
     */
    public synchronized void add(ClientInterface c) throws RemoteException{
        if(nbrJoueur()<=2){
            if(nbrJoueur()==0){
                this.joueurs.add(c);
                c.setSymbole('O');
                c.newFenetre();
                c.attendJ2();
            }else 
                if(joueurs.get(0)==null){
                    this.joueurs.set(0,c);
                    c.setSymbole('O');
                    c.newFenetre();
                    refresh(c);
                    if(nbrJoueur()!=2)
                        c.attendJ2();
                    else 
                        if(this.joueurs.get(1)==null)
                            c.attendJ2();
                        else{
                            if(joueur_courant=='O'){
                                joueurs.get(0).joue();
                                joueurs.get(1).attend();
                            }
                            else{
                                joueurs.get(1).joue();
                                joueurs.get(0).attend();
                            }
                        }
                }
                else 
                    if(nbrJoueur()==1){
                        this.joueurs.add(c);
                        c.setSymbole('X');
                        c.newFenetre();
                        if(joueur_courant=='O'){
                            joueurs.get(0).joue();
                            joueurs.get(1).attend();
                        }
                        else{
                            joueurs.get(1).joue();
                            joueurs.get(0).attend();
                        }
                    }else 
                        if(joueurs.get(1)==null){
                            this.joueurs.set(1,c);
                            c.setSymbole('X');
                            c.newFenetre();
                            refresh(c);
                            if(joueur_courant=='O'){
                                joueurs.get(0).joue();
                                joueurs.get(1).attend();
                            }
                            else{
                                joueurs.get(1).joue();
                                joueurs.get(0).joue();
                                joueurs.get(0).attend();
                            }
                        }
        }
    }

    /**
     * cette méthode permet de supprimer un joueur de la liste de joueurs connectés au jeu de Morpion.
     * Si le joueur à supprimer était le premier de la liste, il sera remplacé par null dans la liste.
     * Si le seconde joueur était connecté, il sera mis en attente pour la connexion d'un nouveau joueur.
     * De même, si le joueur à supprimer était le second de la liste, il sera remplacé par null dans la liste.
     * et si le premier joueur était connecté, il sera mis en attente pour la connexion d'un nouveau joueur.
     * @param c
     * @throws RemoteException
     */
    public synchronized void remove(ClientInterface c) throws RemoteException{
        if(joueurs.get(0).equals(c)){
            joueurs.set(0,null);
            if(nbrJoueur()==2)
                if(joueurs.get(1)!=null)
                    joueurs.get(1).attendJ2();
        }else{
            joueurs.set(1,null);
            if(nbrJoueur()==2)
                if(joueurs.get(0)!=null)
                    joueurs.get(0).attendJ2();
        }
    }

    /**
     * Cette méthode est utilisée pour rafraîchir l'interface du client avec les dernières données du tableau.
     * 
     * @param c 
     * @throws RemoteException
     */
    private void refresh(ClientInterface c) throws RemoteException{
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                c.update(table[i][j], i, j);
    }

    /**
     * Cette méthode démarre une nouvelle partie du jeu.
     * 
     * @param c 
     * @throws RemoteException 
     */
    public synchronized void newPartie(ClientInterface c) throws RemoteException{
        for(int i=0; i<3;i++)
            for(int j=0;j<3;j++)
                this.table[i][j]='N';
        if(c!=null){
            for(ClientInterface ci : joueurs){
                ci.restart();
            }
        }
    }

    /**
     * Cette méthode passe le tour à l'autre joueur.
     * 
     * @param c 
     * @throws RemoteException
     */
    private void nextTurn(char c) throws RemoteException{
        if(c==joueurs.get(0).symbole()){
            joueurs.get(1).joue();
            joueurs.get(0).attend();
            joueur_courant='X';
        }
        else{
            joueurs.get(0).joue();
            joueurs.get(1).attend();
            joueur_courant='O';
        }
    }

    /**
     * Cette méthode permet de définir une case du tableau de jeu.
     * Cette méthode est synchronisée, ce qui signifie qu'elle est accessible par une seule instance à la fois.
     * Elle vérifie aussi si le jeu est gagné ou égalité.
     * @param c
     * @param x
     * @param y
     * @throws RemoteException
     */
    public synchronized void setCase(char c,int x,int y) throws RemoteException{
        if(this.table[x][y]=='N'){
            this.table[x][y]=c;
            if(c==joueurs.get(0).symbole()){
                joueurs.get(1).update(c,x,y);
                nextTurn(joueurs.get(0).symbole());
            }else{
                joueurs.get(0).update(c,x,y);
                nextTurn(joueurs.get(1).symbole());
            } 

        }
            
        if(gagne(x,y)){
            if(c==joueurs.get(0).symbole()){
                joueurs.get(0).gagne();
                joueurs.get(1).perdu();
            }
            else{
                joueurs.get(1).gagne();
                joueurs.get(0).perdu();
            }
        }
        else
            if(egalite()){
                joueurs.get(0).egalite();
                joueurs.get(1).egalite();
            }
    }


    /**
     * Méthode pour déterminer si un joueur a gagné le jeu.
     * @param x
     * @param y
     * @return true si un joueur a gagné le jeu, false sinon.
     */
    private synchronized boolean gagne(int x,int y){
        return
        (((table[x][0] == table[x][1]) &&
          (table[x][1] == table[x][2])) ||
         ((table[0][y] == table[1][y]) &&
          (table[1][y] == table[2][y])) ||
         ((x==y)&&
          (table[0][0] == table[1][1]) &&
          (table[1][1] == table[2][2])) ||
         ((x+y == 2) &&
          (table[0][2] == table[1][1]) &&
          (table[1][1] == table[2][0])));
    }

    /**
     * Méthode pour déterminer si le jeu est terminé avec une égalité.
     * @return true si le jeu est terminé avec une égalité, false sinon.
     */
    private synchronized boolean egalite(){
        for(int x=0;x<3;x++){
            for(int y=0;y<3;y++){
                if(table[x][y]=='N')
                    return false;
            }
        }
        return true;
    }

    /**
     * Cette méthode attend que le joueur associé au client donné redémarre la partie.
     * @param c
     * @throws RemoteException
     */
    public void waitPlayerRestart(ClientInterface c) throws RemoteException{
        if(c.equals(joueurs.get(0))){
            joueurs.get(1).waitPlayerRestart();
        }else joueurs.get(0).waitPlayerRestart();
    }


    /**
     * Cette méthode informe l'autre joueur associé à un autre client que la demande de redémarrage de la partie a été refusée.
     * @param c
     * @throws RemoteException
     */
    public void refuser(ClientInterface c)throws RemoteException{
        if(c.equals(joueurs.get(0))){
            joueurs.get(1).refuser();
        }else joueurs.get(0).refuser();
    }
}