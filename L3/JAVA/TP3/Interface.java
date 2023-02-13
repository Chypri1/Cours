import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.rmi.RemoteException;
import java.util.Random;

/**
 * Cette classe hérite de JFrame et représente ma fenêtre.
 * @author PENNACHI
 */
public class Interface extends JFrame{
    /**
     * Le client qui utilise cette fenetre
     */
    private Client c;
    /**
     * la matrice de boutons celà me facilite la gestion des coordonnées
     */
    private JButton[][] boutons=new JButton[3][3];
    /**
     * Le label qui affiche le tour d'un joueur
     */
    private JLabel label;
    /**
     * Le bouton quitter
     */
    private JButton quitter;
    /**
     * Le bouton rejouer
     */
    private JButton rejouer;
    /**
     * Le panel qui place tous les widget
     */
    private JPanel jp ;

/**
 * Sous-classe qui hérite de ActionListener qui représente l'évènement lors du clic du bouton quitter
 */
public class BoutonActionQuitter implements ActionListener {

    public void actionPerformed(ActionEvent e){
        System.out.println("Fin de l'application");
        dispose();
    }
}

/**
 * Sous-classe qui hérite de ActionListener qui représente l'évènement lors du clic du bouton rejouer
 */
public class BoutonActionRestart implements ActionListener{

    public void actionPerformed(ActionEvent e){
        System.out.println("Bouton rejouer appuyer");
        // appeler une méthode qui recommence
        String s=label.getText();
        attendre();
        label.setText(s);
        rejouer.setEnabled(false);
        try {
            c.m().waitPlayerRestart(c);
        } catch (RemoteException e1) {
            e1.printStackTrace();
        }
    }
}

/**
 * Sous-classe qui hérite de ActionListener qui représente l'évènement lors du clic d'un des boutons du plateau
 */
public class BoutonActionJouer implements ActionListener{
    public void actionPerformed(ActionEvent e){
        if(((JButton)e.getSource()).getIcon()==null){
            ImageIcon image;
            if(c.symbole()=='X'){
                image = new ImageIcon("croix.gif");
                
            }else
                image = new ImageIcon("cercle.gif");
            ((JButton)e.getSource()).setIcon(image);
        }
        try {
            int x=0,y=0;
            for(x=0;x<3;x++){
                for(y=0;y<3;y++)
                    if(((JButton)e.getSource()).equals(boutons[x][y])){
                        c.m().setCase(c.symbole(),x,y);
                    }
            }
        } catch (Exception ex) {
        }
        
    }
} 

