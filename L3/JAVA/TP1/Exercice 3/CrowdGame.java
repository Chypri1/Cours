import javax.swing.JFrame;
import java.awt.Graphics;
import java.awt.Color;
import java.util.ArrayList;
import java.util.Random;

public class CrowdGame {

	CrowdFrame frame;
	int w,h; // largeur et hauteur de la simulation

	public CrowdGame(int w, int h, int nbOfMobiles){
		this.w = w;
		this.h = h;
		// ... A COMPLETER
		this.frame = new CrowdFrame(w,h,this);
	}

	Displayable[] getDisplayables(){
		// ... A COMPLETER
	}

	public static java.awt.Color generateColor(){
		Random rand = new Random();
        return new Color(rand.nextInt(0xFFFFFF));
	}

	public void run(){
		while(true){
			try{Thread.sleep(500);}catch(InterruptedException e){}
			// ... A COMPLETER
			this.frame.repaint();
		}
	}

	public static void main(String[] toto){
		CrowdGame cg = new CrowdGame(1000,800,50);
		cg.run();
	}
}
