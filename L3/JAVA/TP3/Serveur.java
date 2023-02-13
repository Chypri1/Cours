import java.net.InetAddress;
import java.rmi.*;
import java.rmi.registry.LocateRegistry;

/**
 * Programme de test pour ouvrir un serveur utilisant le protocole RMI(Remote Method Invocation).
 */
public class Serveur {
    public static void main(String[] args){
        try {
            LocateRegistry.createRegistry(1099);
            System.out.println( "Serveur : Construction de l'implementation");
            Morpion rev = new Morpion();
            System.out.println("Objet Morpion lie dans le RMIregistry");
            String url="rmi://"+InetAddress.getLocalHost().getHostAddress()+"/TP3";
            Naming.rebind(url, rev);
        System.out.println("Attente des invocations des clients ...");
        }catch (Exception e) {
            System.out.println("Erreur de liaison de l'objet Reverse");
            System.out.println(e.toString());
        }
    } // fin du main
} // fin de la classe