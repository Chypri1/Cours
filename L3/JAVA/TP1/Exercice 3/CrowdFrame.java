import javax.swing.JFrame;
import java.awt.Graphics;
import java.awt.Color;
import java.util.ArrayList;

public class CrowdFrame extends JFrame{

	private CrowdGame game;

	public CrowdFrame(int w, int h, CrowdGame cg){
		super("Simulation de foule");
		this.game = cg;
		this.setBackground(Color.WHITE);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(w,h);
		this.setResizable(false);
		this.setVisible(true);
	}

	public void paint(Graphics gr){
		gr.setColor(Color.WHITE);
		gr.fillRect(0,0,this.getWidth(),this.getHeight());
		Displayable[] t = this.game.getDisplayables();
		for(int i=0;i<t.length;i++) t[i].paint(gr);
	}

}