    /**
     * Constructeur de cette classe
     * @param c
     */
    public Interface(Client c){
        super("Morpion");
        this.c=c;
        this.setSize(800, 600);
        this.addWindowListener(new WindowAdapter(){ //Ajout d'un WindowListener pour détecter lorsque l'utilisateur clique sur le bouton rouge 
            public void windowClosing(WindowEvent e){
                try {
                    c.m().remove(c);
                    System.exit(0);
                } catch (RemoteException e1) {
                    e1.printStackTrace();
                }
            }
        });

        jp= new JPanel(new GridLayout(4,3));
        BoutonActionRestart restart=new BoutonActionRestart();
        BoutonActionQuitter quit=new BoutonActionQuitter();
        BoutonActionJouer jouer=new BoutonActionJouer(); 


        quitter=new JButton("quitter");
        quitter.addActionListener(quit);
        jp.add(quitter);
        jp.add(label=new JLabel("",SwingConstants.CENTER));
        rejouer=new JButton("rejouer");
        rejouer.addActionListener(restart);
        jp.add(rejouer);

        int k=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                boutons[i][j]=new JButton(""+k,null);
                boutons[i][j].addActionListener(jouer);
                jp.add(boutons[i][j]);
                k++;
            }
        }

        this.add(jp);
        //this.pack();
        this.setVisible(true);

    }

    /**
     * Renvoie la matrice de boutons
     * @return Les boutons
     */
    public JButton[][] getButtons(){
        return this.boutons;
    }

    /**
     * Redéfinition de la méthode dispose qui ferme la fenetre, je demande en plus au serveur de retirer ce client.
     */
    @Override
    public void dispose(){
        super.dispose();
        try {
            c.m().remove(c);
        } catch (RemoteException e1) {
            e1.printStackTrace();
        }
        System.exit(0);
    }



    /**
     * Cette méthode désactive tous les boutons sauf le quitter et change le label
     */
    public void attendreJ2(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                this.boutons[i][j].setEnabled(false);
        }
        this.rejouer.setEnabled(false);
        this.label.setText("Attente d'un adversaire");
    }

    /**
     * Cette méthode désactive tous les boutons sauf les boutons quitter et rejoeur et change le label
     */
    public void attendre(){
        this.label.setText("Tour du Joueur adversaire");
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(ActionListener l: boutons[i][j].getActionListeners())
                    boutons[i][j].removeActionListener(l);
    }

    /**
     * Cette méthode réactive tous les boutons et change le label
     */
    public void joue(){
        this.label.setText("A votre tour");
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++){
                boutons[i][j].addActionListener(new BoutonActionJouer());
                boutons[i][j].setEnabled(true);
            }
        this.rejouer.setEnabled(true);
    }

    /**
     * Affiche un jdialog lors d'un égalité
     */
    public void egalite(){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(ActionListener l: boutons[i][j].getActionListeners())
                    boutons[i][j].removeActionListener(l);

        JDialog jd=new JDialog(this);
        jd.setSize(400,300);
        jd.setLocationRelativeTo(this);
        jd.setAlwaysOnTop(true);
        jd.setModalityType(Dialog.DEFAULT_MODALITY_TYPE);

        JPanel jp=new JPanel(new BorderLayout());
        jp.add(new JLabel("Egalite dommage :/",SwingConstants.CENTER),BorderLayout.NORTH);
        Random rand=new Random();
        JLabel egalite;
        if(rand.nextInt(10)==5)
            egalite=new JLabel(new ImageIcon("spiderman4.gif"));
        else egalite =new JLabel(new ImageIcon("egalite.gif"));
        jp.add(egalite,BorderLayout.CENTER);
        JButton close=new JButton("Close");
        close.addActionListener((e)->{jd.dispose();});
        jp.add(close,BorderLayout.SOUTH);
        jd.add(jp);
        System.out.println("Egalite dommage :^D");
        javax.swing.SwingUtilities.invokeLater(()->{jd.setVisible(true);});//Obligatoire d'ouvrir un nouveau thread car les thread RMI et AWT sont surchargés.
    }

    /**Affiche un JDialog lors d'une victoire */
    public void gagne(){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(ActionListener l: boutons[i][j].getActionListeners())
                    boutons[i][j].removeActionListener(l);

        JDialog jd=new JDialog(this);
        jd.setSize(300,200);
        jd.setLocationRelativeTo(this);
        jd.setAlwaysOnTop(true);
        jd.setModalityType(Dialog.DEFAULT_MODALITY_TYPE);

        JPanel jp=new JPanel(new BorderLayout());
        jp.add(new JLabel("Tu as gagne",SwingConstants.CENTER),BorderLayout.CENTER);
        JButton close=new JButton("Close");
        close.addActionListener((e)->{jd.dispose();});
        jp.add(close,BorderLayout.SOUTH);
        jd.add(jp);
        System.out.println("Tu as gagne");
        javax.swing.SwingUtilities.invokeLater(()->{jd.setVisible(true);}); //Obligatoire d'ouvrir un nouveau thread car les thread RMI et AWT sont surchargés.

    }

    /**
     * Affiche un JDialog lors d'une lose
     */
    public void perdu(){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(ActionListener l: boutons[i][j].getActionListeners())
                    boutons[i][j].removeActionListener(l);
        
        JDialog jd=new JDialog(this);
        jd.setSize(300,200);
        jd.setLocationRelativeTo(this);
        jd.setAlwaysOnTop(true);
        jd.setModalityType(Dialog.DEFAULT_MODALITY_TYPE);

        JPanel jp=new JPanel(new BorderLayout());
        jp.add(new JLabel("Tu as perdu",SwingConstants.CENTER),BorderLayout.CENTER);
        JButton close=new JButton("Close");
        close.addActionListener((e)->{jd.dispose();});
        jp.add(close,BorderLayout.SOUTH);
        jd.add(jp);
        System.out.println("Tu as perdu");
        javax.swing.SwingUtilities.invokeLater(()->{jd.setVisible(true);});//Obligatoire d'ouvrir un nouveau thread car les thread RMI et AWT sont surchargés.

    }

    /**
     * Affiche un JDialog lors que l'autre joueur demande un rematch 
     */
    public void waitPlayerRestart(){
        JDialog jd=new JDialog(this);
        JPanel p=new JPanel(new BorderLayout());
        JPanel buttons=new JPanel(new GridLayout(1,2));
        JButton accepter=new JButton("Accepter");
        accepter.addActionListener((e)->{jd.dispose();
            try {
                c.m().newPartie(c);
            } catch (RemoteException e1) {
            e1.printStackTrace();
        }});
        JButton refuser=new JButton("Refuser");
        refuser.addActionListener((e)->{jd.dispose();
            try {
            c.m().refuser(c);
            } catch (RemoteException e1) {
            e1.printStackTrace();
        }});
        buttons.add(accepter);
        buttons.add(refuser);
        p.add(new JLabel("L'adversaire veut rejouer le match",SwingConstants.CENTER),BorderLayout.CENTER);
        p.add(buttons,BorderLayout.SOUTH);
        jd.add(p);
        jd.setSize(300,200);
        jd.setLocationRelativeTo(this);
        jd.setAlwaysOnTop(true);
        jd.setModalityType(Dialog.DEFAULT_MODALITY_TYPE);
        javax.swing.SwingUtilities.invokeLater(()->{jd.setVisible(true);});
    }

    /**
     * Réinitialise tous les boutons
     */
    public void restart(){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                boutons[i][j].setIcon(null);
        if(label.getText().equals("A votre tour")){
            joue();
        }
        else attendre();
    }

    /**
     * Reprend la partie
     */
    public void refuser(){
        if(label.getText().equals("A votre tour")){
            joue();
        }
        else attendre();
        this.rejouer.setEnabled(true);
    }


}